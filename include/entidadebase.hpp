#ifndef ENTIDADE_BASE_HPP
#define ENTIDADE_BASE_HPP

#include <string>

//TODO: Implementar
/**
  * Decidir critérios para os nomes, emails e senhas
*/

/**
 * @brief Classe responsavel por atuar como
 * classe pai
 */
class Entidadebase
{
private:
    std::string _nome;
    std::string _email;
    unsigned int _id;
    std::string _senha;
public:
    Entidadebase(
        std::string nome,
        std::string email,
        unsigned int id,
        std::string senha
    );

    std::string getNome() const;
    std::string getEmail() const;
    unsigned int getId() const;
    std::string getSenha() const;

    void setNome(const std::string& nome);
    void setEmail(const std::string& email);
    void setId(unsigned int id);
    void setSenha(const std::string& senha);
};

#endif