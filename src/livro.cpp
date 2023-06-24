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

unsigned int Livro::getId() const {
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

/*float Livro::somatoria_avaliacao(float &av) {
    // se avaliacao negativa, retornar erro
    return _avaliacao + av;
}*/

/*float Livro::somatoria_avaliacao() const {
    float soma = 0.0f;
    for (const auto& avaliacao : _avaliacoes) {
        soma += avaliacao;
    }
    return soma;
}

float Livro::media_avaliacao() const {
    // se avaliacao negativa, retornar erro
    if (_numAvaliacoes == 0) {
        return 0.0f;
    }
    return somatoria_avaliacao() / _numAvaliacoes;
}

void Livro::adicionar_avaliacao(float avaliacao) {
    // Incrementa o número de avaliações
    _numAvaliacoes++;

    // Calcula a nova soma das avaliações
    float novaSomatoria = somatoria_avaliacao() + avaliacao;

    // Atualiza a avaliação média
    _avaliacao = novaSomatoria / _numAvaliacoes;
}*/