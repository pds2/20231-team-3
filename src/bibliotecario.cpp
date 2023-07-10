#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_usuarios.hpp"
#include "../include/db_administradores.hpp"

#include <ctime>

Bibliotecario::Bibliotecario() : Entidadebase() {}

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha,
                             const std::string email,
                             unsigned int id_db
) : Entidadebase(nome, senha, email, 3, id_db) {}

unsigned int Bibliotecario::EstaDisponivel(Livro& livro)
{
    using namespace bbt_def;
    auto db = DbAcervo();
    auto consulta = db.consulta(livro.getTitulo(), sql::schema_acervo::titulo);
    
    for(auto& livro_i : consulta)
    {
        if(livro.getAutor() != livro_i.getAutor()) continue;
        if(livro_i.getEstado() == 0) return livro_i.getId();
    }
    return 0;
}

Livro Bibliotecario::EmprestaLivro(Livro &livro, Usuario& user)
{
    auto id_disponivel = EstaDisponivel(livro);

    if (!id_disponivel) throw LivroIndisponivel();

    using namespace bbt_def;
    auto db_users = DbUsuarios();
    auto db_acervo = DbAcervo();
    auto user_consulta = db_users.consulta(
        user.getEmail(),
        sql::schema_usuarios::email)
        .back();
    
    auto&& user_id = user_consulta.getId();
    auto&& user_qtd_livros = user_consulta.getqntdlivros();
    if(user_qtd_livros >= user_consulta.get_max_livros()) throw MaximoLivros();

    db_acervo.sobrescrever_em_id(user_id,
    sql::schema_acervo::posse_id,
    id_disponivel);

    db_users.sobrescrever_em_id(user_qtd_livros + 1, sql::schema_usuarios::n_livros, user_id);

    Livro livro_temp = Livro();
    livro_temp.setDataAluguel(obterDataAtual());
    livro_temp.setDataDevolucao(obterOffsetDataAtual(dias_aluguel));

    std::string data_aluguel = livro_temp.getDataAluguel();
    std::string data_devolucao = livro_temp.getDataDevolucao();

    db_acervo.sobrescrever_em_id(
        db_acervo.data_padrao_para_sql(data_aluguel),
        sql::schema_acervo::data_aluguel,
        id_disponivel);

    db_acervo.sobrescrever_em_id(
        db_acervo.data_padrao_para_sql(data_devolucao),
        sql::schema_acervo::data_devolucao,
        id_disponivel);

    return db_acervo.consulta(id_disponivel, sql::id).back();
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
    
    auto livro_consulta = db_ac.consulta(livro.getTitulo(), sql::schema_acervo::titulo);
    if(livro_consulta.size() == 0) throw LivroIndisponivel();

    bool devolvido = false;
    for(auto& livro_i : livro_consulta)
    {
        if(livro_i.getEstado() != user_consulta.back().getId() || livro_i.getAutor() != livro.getAutor()) continue;
        db_user.sobrescrever_em_id(
            user_consulta.back().getqntdlivros() - 1,
            sql::schema_usuarios::n_livros,
            user_consulta.back().getId());

        db_ac.set_nulo_id(sql::schema_acervo::posse_id, livro_i.getId());
        db_ac.set_nulo_id(sql::schema_acervo::data_aluguel, livro_i.getId());
        db_ac.set_nulo_id(sql::schema_acervo::data_devolucao, livro_i.getId());
        devolvido = true;
        break;
    }
    if(!devolvido) throw LivroIndisponivel();
}

Usuario Bibliotecario::BuscaUsuario(Usuario& usuario)
{
    using namespace bbt_def::sql;
    auto db_user = DbUsuarios();
    auto consulta_user = db_user.consulta(usuario.getEmail(), schema_usuarios::email);

    if(consulta_user.size() == 0) throw UsuarioNaoEncontrado();
    return consulta_user.back();
}

std::string Bibliotecario::obterDataAtual()
{
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    return std::string(buffer);
}

std::string Bibliotecario::obterOffsetDataAtual(int dias)
{
    std::time_t&& diaria = 24 * 60 * 60;
    std::time_t now_offset = std::time(nullptr) + dias * diaria;
    std::tm* ptm = std::localtime(&now_offset);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    auto retorno = std::string(buffer);
    return retorno;
}

void Bibliotecario::sign_in()
{
    auto db_adm = DbAdministradores();
    auto consulta = db_adm.consulta(
        this->getEmail(),
        bbt_def::sql::schema_administradores::email);
    
    if(consulta.size() != 0) throw EmailJaCadastrado();

    db_adm.inserir_linha(*this);
}