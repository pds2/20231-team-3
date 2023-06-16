#include "../include/livro.hpp"

Livro::Livro(std::string titulo,
             std::string autor,
             std::string genero,
             std::string resumo,
             std::string idioma,
             unsigned int numpag,
             unsigned int ano,
             float avaliacao)
    : _titulo(titulo), _autor(autor), _genero(genero), _resumo(resumo), _idioma(idioma), _numpag(numpag), _ano(ano), _avaliacao(avaliacao) {}
    

std::set<std::string> Livros;