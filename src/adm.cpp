#include "../include/adm.hpp"
#include "entidadebase.hpp"
#include "db_acervo.hpp"

Administrador::Administrador(
    const std::string nome,
    const std::string senha,
    const std::string email,
    int id
) : Entidadebase(nome, senha, email, id) {}


void Administrador::InserirLivro(Livro& livro)
{
    /*
        acervo.adicionarLivro(
        livro.getTitulo(),
        livro.getAutor(),
        livro.getGenero(),
        livro.getResumo(),
        livro.getIdioma(),
        livro.getNumPaginas(),
        livro.getAno(),
        livro.getAvaliacao(),
        livro.getId()
    );
    */
   auto db = DbAcervo();
   db.inserir_linha(livro);
}

void Administrador::RemoverLivro(Livro& livro)
{
    /*
    unsigned int id = livro.getId();
    Livro livroEncontrado = acervo.buscar_livro(id);

    if (!livroEncontrado.getTitulo().empty()) {
        // Livro encontrado no acervo, remover
        acervo.remover_livro(id);
    }
    */
   auto db = DbAcervo();
   db.deletar_linha_id(livro.getId());
}