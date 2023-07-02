#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

//TODO: Implementar
/**
  * O ID desse tipo de usuario deve ser 1
*/

/**
 * @brief Classe responsavel por criar um usuario comum.
 */
class Usuario : public Entidadebase
{
private:
    std::vector<Livro> _livrosPegos;
    std::vector<Livro> _livrosAvaliados;
    unsigned int _numerodelivros;

public:
    Usuario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id = 1,
        std::vector<Livro> livrosPegos = {},
        std::vector<Livro> livrosAvaliados = {},
        unsigned int numerodelivros = 3
    );

    void pegar_livro(Livro &u);
    void devolver_livro(Livro &u);
    void avaliar_livro(Livro &u, float &avaliacaousuario) const;
    // calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois

    bool checkvip(Usuario &user);

    int getqntdlivros();
};

#endif