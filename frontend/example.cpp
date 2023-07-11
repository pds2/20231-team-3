//include c++

#include <iostream>
#include <vector>
#include <string>
#include <thread> // Inclua a biblioteca thread


//include crow c++
#include <crow.h>
#include <fstream>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <streambuf>
#include <nlohmann/json.hpp>

//include acesso ao banco de dados

#include <sqlite3.h>


// Protótipo da função getLivros
void getLivros(const crow::request& req, crow::response& res);

int main() {
    crow::SimpleApp app;

    //abrir db
    int sqlite3_close(sqlite3*);

    const char *sqlite3_errmsg(sqlite3*);

    sqlite3 *db;
    int rc = sqlite3_open("20231-team-3/data/db_bbt.db", &db);

    if (rc) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::cout << "Banco de dados aberto com sucesso!" << std::endl;

    sqlite3_close(db);

    // Rota para servir o arquivo HTML
    CROW_ROUTE(app, "/")
        .name("index")
        ([]() {
        // Abre o arquivo HTML
        std::ifstream t("index.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);
        });


    // Rota para listar os livros
    CROW_ROUTE(app, "/api/livros")
        .name("api-livros")
        .methods("GET"_method)
        (getLivros);

    app.bindaddr("0.0.0.0").port(8080).multithreaded().run();

    return 0;
}

// Função para acessar o banco de dados e recuperar os livros
void getLivros(const crow::request& req, crow::response& res) {
    sqlite3* db;
    int rc = sqlite3_open("db_bbt.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        res.code = 500;
        res.end();
        return;
    }

    sqlite3_stmt* stmt = nullptr;

    rc = sqlite3_prepare_v2(db, "SELECT * FROM livros;", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        res.code = 500;
        res.end();
        return;
    }

    std::string response = "<html><body><h1>Livros disponíveis:</h1><ul>";
    nlohmann::json responseJson = nlohmann::json::array();

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* titulo = sqlite3_column_text(stmt, 1);
        const unsigned char* autor = sqlite3_column_text(stmt, 2);

        nlohmann::json livro;
        livro["id"] = id;
        livro["titulo"] = std::string(reinterpret_cast<const char*>(titulo));
        livro["autor"] = std::string(reinterpret_cast<const char*>(autor));

        responseJson.push_back(livro);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    res.code = 200;
    res.set_header("Content-Type", "application/json");
    res.write(responseJson.dump());
    res.end();
}
