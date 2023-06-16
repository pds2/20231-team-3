#ifndef BIBLIOTECARIO_HPP
#define BIBLIOTECARIO_HPP

#include "acervo.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

//TODO: Implementar
/**
  * O ID desse tipo de usuario deve ser 3
  * Decidir se serão necessários mais métodos
*/

/**
 * @brief Classe responsavel por criar um bibliotecario
 */
class Bibliotecario : public Entidadebase
{
private:
    
public:
    Bibliotecario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id = 3
    );

    /**
     * @brief Método deve retornar true se livro disponível e false se indisponivel
     */
    bool EstaDisponivel(Livro &livro);

    /**
     * @brief Se livro disponivel, emprestar, se nao, lancar erro
     */
    Livro EmprestaLivro(Livro &livro);
};

#endif