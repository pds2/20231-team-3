#include <iostream>
#include "../include/livro.hpp"
#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"

#include <iomanip>
#include <vector>

using namespace std;

// #include "database_biblioteca.hpp"

int main() {
    Usuario usuario("João", "123456", "joao@example.com", 1);
    Bibliotecario bibliotecario("Maria", "abcdef", "maria@example.com", 2);
    Administrador administrador("Admin", "admin123", "admin@example.com", 3);

    std::cout << "Bem-vindo à biblioteca virtual!\n";

    while (true) {
        std::cout << "\nEscolha uma opção:\n";
        std::cout << "1. Adicionar livro\n";
        std::cout << "2. Remover livro\n";
        std::cout << "3. Emprestar livro\n";
        std::cout << "4. Devolver livro\n";
        std::cout << "5. Sair\n";

        int opcao;
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                std::string titulo, autor, genero, resumo, idioma;
                unsigned int numPaginas, ano, id;
                float avaliacao;

                std::cout << "Digite o título do livro: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);

                std::cout << "Digite o autor do livro: ";
                std::getline(std::cin, autor);

                std::cout << "Digite o gênero do livro: ";
                std::getline(std::cin, genero);

                std::cout << "Digite o resumo do livro: ";
                std::getline(std::cin, resumo);

                std::cout << "Digite o idioma do livro: ";
                std::getline(std::cin, idioma);

                std::cout << "Digite o número de páginas do livro: ";
                std::cin >> numPaginas;

                std::cout << "Digite o ano de publicação do livro: ";
                std::cin >> ano;

                std::cout << "Digite a avaliação do livro: ";
                std::cin >> avaliacao;

                std::cout << "Digite o ID do livro: ";
                std::cin >> id;

                Livro livro(titulo, autor, genero, resumo, idioma, numPaginas, ano, avaliacao, id);
                administrador.InserirLivro(livro);

                std::cout << "Livro adicionado com sucesso!\n";
                break;
            }
            case 2: {
                unsigned int id;

                std::cout << "Digite o ID do livro a ser removido: ";
                std::cin >> id;

                Livro livroRemover = acervo.buscar_livro(id);
                administrador.RemoverLivro(livroRemover);

                std::cout << "Livro removido com sucesso!\n";
                break;
            }
            case 3: {
                unsigned int id;

                std::cout << "Digite o ID do livro a ser emprestado: ";
                std::cin >> id;

                Livro livroEmprestar = acervo.buscar_livro(id);
                if (bibliotecario.EstaDisponivel(livroEmprestar)) {
                    Livro livroEmprestado = bibliotecario.EmprestaLivro(livroEmprestar);
                    usuario.pegar_livro(livroEmprestado);
                    std::cout << "Livro emprestado com sucesso!\n";
                } else {
                    std::cout << "O livro não está disponível para empréstimo.\n";
                }
                break;
            }
            case 4: {
                unsigned int id;

                std::cout << "Digite o ID do livro a ser devolvido: ";
                std::cin >> id;

                Livro livroDevolver = acervo.buscar_livro(id);
                usuario.devolver_livro(livroDevolver);
                std::cout << "Livro devolvido com sucesso!\n";
                break;
            }
            case 5:
                std::cout << "Obrigado por utilizar a biblioteca virtual. Até logo!\n";
                return 0;
            default:
                std::cout << "Opção inválida. Por favor, tente novamente.\n";
                break;
        }
    }

    return 0;
}