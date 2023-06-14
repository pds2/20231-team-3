#include "coluna_sql.hpp"

ColunaSQL::ColunaSQL(std::string nome_col, TipoDadoSQL tipo_col, std::string unique_col) :
    _nome_col(nome_col), _tipo_col(tipo_col), _unique_col(unique_col) {}

std::string ColunaSQL::get_nome_col() const
{
    return _nome_col;
}

TipoDadoSQL ColunaSQL::get_tipo_col() const
{
    return _tipo_col;
}

std::string ColunaSQL::get_unique_col() const
{
    return _unique_col;
}