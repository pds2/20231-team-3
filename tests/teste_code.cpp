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
#include <stdexcept>

std::string obterDataAtual(); // Declaração antecipada da função

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

 /*TEST_CASE("02 - Testando empréstimo de livro") {
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
    
    try {
        b1.EmprestaLivro(l1_db, u1_db);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em b1.EmprestaLivro(u1_db): " << ex.what() << std::endl;
        throw;
    }

    try {
        b1.DevolveLivro(l1_db, u1_db);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em b1.DevolveLivro(u1_db): " << ex.what() << std::endl;
        throw;
    }

    float avaliacao1 = 4.0f;
    try {
        u1.avaliar_livro(l1_db, avaliacao1);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em u1.avaliar_livro(l1_db, avaliacao1): " << ex.what() << std::endl;
        throw;
    }

    try {
        b1.EmprestaLivro(l1_db, u2_db);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em b1.EmprestaLivro(u2_db): " << ex.what() << std::endl;
        throw;
    }

    try {
        b1.DevolveLivro(l1_db, u2_db);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em b1.DevolveLivro(u2_db): " << ex.what() << std::endl;
        throw;
    }

    float avaliacao2 = 3.0f;
    try {
        u2.avaliar_livro(l1_db, avaliacao2);
    } catch (const std::exception& ex) {
        std::cout << "Exceção lançada em u2.avaliar_livro(l1_db, avaliacao2): " << ex.what() << std::endl;
        throw;
    }

    float avaliacao3 = 3.50f;
    float avaliacao = db_ac.consulta(
        l1_db.getId(),
        bbt_def::sql::id).back().getAvaliacao();

    CHECK(avaliacao == avaliacao3);
}*/ 

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
    //CHECK(livro.getId() == 1);
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
    //CHECK(livro2.getId() == 2);
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
    Administrador administrador("Joaquim", "senha321", "joaquim@example.com", 2);
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 0);
    administrador.InserirLivro(livro15);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 4.2f;
    usuario.avaliar_livro(livro15, avaliacao);
    auto consulta = usuario.consultaLivros(
        livro15.getTitulo(),
        bbt_def::sql::schema_acervo::titulo);

    Livro* livro_consulta;
    for(auto& livro : consulta)
    {
        if(livro15.getAutor() == livro.getAutor())
        {
            livro_consulta = &livro;
            break;
        }
    }

    CHECK(livro_consulta->getAvaliacao() == 4.2f);
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
    Administrador administrador("Joaquim", "senha321", "joaquim@example.com", 2);
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 0);
    administrador.InserirLivro(livro15);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 6.0f;

    CHECK_THROWS_AS(usuario.avaliar_livro(livro15, avaliacao), const AvaliacaoInvalida&);
}

/*TEST_CASE("09 - Teste de adicionar livros com nota inválida") {
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Administrador administrador("Joaquim", "senha321", "joaquim@example.com", 2);
    Livro livro15("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 0, 0);
    administrador.InserirLivro(livro15);
    usuario.pegar_livro(livro15);
    usuario.devolver_livro(livro15);
    float avaliacao = 6.0f;

    CHECK_THROWS_AS(usuario.avaliar_livro(livro15, avaliacao), AvaliacaoInvalida);
    CHECK_THROWS_WITH(
        usuario.avaliar_livro(livro15, avaliacao),
        "Nota deve ser entre 0 e 5"
    );
}*/


TEST_CASE("10 - Testa nome de Usuario"){
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});

    CHECK(usuario.getNome() == "João");
}

