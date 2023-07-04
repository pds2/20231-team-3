#include <iostream>
#include <fstream>
#include <string>
#include <crow.h>
#include <cstdlib>
#include <vector>
#include <boost/filesystem.hpp>
#include <streambuf>

int main() {
    crow::SimpleApp app;

    // Rota para servir o arquivo HTML
    CROW_ROUTE(app, "/")
        .name("index")
        ([]() {
        // Abre o arquivo HTML
        std::ifstream t("routes/index.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);
        });


    //conteúdo url sobre o projeto
    CROW_ROUTE(app,"/sobre")
        .name("sobre")
        ([]{
        // Abre o arquivo HTML
        std::ifstream t("routes/sobre.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo livro HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);        
        });

    //conteúdo url de ação
    CROW_ROUTE(app,"/categoria/acao")
        .name("categoria/acao")
        ([]{
            // Abre o arquivo HTML
        std::ifstream t("routes/pag_acao.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo livro HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);
        });

    //conteúdo url de livros
    CROW_ROUTE(app, "/livros")
        .name("livros")
        ([]() {
        // Abre o arquivo HTML
        std::ifstream t("routes/pag_livro.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo livro HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);
        });
    
    
    CROW_ROUTE(app, "/categoria/romance")
        .name("categoria/romance")
        ([]() {
        // Abre o arquivo HTML
        std::ifstream t("routes/pag_romance.html");
        if (!t.is_open()) {
        // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
        return crow::response(500, "Erro ao abrir o arquivo HTML");
        }

        // Lê o conteúdo do arquivo HTML em uma string
        std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

        // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
        return crow::response(html);
        });

    CROW_ROUTE(app, "/categoria/suspense")
        .name("categoria/suspense")
            ([]() {
            // Abre o arquivo HTML
            std::ifstream t("routes/pag_suspense.html");
            if (!t.is_open()) {
            // Se ocorrer algum erro ao abrir o arquivo, retorne uma resposta de erro
            return crow::response(500, "Erro ao abrir o arquivo HTML");
            }

            // Lê o conteúdo do arquivo HTML em uma string
            std::string html((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

            // Retorna o conteúdo do arquivo HTML como uma resposta HTTP com o tipo de conteúdo correto
            return crow::response(html);
            });


    app.port(18080).multithreaded().run();

    return 0;
}