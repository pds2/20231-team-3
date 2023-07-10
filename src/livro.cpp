#include <regex>

#include "../include/livro.hpp"

Livro::Livro(std::string titulo,
             std::string autor,
             std::string genero,
             std::string resumo,
             std::string idioma,
             unsigned int numpag,
             unsigned int ano,
             float avaliacao,
             unsigned int id,
             unsigned int emprestado,
             unsigned int qtde_avaliacoes) :

             _titulo(titulo),
             _autor(autor),
             _genero(genero),
             _resumo(resumo),
             _idioma(idioma),
             _numpag(numpag),
             _ano(ano),
             _avaliacao(avaliacao),
             _id(id),
             _emprestado(emprestado),
             _data_aluguel(""),
             _data_devolucao(""),
             _qtde_avaliacoes(qtde_avaliacoes) {}

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

unsigned int Livro::getEstado() {
    // zero (0) se não emprestado
    return _emprestado;
}

std::string Livro::getDataAluguel() {
    if(_data_aluguel == "") throw DataNaoSettada();
    return _data_aluguel;
}

std::string Livro::getDataDevolucao() {
    if(_data_devolucao == "") throw DataNaoSettada();
    return _data_devolucao;
}

unsigned int Livro::getQtdAvaliacoes()
{
    return _qtde_avaliacoes;
}

void Livro::setEstado(unsigned int id) {
    _emprestado = id;
}

void Livro::setId(unsigned int id)
{
    _id = id;
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

void Livro::setDataAluguel(const std::string data_aluguel) {
    std::regex reg_data("\\d{2}\\/\\d{2}\\/\\d{4}");

    if(!std::regex_match(data_aluguel, reg_data))
    {
        throw DataInvalida();
    }

    auto dia = std::stoi(data_aluguel.substr(0, 2));
    auto mes = std::stoi(data_aluguel.substr(3, 2));
    auto ano = std::stoi(data_aluguel.substr(6, 4));
    bool bissexto = ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0);
    std::set<unsigned int> meses_30 = {2,4,6,9,11};

    if(ano < 1000 || ano > 9999) throw DataInvalida("Insira um ano válido");
    if(mes > 12 || dia > 31) throw DataInvalida();
    if(meses_30.find(mes) != meses_30.end())
    {
        if(dia == 31) throw DataInvalida(); 
    }
    if(mes == 2 && dia > 29) throw DataInvalida("Insira um dia válido");
    if(mes == 2 && dia == 29)
    {
        if(!bissexto) throw DataInvalida("Insira um dia válido");
    }

    _data_aluguel = data_aluguel;
}

void Livro::setDataDevolucao(const std::string data_devolucao) {
    std::regex reg_data("\\d{2}\\/\\d{2}\\/\\d{4}");

    if(!std::regex_match(data_devolucao, reg_data))
    {
        throw DataInvalida();
    }

    auto dia = std::stoi(data_devolucao.substr(0, 2));
    auto mes = std::stoi(data_devolucao.substr(3, 2));
    auto ano = std::stoi(data_devolucao.substr(6, 4));
    bool bissexto = ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0);
    std::set<unsigned int> meses_30 = {2,4,6,9,11};

    if(ano < 1000 || ano > 9999) throw DataInvalida("Insira um ano válido");
    if(mes > 12 || dia > 31) throw DataInvalida();
    if(meses_30.find(mes) != meses_30.end())
    {
        if(dia == 31) throw DataInvalida(); 
    }
    if(mes == 2 && dia > 29) throw DataInvalida("Insira um dia válido");
    if(mes == 2 && dia == 29)
    {
        if(!bissexto) throw DataInvalida("Insira um dia válido");
    }

    _data_devolucao = data_devolucao;
}

void Livro::setQtdAvaliacoes(unsigned int qtd)
{
    _qtde_avaliacoes = qtd;
}