#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <stdexcept>
#include <exception>
#include <iostream>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Classe de exceção de avaliação inválida.
 */
class AvaliacaoInvalida : public std::runtime_error {
public:
    AvaliacaoInvalida() : std::runtime_error("Avaliação inválido") {}
};

/**
 * @brief Classe de exceção de data inválida.
 */
class DataInvalida : public std::runtime_error {
public:
    DataInvalida() : std::runtime_error("O formato de data deve ser DD/MM/AAAA") {}
    DataInvalida(std::string msg) : std::runtime_error(msg) {}
};

/**
 * @brief Classe de exceção de data não settada.
 */
class DataNaoSettada : public std::runtime_error {
public:
    DataNaoSettada() : std::runtime_error("Não há data") {}
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
    unsigned int _emprestado; // indica se o livro está emprestado
    std::string _data_aluguel;
    std::string _data_devolucao;
    unsigned int _qtde_avaliacoes;

    std::vector<float> _avaliacoes;

public:
    /**
     * @brief Construtor da classe Livro sem argumentos. Inicializa com membros vazios.
     */
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
     * @param id ID do livro.
     * @param emprestado ID do usuário de empréstimo do livro.
     * @param qtde_avaliacoes Quantidade de avaliações feitas do livro.
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
        unsigned int id = 0,
        unsigned int emprestado = 0,
        unsigned int qtde_avaliacoes = 0
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
    float getAvaliacao() const;

    /**
     * @brief Obtém o ID do livro.
     * @return Retorna o ID do livro como um valor inteiro.
     */
    unsigned int getId();

    /**
     * @brief Obtém o estado de empréstimo do livro.
     * @return Retorna o ID de quem estiver emprestado, caso contrário, retorna zero.
     */
    unsigned int getEstado();

    /**
     * @brief Obtém a data de aluguel do livro.
     * @return Retorna uma string com a data de aluguel. Se não houver, retorna string vazia.
     */
    std::string getDataAluguel();   

    /**
     * @brief Obtém a data de devolução do livro.
     * @return Retorna uma string com a data de devolução. Se não houver, retorna string vazia.
     */
    std::string getDataDevolucao();

    /**
     * @brief Obtém a quantidade de avaliações feitas.
     * @return Retorna a quantidade de avaliações.
     */
    unsigned int getQtdAvaliacoes(); 

    /**
     * @brief Define o estado de empréstimo do livro.
     * @param id Novo ID do usuário de empréstimo do livro.
     */
    void setEstado(unsigned int id);

    /**
     * @brief Define o ID do livro.
     * @param id ID do livro.
     */
    void setId(unsigned int id);

    /**
     * @brief Define a avaliação do livro.
     * @param useravaliacao Avaliação do usuário a ser adicionada.
     */
    void setAvaliacao(const float& useravaliacao);

    /**
     * @brief Define a data de aluguel do livro.
     * @param data_aluguel Data de aluguel do livro.
     */
    void setDataAluguel(const std::string data_aluguel);    

    /**
     * @brief Define a data de devolução do livro.
     * @param data_devolucao Data de devolução do livro.
     */
    void setDataDevolucao(const std::string data_devolucao);

    /**
     * @brief Define a quantidade de avaliações do livro.
     * @param qtd Quantidade de avaliações.
     */
    void setQtdAvaliacoes(unsigned int qtd);
};

class LivroNaoEncontrado : public std::exception {
public:
    LivroNaoEncontrado() = default;

    const char* what() const noexcept override {
        return "Livro não encontrado";
    }
};


class LivroNaoEmprestado : public std::exception {
    private:
        std::string mensagem;

    public:
        LivroNaoEmprestado(const std::string& livro);

        const char* what() const noexcept override;
};

#endif