#include <iostream>

#include "tipo_dado_sql.hpp"

TipoDadoSQL::TipoDadoSQL() : _tipo_sql("null") {}

TipoDadoSQL::TipoDadoSQL(int integer) : _dado_int(integer), _tipo_sql("integer") {}

TipoDadoSQL::TipoDadoSQL(double real) : _dado_double(real), _tipo_sql("real") {}

TipoDadoSQL::TipoDadoSQL(std::string text) : _dado_string(text), _tipo_sql("text") {}

std::string TipoDadoSQL::get_tipo_sql()
{
    return _tipo_sql;
}

int TipoDadoSQL::get_int() const
{
    if(_tipo_sql != "integer") throw metodo_incompativel_e();
    return _dado_int;
}

double TipoDadoSQL::get_double() const
{
    if(_tipo_sql != "real") throw metodo_incompativel_e();
    return _dado_double;
}

std::string TipoDadoSQL::get_string() const
{
    if(_tipo_sql != "text") throw metodo_incompativel_e();
    return _dado_string;
}

void TipoDadoSQL::imprime_valor()
{
    if(_tipo_sql == "integer") std::cout << "[" << _dado_int << "]";
    else if(_tipo_sql == "real") std::cout << "[" << _dado_double << "]";
    else if(_tipo_sql == "text") std::cout << "[" << _dado_string << "]";
    else if(_tipo_sql == "null") std::cout << "[null]";
}