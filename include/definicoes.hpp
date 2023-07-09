#ifndef BBT_DEFINICOES
#define BBT_DEFINICOES

#include <string>
#include <vector>
#include "../include/coluna_sql.hpp"
#include "../third_party/sqlite_modern_cpp.h"

namespace bbt_def
{
    const unsigned int max_livros_user = 3;
    
    namespace sql
    {
        const std::string id = "id";
        const std::string NOME_DB = "data/db_bbt.db";

        namespace schema_administradores
        {
            const std::string nome_tabela = "administradores";

            const std::string nome = "nome";
            const std::string email = "email";
            const std::string senha = "senha";
            const std::string id_categoria = "id_categoria";

            // definição das colunas: nome, tipo, unique, primary key, default null
            const std::vector<ColunaSQL> colunas =
            {
                ColunaSQL(id, "integer", "", "primary key", "not null"),
                ColunaSQL(nome, "text", "", "", "not null"),
                ColunaSQL(email, "text", "unique", "", "not null"),
                ColunaSQL(senha, "text", "", "", "not null"),
                ColunaSQL(id_categoria, "integer", "", "", "not null")
            };
        }

        namespace schema_usuarios
        {
            const std::string nome_tabela = "usuarios";

            const std::string nome = "nome";
            const std::string email = "email";
            const std::string senha = "senha";
            const std::string id_categoria = "id_categoria";
            const std::string n_livros = "n_livros";

            // definição das colunas: nome, tipo, unique, primary key, default null
            const std::vector<ColunaSQL> colunas =
            {
                ColunaSQL(id, "integer", "", "primary key", "not null"),
                ColunaSQL(nome, "text", "", "", "not null"),
                ColunaSQL(email, "text", "unique", "", "not null"),
                ColunaSQL(senha, "text", "", "", "not null"),
                ColunaSQL(id_categoria, "integer", "", "", "not null"),
                ColunaSQL(n_livros, "integer", "", "", "default null")
            };
        }

        namespace schema_acervo
        {
            const std::string nome_tabela = "acervo";

            const std::string titulo = "titulo";
            const std::string autor = "autor";
            const std::string genero = "genero";
            const std::string resumo = "resumo";
            const std::string idioma = "idioma";
            const std::string numpag = "numpag";
            const std::string ano = "ano";
            const std::string avaliacao = "avaliacao";
            const std::string posse_id = "posse_id";
            const std::string data_aluguel = "data_aluguel";
            const std::string data_devolucao = "data_devolucao";
            const std::string n_avaliacoes = "n_avaliacoes";

            const std::string clausula_adicional = 
            ", foreign key (" + posse_id +
            ") references " + schema_usuarios::nome_tabela +
            " (" + id + ") on update set null on delete set null";

            // definição das colunas: nome, tipo, unique, primary key, default null
            const std::vector<ColunaSQL> colunas =
            {
                ColunaSQL(id, "integer", "", "primary key", "not null"),
                ColunaSQL(titulo, "text", "", "", "not null"),
                ColunaSQL(autor, "text", "", "", "not null"),
                ColunaSQL(genero, "text", "", "", "not null"),
                ColunaSQL(resumo, "text", "", "", "not null"),
                ColunaSQL(idioma, "text", "", "", "not null"),
                ColunaSQL(numpag, "integer", "", "", "not null"),
                ColunaSQL(ano, "integer", "", "", "not null"),
                ColunaSQL(avaliacao, "real", "", "", "not null"),
                ColunaSQL(posse_id, "integer", "", "", "default null"),
                ColunaSQL(data_aluguel, "text", "", "", "default null"),
                ColunaSQL(data_devolucao, "text", "", "", "default null"),
                ColunaSQL(n_avaliacoes, "integer", "", "", "default null")
            };
        }
    }
}

#endif