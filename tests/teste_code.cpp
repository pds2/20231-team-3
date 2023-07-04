#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../third_party/doctest.h"

#include "../include/acervo.hpp"
#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/entidadebase.hpp"
#include "../include/livro.hpp"
#include "../include/usuario.hpp"
// #include "usuariovip.hpp" - Não sabemos o que fazer com ela

#include <string>

/*TEST_CASE("01 - Testando o construtor sem parâmetros") {
    CHECK_NOTHROW(Acervo());
    CHECK_NOTHROW(Administrador());
    CHECK_NOTHROW(Bibliotecario());
    CHECK_NOTHROW(Entidadebase());
    CHECK_NOTHROW(Livro());
    CHECK_NOTHROW(Usuario());
}*/

TEST_CASE("02 - Testando empréstimo de livro") {
    std::vector<Livro> templivrosPegos;
    std::vector<Livro> templivrosAvaliados;
    Livro l1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2022, 0.0, 123, 0);
    Usuario u1("User", "40028922", "user@example.com", 1, templivrosPegos, templivrosAvaliados, 3);
    Usuario u2("User2", "40028922", "user2@example.com", 1, templivrosPegos, templivrosAvaliados, 3);
    
    CHECK_NOTHROW(u1.pegar_livro(l1));
    CHECK_NOTHROW(u1.devolver_livro(l1));
    float avaliacao1 = 4.0f;
    CHECK_NOTHROW(u1.avaliar_livro(l1, avaliacao1));

    CHECK_NOTHROW(u2.pegar_livro(l1));
    CHECK_NOTHROW(u2.devolver_livro(l1));
    float avaliacao2 = 3.0f;
    CHECK_NOTHROW(u2.avaliar_livro(l1, avaliacao2));

    float avaliacao3 = 3.50f;
    float avaliacao = l1.getAvaliacao();
    CHECK(avaliacao == avaliacao3);
}

TEST_CASE("03 - Teste criando usuário") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {}, 0);
    CHECK(usuario.getNome() == "João");
    CHECK(usuario.getSenha() == "senha123");
    CHECK(usuario.getEmail() == "joao@example.com");
    CHECK(usuario.getId() == 1);
    CHECK(usuario.getqntdlivros() == 0);
}

TEST_CASE("04 - Teste criando livros") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1,  0);
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
}

TEST_CASE("05 - Teste pegar livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {}, 0);
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1,  0);
    usuario.pegar_livro(livro1);
    CHECK(usuario.getqntdlivros() == 1);
    CHECK(usuario.getqntdlivros() == 1);
}

TEST_CASE("06 - Teste devolver livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {}, 0);
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1,  0);
    usuario.devolver_livro(livro1);
    CHECK(usuario.getqntdlivros() == 0);
}

TEST_CASE("07 - Teste Avaliar livro") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {}, 0);
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 2,  0);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 4.2f;
    usuario.avaliar_livro(livro15, avaliacao);
    CHECK(livro15.getAvaliacao() == 4.2f);
}

TEST_CASE("08 - Teste de pegar e devolver múltiplos livros") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {}, 0);
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1,  0);
    Livro livro3("Livro 3", "Autor 3", "Gênero 3", "Resumo 3", "Idioma 3", 300, 2018, 3.5f, 2,  0);

    usuario.pegar_livro(livro1);
    usuario.pegar_livro(livro3);

    CHECK(usuario.getqntdlivros() == 2);

    usuario.devolver_livro(livro1);

    CHECK(usuario.getqntdlivros() == 1);

    usuario.devolver_livro(livro3);

    CHECK(usuario.getqntdlivros() == 0);
}