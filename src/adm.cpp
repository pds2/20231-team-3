#include "../include/adm.hpp"
#include "entidadebase.hpp"
#include "db_acervo.hpp"

Administrador::Administrador(
    const std::string nome,
    const std::string senha,
    const std::string email,
    unsigned int id_db
) : Entidadebase(nome, senha, email, 4, id_db) {}

bool Administrador::EstaDisponivel(Livro& livro)
{
    auto db = DbAcervo();
    auto vec = db.consulta(livro.getTitulo(), bbt_def::sql::schema_acervo::titulo);
    if(vec.size() == 0) return false;
    else return true;
}

void Administrador::InserirLivro(Livro& livro)
{
   auto db = DbAcervo();
   db.inserir_linha(livro);
}

void Administrador::RemoverLivro(Livro& livro)
{
   auto db = DbAcervo();
   db.deletar_linha_id(livro.getId());
}