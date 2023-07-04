#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <stdexcept>
#include <exception>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class AvaliacaoInvalida : public std::runtime_error {
public:
    AvaliacaoInvalida() : std::runtime_error("Avaliação inválido") {}
};

/**
 * @brief Classe que representa um livro.
 */
class Livro
{
private:
    std::string _titulo;
    std::string _autor;
    std::string _genero;
    std::string _resumo;
    std::string _idioma;
    unsigned int _numpag;
    unsigned int _ano;
    float _avaliacao;
    unsigned int _id;
    static int _proximoid;
    bool _emprestado; // indica se o livro está emprestado

    std::vector<float> _avaliacoes;

public:
    Livro();
    /**
     * @brief Construtor da classe Livro.
     * @param titulo Título do livro.
     * @param autor Autor do livro.
     * @param genero Gênero do livro.
     * @param resumo Resumo do livro.
     * @param idioma Idioma do livro.
     * @param numpag Número de páginas do livro.
     * @param ano Ano de lançamento do livro.
     * @param avaliacao Avaliação média do livro.
     * @param emprestado Estado de empréstimo do livro.
     */
    Livro (
        std::string titulo,
        std::string autor,
        std::string genero,
        std::string resumo,
        std::string idioma,
        unsigned int numpag,
        unsigned int ano,
        float avaliacao = 0,
        bool emprestado = 0
    );

    /**
     * @brief Obtém o título do livro.
     * @return Retorna o título do livro como uma string.
     */
    std::string getTitulo() const;

    /**
     * @brief Obtém o autor do livro.
     * @return Retorna o autor do livro como uma string.
     */
    std::string getAutor() const;

    /**
     * @brief Obtém o gênero do livro.
     * @return Retorna o gênero do livro como uma string.
     */
    std::string getGenero() const;

    /**
     * @brief Obtém o resumo do livro.
     * @return Retorna o resumo do livro como uma string.
     */
    std::string getResumo() const;

    /**
     * @brief Obtém o idioma do livro.
     * @return Retorna o idioma do livro como uma string.
     */
    std::string getIdioma() const;

    /**
     * @brief Obtém o número de páginas do livro.
     * @return Retorna o número de páginas do livro como um valor inteiro.
     */
    unsigned int getNumPaginas() const;

    /**
     * @brief Obtém o ano de lançamento do livro.
     * @return Retorna o ano de lançamento do livro como um valor inteiro.
     */
    unsigned int getAno() const;

    /**
     * @brief Obtém a avaliação média do livro.
     * @return Retorna a avaliação média do livro como um valor de ponto flutuante.
     */
    float getAvaliacao();

    /**
     * @brief Obtém o ID do livro.
     * @return Retorna o ID do livro como um valor inteiro.
     */
    unsigned int getId();

    /**
     * @brief Obtém o estado de empréstimo do livro.
     * @return Retorna true se o livro estiver emprestado, caso contrário, retorna false.
     */
    bool getEstado();

    /**
     * @brief Define o estado de empréstimo do livro.
     * @param estado Novo estado de empréstimo do livro.
     */
    void setEstado(bool estado);

    /**
     * @brief Define a avaliação do livro.
     * @param useravaliacao Avaliação do usuário a ser adicionada.
     */
    void setAvaliacao(const float& useravaliacao);

    // float somatoria_avaliacao(float &av);
    // float media_avaliacao(unsigned int &numavaliacoes);
};

#endif