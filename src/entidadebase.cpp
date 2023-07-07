#include "../include/entidadebase.hpp"

Entidadebase::Entidadebase(std::string nome,
                           std::string senha,
                           std::string email,
                           unsigned int id)
    : _nome(nome), _senha(senha), _email(email), _id(id) {}

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

std::vector<std::tuple<unsigned int, Livro, AdtDataSQL>>
Entidadebase::consultaLivros(std::string valor, std::string coluna)
{
    auto db = DbAcervo();
    auto livros = db.consulta(valor, coluna);
    for(auto& livro : livros)
    {
        auto&& id = std::get<0>(livro);
        std::get<1>(livro).setId(id);
    }

    return livros;
}

void Entidadebase::imprimeConsulta(std::vector<std::tuple<unsigned int, Livro, AdtDataSQL>>& consulta)
{
    for(auto& linha : consulta)
    {
        auto id = std::get<0>(linha);
        auto livro = std::get<1>(linha);
        std::cout << id << " - " << livro.getTitulo() << ". Autor: " << livro.getAutor() << std::endl;
    }
}