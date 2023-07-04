#ifndef ADM_HPP
#define ADM_HPP

#include "acervo.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"

#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Construtor da classe Administrador.
 * Recebe o nome, senha, email e id como parâmetros
 * e inicializa a classe base Entidadebase.
 */
class Administrador : public Entidadebase
{
private:
public:
    Administrador();
    /**
     * @brief Construtor da classe Administrador.
     * @param nome Nome do administrador.
     * @param senha Senha do administrador.
     * @param email Email do administrador.
     * @param id ID do administrador.
     */
    Administrador(
        const std::string nome,
        const std::string senha,
        const std::string email,
        int id = 4);

    /**
     * @brief Função para inserir um livro no acervo.
     * @param acervo Referência para o acervo.
     * @param livro Referência para o livro a ser inserido.
     */
    void InserirLivro(Acervo &acervo, Livro &livro);

    /**
     * @brief Função para remover um livro do acervo.
     * @param acervo Referência para o acervo.
     * @param livro Referência para o livro a ser removido.
     */
    void RemoverLivro(Acervo &acervo, Livro &livro);
};

#endif