#ifndef BIBLIOTECARIO_HPP
#define BIBLIOTECARIO_HPP

#include "../include/entidadebase.hpp"
#include "../include/livro.hpp"
#include "../include/usuario.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Classe de exceção de livro indisponível.
 */
class LivroIndisponivel : public std::runtime_error {
public:
    LivroIndisponivel() : std::runtime_error("Livro indisponível") {}
};

/**
 * @brief Classe de exceção de usuário não encontrado.
 */
class UsuarioNaoEncontrado : public std::runtime_error {
public:
    UsuarioNaoEncontrado() : std::runtime_error("Usuário não encontrado") {}
};

/**
 * @brief Classe responsável por criar um bibliotecário
 */
class Bibliotecario : public Entidadebase
{
public:

    /**
     * @brief Construtor da classe Bibliotecario.
     * @param nome Nome do bibliotecário.
     * @param senha Senha do bibliotecário.
     * @param email Email do bibliotecário.
     * @param id_db ID do banco de dados.
     */
    Bibliotecario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id_db = 0
    );

    /**
     * @brief Verifica se um livro está disponível para empréstimo.
     * @param livro Referência para o livro a ser verificado.
     * @param acervo Referência para o acervo.
     * @return Retorna o ID do livro se estiver disponível, zero caso contrário.
     */
    unsigned int EstaDisponivel(Livro &livro);

    /**
     * @brief Realiza o empréstimo de um livro.
     * @param livro Referência para o livro a ser emprestado.
     * @return Retorna o livro após o empréstimo (pode ser necessário ajustar os argumentos do construtor).
     */
    Livro EmprestaLivro(Livro &livro, Usuario& user);

    /**
     * @brief Registra a devolução de um livro.
     * @param livro Livro a ser devolvido.
     * @param usuario Usuario que tem a posse do livro.
     */
    void DevolveLivro(Livro& livro, Usuario& usuario);

    Usuario BuscaUsuario(Usuario& user);

    void sign_in();

    /**
    * @brief Obtém a data atual no formato de string
    * @return A data atual no formato de string
    */
    std::string obterDataAtual();

    /**
    * @brief Obtém a data atual mais um offset em dias no formato de string
    * @param dias Offset em dias, pode ser positivo ou negativo
    * @return A data atual mais o offset no formato de string
    */
    std::string obterOffsetDataAtual(int dias);

    /*
     * @brief Define a data de empréstimo do livro
     * @param data A data de empréstimo
     */

    //void setDataEmprestimo(const std::string& data);
};

#endif
