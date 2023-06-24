#include <iostream>
#include "include/acervo.hpp"
#include "include/livro.hpp"
#include "include/adm.hpp"
#include "include/bibliotecario.hpp"
#include "include/usuario.hpp"
// #include "database_biblioteca.hpp"

int main()
{
    // DbtoolsBiblioteca db = DbtoolsBiblioteca();
    // db.criar_tabela("teste");

    Acervo acervo;

    Livro livro1("Livro 1", "Autor 1", "Gênero 1", "Resumo 1", "Idioma 1", 200, 2022, 0.0, 123);
    Livro livro2("Livro 2", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 125);
    Livro livro3("Livro 3", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 132);
    Livro livro4("Livro 3", "Autor 2", "Gênero 2", "Resumo 2", "Idioma 2", 150, 2021, 0.0, 133);

    Administrador adm("Admin", "senha123", "admin@example.com", 4);

    adm.InserirLivro(acervo, livro1);
    adm.InserirLivro(acervo, livro2);
    adm.InserirLivro(acervo, livro3);
    adm.InserirLivro(acervo, livro4);

    //Bibliotecario biblio("Biblio", "senha124", "biblio@example.com", 5);

    std::cout << "Acervo contém " << acervo.tamanho() << " livros." << std::endl;

    Livro livroEncontrado = acervo.buscar_livro(132);
    if (!livroEncontrado.getTitulo().empty())
    {
        std::cout << "Livro encontrado: " << livroEncontrado.getTitulo() << std::endl;
    }
    else
    {
        std::cout << "Livro não encontrado." << std::endl;
    }

    adm.RemoverLivro(acervo, livro2);

    std::cout << "Acervo contém " << acervo.tamanho() << " livros." << std::endl;

    livroEncontrado = acervo.buscar_livro(133);
    if (!livroEncontrado.getTitulo().empty())
    {
        std::cout << "Livro encontrado: " << livroEncontrado.getTitulo() << std::endl;
    }
    else
    {
        std::cout << "Livro não encontrado." << std::endl;
    }

    /*if (biblio.EstaDisponivel(livro1))
    {
        std::cout << "Livro disponível" << std::endl;
    }
    else
    {
        std::cout << "Livro não disponível" << std::endl;
    }*/

    livro4.setAvaliacao(5);
    livro4.setAvaliacao(4);
    livro4.setAvaliacao(5);
    // (5 + 4 + 3)/3 = 12/3 = 4
    std::cout << "Nota do livro: " << livro4.getAvaliacao() << std::endl;

    return 0;
}