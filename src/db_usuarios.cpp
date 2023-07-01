#include "definicoes.hpp"
#include "db_usuarios.hpp"

DbUsuarios::DbUsuarios() : BbtWrapperSQL(
    bbt_def::sql::schema_usuarios::nome_tabela,
    bbt_def::sql::schema_usuarios::colunas) {}

void DbUsuarios::_diretriz(sqlite::database_binder& ps_binder, Entidadebase obj)
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

std::pair<Entidadebase, AdtDataSQL> DbUsuarios::_diretriz(
    sqlite::row_iterator::value_type linha_binder)
{
    std::unique_ptr<std::string> nome, email, senha;
    std::unique_ptr<unsigned int> id_categoria;
    std::unique_ptr<unsigned int> num_livros;
    AdtDataSQL adt_data = AdtDataSQL();
    try
    {
        linha_binder
        >> nome >> email >> senha >> id_categoria >> num_livros;

        if(num_livros != nullptr) adt_data.long_data.push_back(*num_livros);
        else adt_data.long_data.push_back(0);

        if(*id_categoria == 1)
        {
            return {Usuario(*nome, *senha, *email), adt_data};
        }
        else if (*id_categoria == 2)
        {
            return {Usuariovip(*nome, *senha, *email), adt_data};
        }
        else throw std::logic_error("id da categoria não corresponde a nenhuma categoria\n");
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
    return {};
}