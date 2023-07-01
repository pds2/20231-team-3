#include "coluna_sql.hpp"

ColunaSQL::ColunaSQL(
    std::string nome_col,
    std::string tipo,
    std::string unique_col,
    std::string primary_key,
    std::string default_null) :
    _nome_col(nome_col),
    _tipo_col(tipo),
    _unique_col(unique_col),
    _primary_key_col(primary_key),
    _default_null_col(default_null) {}

std::string ColunaSQL::get_nome_col() const
{
    return _nome_col;
}

std::string ColunaSQL::get_tipo_col() const
{
    return _tipo_col;
}

std::string ColunaSQL::get_unique_col() const
{
    return _unique_col;
}

std::string ColunaSQL::get_primary_key_col() const
{
    return _primary_key_col;
}

std::string ColunaSQL::get_default_null_col() const
{
    return _default_null_col;
}