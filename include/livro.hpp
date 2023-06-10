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
    unsigned float _avaliacao;

public:
    Livro (
        std::string titulo;
        std::string autor;
        std::string genero;
        std::string resumo;
        std::string idioma;
        unsigned int numpag;
        unsigned int ano;
        unsigned float avaliacao
    )
};

std::set<string> Livros;

#endif