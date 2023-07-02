#include "doctest.h"

#include "acervo.hpp"
#include "adm.hpp"
#include "bibliotecario.hpp"
#include "entidadebase.hpp"
#include "livro.hpp"
#include "usuario.hpp"
// #include "usuariovip.hpp" - Não sabemos o que fazer com ela

#include <string>

TEST_CASE("01 - Testando o construtor sem parâmetros") {
    CHECK_NOTHROW(Acervo());
    CHECK_NOTHROW(Administrador());
    CHECK_NOTHROW(Bibliotecario());
    CHECK_NOTHROW(Entidadebase());
    CHECK_NOTHROW(Livro());
    CHECK_NOTHROW(Usuario());
}

TEST_CASE("02 - Testando empréstimo de livro") {
    Livro *l1 = new Livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2022, 0.0, 123, 0);
    Usuario *u1 = new Usuario("User", "40028922", "user@example.com", 1, templivrosPegos, templivrosAvaliados, 3);
    Usuario *u2 = new Usuario("User2", "40028922", "user2@example.com", 1, templivrosPegos, templivrosAvaliados, 3);
    
    // DestinationPackages pacotes;
    CHECK_NOTHROW(u1->pegar_livro(l1));
    CHECK_NOTHROW(u1->devolver_livro(l1));
    CHECK_NOTHROW(u1->avaliar_livro(l1, 4.0));

    CHECK_NOTHROW(u2->pegar_livro(l1));
    CHECK_NOTHROW(u2->devolver_livro(l1));
    CHECK_NOTHROW(u2->avaliar_livro(l1, 3.0));

    CHECK(l1->getAvaliacao == 3.50);
    
    delete l1;
    delete u1;
    delete u2;
}