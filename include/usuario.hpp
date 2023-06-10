#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>

class Usuario
{
private:
    virtual std::string _nome;
    virtual std::string _senha;
    virtual std::string _email;
    virtual unsigned int _id;
    virtual unsigned int _numerodelivros;
    // possível multa

public:
    void cadastrar_usuario (Usuario &u);
    void login_usuario (Usuario &u);
    // implementação?
    void pegar_livro (Livro &u);
    // aplicar limite de livros pegos por _id de usuário
    void devolver_livro (Livro &u);
    void avaliar_livro (Livro &u);
    // calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois
};

//lista de usuários

#endif