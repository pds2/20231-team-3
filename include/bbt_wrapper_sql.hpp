#ifndef DATABASE_BIBLIOTECA
#define DATABASE_BIBLIOTECA

#include "sqlite_modern_cpp.h"
#include "sqlite_modern_cpp/type_wrapper.h"
#include "tipo_dado_sql.hpp"
#include "coluna_sql.hpp"

// classe de identificação de exceção no banco de dados
class sql_wrapper_e{};

// classe wrapper do wrapper do SQLite
class BbtWrapperSQL
{
    private:
        // nome do arquivo do banco de dados
        // o banco de dados é único no sistema
        const static std::string _NOME_DB;

        // nome da tabela padrão
        const std::string _nome_tabela;

        // vetor de colunas da tabela, contendo [nome, tipo de dados, unique] da coluna
        // unique é preenchido com "unique" caso a coluna não admita valores repetidos
        // caso contrário, a coluna admite valores repetidos
        const std::vector<ColunaSQL> _colunas;
        
        // referência para o acesso ao banco de dados
        sqlite::database* _db_sqlite_ref;

        // buffer auxiliar para inserir linha
        std::vector<TipoDadoSQL> _inserir_buffer;

        // método auxiliar para resetar o buffer _inserir_buffer
        void _reset_inserir_buffer();

        // método auxiliar que retorna uma string de diretriz SQLite contendo as colunas
        // saída: (col1,col2,col3,...)
        std::string _ps_colunas();

        // método auxiliar que retorna uma string genérica de diretriz SQLite para operação em linha
        // formato de saída: (?,?,?,...)
        std::string _ps_linha();

        // método auxiliar que verifica a compatibilidade entre tipo de coluna e tipo de dado
        bool _compativel(ColunaSQL&& col, TipoDadoSQL&& tipo);

        // método auxiliar que verifica se os vetores tem o mesmo tamanho
        bool _mesmo_tamanho(const std::vector<ColunaSQL>&& colunas, std::vector<TipoDadoSQL>&& tipos);

        // método auxiliar que insere um dado na coluna
        void _inserir_dado(sqlite::database_binder& ps, TipoDadoSQL&& item);

        // método auxiliar que retorna vetor com os dados de uma linha
        template<class T>
        void _armazena_linha(T&& ref, std::vector<TipoDadoSQL>& data_buffer);
    
    protected:
        // método que insere uma linha inteira na tabela
        // recebe um vetor de itens
        void inserir_linha(std::vector<TipoDadoSQL>&& itens);
    
    public:
        // construtor da classe
        // recebe uma string com o nome da tabela e um vetor de tipos de coluna
        BbtWrapperSQL(std::string nome_tabela, std::vector<ColunaSQL> colunas);

        // destrutor da classe
        ~BbtWrapperSQL();

        // método que sobrescreve itens em uma linha de diversas colunas, com base no id
        void sobrescrever_em_id(std::vector<ColunaSQL>&& colunas,
                             std::vector<TipoDadoSQL>&& itens,
                             unsigned int id);

        // método que realiza o commit, iniciando uma nova transaction em seguida
        // por padrão, o commit é feito ao invocar o destrutor do objeto
        void commit();

        // método para tornar itens de uma linha em nulos de acordo com as colunas
        // não remove a linha da tabela
        void remover_itens_id(std::vector<ColunaSQL> colunas, unsigned int id);

        // método que deleta linha da tabela
        void deletar_linhas_id(std::vector<unsigned int> ids);

        // método que retorna um vetor de vetores com as linhas
        // de acordo com a recorrência do valor fornecido e da coluna fornecida
        std::vector<std::vector<TipoDadoSQL>> consulta(TipoDadoSQL&& item, ColunaSQL&& coluna);
        
        // método que retorna um vetor com os dados da linha
        std::vector<TipoDadoSQL> consulta_por_id(unsigned int id);

        // método que insere uma linha sem precisar declarar um objeto TipoDadoSQL
        // passo base
        template <class T>
        void inserir_linha(T&& item)
        {
            _inserir_buffer.push_back(TipoDadoSQL(item));
            inserir_linha(std::move(_inserir_buffer));
            _reset_inserir_buffer();
        }

        // método que insere uma linha sem precisar declarar um objeto TipoDadoSQL
        // passo recursivo
        template <class T, class ... Ts>
        void inserir_linha(T&& item, Ts&& ... itens)
        {
            _inserir_buffer.push_back(TipoDadoSQL(item));
            inserir_linha(itens ...);
        }
};

#endif