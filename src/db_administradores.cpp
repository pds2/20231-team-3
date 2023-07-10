#include "../include/definicoes.hpp"
#include "../include/db_administradores.hpp"

DbAdministradores::DbAdministradores() : BbtWrapperSQL(
    bbt_def::sql::schema_administradores::nome_tabela,
    bbt_def::sql::schema_administradores::colunas) {}

void DbAdministradores::_diretriz(sqlite::database_binder& ps_binder, Entidadebase obj)
{
    try
    {
        ps_binder
        << obj.getNome()
        << obj.getEmail()
        << obj.getSenha()
        << obj.getId();    
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
}

Entidadebase DbAdministradores::_diretriz(
    sqlite::row_iterator::value_type linha_binder)
{
    std::unique_ptr<std::string> nome, email, senha;
    std::unique_ptr<unsigned int> id, id_categoria;
    try
    {
        linha_binder >> id
        >> nome >> email >> senha >> id_categoria;
        
        if(*id_categoria == 3)
        {
            return Bibliotecario(*nome, *senha, *email, *id);
        }
        else if(*id_categoria == 4)
        {
            return Administrador(*nome, *senha, *email, *id);
        }
        else throw std::logic_error("id da categoria não corresponde a nenhuma categoria\n");
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    };
    return Entidadebase();
}