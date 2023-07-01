#ifndef ColunaSQL_SQL
#define ColunaSQL_SQL

#include <string>

class ColunaSQL
{
    private:
        const std::string _nome_col;
        const std::string _tipo_col;
        const std::string _unique_col;
        const std::string _primary_key_col;
        const std::string _default_null_col;
    
    public:
        // construtor que recebe o nome da ColunaSQL, o tipo e condição unique
        ColunaSQL(
            std::string nome_col,
            std::string tipo,
            std::string unique_col = "",
            std::string primary_key = "",
            std::string default_null = "");

        // getter para o nome da ColunaSQL
        std::string get_nome_col() const;

        //getter para o tipo da ColunaSQL
        std::string get_tipo_col() const;

        // getter para a condição unique
        std::string get_unique_col() const;

        // getter para a condição de primary key
        std::string get_primary_key_col() const;

        // getter para condição de coluna com nulo padrão ou não nulo
        std::string get_default_null_col() const;
};

#endif