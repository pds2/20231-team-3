#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../third_party/doctest.h"

#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/entidadebase.hpp"
#include "../include/livro.hpp"
#include "../include/usuario.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_usuarios.hpp"
#include "../include/db_administradores.hpp"

#include <string>

/*TEST_CASE("01 - Testando o construtor sem parâmetros") {
    CHECK_NOTHROW(Acervo());
    CHECK_NOTHROW(Administrador());
    CHECK_NOTHROW(Bibliotecario());
    CHECK_NOTHROW(Entidadebase());
    CHECK_NOTHROW(Livro());
    CHECK_NOTHROW(Usuario());
}*/

void reset_db()
{
    auto db_ac = DbAcervo();
    db_ac.reset();
    auto db_user = DbUsuarios();
    db_user.reset();
    auto db_adm = DbAdministradores();
    db_adm.reset();
}

TEST_CASE("02 - Testando empréstimo de livro") {
    reset_db();

    auto db_user = DbUsuarios();
    auto db_ac = DbAcervo();
    auto db_adm = DbAdministradores();

    Livro l1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2022, 0.0);
    Usuario u1("User", "40028922", "user@example.com", 1, 0);
    Usuario u2("User2", "40028922", "user2@example.com", 1, 0);
    Bibliotecario b1("Bbt1", "123123", "bbt1@example.com");

    db_ac.inserir_linha(l1);
    db_user.inserir_linha(u1);
    db_user.inserir_linha(u2);
    db_adm.inserir_linha(b1);

    auto l1_db = db_ac.consulta(
        l1.getTitulo(),
        bbt_def::sql::schema_acervo::titulo).back();
    
    auto u1_db = db_user.consulta(
        u1.getEmail(),
        bbt_def::sql::schema_usuarios::email).back();

    auto u2_db = db_user.consulta(
        u2.getEmail(),
        bbt_def::sql::schema_usuarios::email).back();
    
    CHECK_NOTHROW(b1.EmprestaLivro(l1_db, u1_db));
    CHECK_NOTHROW(b1.DevolveLivro(l1_db, u1_db));
    float avaliacao1 = 4.0f;
    CHECK_NOTHROW(u1.avaliar_livro(l1_db, avaliacao1));

    CHECK_NOTHROW(b1.EmprestaLivro(l1_db, u2_db));
    CHECK_NOTHROW(b1.DevolveLivro(l1_db, u2_db));
    float avaliacao2 = 3.0f;
    CHECK_NOTHROW(u2.avaliar_livro(l1_db, avaliacao2));

    float avaliacao3 = 3.50f;
    float avaliacao = db_ac.consulta(
        l1_db.getId(),
        bbt_def::sql::id).back().getAvaliacao();

    CHECK(avaliacao == avaliacao3);
}

TEST_CASE("03 - Teste criando usuário") {
    reset_db();
    auto db_user = DbUsuarios();
    
    Usuario usuario_cpp("João", "senha123", "joao@example.com", 1, 0, {}, {});
    db_user.inserir_linha(usuario_cpp);

    auto usuario = db_user.consulta(
        usuario_cpp.getEmail(),
        bbt_def::sql::schema_usuarios::email).back();

    CHECK(usuario.getNome() == "João");
    CHECK(usuario.getSenha() == "senha123");
    CHECK(usuario.getEmail() == "joao@example.com");
    CHECK(usuario.getqntdlivros() == 0);
}

TEST_CASE("04 - Teste criando livros") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f,  0);
    CHECK(livro.getTitulo() == "Livro 1");
    CHECK(livro.getAutor() == "Autor 1");
    CHECK(livro.getGenero() == "Gênero 1");
    CHECK(livro.getResumo() == "Resumo 1");
    CHECK(livro.getIdioma() == "Idioma 1");
    CHECK(livro.getNumPaginas() == 200);
    CHECK(livro.getAno() == 2021);
    CHECK(livro.getAvaliacao() == 4.5f);
    CHECK(livro.getId() == 1);
    CHECK(livro.getEstado() == 0);

    Livro livro2("Livro 2", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 200, 2021, 4.5f,  0);
    CHECK(livro2.getTitulo() == "Livro 2");
    CHECK(livro2.getAutor() == "Autor 2");
    CHECK(livro2.getGenero() == "Gênero 2");
    CHECK(livro2.getResumo() == "Resumo 2");
    CHECK(livro2.getIdioma() == "Idioma 2");
    CHECK(livro2.getNumPaginas() == 200);
    CHECK(livro2.getAno() == 2021);
    CHECK(livro2.getAvaliacao() == 4.5f);
    CHECK(livro2.getId() == 2);
    CHECK(livro2.getEstado() == 0);
}

TEST_CASE("05 - Teste pegar livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    usuario.pegar_livro(livro1);
    CHECK(usuario.getqntdlivros() == 1);
}

TEST_CASE("06 - Teste devolver livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    usuario.devolver_livro(livro1);
    CHECK(usuario.getqntdlivros() == 0);
}

TEST_CASE("07 - Teste Avaliar livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 0);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 4.2f;
    usuario.avaliar_livro(livro15, avaliacao);
    CHECK(livro15.getAvaliacao() == 4.2f);
}

TEST_CASE("08 - Teste de pegar e devolver múltiplos livros") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    Livro livro3("Livro 3", "Autor 3", "Gênero 3", "Resumo 3", "Idioma 3", 300, 2018, 3.5f, 0);

    usuario.pegar_livro(livro1);
    usuario.pegar_livro(livro3);

    CHECK(usuario.getqntdlivros() == 2);

    usuario.devolver_livro(livro1);

    CHECK(usuario.getqntdlivros() == 1);

    usuario.devolver_livro(livro3);

    CHECK(usuario.getqntdlivros() == 0);
}

TEST_CASE("09 - Teste de adicionar livros com nota inválida") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 0);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 6.0f;

    CHECK_THROWS_AS(usuario.avaliar_livro(livro15, avaliacao), AvaliacaoInvalida);
}