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
     * @return Retorna true se o livro estiver disponível, false caso contrário.
     */
    bool EstaDisponivel(Livro &livro);

    /**
     * @brief Realiza o empréstimo de um livro.
     * @param livro Referência para o livro a ser emprestado.
     * @return Retorna o livro após o empréstimo (pode ser necessário ajustar os argumentos do construtor).
     */
    void EmprestaLivro(Livro &livro, Usuario& user);

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
