#ifndef ADM_HPP
#define ADM_HPP

#include "acervo.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

class Administrador : public Entidadebase
{
private:
    
public:
    Administrador();
    Administrador(
        const std::string nome,
        const std::string senha,
        const std::string email,
        int id = 4
    );

    void InserirLivro(Livro& livro);
    void RemoverLivro(Livro& livro);
};

#endif