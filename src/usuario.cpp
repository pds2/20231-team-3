#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../include/usuario.hpp"

// TODO: Implementar

/**
 * @brief Classe responsavel por criar um Usuario
 */

Usuario::Usuario(const std::string nome,
                 const std::string senha,
                 const std::string email,
                 unsigned int id,
                 std::vector<Livro> livrosPegos,
                 std::vector<Livro> livrosAvaliados,
                 unsigned int numerodelivros)
    : _nome(nome), _email(email), _id(id), _senha(senha), _livrosPegos(livrosPegos), _livrosAvaliados(livrosAvaliados), _numerodelivros(numerodelivros) {}

void Usuario::pegar_livro(Livro &u) const
{
    _numerodelivros--;
    _livrosPegos.push_back(u);
}

void Usuario::devolver_livro(Livro &u) const
{
}

void Usuario::avaliar_livro(Livro &u) const
{
    // set
}
// calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois

int Usuario::getqntdlivros(std::vector<Livro> livrop)
{
    return livrop.size();
}