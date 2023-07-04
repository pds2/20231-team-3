#ifndef ENTIDADE_BASE_HPP
#define ENTIDADE_BASE_HPP

#include <iostream>
#include <string>

/**
 * @brief Classe base para entidades do sistema.
 */
class Entidadebase
{
private:
    std::string _nome;
    std::string _senha;
    std::string _email;
    unsigned int _id;

public:
    Entidadebase();
    /**
     * @brief Construtor da classe Entidadebase.
     * @param nome Nome da entidade.
     * @param senha Senha da entidade.
     * @param email Email da entidade.
     * @param id ID da entidade.
     */
    Entidadebase(
        const std::string nome,
        const std::string senha,
        const std::string email,
        unsigned int id
    );

    /**
     * @brief Obtém o nome da entidade.
     * @return Retorna o nome da entidade como uma string.
     */
    std::string getNome();

    /**
     * @brief Obtém o email da entidade.
     * @return Retorna o email da entidade como uma string.
     */
    std::string getEmail();

    /**
     * @brief Obtém o ID da entidade.
     * @return Retorna o ID da entidade como um valor inteiro.
     */
    unsigned int getId();

    /**
     * @brief Obtém a senha da entidade.
     * @return Retorna a senha da entidade como uma string.
     */
    std::string getSenha();

    /**
     * @brief Define o nome da entidade.
     * @param nome Novo nome da entidade.
     */
    void setNome(const std::string &nome);

    /**
     * @brief Define o email da entidade.
     * @param email Novo email da entidade.
     */
    void setEmail(const std::string &email);

    /**
     * @brief Define o ID da entidade.
     * @param id Novo ID da entidade.
     */
    void setId(unsigned int id);

    /**
     * @brief Define a senha da entidade.
     * @param senha Nova senha da entidade.
     */
    void setSenha(const std::string &senha);
};

#endif