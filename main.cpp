#include <iostream>
#include "include/acervo.hpp"
#include "include/livro.hpp"
#include "include/adm.hpp"
#include "include/bibliotecario.hpp"
#include "include/usuario.hpp"

#include <iomanip>
// #include "database_biblioteca.hpp"

int main()
{
    // DbtoolsBiblioteca db = DbtoolsBiblioteca();
    // db.criar_tabela("teste");

    Acervo acervo;

    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2022, 0.0, 123, 0);
    Livro livro2("Livro 2", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 125, 0);
    Livro livro3("Livro 3", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 132, 0);
    Livro livro4("Livro 3", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 133, 0);

    Administrador adm("Admin", "senha123", "admin@example.com", 4);

    adm.InserirLivro(acervo, livro1);
    adm.InserirLivro(acervo, livro2);
    adm.InserirLivro(acervo, livro3);
    adm.InserirLivro(acervo, livro4);

    Bibliotecario biblio("Biblio", "senha124", "biblio@example.com", 3);

    /*if (biblio.EstaDisponivel(livro1, acervo))
    {
        std::cout << "Livro disponível" << std::endl;
    }
    else
    {
        std::cout << "Livro não disponível" << std::endl;
    }*/

    std::vector<Livro> templivrosPegos;
    std::vector<Livro> templivrosAvaliados;
    std::vector<Livro> temp;
    // Preencha os vetores livrosPegos e livrosAvaliados com os livros desejados

    Usuario user("User", "40028922", "user@example.com", 1, templivrosPegos, templivrosAvaliados, 3);
    Usuario user2("User2", "40028922", "user2@example.com", 1, templivrosPegos, templivrosAvaliados, 3);

    std::cout << user.getqntdlivros() << std::endl;

    if (biblio.EstaDisponivel(livro1, acervo))
    {
        std::cout << "Livro disponível" << std::endl;
        user.pegar_livro(livro1);
    }
    else
    {
        std::cout << "Livro não disponível" << std::endl;
    }

    float a = 4.2;
    user.avaliar_livro(livro1, a);
    user.devolver_livro(livro1);

    if (biblio.EstaDisponivel(livro1, acervo))
    {
        std::cout << "Livro disponível" << std::endl;
        user2.pegar_livro(livro1);
    }
    else
    {
        std::cout << "Livro não disponível" << std::endl;
    }

    float b = 3.7;
    user2.avaliar_livro(livro1, b);
    user2.devolver_livro(livro1);

    std::cout << user.getqntdlivros() << std::endl;
    std::cout << user2.getqntdlivros() << std::endl;

    std::cout << livro1.getAvaliacao() << std::endl;

    return 0;
}