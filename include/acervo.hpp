#ifndef ACERVO_HPP
#define ACERVO_HPP

#include <iostream>
#include <map>
#include <string>
#include "livro.hpp" // Inclua o arquivo de cabeçalho do Livro aqui

class Acervo
{
private:
    std::map<unsigned int, Livro*> _livros;

public:
    void adicionarLivro(
        std::string titulo,
        std::string autor,
        std::string genero,
        std::string resumo,
        std::string idioma,
        unsigned int numpag,
        unsigned int ano,
        float avaliacao,
        unsigned int id
    );
    void inserir_livro(const Livro& livro);
    void remover_livro(const unsigned int& id);
    Livro buscar_livro(const unsigned int& id);
    std::size_t tamanho() const;
};

#endif