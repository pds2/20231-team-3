#ifndef ColunaSQL_SQL
#define ColunaSQL_SQL

#include "tipo_dado_sql.hpp"

class ColunaSQL
{
    private:
        std::string _nome_col;
        TipoDadoSQL _tipo_col;
        std::string _unique_col;
    
    public:
        // construtor que recebe o nome da ColunaSQL, o tipo e condição unique
        ColunaSQL(std::string nome_col, TipoDadoSQL tipo_col, std::string unique_col);

        // getter para o nome da ColunaSQL
        std::string get_nome_col() const;

        //getter para o tipo da ColunaSQL
        TipoDadoSQL get_tipo_col() const;

        // getter para a condição unique
        std::string get_unique_col() const;
};

#endif