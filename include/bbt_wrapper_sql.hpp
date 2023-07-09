#ifndef DATABASE_BIBLIOTECA
#define DATABASE_BIBLIOTECA

#include "sqlite_modern_cpp.h"
#include "sqlite_modern_cpp/type_wrapper.h"
#include "definicoes.hpp"
#include "coluna_sql.hpp"
#include "usuario.hpp"
#include "adm.hpp"
#include "bibliotecario.hpp"
#include "livro.hpp"

// exceção para acesso negado
class acesso_negado_e : public std::exception
{
    public:
        acesso_negado_e(std::string msg) : std::exception()
        {
            std::cerr << msg << std::endl;
        }
};

// classe wrapper do wrapper do SQLite
template <typename TAD>
class BbtWrapperSQL
{
    private:
        // nome do arquivo do banco de dados
        // o banco de dados é único no sistema
        const std::string _NOME_DB = bbt_def::sql::NOME_DB;

        // nome da tabela padrão
        const std::string _nome_tabela;

        // vetor de colunas da tabela, contendo [nome, tipo de dados, unique] da coluna
        // unique é preenchido com "unique" caso a coluna não admita valores repetidos
        // caso contrário, a coluna admite valores repetidos
        const std::vector<ColunaSQL> _colunas;

        // referência para o acesso ao banco de dados
        sqlite::database _db_sqlite_ref;

    protected:
        // método que lida com exceções genéricas
        void _sql_excecao(std::exception_ptr ex)
        {
            try
            {
                std::rethrow_exception(ex);
            }
            catch(const sqlite::errors::busy& e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during:\n"
                << e.get_sql()
                << "\nÉ necessário fazer o commit ao operar funções de diferentes tabelas de forma cruzada"
                << std::endl;
                std::rethrow_exception(std::current_exception());
            }
            catch (const sqlite::errors::constraint_unique &e)
            {
                std::cerr << e.get_code() << ": " << e.what() << " during:\n"
                << e.get_sql() << "\nInserção de item repetido em coluna unique"
                << std::endl;
                std::rethrow_exception(std::current_exception());
            }
            catch (const sqlite::sqlite_exception& e) {
                std::cerr << e.get_code() << ": " << e.what() << " during:\n "
                << e.get_sql() << "\n "
                << "Erro desconhecido específico SQLite" << std::endl;
                std::rethrow_exception(std::current_exception());
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n'
                << "Erro desconhecido" << std::endl;
                std::rethrow_exception(std::current_exception());
            }
        }

        // método auxiliar que retorna uma string de diretriz SQLite contendo as colunas
        // saída: (col1,col2,col3,...)
        std::string _ps_colunas()
        {
            std::ostringstream ostr_buffer;

            for(auto col : _colunas)
            {
                if(col.get_nome_col() != bbt_def::sql::id)
                {
                    ostr_buffer << col.get_nome_col() << ",";                
                }
            }
            auto ps_buffer = ostr_buffer.str();
            ps_buffer.pop_back();
            return ps_buffer;
        }

        // método auxiliar que retorna uma string genérica de diretriz SQLite para operação em linha
        // formato de saída: (?,?,?,...)
        std::string _ps_linha()
        {
            std::ostringstream ostr_buffer
            ostr_buffer << "(";

            for(int i = 0; i < _colunas.size()-1; i++)
            {
                ostr_buffer << "?,";
            }
            auto ps_buffer = ostr_buffer.str();
            ps_buffer.pop_back();
            return ps_buffer + ")";
        }

        // método auxiliar para armazenar diretrizes específicas de cada tabela
        // sobrecarga para o tipo database_binder
        virtual void _diretriz(sqlite::database_binder& ps_binder, TAD obj) = 0;

        // método auxiliar para armazenar diretrizes específicas de cada tabela
        // sobrecarga para o tipo row_iterator (retornos múltiplos)
        virtual TAD _diretriz(
            sqlite::row_iterator::value_type linha_binder) = 0;

        // getter ponteiro da coluna
        const ColunaSQL* _get_coluna(std::string coluna)
        {
            for(auto col = _colunas.begin(); col != _colunas.end(); col++)
            {
                if(col->get_nome_col() == coluna) return &(*col);
            }

            throw std::invalid_argument("A coluna " + coluna + " não existe\n");
        }
    
    public:
        // construtor da classe
        // recebe uma string com o nome da tabela e um vetor de tipos de coluna
        BbtWrapperSQL(
            std::string nome_tabela,
            std::vector<ColunaSQL> colunas,
            std::string clausula_adicional = "") :

            _nome_tabela(nome_tabela),
            _colunas(colunas),
            _db_sqlite_ref(sqlite::database(bbt_def::sql::NOME_DB))
        {
            try
            {
                _db_sqlite_ref << "pragma foreign_keys = on;";
                _db_sqlite_ref << "begin;";

                // registra o nome da coluna, o tipo, default null e condição de unique
                std::ostringstream ostr_buffer;
                for(auto col : colunas)
                {
                    std::string unique = "";
                    std::string primary_key = "";
                    std::string default_null = " not null ";

                    if(col.get_unique_col() == "unique") unique = " unique ";
                    if(col.get_primary_key_col() == "primary key") primary_key = " primary key autoincrement ";
                    if(col.get_default_null_col() == "default null") default_null = " default null ";

                    // adiciona ao buffer de comando do SQLite com nome e tipo das colunas
                    ostr_buffer
                        << col.get_nome_col() << " "
                        << col.get_tipo_col() << primary_key
                        << default_null << unique << ",";
                }

                // remove vírgula excedente
                auto sql_exec_buffer = ostr_buffer.str("");
                sql_exec_buffer.pop_back();

                ostr_buffer
                    << "create table if not exists " << nome_tabela
                    << "(" << sql_exec_buffer << clausula_adicional << ");";

                // cria tabela, se não existir
                _db_sqlite_ref << ostr_buffer.str();
            
                _db_sqlite_ref << "commit;";
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }    
        }

