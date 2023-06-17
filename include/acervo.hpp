#ifndef ACERVO_HPP
#define ACERVO_HPP

#include <iostream>
#include <map>
#include <string>
#include "livro.hpp" // Inclua o arquivo de cabeçalho do Livro aqui

class Acervo
{
private:
    std::map<std::string, Livro*> _livros;

public:
    void adicionarLivro(
        std::string titulo,
        std::string autor,
        std::string genero,
        std::string resumo,
        std::string idioma,
        unsigned int numpag,
        unsigned int ano,
        float avaliacao
    );
    void inserir_livro(const Livro& livro);
    void remover_livro(const std::string& livro);
    Livro buscar_livro(const std::string& titulo);
    std::size_t tamanho() const;
};

#endif