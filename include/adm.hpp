#ifndef ADM_HPP
#define ADM_HPP

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
     * @param id_sql ID do banco de dados.
     */
    Administrador(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id_db = 0);
    
    /**
     * @brief Função para verificar existência de livro no acervo.
     * @param livro Referência para o livro a ser consultado.
     */
    bool EstaDisponivel(Livro &livro);

    /**
     * @brief Função para inserir um livro no acervo.
     * @param livro Referência para o livro a ser inserido.
     */
    void InserirLivro(Livro &livro);

    /**
     * @brief Função para remover um livro do acervo.
     * @param livro Referência para o livro a ser removido.
     */
    void RemoverLivro(Livro &livro);
};

#endif