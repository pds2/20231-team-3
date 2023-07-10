#include "../include/entidadebase.hpp"
#include "../include/livro.hpp"
#include "../include/db_acervo.hpp"

Entidadebase::Entidadebase() : _nome(""), _senha(""), _email(""), _id(0), _id_sql(0) {}

Entidadebase::Entidadebase(std::string nome,
                           std::string senha,
                           std::string email,
                           unsigned int id,
                           unsigned int id_db)
    : _nome(nome), _senha(senha), _email(email), _id(id), _id_sql(id_db) {}

std::string Entidadebase::getNome()
{
    return _nome;
}

std::string Entidadebase::getEmail()
{
    return _email;
}

unsigned int Entidadebase::getId()
{
    return _id;
}

unsigned int Entidadebase::getIdDb()
{
    return _id_sql;
}

std::string Entidadebase::getSenha()
{
    return _senha;
}

void Entidadebase::setNome(const std::string &nome)
{
    _nome = nome;
}

void Entidadebase::setEmail(const std::string &email)
{
    _email = email;
}

void Entidadebase::setId(unsigned int id)
{
    _id = id;
}

void Entidadebase::setSenha(const std::string &senha)
{
    _senha = senha;
}

std::vector<Livro> Entidadebase::consultaLivros(std::string valor, std::string coluna)
{
    auto db = DbAcervo();
    auto livros = db.consulta(valor, coluna);
    return livros;
}

void Entidadebase::imprimeConsulta(std::vector<Livro>& consulta)
{
    for(auto& linha : consulta)
    {
        auto id = linha.getId();
        std::cout << id << " - " << linha.getTitulo() << ". Autor: " << linha.getAutor() << std::endl;
    }
}