#include "../include/adm.hpp"
#include "../include/entidadebase.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_administradores.hpp"

Administrador::Administrador(
    const std::string nome,
    const std::string senha,
    const std::string email,
    unsigned int id_db
) : Entidadebase(nome, senha, email, 4, id_db) {}

void Administrador::InserirLivro(Livro& livro)
{
   auto db = DbAcervo();
   db.inserir_linha(livro);
}

void Administrador::RemoverLivro(Livro& livro)
{
   auto db = DbAcervo();
   auto alugado = livro.getEstado();
   if(alugado) throw LivroAlugado();
   db.deletar_linha_id(livro.getId());
}

void Administrador::sign_in()
{
    auto db_adm = DbAdministradores();
    auto consulta = db_adm.consulta(
        this->getEmail(),
        bbt_def::sql::schema_administradores::email);
    
    if(consulta.size() != 0) throw EmailJaCadastrado();

    db_adm.inserir_linha(*this);
}