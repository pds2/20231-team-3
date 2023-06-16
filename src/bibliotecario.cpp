#include "../include/bibliotecario.hpp"

// passar valor id

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha, 
                             const std::string email,
                             unsigned int id = 3)
    : _nome(nome), _email(email), _id(id), _senha(senha) {}

bool Bibliotecario::EstaDisponivel(Livro &livro) {
    if (Acervo::buscar_livro(livro) == NULL)
    {
        throw busca_vazia();
    }
    return Acervo::buscar_livro(livro);
}

Livro Bibliotecario::EmprestaLivro(Livro &livro) {
    // Implementar
}