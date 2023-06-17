#include "db_usuarios.hpp"

namespace sql_schema
{
    const std::string nome_tabela = "usuarios";
    const ColunaSQL&& nome = ColunaSQL("nome", TipoDadoSQL(""));
    const ColunaSQL&& registro = ColunaSQL("registro", TipoDadoSQL(1), "unique");
    const ColunaSQL&& is_vip = ColunaSQL("is_vip", TipoDadoSQL(1));
    const ColunaSQL&& login = ColunaSQL("login", TipoDadoSQL(""), "unique");
    const ColunaSQL&& senha = ColunaSQL("senha", TipoDadoSQL(""));
    const ColunaSQL&& livros_posse = ColunaSQL("livros_posse", TipoDadoSQL(""));
    const std::vector<ColunaSQL> colunas = {nome,registro,is_vip,login,senha,livros_posse};
}

DbUsuarios::DbUsuarios() : BbtWrapperSQL(sql_schema::nome_tabela,sql_schema::colunas) {}