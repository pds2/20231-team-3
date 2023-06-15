#ifndef ADM_HPP
#define ADM_HPP

#include "acervo.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

//TODO: Implementar
/**
 * possível carteira
*/

/**
 * @brief Classe responsavel por criar um Administrador
 */
class Bibliotecario : public Entidadebase
{
private:
    
public:
    Bibliotecario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        int id = 4
    );

    /**
     * @brief Insere livro
     */
    void InserirLivro(Livro& livro);

    /**
     * @brief Remove livro
     */
    void RemoverLivro(Livro& livro);
};

#endif