#include "../include/livro.hpp"

Livro::Livro(std::string titulo,
             std::string autor,
             std::string genero,
             std::string resumo,
             std::string idioma,
             unsigned int numpag,
             unsigned int ano,
             float avaliacao,
             unsigned int id)
    : _titulo(titulo), _autor(autor), _genero(genero), _resumo(resumo), _idioma(idioma), _numpag(numpag), _ano(ano), _avaliacao(avaliacao), _id(id){}

std::string Livro::getTitulo() const {
    return _titulo;
}

std::string Livro::getAutor() const {
    return _autor;
}

std::string Livro::getGenero() const {
    return _genero;
}

std::string Livro::getResumo() const {
    return _resumo;
}

std::string Livro::getIdioma() const {
    return _idioma;
}

unsigned int Livro::getNumPaginas() const {
    return _numpag;
}

unsigned int Livro::getAno() const {
    return _ano;
}

float Livro::getAvaliacao() const {
    return _avaliacao;
}

unsigned int Livro::getId() {
    return _id;
}

void Livro::setAvaliacao(const float& useravaliacao) {
    static unsigned int count = 0;
    static float h = 0;

    float temp = useravaliacao;  // Copia o valor para uma variável temporária
    h += temp;
    count++;
    _avaliacao = h / count;
}

bool Livro::isEmprestado() const {
    return _emprestado;
}

/*void Livro::setEmprestado(bool status) {
    _emprestado = status;
}*/