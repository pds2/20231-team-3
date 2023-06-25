#include "../include/acervo.hpp"

void Acervo::adicionarLivro(
    std::string titulo,
    std::string autor,
    std::string genero,
    std::string resumo,
    std::string idioma,
    unsigned int numpag,
    unsigned int ano,
    float avaliacao,
    unsigned int id)
{
    Livro *livro = new Livro(titulo, autor, genero, resumo, idioma, numpag, ano, avaliacao, id);
    _livros[id] = livro;
    // verificar memory leak
}

/*void Acervo::inserir_livro(const Livro& livro)
{
    std::string titulo = livro.getTitulo();
    _livros[titulo] = new Livro(livro);
    // possível memory leak
}*/

Livro Acervo::buscar_livro(const unsigned int &id)
{
    auto it = _livros.find(id);
    if (it != _livros.end())
    {
        return *(it->second); // Retorna o livro encontrado
    }
    else
    {
        // Faça o tratamento caso o livro não seja encontrado
        // Por exemplo, lançar uma exceção ou retornar um livro padrão
        // Aqui, retornaremos um livro vazio
        return Livro("", "", "", "", "", 0, 0, 0.0f, 0);
    }
}

void Acervo::remover_livro(const unsigned int &id)
{
    auto it = _livros.find(id);
    if (it != _livros.end())
    {
        delete it->second; // Libera a memória do objeto Livro
        _livros.erase(it); // Remove o livro do mapa
    }
}

std::size_t Acervo::tamanho() const
{
    return _livros.size();
}