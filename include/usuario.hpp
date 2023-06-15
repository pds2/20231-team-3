#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>

class Usuario : public Usuariobase
{
private:
    unsigned int _numerodelivros;
    int _id;
    void pegar_livro(Livro &u) const;
    // aplicar limite de livros pegos por _id de usuário
    void devolver_livro(Livro &u) const;
    void avaliar_livro(Livro &u) const;
    // calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois
    std::vector<Livro> livrosPegos;
    std::vector<Livro> livrosAvaliados;

public:
    Usuario(
        const std::string nome,
        const std::string seznha,
        const std::string email,
        int id
    );

    int id = 1;
    unsigned int get_numerolivros();
};

// lista de usuários

#endif