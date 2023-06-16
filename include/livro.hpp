#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <iostream>
#include <set>
#include <string>

class Livro
{
private:
    std::string _titulo;
    std::string _autor;
    std::string _genero;
    std::string _resumo;
    std::string _idioma;
    unsigned int _numpag;
    unsigned int _ano;
    float _avaliacao;

public:
    Livro (
        std::string titulo,
        std::string autor,
        std::string genero,
        std::string resumo,
        std::string idioma,
        unsigned int numpag,
        unsigned int ano,
        float avaliacao
    );
};

std::set<std::string> Livros;

#endif