#ifndef ACERVO_HPP
#define ACERVO_HPP

#include <map>

#include "livro.hpp"
#include "usuario.hpp"

class Acervo
{
private:
    std::map<Livros> acervo;
public:
    void buscar_livro(Livro &l);
};

#endif