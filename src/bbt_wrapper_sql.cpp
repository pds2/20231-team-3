#include "bbt_wrapper_sql.hpp"

// definição do nome do banco de dados
const std::string BbtWrapperSQL::_NOME_DB = "data/db_bbt.db";

// definição da referência global do banco de dados
//sqlite::database* BbtWrapperSQL::_db_sqlite_ref = new sqlite::database(_NOME_DB);

// definição do construtor
BbtWrapperSQL::BbtWrapperSQL(
    std::string nome_tabela,
    std::vector<ColunaSQL> colunas) :
    _nome_tabela(nome_tabela),
    _colunas(colunas)
{
    _inserir_buffer = {};
    _db_sqlite_ref = new sqlite::database(_NOME_DB);
    *_db_sqlite_ref << "begin;";
    try
    {
        // registra o nome da coluna, o tipo, default null e condição de unique
        std::string sql_exec_buffer = "";
        for(auto col : colunas)
        {
            std::string unique = "";
            if(col.get_unique_col() == "unique") unique = " unique";

            // adiciona ao buffer de comando do SQLite com nome e tipo das colunas
            sql_exec_buffer +=
                col.get_nome_col() + " " +
                col.get_tipo_col().get_tipo_sql() + " default null" +
                unique + ",";
        }

        // remove vírgula excedente
        sql_exec_buffer.pop_back();

        // cria tabela, se não existir
        *_db_sqlite_ref <<
            "create table if not exists " + nome_tabela +
            "(_id integer primary key autoincrement not null," + sql_exec_buffer + ");";
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }
    
}

// definição do destrutor
BbtWrapperSQL::~BbtWrapperSQL()
{
    *_db_sqlite_ref << "commit;";
    delete _db_sqlite_ref;
}

void BbtWrapperSQL::_reset_inserir_buffer()
{
    _inserir_buffer = {};
}

// definição do método auxiliar de string contendo as colunas
std::string BbtWrapperSQL::_ps_colunas()
{
    std::string ps_buffer = "";
    for(auto col : _colunas)
    {
        ps_buffer += col.get_nome_col() + ",";
    }
    ps_buffer.pop_back();
    return ps_buffer;
}

// definição do método auxiliar de string genérica para operação em linha
std::string BbtWrapperSQL::_ps_linha()
{
    std::string ps_buffer = "(";
    for(int i = 0; i < _colunas.size(); i++)
    {
        ps_buffer += "?,";
    }
    ps_buffer.pop_back();
    return ps_buffer + ")";
}

bool BbtWrapperSQL::_compativel(ColunaSQL&& col, TipoDadoSQL&& tipo)
{
    if(tipo.get_tipo_sql() == "null") return true;
    
    else if(col.get_tipo_col().get_tipo_sql() != tipo.get_tipo_sql()) return false;

    else return true;
}

bool BbtWrapperSQL::_mesmo_tamanho(const std::vector<ColunaSQL>&& colunas, std::vector<TipoDadoSQL>&& tipos)
{
    if(colunas.size() != tipos.size()) return false;
    else return true;
}

