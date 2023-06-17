#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <iostream>
#include <set>
#include <string>

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

public:
    Livro (
        std::string titulo,
        std::string autor,
        std::string genero,
        std::string resumo,
        std::string idioma,
        unsigned int numpag,
        unsigned int ano,
        float avaliacao = 0,
        unsigned int id = 1
    );

    // Métodos de acesso para obter informações sobre o livro
    std::string getTitulo() const;
    std::string getAutor() const;
    std::string getGenero() const;
    std::string getResumo() const;
    std::string getIdioma() const;
    unsigned int getNumPaginas() const;
    unsigned int getAno() const;
    float getAvaliacao() const;
    unsigned int getId() const;

    void setAvaliacao(float &useravaliacao);

    float somatoria_avaliacao(float &av);
    float media_avaliacao(unsigned int &numavaliacoes);
};

#endif