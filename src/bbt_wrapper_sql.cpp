#include "bbt_wrapper_sql.hpp"

// definição do nome do banco de dados
const std::string BbtWrapperSQL::_NOME_DB = "data/db_bbt.db";

// definição da referência global do banco de dados
//sqlite::database* BbtWrapperSQL::_db_sqlite_ref = new sqlite::database(_NOME_DB);

// definição do construtor
BbtWrapperSQL::BbtWrapperSQL(
    std::string nome_tabela,
    std::vector<ColunaSQL*> colunas) :
    _nome_tabela(nome_tabela),
    _colunas(colunas)
{
    _db_sqlite_ref = new sqlite::database(_NOME_DB);
    *_db_sqlite_ref << "begin;";
    try
    {
        // registra o nome da coluna, o tipo, default null e condição de unique
        std::string sql_exec_buffer = "";
        for(auto col : colunas)
        {
            std::string unique = "";
            if(col->get_unique_col() == "unique") unique = " unique";

            // adiciona ao buffer de comando do SQLite com nome e tipo das colunas
            sql_exec_buffer +=
                col->get_nome_col() + " " +
                col->get_tipo_col().get_tipo_sql() + " default null" +
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
    }
    
}

// definição do destrutor
BbtWrapperSQL::~BbtWrapperSQL()
{
    *_db_sqlite_ref << "commit;";
    delete _db_sqlite_ref;
}

// definição do método auxiliar de string contendo as colunas
std::string BbtWrapperSQL::_ps_colunas()
{
    std::string ps_buffer = "(";
    for(auto col : _colunas)
    {
        ps_buffer += col->get_nome_col() + ",";
    }
    ps_buffer.pop_back();
    return ps_buffer + ")";
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

bool BbtWrapperSQL::_compativel(ColunaSQL& col, TipoDadoSQL tipo)
{
    if(tipo.get_tipo_sql() == "null") return true;
    
    else if(col.get_tipo_col().get_tipo_sql() != tipo.get_tipo_sql()) return false;

    else return true;
}

bool BbtWrapperSQL::_mesmo_tamanho(std::vector<ColunaSQL*> colunas, std::vector<TipoDadoSQL*> tipos)
{
    if(colunas.size() != tipos.size()) return false;
    else return true;
}

void BbtWrapperSQL::_inserir_dado(sqlite::database_binder& ps, TipoDadoSQL* item)
{
    if(item->get_tipo_sql() == "integer")
    {
        ps << item->get_int();
    }
    else if(item->get_tipo_sql() == "real")
    {
        ps << item->get_double();
    }
    else if(item->get_tipo_sql() == "text")
    {
        ps << item->get_string();
    }
    else if(item->get_tipo_sql() == "null")
    {
        ps << nullptr;
    }
}

void BbtWrapperSQL::inserir_linha(std::vector<TipoDadoSQL*> itens)
{
    //verifica se o tamanho da entrada é correto para inserir em toda a linha da tabela
    if(!_mesmo_tamanho(_colunas, itens))
    {
        throw std::invalid_argument("Número de itens deve ser igual ao número de colunas");
    }

    try
    {
        auto ps_buffer = *_db_sqlite_ref <<
        "insert into " + _nome_tabela + _ps_colunas() + " values " + _ps_linha() + ";";

        // insere de acordo com o tipo
        for(auto item : itens)
        {
            _inserir_dado(ps_buffer, item);
        }
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
    }
}

void BbtWrapperSQL::sobrescrever_em(
    std::vector<ColunaSQL*> colunas,
    std::vector<TipoDadoSQL*> itens,
    unsigned int id)
{
    if(!_mesmo_tamanho(colunas, itens))
    {
        throw std::invalid_argument("Número de itens deve ser igual ao número de colunas");
    }

    try
    {
        std::string str_buffer = "update " + _nome_tabela + " set ";

        for(int i = 0; i < itens.size(); i++)
        {
            if(!_compativel(*colunas.at(i), *itens.at(i)))
            {
                throw std::invalid_argument("Tipo não compatível com coluna");
            }

            str_buffer += colunas.at(i)->get_nome_col() + " = ?,";
        }

        str_buffer.pop_back();
        auto ps_buffer = *_db_sqlite_ref << str_buffer + " where _id = ?;";
        
        for(auto item : itens)
        {
            _inserir_dado(ps_buffer, item);
        }

        ps_buffer << id;
    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
        << e.get_sql() << std::endl;
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
    }
    
}

void BbtWrapperSQL::remover_itens_id(std::vector<ColunaSQL*> colunas, unsigned int id)
{
    std::vector<TipoDadoSQL*> nulos;
    for(auto col : colunas) nulos.push_back(new TipoDadoSQL());

    sobrescrever_em(colunas, nulos, id);
    
    for(auto i : nulos) delete i;
}