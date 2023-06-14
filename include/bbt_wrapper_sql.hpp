#ifndef DATABASE_BIBLIOTECA
#define DATABASE_BIBLIOTECA

#include "sqlite_modern_cpp.h"
#include "tipo_dado_sql.hpp"
#include "coluna_sql.hpp"

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
        const std::vector<ColunaSQL*> _colunas;
        
        // referência para o acesso ao banco de dados
        sqlite::database* _db_sqlite_ref;

        // método auxiliar que retorna uma string de diretriz SQLite contendo as colunas
        // saída: (col1,col2,col3,...)
        std::string _ps_colunas();

        // método auxiliar que retorna uma string genérica de diretriz SQLite para operação em linha
        // formato de saída: (?,?,?,...)
        std::string _ps_linha();

        // método auxiliar que verifica a compatibilidade entre tipo de coluna e tipo de dado
        bool _compativel(ColunaSQL& col, TipoDadoSQL tipo);

        // método auxiliar que verifica se os vetores tem o mesmo tamanho
        bool _mesmo_tamanho(std::vector<ColunaSQL*> colunas, std::vector<TipoDadoSQL*> tipos);

        // método auxiliar que insere um dado na coluna
        void _inserir_dado(sqlite::database_binder& ps, TipoDadoSQL* item);
    
    public:
        // construtor da classe
        // recebe uma string com o nome da tabela e um vetor de tipos de coluna
        BbtWrapperSQL(std::string nome_tabela, std::vector<ColunaSQL*> colunas);

        // destrutor da classe
        ~BbtWrapperSQL();

        // método que insere uma linha inteira na tabela
        // recebe um vetor de itens
        void inserir_linha(std::vector<TipoDadoSQL*> itens);

        // método que sobrescreve itens em uma linha de diversas colunas, com base no id
        void sobrescrever_em(std::vector<ColunaSQL*> colunas, std::vector<TipoDadoSQL*> itens, unsigned int id);

        // método que realiza o commit, iniciando uma nova transaction em seguida
        // por padrão, o commit é feito ao invocar o destrutor do objeto
        void commit();

        // método para tornar itens de uma linha em nulos de acordo com as colunas
        // não remove a linha do banco de dados
        void remover_itens_id(std::vector<ColunaSQL*> colunas, unsigned int id);

        // std::string consulta_por_id(unsigned int id, Colu);
        // std::string consulta_por_item(std::string item);
        // void deletar_linha_id(unsigned int id);
};

#endif