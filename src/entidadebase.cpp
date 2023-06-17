#include "../include/entidadebase.hpp"

Entidadebase::Entidadebase(const std::string nome, 
                           const std::string email, 
                           unsigned int id, 
                           const std::string senha)
    : _nome(nome), _email(email), _id(id), _senha(senha) {}

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
