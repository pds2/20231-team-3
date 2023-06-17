#include "../include/adm.hpp"
#include "entidadebase.hpp"

Administrador::Administrador(
    const std::string nome,
    const std::string senha,
    const std::string email,
    int id
) : Entidadebase(nome, senha, email, id) {}


void Administrador::InserirLivro(Acervo& acervo, Livro& livro)
{
        acervo.adicionarLivro(
        livro.getTitulo(),
        livro.getAutor(),
        livro.getGenero(),
        livro.getResumo(),
        livro.getIdioma(),
        livro.getNumPaginas(),
        livro.getAno(),
        livro.getAvaliacao()
    );
}

void Administrador::RemoverLivro(Acervo& acervo, Livro& livro)
{
    std::string titulo = livro.getTitulo();
    Livro livroEncontrado = acervo.buscar_livro(titulo);

    if (!livroEncontrado.getTitulo().empty()) {
        // Livro encontrado no acervo, remover
        acervo.remover_livro(titulo);
    }
}
