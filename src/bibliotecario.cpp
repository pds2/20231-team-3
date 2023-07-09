#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"
#include "db_acervo.hpp"
#include "db_usuarios.hpp"

#include <ctime>

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha,
                             const std::string email,
                             unsigned int id_db
) : Entidadebase(nome, senha, email, 3, id_db) {}

unsigned int Bibliotecario::EstaDisponivel(Livro& livro)
{
    using namespace bbt_def;
    auto db = DbAcervo();
    auto consulta = db.consulta(livro.getId(), sql::id);
    
    for(auto& livro : consulta)
    {
        if (livro.getEstado() == 0) return livro.getId();
    }
    return 0;
}

Livro Bibliotecario::EmprestaLivro(Livro &livro, Usuario& user)
{
    auto id_disponivel = EstaDisponivel(livro);

    if (!id_disponivel) throw LivroIndisponivel();

    using namespace bbt_def::sql;
    auto db_users = DbUsuarios();
    auto db_acervo = DbAcervo();
    auto user_id = db_users.consulta(
        user.getEmail(),
        schema_usuarios::email)
        .back()
        .getIdDb();

    db_acervo.sobrescrever_em_id(user_id,
    schema_acervo::posse_id,
    id_disponivel);

    return db_acervo.consulta(id_disponivel, id).back();
}

void Bibliotecario::DevolveLivro(Livro &livro, Usuario& usuario)
{
    auto db_user = DbUsuarios();
    auto db_ac = DbAcervo();

    using namespace bbt_def;
    auto user_consulta = db_user.consulta(
        usuario.getEmail(),
        sql::schema_usuarios::email);
    if(user_consulta.size() == 0) throw UsuarioNaoEncontrado();
    
    auto livro_consulta = db_ac.consulta(livro.getEstado(), sql::schema_acervo::posse_id);
    if(livro_consulta.size() == 0) throw LivroIndisponivel();

    db_user.sobrescrever_em_id(user_consulta.back().getqntdlivros() - 1,
    sql::schema_usuarios::n_livros,
    user_consulta.back().getId());

    db_ac.set_nulo_id(sql::schema_acervo::posse_id, livro_consulta.back().getId());

}

std::string obterDataAtual()
{
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    return std::string(buffer);
}