void BbtWrapperSQL::_inserir_dado(sqlite::database_binder& ps, TipoDadoSQL&& item)
{
    try
    {
        if(item.get_tipo_sql() == "integer")
        {
            ps << item.get_int();
        }
        else if(item.get_tipo_sql() == "real")
        {
            ps << item.get_double();
        }
        else if(item.get_tipo_sql() == "text")
        {
            ps << item.get_string();
        }
        else if(item.get_tipo_sql() == "null")
        {
            ps << nullptr;
        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr << e.get_code() << ": " << e.what() << " during:\n "
        << e.get_sql() << "\n " << std::endl;
        throw sql_wrapper_e();
    }
}

template<class T>
void BbtWrapperSQL::_armazena_linha(T&& ref, std::vector<TipoDadoSQL>& data_buffer)
{
    std::unique_ptr<int> int_buffer;
    std::unique_ptr<double> double_buffer;
    std::unique_ptr<std::string> string_buffer;

    try
    {
        // insere no vetor de retorno os dados da linha de cada coluna
        for(auto col : _colunas)
        {
            if(col.get_tipo_col().get_tipo_sql() == "integer")
            {
                ref >> int_buffer;
                if(int_buffer == nullptr) data_buffer.push_back(TipoDadoSQL());
                else data_buffer.push_back(TipoDadoSQL(*int_buffer));
            }
            else if(col.get_tipo_col().get_tipo_sql() == "real")
            {
                ref >> double_buffer;
                if(double_buffer == nullptr) data_buffer.push_back(TipoDadoSQL());
                else data_buffer.push_back(TipoDadoSQL(*double_buffer));
            }
            else if(col.get_tipo_col().get_tipo_sql() == "text")
            {
                ref >> string_buffer;
                if(string_buffer == nullptr) data_buffer.push_back(TipoDadoSQL());
                else data_buffer.push_back(TipoDadoSQL(*string_buffer));
            }
        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr << e.get_code() << ": " << e.what() << " during:\n "
        << e.get_sql() << "\n " << std::endl;
        throw sql_wrapper_e();
    }
    
    
}

void BbtWrapperSQL::inserir_linha(std::vector<TipoDadoSQL>&& itens)
{
    //verifica se o tamanho da entrada é correto para inserir em toda a linha da tabela
    if(!_mesmo_tamanho(std::move(_colunas), std::move(itens)))
    {
        throw std::invalid_argument("Número de itens deve ser igual ao número de colunas");
    }

    try
    {
        auto ps_buffer = *_db_sqlite_ref <<
        "insert into " + _nome_tabela + "(" + _ps_colunas() + ") values " + _ps_linha() + ";";

        // insere de acordo com o tipo
        for(auto item : itens)
        {
            _inserir_dado(ps_buffer, std::move(item));
        }
    }
    catch (const sqlite::errors::constraint &e)
    {
        std::cerr << e.get_code() << ": " << e.what() << " during:\n"
        << e.get_sql() << "\nPossível motivo do erro: inserção de item repetido em coluna unique"
        << std::endl;
        throw sql_wrapper_e();
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr << e.get_code() << ": " << e.what() << " during:\n "
        << e.get_sql() << "\n " << std::endl;
        throw sql_wrapper_e();
    }
}

void BbtWrapperSQL::sobrescrever_em_id(
    std::vector<ColunaSQL>&& colunas,
    std::vector<TipoDadoSQL>&& itens,
    unsigned int id)
{
    if(!_mesmo_tamanho(std::move(colunas), std::move(itens)))
    {
        throw std::invalid_argument("Número de itens deve ser igual ao número de colunas");
    }

    try
    {
        std::string str_buffer = "update " + _nome_tabela + " set ";

        // alimenta o str_buffer: <nome da coluna> = ?
        for(int i = 0; i < itens.size(); i++)
        {
            if(!_compativel(std::move(colunas.at(i)), std::move(itens.at(i))))
            {
                throw std::invalid_argument("Tipo não compatível com coluna");
            }

            str_buffer += colunas.at(i).get_nome_col() + " = ?,";
        }

        // remove vírgula excedente
        str_buffer.pop_back();

        auto ps_buffer = *_db_sqlite_ref << str_buffer + " where _id = ?;";
        
        // insere os dados no buffer
        for(auto item : itens)
        {
            _inserir_dado(ps_buffer, std::move(item));
        }

        ps_buffer << id;
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }
}

void BbtWrapperSQL::commit()
{
    try
    {
        *_db_sqlite_ref << "commit;";
        *_db_sqlite_ref << "begin;";
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }
    
}

void BbtWrapperSQL::remover_itens_id(std::vector<ColunaSQL> colunas, unsigned int id)
{
    // cria um vetor de nulos
    std::vector<TipoDadoSQL> nulos;
    for(auto col : colunas) nulos.push_back(TipoDadoSQL());

    // sobrescreve os dados com o vetor de nulos
    sobrescrever_em_id(std::move(colunas), std::move(nulos), id);
}

void BbtWrapperSQL::deletar_linhas_id(std::vector<unsigned int> ids)
{
    try
    {
        for(auto id : ids)
        {
            *_db_sqlite_ref << "delete from " + _nome_tabela + " where _id = ?;" << id;
        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }
}

std::vector<std::vector<TipoDadoSQL>> BbtWrapperSQL::consulta(TipoDadoSQL&& item, ColunaSQL&& coluna)
{
    if(!_compativel(std::move(coluna), std::move(item))){
        throw std::invalid_argument("Item consultado deve ser do mesmo tipo da coluna");
    }

    // inicialização do return
    std::vector<std::vector<TipoDadoSQL>> data_buffer;

    try
    {
        // loop que itera sobre as linhas retornadas da consulta
        if(item.get_tipo_sql() == "null")
        {
            for(auto&& linha : *_db_sqlite_ref << "select " + _ps_colunas() +
                                                " from " + _nome_tabela +
                                                " where " + coluna.get_nome_col() +
                                                " is null;")
            {
                data_buffer.push_back({});
                _armazena_linha(linha,data_buffer.back());
            }
        }
        else if(coluna.get_tipo_col().get_tipo_sql() == "integer")
        {
            for(auto&& linha : *_db_sqlite_ref << "select " + _ps_colunas() +
                                                " from " + _nome_tabela +
                                                " where " + coluna.get_nome_col() +
                                                " = ?;" << item.get_int())
            {
                data_buffer.push_back({});
                _armazena_linha(linha,data_buffer.back());
            }
        }
        else if(coluna.get_tipo_col().get_tipo_sql() == "real")
        {
            for(auto&& linha : *_db_sqlite_ref << "select " + _ps_colunas() +
                                                " from " + _nome_tabela +
                                                " where " + coluna.get_nome_col() +
                                                " = ?;" << item.get_double())
            {
                data_buffer.push_back({});
                _armazena_linha(linha,data_buffer.back());
            }
        }
        else if(coluna.get_tipo_col().get_tipo_sql() == "text")
        {
            for(auto&& linha : *_db_sqlite_ref << "select " + _ps_colunas() +
                                                " from " + _nome_tabela +
                                                " where " + coluna.get_nome_col() +
                                                " = ?;" << item.get_string())
            {
                data_buffer.push_back({});
                _armazena_linha(linha,data_buffer.back());
            }
        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }

    return data_buffer;
}

std::vector<TipoDadoSQL> BbtWrapperSQL::consulta_por_id(unsigned int id)
{
    // inicialização do return
    std::vector<TipoDadoSQL> data_buffer;

    try
    {
        for(auto&& ps_binder : *_db_sqlite_ref << "select " + _ps_colunas() + " from " + _nome_tabela + 
                        " where _id = ?;" << id){

        _armazena_linha(ps_binder, data_buffer);
                        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
        throw sql_wrapper_e();
    }
    
    return data_buffer;
}