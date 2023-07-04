#include "../include/livro.hpp"

int Livro::_proximoid = 0;

Livro::Livro(std::string titulo,
             std::string autor,
             std::string genero,
             std::string resumo,
             std::string idioma,
             unsigned int numpag,
             unsigned int ano,
             float avaliacao,
             bool emprestado)
    : _titulo(titulo), _autor(autor), _genero(genero), _resumo(resumo), _idioma(idioma), _numpag(numpag), _ano(ano), _avaliacao(avaliacao), _emprestado(emprestado) 
    {
        _id = _proximoid;
        _proximoid++;
    }

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

float Livro::getAvaliacao() {
    return _avaliacao;
}

unsigned int Livro::getId() {
    return _id;
}

void Livro::setAvaliacao(const float& useravaliacao) {
    if (!(useravaliacao >= 0 && useravaliacao <= 5)) {
        throw AvaliacaoInvalida();
    }
    
    _avaliacoes.push_back(useravaliacao);

        float sum = 0;
        for (const auto& avaliacao : _avaliacoes) {
            sum += avaliacao;
        }

        _avaliacao = sum / _avaliacoes.size();
}

bool Livro::getEstado() {
    // verdadeiro (1) se emprestado
    return _emprestado;
}

void Livro::setEstado(bool estado) {
    _emprestado = estado;
}

/*bool Livro::isEmprestado() const {
    return _emprestado;
}*/

/*void Livro::setEmprestado(bool status) {
    _emprestado = status;
}*/