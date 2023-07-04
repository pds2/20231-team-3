#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

class MaximoLivros : public std::runtime_error {
public:
    MaximoLivros() : std::runtime_error("Você não pode pegar mais que 3 livros.") {}
};

/**
 * @brief Classe responsável por criar um usuário.
 */
class Usuario : public Entidadebase
{
private:
    std::vector<Livro> _livrosPegos;
    std::vector<Livro> _livrosAvaliados;
    unsigned int _numerodelivros;

public:
    Usuario();
    /**
     * @brief Construtor da classe Usuario.
     * @param nome Nome do usuário.
     * @param senha Senha do usuário.
     * @param email Email do usuário.
     * @param id ID do usuário.
     * @param livrosPegos Vetor de livros pegos pelo usuário.
     * @param livrosAvaliados Vetor de livros avaliados pelo usuário.
     * @param numerodelivros Número de livros que o usuário possui.
     */
    Usuario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id = 1,
        std::vector<Livro> livrosPegos = {},
        std::vector<Livro> livrosAvaliados = {}
    );

    /**
     * @brief Adiciona um livro ao vetor de livros pegos pelo usuário.
     * @param u Livro a ser adicionado.
     */
    void pegar_livro(Livro &u);

    /**
     * @brief Remove um livro do vetor de livros pegos pelo usuário.
     * @param u Livro a ser devolvido.
     */
    void devolver_livro(Livro &u);

    /**
     * @brief Avalia um livro dado pelo usuário.
     * @param u Livro a ser avaliado.
     * @param avaliacaousuario Avaliação atribuída pelo usuário.
     */
    void avaliar_livro(Livro &u, float &avaliacaousuario) const;

    /**
     * @brief Obtém a quantidade de livros pegos pelo usuário.
     * @return Retorna o número de livros pegos como um valor inteiro.
     */
    int getqntdlivros();

    bool checkvip(Usuario &user);
};

#endif