#ifndef BIBLIOTECARIO_HPP
#define BIBLIOTECARIO_HPP

#include "acervo.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Classe responsável por criar um bibliotecário
 */
class Bibliotecario : public Entidadebase
{
private:
    
public:
    Bibliotecario();
    Bibliotecario(
        const std::string nome,
        const std::string senha,
        const std::string email,
        int id = 3
    );

    /*
     * @brief Verifica se o livro está disponível no acervo
     * @param livro O livro a ser verificado
     * @return true se o livro está disponível, false caso contrário
     */
    bool EstaDisponivel(Livro &livro, Acervo &acervo);

    /*
     * @brief Empréstimo de um livro
     * @param livro O livro a ser emprestado
     * @return O livro emprestado
     * @throw LivroNaoEncontradoException se o livro não estiver disponível no acervo
     * @throw LivroJaEmprestadoException se o livro já estiver emprestado
     */
    Livro EmprestaLivro(Livro &livro);

    /*
     * @brief Define o ID do usuário que pegou emprestado o livro
     * @param idUsuario O ID do usuário
     */

    //void setUsuarioEmprestimo(int idUsuario);

    /*
     * @brief Define a data de empréstimo do livro
     * @param data A data de empréstimo
     */

    //void setDataEmprestimo(const std::string& data);
};

/*
 * @brief Obtém a data atual no formato de string
 * @return A data atual no formato de string
 */
/*
std::string obterDataAtual();*/

#endif