/*TEST_CASE("11 - Testa campos deixados em branco no preenchimento do Livro"){
    SUBCASE("Titulo não preenchido"){
        CHECK_THROWS_AS(Livro(" ", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(
            Livro(" ", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0),
            "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Autor não preenchido"){
        CHECK_THROWS_AS(Livro("Titulo 1", " ", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(
            Livro("Titulo 1", " ", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0),
            "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Genero não preenchido"){
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", " ", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(
            Livro("Titulo 1", "Autor 1", " ", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0),
            "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Resumo não preenchido"){
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", "Gênero 1", " ", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(
            Livro("Titulo 1", "Autor 1", "Gênero 1", " ", "Idioma 1", 200, 2021, 4.5f, 0),
            "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Idioma não preenchido"){
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", "Gênero 1", "Resumo 1", " ", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(
            Livro("Titulo 1", "Autor 1", "Gênero 1", "Resumo 1", " ", 200, 2021, 4.5f, 0),
            "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
}*/

TEST_CASE("11 - Testa campos deixados em branco no preenchimento do Livro") {
    SUBCASE("Titulo não preenchido") {
        CHECK_THROWS_AS(Livro("", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(Livro("", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), "Todos os campos precisam ser preenchidos para prosseguir");
    }

    SUBCASE("Autor não preenchido") {
        CHECK_THROWS_AS(Livro("Titulo 1", "", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(Livro("Titulo 1", "", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), "Todos os campos precisam ser preenchidos para prosseguir");
    }

    SUBCASE("Genero não preenchido") {
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", "", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(Livro("Titulo 1", "Autor 1", "", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0), "Todos os campos precisam ser preenchidos para prosseguir");
    }

    SUBCASE("Resumo não preenchido") {
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", "Gênero 1", "", "Idioma 1", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(Livro("Titulo 1", "Autor 1", "Gênero 1", "", "Idioma 1", 200, 2021, 4.5f, 0), "Todos os campos precisam ser preenchidos para prosseguir");
    }

    SUBCASE("Idioma não preenchido") {
        CHECK_THROWS_AS(Livro("Titulo 1", "Autor 1", "Gênero 1", "Resumo 1", "", 200, 2021, 4.5f, 0), std::invalid_argument);
        CHECK_THROWS_WITH(Livro("Titulo 1", "Autor 1", "Gênero 1", "Resumo 1", "", 200, 2021, 4.5f, 0), "Todos os campos precisam ser preenchidos para prosseguir");
    }
}


TEST_CASE("12 - Testa Campos deixados em branco no preenchimento do Usuario"){
    SUBCASE("Nome não preenchido"){
    CHECK_THROWS_AS(Usuario("", "senha123", "joao@example.com", 1, {}, {}), std::invalid_argument);
    CHECK_THROWS_WITH(
        Usuario("", "senha123", "joao@example.com", 1, {}, {}),
        "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Senha não preenchida"){
    CHECK_THROWS_AS(Usuario("João", "", "joao@example.com", 1, {}, {}), std::invalid_argument);
    CHECK_THROWS_WITH(
        Usuario("João", "", "joao@example.com", 1, {}, {}),
        "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
    SUBCASE("Email não preenchido"){
    CHECK_THROWS_AS(Usuario("João", "senha123", "", 1, {}, {}), std::invalid_argument);
    CHECK_THROWS_WITH(
        Usuario("João", "senha123", "", 1, {}, {}),
        "Todos os campos precisam ser preenchidos para prosseguir"
        );
    }
}

TEST_CASE("13 - Teste de disponibilidade de livro") {
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    Livro livro2("Livro 2", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 300, 2022, 3.5f, 1);

    Bibliotecario bibliotecario("João", "senha123", "joao@example.com", 1);

    CHECK(bibliotecario.EstaDisponivel(livro1) == true);  // Livro não emprestado
    CHECK(bibliotecario.EstaDisponivel(livro2) == false); // Livro emprestado
}

/* TEST_CASE("14 - Teste da função obterDataAtual") {
    // Verificar se a data retornada é válida, considerando o formato "dd/mm/aaaa"
    std::string dataAtual = obterDataAtual();
    CHECK(dataAtual.length() == 10);
    CHECK(dataAtual[2] == '/');
    CHECK(dataAtual[5] == '/');
    CHECK(dataAtual[0] >= '0' && dataAtual[0] <= '3');
    CHECK(dataAtual[1] >= '0' && dataAtual[1] <= '9');
    CHECK(dataAtual[3] >= '0' && dataAtual[3] <= '1');
    CHECK(dataAtual[4] >= '0' && dataAtual[4] <= '9');
    CHECK(dataAtual[6] >= '0' && dataAtual[6] <= '9');
    CHECK(dataAtual[7] >= '0' && dataAtual[7] <= '9');
    CHECK(dataAtual[8] >= '0' && dataAtual[8] <= '9');
    CHECK(dataAtual[9] >= '0' && dataAtual[9] <= '9');
} */

/* TEST_CASE("15 - Teste de empréstimo de livro com livro não disponível") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1);
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});

    Bibliotecario bibliotecario("Ana", "senha789", "ana@example.com", 2);

    CHECK_THROWS_AS(bibliotecario.EmprestaLivro(livro, usuario), std::invalid_argument); // Livro não disponível
    CHECK(usuario.getLivrosPegos().size() == 0); // Verificar se o livro não foi adicionado à lista de livros pegos pelo usuário
} */

TEST_CASE("15 - Teste de empréstimo de livro com livro não disponível") {
    reset_db();

    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1);
    Usuario usuario("João", "senha123", "joao@example.com", 1, {}, {});
    Bibliotecario bibliotecario("Ana", "senha789", "ana@example.com", 2);

    auto db_ac = DbAcervo();
    auto db_user = DbUsuarios();
    db_ac.inserir_linha(livro);
    db_user.inserir_linha(usuario);

    CHECK_THROWS_AS(bibliotecario.EmprestaLivro(livro, usuario), std::invalid_argument); // Livro não disponível
    CHECK(usuario.getqntdlivros() == 0); // Verificar se o livro não foi adicionado à lista de livros pegos pelo usuário
}

TEST_CASE("16 - Teste de disponibilidade de livro com livro excluído") {
    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    Livro livro2("Livro 2", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 300, 2022, 3.5f, 1);

    Bibliotecario bibliotecario("João", "senha123", "joao@example.com", 1);

    CHECK(bibliotecario.EstaDisponivel(livro1) == true);  // Livro não excluído
    CHECK(bibliotecario.EstaDisponivel(livro2) == false); // Livro excluído
}

TEST_CASE("17 - Teste de remoção de livro inexistente") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 0);
    Administrador administrador("João", "senha123", "joao@example.com", 1);

    // Verificar se não há exceções ao tentar remover um livro inexistente
    CHECK_NOTHROW(administrador.RemoverLivro(livro));
}

TEST_CASE("18 - Teste de remoção de livro com livro emprestado") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, 1);
    Administrador administrador("João", "senha123", "joao@example.com", 1);

    // Adicionar o livro ao acervo antes de tentar removê-lo
    // Implemente a adição ao acervo de acordo com a sua implementação

    // Verificar se não há exceções ao tentar remover um livro emprestado
    CHECK_NOTHROW(administrador.RemoverLivro(livro));
}

TEST_CASE("19 - Teste de obtenção do título do livro") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, false);
    CHECK(livro.getTitulo() == "Livro 1");
}

TEST_CASE("20 - Teste de obtenção do autor do livro") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, false);
    CHECK(livro.getAutor() == "Autor 1");
}

TEST_CASE("21 - Teste de obtenção do gênero do livro") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, false);
    CHECK(livro.getGenero() == "Gênero 1");
}

TEST_CASE("22 - Teste de obtenção do resumo do livro") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, false);
    CHECK(livro.getResumo() == "Resumo 1");
}

TEST_CASE("23 - Teste de obtenção do idioma do livro") {
    Livro livro("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2021, 4.5f, false);
    CHECK(livro.getIdioma() == "Idioma 1");
}

//Testar construtor das demais classes