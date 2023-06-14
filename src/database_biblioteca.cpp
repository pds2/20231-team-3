#include "database_biblioteca.hpp"

DbtoolsBiblioteca::DbtoolsBiblioteca()
{
    try
    {
        _database = sqlite::database("db_bbt.db");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
}

void DbtoolsBiblioteca::criar_tabela(std::string nome_tabela)
{
    try
    {
        _database <<
        "create table if not exists ? ("
        "_id integer primary key autoincrement not null);";
        _database << nome_tabela;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}