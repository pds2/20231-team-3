#include "../include/acervo.hpp"

void Acervo::adicionarLivro(
    std::string titulo,
    std::string autor,
    std::string genero,
    std::string resumo,
    std::string idioma,
    unsigned int numpag,
    unsigned int ano,
    float avaliacao
)
{
    Livro* livro = new Livro(titulo, autor, genero, resumo, idioma, numpag, ano, avaliacao);
    _livros[titulo] = livro;
    // verificar memory leak
}

void Acervo::inserir_livro(const Livro& livro)
{
    std::string titulo = livro.getTitulo();
    _livros[titulo] = new Livro(livro);
    // possível memory leak
}

Livro Acervo::buscar_livro(const std::string& titulo)
{
    auto it = _livros.find(titulo);
    if (it != _livros.end()) {
        return *(it->second); // Retorna o livro encontrado
    } else {
        // Faça o tratamento caso o livro não seja encontrado
        // Por exemplo, lançar uma exceção ou retornar um livro padrão
        // Aqui, retornaremos um livro vazio
        return Livro("", "", "", "", "", 0, 0, 0.0f);
    }
}

void Acervo::remover_livro(const std::string& titulo)
{
    auto it = _livros.find(titulo);
    if (it != _livros.end()) {
        delete it->second; // Libera a memória do objeto Livro
        _livros.erase(it); // Remove o livro do mapa
    }
}

std::size_t Acervo::tamanho() const
{
    return _livros.size();
}