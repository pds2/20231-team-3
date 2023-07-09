#include <iostream>

#include "../third_party/doctest.h"
#include "../include/definicoes.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_usuarios.hpp"

TEST_CASE("teste de criação de banco de dados")
{
    remove(bbt_def::sql::NOME_DB.c_str());

    auto db_us = DbUsuarios();
    auto db_ac = DbAcervo();
}

TEST_CASE("teste de inserção de um livro")
{
    auto db_us = DbUsuarios();
    auto db_ac = DbAcervo();
    db_ac.del_linhas();
    auto livro1 = Livro("titulo1", "autor1", "genero1", "resumo1", "idioma1", 10, 2023, 5);
    auto livro2 = Livro("titulo2", "autor2", "genero2", "resumo2", "idioma2", 10, 2023, 5);

    db_ac.inserir_linha(livro1);
    db_ac.inserir_linha(livro2);

    auto livro1_consulta = db_ac.consulta("titulo1", bbt_def::sql::schema_acervo::titulo).back();

    auto livro2_consulta = db_ac.consulta("titulo2", bbt_def::sql::schema_acervo::titulo).back();

    CHECK_EQ(livro1.getTitulo(), livro1_consulta.getTitulo());
    CHECK_EQ(livro1.getAutor(), livro1_consulta.getAutor());
    CHECK_EQ(livro1.getGenero(), livro1_consulta.getGenero());
    CHECK_EQ(livro1.getResumo(), livro1_consulta.getResumo());
    CHECK_EQ(livro1.getIdioma(), livro1_consulta.getIdioma());
    CHECK_EQ(livro1.getNumPaginas(), livro1_consulta.getNumPaginas());
    CHECK_EQ(livro1.getAno(), livro1_consulta.getAno());
    CHECK_EQ(livro1.getAvaliacao(), livro1_consulta.getAvaliacao());

    CHECK_EQ(livro2.getTitulo(), livro2_consulta.getTitulo());
    CHECK_EQ(livro2.getAutor(), livro2_consulta.getAutor());
    CHECK_EQ(livro2.getGenero(), livro2_consulta.getGenero());
    CHECK_EQ(livro2.getResumo(), livro2_consulta.getResumo());
    CHECK_EQ(livro2.getIdioma(), livro2_consulta.getIdioma());
    CHECK_EQ(livro2.getNumPaginas(), livro2_consulta.getNumPaginas());
    CHECK_EQ(livro2.getAno(), livro2_consulta.getAno());
    CHECK_EQ(livro2.getAvaliacao(), livro2_consulta.getAvaliacao());
}

TEST_CASE("Teste de consulta")
{
    auto db_us = DbUsuarios();
    auto db_ac = DbAcervo();
    db_ac.del_linhas();

    auto livro1 = Livro("titulo1", "autor1", "genero1", "resumo1", "idioma1", 10, 2023, 5);
    auto livro2 = Livro("titulo2", "autor1", "genero2", "resumo2", "idioma2", 10, 2023, 5);

    db_ac.inserir_linha(livro1);
    db_ac.inserir_linha(livro2);

    auto autor_consulta = db_ac.consulta("autor1", bbt_def::sql::schema_acervo::autor);
    CHECK_EQ(2, autor_consulta.size());

    unsigned int id_livro_titulo1;
    for(auto livro : autor_consulta)
    {
        if(livro.getTitulo() == "titulo1") id_livro_titulo1 = livro.getId();
    }

    db_ac.sobrescrever_em_id(
        std::string("29/06/2023"),
        bbt_def::sql::schema_acervo::data_aluguel,
        id_livro_titulo1);
    
    auto data_livro_titulo1 = db_ac.consulta("29/06/2023", bbt_def::sql::schema_acervo::data_aluguel)
    .back()
    .getDataAluguel();
    
    CHECK_EQ("29/06/2023", data_livro_titulo1);
}

TEST_CASE("Teste da chave cruzada entre tabela usuários e tabela acervo")
{
    auto db_ac = DbAcervo();
    auto db_us = DbUsuarios();

    db_ac.del_linhas();
    db_us.del_linhas();

    auto livro1 = Livro("titulo1", "autor1", "genero1", "resumo1", "idioma1", 10, 2023, 5);
    auto livro2 = Livro("titulo2", "autor1", "genero2", "resumo2", "idioma2", 10, 2023, 5);
    
    auto user1 = Usuario("user1", "senha", "email1");
    auto user2 = Usuario("user2", "senha", "email2");
    auto user3 = Usuario("user3", "senha", "email3");

    db_us.inserir_linha(user1);
    db_us.inserir_linha(user2);
    db_us.inserir_linha(user3);

    db_ac.inserir_linha(livro1);
    db_ac.inserir_linha(livro2);

    auto id_livro1 = db_ac.consulta("titulo1", bbt_def::sql::schema_acervo::titulo)
    .back()
    .getId();

    auto id_user2 = db_us.consulta("user2", bbt_def::sql::schema_usuarios::nome)
    .back()
    .getId();

    db_ac.sobrescrever_em_id(id_user2, bbt_def::sql::schema_acervo::posse_id, id_livro1);

    auto id_posse_livro1 = db_ac.consulta("titulo1", bbt_def::sql::schema_acervo::titulo)
    .back()
    .getEstado();

    CHECK_EQ(id_posse_livro1, id_user2);

    db_us.deletar_linha_id(id_user2);

    auto livro1_posse = db_ac.consulta("titulo1", bbt_def::sql::schema_acervo::titulo)
    .back()
    .getEstado();

    CHECK_EQ(livro1_posse, 0);
}

TEST_CASE("teste de sobrescrita de linhas")
{
    auto db_ac = DbAcervo();
    db_ac.del_linhas();

    auto livro1 = Livro("titulo1", "autor1", "genero1", "resumo1", "idioma1", 10, 2020, 0.0);
    auto livro2 = Livro("titulo2", "autor1", "genero1", "resumo2", "idioma1", 10, 2020, 0.0);

    db_ac.inserir_linha(livro1);

    auto id_livro1 = db_ac.consulta("titulo1", bbt_def::sql::schema_acervo::titulo)
    .back()
    .getId();

    db_ac.sobrescrever_em_id(livro2, id_livro1);

    auto livro_subst = db_ac.consulta(id_livro1, bbt_def::sql::id).back();

    CHECK_EQ("titulo2", livro_subst.getTitulo());
}