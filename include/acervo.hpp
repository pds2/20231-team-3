#ifndef ACERVO_HPP
#define ACERVO_HPP

#include <map>

#include "livro.hpp"
#include "usuario.hpp"

class Acervo
{
private:
    std::map<std::string, Livro> acervo;
public:
    Livro buscar_livro(std::string& titulo);
};

#endif