        // método que sobrescreve itens fornecidos do TAD no banco de dados
        void sobrescrever_em_id(TAD obj, unsigned int id)
        {
            try
            {
                std::ostringstream ostr_buffer = "update " << _nome_tabela << " set ";

                // alimenta o str_buffer: "nome da coluna" = ?
                for(auto col : _colunas)
                {
                    if(col.get_nome_col() == bbt_def::sql::id) continue;
                    str_buffer << col.get_nome_col() + " = ?,";
                }

                // remove vírgula excedente
                auto str_buffer = ostr_buffer.str();
                str_buffer.pop_back();


                auto ps_binder = _db_sqlite_ref
                << str_buffer + " where " + bbt_def::sql::id + " = ?;";
                
                // insere os dados no binder
                _diretriz(ps_binder, obj);

                ps_binder << id;
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
        }

        // método sobrecarga que sobrescreve item específico em coluna
        template <typename tipo>
        void sobrescrever_em_id(tipo item, std::string coluna, unsigned int id)
        {
            try
            {
                if(coluna == bbt_def::sql::id)
                {
                    throw std::invalid_argument("É proibido alterar a coluna " + bbt_def::sql::id);
                }

                std::ostringstream ostr_buffer;
                ostr_buffer
                    << "update " << _nome_tabela << " set "
                    << _get_coluna(coluna)->get_nome_col() << " = ? where "
                    << bbt_def::sql::id << " = ?;";

                _db_sqlite_ref << ostr_buffer.str() << item << id;
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }  
        }

        // método que insere uma linha com os dados do TAD
        void inserir_linha(TAD obj)
        {
            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer
                    << "insert into " << _nome_tabela << "("
                    << _ps_colunas() << ") values " << _ps_linha() << ";";

                auto&& ps_binder = _db_sqlite_ref << ostr_buffer.str();

                // insere de acordo com o tipo
                _diretriz(ps_binder, obj);
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
        }

        // método para tornar itens de uma linha em nulos de acordo com as colunas
        // não remove a linha da tabela
        void set_nulo_id(std::string coluna, unsigned int id)
        {
            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer
                    << "update " << _nome_tabela
                    << " set " << _get_coluna(coluna)->get_nome_col()
                    << " = null where " << bbt_def::sql::id << " = ?;";

                _db_sqlite_ref << ostr_buffer.str() << id;
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
        }

        // método que deleta linha da tabela fornecendo id
        void deletar_linha_id(unsigned int id)
        {
            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer
                    << "delete from " << _nome_tabela << " where "
                    << bbt_def::sql::id << " = ?;";

                _db_sqlite_ref << ostr_buffer.str() << id;
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
        }

        // método que retorna um vetor de pares
        // <ids, TAD>
        // ordena a coluna de acordo com o boolean fornecido
        // ascendente: true, descendente: false
        template <typename tipo>
        std::vector<TAD>
        consulta(tipo item, std::string coluna, bool ascendente = true)
        {
            auto ordem = [&]()
            {
                if(ascendente)
                {
                    return "order by " + _get_coluna(coluna)->get_nome_col() + " asc";
                }
                else
                {
                    return "order by " + _get_coluna(coluna)->get_nome_col() + " desc";
                }
            };

            // inicialização do return
            std::vector<TAD>&& vec_buffer = {};

            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer
                    << "select " << bbt_def::sql::id << ","
                    << _ps_colunas() << " from " << _nome_tabela
                    << " where " << _get_coluna(coluna)->get_nome_col()
                    << " = ? " << ordem() << ";";

                for(auto&& linha : _db_sqlite_ref << ostr_buffer.str() << item)
                {
                    TAD TAD_buffer = _diretriz(linha);
                    vec_buffer.push_back(TAD_buffer);
                }
                return vec_buffer;
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
            return vec_buffer;
        }
        
        // método para deletar todas as linhas
        // apenas para teste
        void del_linhas()
        {
            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer << "delete from " << _nome_tabela << ";";

                _db_sqlite_ref << ostr_buffer.str();
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }
        }

        // método que deleta tudo, menos o banco de dados
        // apenas para teste
        void reset()
        {
            try
            {
                std::ostringstream ostr_buffer;
                ostr_buffer << "drop table if exists " << _nome_tabela << ";";

                _db_sqlite_ref << ostr_buffer.str();
            }
            catch(const std::exception& e)
            {
                _sql_excecao(std::current_exception());
            }   
        }
        
        // método para iniciar transaction
        void transaction()
        {
            try
            {
                _db_sqlite_ref << "begin;";
            }
            catch (const std::exception& e) {
                _sql_excecao(std::current_exception());
            }
        }

        // método que realiza o commit, iniciando uma nova transaction em seguida
        // por padrão, o commit é feito ao invocar o destrutor do objeto
        void commit()
        {
            try
            {
                _db_sqlite_ref << "commit;";
            }
            catch (const std::exception& e) {
                _sql_excecao(std::current_exception());
            }
        }
};

#endif