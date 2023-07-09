#include "definicoes.hpp"
#include "db_usuarios.hpp"

DbUsuarios::DbUsuarios() : BbtWrapperSQL(
    bbt_def::sql::schema_usuarios::nome_tabela,
    bbt_def::sql::schema_usuarios::colunas) {}

void DbUsuarios::_diretriz(sqlite::database_binder& ps_binder, Usuario obj)
{
    try
    {
        ps_binder
        << obj.getNome()
        << obj.getEmail()
        << obj.getSenha()
        << obj.getId()
        << obj.getqntdlivros();
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
}

Usuario DbUsuarios::_diretriz(
    sqlite::row_iterator::value_type linha_binder)
{
    std::unique_ptr<std::string> nome, email, senha;
    std::unique_ptr<unsigned int> id, id_categoria, n_livros;
    
    try
    {
        linha_binder >> id
        >> nome >> email >> senha >> id_categoria >> n_livros;

        if(*id_categoria == 1)
        {
            return Usuario(*nome, *senha, *email, *id, *n_livros);
        }
        else throw std::logic_error("id da categoria não corresponde a nenhuma categoria\n");
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
    return {};
}