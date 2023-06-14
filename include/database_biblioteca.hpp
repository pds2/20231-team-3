#ifndef DATABASE_BIBLIOTECA
#define DATABASE_BIBLIOTECA

#include "sqlite_modern_cpp.h"

class DbtoolsBiblioteca
{
    private:
        static sqlite::database _database;
        const std::string _nome_tabela;
    
    public:
        DbtoolsBiblioteca();
        void criar_tabela(std::string nome_tabela);
        void inserir_coluna(std::string nome_coluna);
        void inserir_itens(std::vector<std::string> itens);
        void retirar_itens(std::vector<std::string> itens);
        std::string consulta_por_index(unsigned int index);
        std::string consulta_por_item(std::string item);
};

#endif