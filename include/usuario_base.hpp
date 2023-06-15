#ifndef USUARIO_BASE_HPP
#define USUARIO_BASE_HPP

#include <iostream>
#include <set>
#include <string>

class Usuariobase
{
private:
    std::string _nome;
    std::string _senha;
    std::string _email;
    unsigned int _id;
    // possível multa

public:
    Usuariobase(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id
    );
};

// lista de usuários

#endif