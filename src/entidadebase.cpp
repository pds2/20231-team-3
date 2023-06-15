#include "../include/entidadebase.hpp"

Entidadebase::Entidadebase() {
    std::string nome,
    std::string email,
    unsigned int id,
    std::string senha
}: Entidadebase(nome), Entidadebase(email), Entidadebase(id), Entidadebase(senha) { }

std::string Entidadebase::getNome() const {
    return _nome;
}

std::string Entidadebase::getEmail() const {
    return _email;
}

unsigned int Entidadebase::getId() const {
    return _id;
}

std::string Entidadebase::getSenha() const {
    return _senha;
}