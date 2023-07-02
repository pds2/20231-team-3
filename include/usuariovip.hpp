#ifndef USUARIO_VIP_HPP
#define USUARIO_VIP_HPP

#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

//TODO: Implementar
/**
  * O ID desse tipo de usuario deve ser 2
*/

/**
 * @brief Classe responsavel por criar um usuario vip.
 */

class Uusariovip : public Entidadebase
{
private:
    std::vector<Livro> _livrosPegos(5);
    //std::vector<Livro> _livrosAvaliados;
    unsigned int _numerodelivros;

public:
    Uusariovip(
        const std::string nome,
        const std::string senha,
        const std::string email,
        int id = 2,
        std::vector<Livro> livrosPegos,
        std::vector<Livro> livrosAvaliados,
        unsigned int numerodelivros = 5
    );

    void pegar_livro(Livro &u) const;
    void devolver_livro(Livro &u) const;
    void avaliar_livro(Livro &u) const;
    // calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois
};

#endif