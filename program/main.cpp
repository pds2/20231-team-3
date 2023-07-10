#include <iostream>

#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_administradores.hpp"
#include "../include/db_usuarios.hpp"
#include "../include/usuario.hpp"

Usuario usuario;
Administrador administrador;
Bibliotecario bibliotecario;

void exibirMenuPrincipal()
{
    std::cout << "========== Menu Principal ==========" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Usuário" << std::endl;
    std::cout << "2. Administrador" << std::endl;
    std::cout << "3. Bibliotecário" << std::endl;
    std::cout << "4. Sair" << std::endl;
}

void exibirMenuUsuario()
{
    std::cout << "========== Menu do Usuário ==========" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Pegar livro emprestado" << std::endl;
    std::cout << "2. Devolver livro" << std::endl;
    std::cout << "3. Avaliar livro" << std::endl;
    std::cout << "4. Voltar ao menu principal" << std::endl;
}

void exibirMenuAdministrador()
{
    std::cout << "========== Menu do Administrador ==========" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Inserir livro" << std::endl;
    std::cout << "2. Remover livro" << std::endl;
    std::cout << "3. Voltar ao menu principal" << std::endl;
}

void exibirMenuBibliotecario()
{
    std::cout << "========== Menu do Bibliotecário ==========" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Emprestar livro" << std::endl;
    std::cout << "2. Devolver livro" << std::endl;
    std::cout << "3. Buscar usuário" << std::endl;
    std::cout << "4. Voltar ao menu principal" << std::endl;
}

int obterOpcao()
{
    int opcao;
    std::cout << "Digite sua opção: ";
    std::cin >> opcao;
    std::cin.ignore();
    return opcao;
}

void pegarLivroUsuario()
{
    std::cout << "Opção selecionada: Pegar livro emprestado" << std::endl;
    
    // Implemente a lógica para pegar um livro emprestado como usuário
    std::string titulo;
    std::cout << "Digite o título do livro que deseja pegar emprestado: ";
    std::getline(std::cin, titulo);

    // Realize a lógica para pegar o livro emprestado pelo usuário
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        usuario.pegar_livro(livro);
        std::cout << "Livro '" << titulo << "' foi emprestado com sucesso!" << std::endl;
    } catch (const MaximoLivros& e) {
        std::cout << "Você já atingiu o limite máximo de livros emprestados." << std::endl;
    } catch (const LivroIndisponivel& e) {
        std::cout << "O livro '" << titulo << "' não está disponível para empréstimo." << std::endl;
    }
}

void devolverLivroUsuario()
{
    std::cout << "Opção selecionada: Devolver livro" << std::endl;
    // Implemente a lógica para devolver um livro como usuário
    std::string titulo;
    std::cout << "Digite o título do livro que deseja devolver: ";
    std::getline(std::cin, titulo);

    // Realize a lógica para devolver o livro pelo usuário
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        usuario.devolver_livro(livro);
        std::cout << "Livro '" << titulo << "' foi devolvido com sucesso!" << std::endl;
    } catch (const LivroNaoEncontrado& e) {
        std::cout << "O livro '" << titulo << "' não foi encontrado nos livros emprestados." << std::endl;
    }
}

void avaliarLivroUsuario()
{
    std::cout << "Opção selecionada: Avaliar livro" << std::endl;
    // Implemente a lógica para avaliar um livro como usuário
    std::string titulo;
    std::cout << "Digite o título do livro que deseja avaliar: ";
    std::getline(std::cin, titulo);
    float avaliacao;
    std::cout << "Digite a sua avaliação (de 0 a 5): ";
    std::cin >> avaliacao;
    std::cin.ignore();

    // Realize a lógica para avaliar o livro pelo usuário
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        usuario.avaliar_livro(livro, avaliacao);
        std::cout << "Livro '" << titulo << "' foi avaliado com sucesso!" << std::endl;
    } catch (const LivroNaoEncontrado& e) {
        std::cout << "O livro '" << titulo << "' não foi encontrado." << std::endl;
    } catch (const AvaliacaoInvalida& e) {
        std::cout << "A avaliação deve estar entre 0 e 5." << std::endl;
    }
}

void inserirLivro()
{
    std::cout << "Opção selecionada: Inserir livro" << std::endl;
    // Implemente a lógica para inserir um livro como administrador
    std::string titulo, autor, genero, resumo, idioma;
    unsigned int numPaginas, ano;
    float avaliacao;

    std::cout << "Digite as informações do livro:" << std::endl;
    std::cout << "Título: ";
    std::getline(std::cin, titulo);
    std::cout << "Autor: ";
    std::getline(std::cin, autor);
    std::cout << "Gênero: ";
    std::getline(std::cin, genero);
    std::cout << "Resumo: ";
    std::getline(std::cin, resumo);
    std::cout << "Idioma: ";
    std::getline(std::cin, idioma);
    std::cout << "Número de páginas: ";
    std::cin >> numPaginas;
    std::cin.ignore();
    std::cout << "Ano de publicação: ";
    std::cin >> ano;
    std::cin.ignore();
    std::cout << "Avaliação média: ";
    std::cin >> avaliacao;
    std::cin.ignore();

    // Realize a lógica para inserir o livro pelo administrador
    Livro livro(titulo, autor, genero, resumo, idioma, numPaginas, ano, avaliacao);
    administrador.InserirLivro(livro);
    std::cout << "Livro inserido com sucesso!" << std::endl;
}

void removerLivro()
{
    std::cout << "Opção selecionada: Remover livro" << std::endl;
    // Implemente a lógica para remover um livro como administrador
    std::string titulo;
    std::cout << "Digite o título do livro que deseja remover: ";
    std::getline(std::cin, titulo);

    // Realize a lógica para remover o livro pelo administrador
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        administrador.RemoverLivro(livro);
        std::cout << "Livro '" << titulo << "' removido com sucesso!" << std::endl;
    } catch (const LivroNaoEncontrado& e) {
        std::cout << "O livro '" << titulo << "' não foi encontrado." << std::endl;
    } catch (const LivroAlugado& e) {
        std::cout << "O livro '" << titulo << "' está alugado e não pode ser removido." << std::endl;
    }
}

void emprestarLivro()
{
    std::cout << "Opção selecionada: Emprestar livro" << std::endl;
    // Implemente a lógica para emprestar um livro como bibliotecário
    std::string titulo;
    std::cout << "Digite o título do livro que deseja emprestar: ";
    std::getline(std::cin, titulo);

    // Realize a lógica para emprestar o livro pelo bibliotecário
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        bibliotecario.EmprestaLivro(livro, usuario);
        std::cout << "Livro '" << titulo << "' emprestado com sucesso!" << std::endl;
    } catch (const LivroNaoEncontrado& e) {
    std::cout << "O livro '" << titulo << "' não foi encontrado." << std::endl;
    } catch (const LivroIndisponivel& e) {
        std::cout << "O livro '" << titulo << "' não está disponível para empréstimo." << std::endl;
    } catch (const UsuarioNaoEncontrado& e) {
        std::cout << "O usuário não foi encontrado." << std::endl;
    }
}

void devolverLivroBibliotecario()
{
    std::cout << "Opção selecionada: Devolver livro" << std::endl;
    // Implemente a lógica para devolver um livro como bibliotecário
    std::string titulo;
    std::cout << "Digite o título do livro que deseja devolver: ";
    std::getline(std::cin, titulo);

    // Realize a lógica para devolver o livro pelo bibliotecário
    Livro livro(titulo, "", "", "", "", 0, 0, 0.0);
    try {
        bibliotecario.DevolveLivro(livro, usuario);
        std::cout << "Livro '" << titulo << "' devolvido com sucesso!" << std::endl;
    } catch (const LivroNaoEncontrado& e) {
        std::cout << "O livro '" << titulo << "' não foi encontrado." << std::endl;
    } catch (const LivroNaoEmprestado& e) {
        std::cout << "O livro '" << titulo << "' não está emprestado." << std::endl;
    }
}

void buscarUsuario()
{
    std::cout << "Opção selecionada: Buscar usuário" << std::endl;
    // Implemente a lógica para buscar um usuário como bibliotecário
    std::string nome;
    std::cout << "Digite o nome do usuário que deseja buscar: ";
    std::getline(std::cin, nome);

    // Realize a lógica para buscar o usuário pelo bibliotecário
    try {
        Usuario usuario = bibliotecario.BuscaUsuario(usuario);
        std::cout << "Usuário encontrado: " << usuario.getNome() << std::endl;
        // Exiba as informações do usuário, se necessário
    } catch (const UsuarioNaoEncontrado& e) {
        std::cout << "Usuário não encontrado." << std::endl;
    }
}

int main()
{
    int opcao;
    do
    {
        exibirMenuPrincipal();
        opcao = obterOpcao();

        switch (opcao)
        {
            case 1: // Usuário
            {
                int opcaoUsuario;
                do
                {
                    exibirMenuUsuario();
                    opcaoUsuario = obterOpcao();

                    switch (opcaoUsuario)
                    {
                        case 1:
                            pegarLivroUsuario();
                            break;
                        case 2:
                            devolverLivroUsuario();
                            break;
                        case 3:
                            avaliarLivroUsuario();
                            break;
                        case 4:
                            std::cout << "Voltando ao menu principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opção inválida. Tente novamente." << std::endl;
                    }
                } while (opcaoUsuario != 4);

                break;
            }
            case 2: // Administrador
            {
                int opcaoAdmin;
                do
                {
                    exibirMenuAdministrador();
                    opcaoAdmin = obterOpcao();

                    switch (opcaoAdmin)
                    {
                        case 1:
                            inserirLivro();
                            break;
                        case 2:
                            removerLivro();
                            break;
                        case 3:
                            std::cout << "Voltando ao menu principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opção inválida. Tente novamente." << std::endl;
                    }
                } while (opcaoAdmin != 3);

                break;
            }
            case 3: // Bibliotecário
            {
                int opcaoBibliotecario;
                do
                {
                    exibirMenuBibliotecario();
                    opcaoBibliotecario = obterOpcao();

                    switch (opcaoBibliotecario)
                    {
                        case 1:
                            emprestarLivro();
                            break;
                        case 2:
                            devolverLivroBibliotecario();
                            break;
                        case 3:
                            buscarUsuario();
                            break;
                        case 4:
                            std::cout << "Voltando ao menu principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opção inválida. Tente novamente." << std::endl;
                    }
                } while (opcaoBibliotecario != 4);

                break;
            }
            case 4:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opcao != 4);

    return 0;
}

// // Função para exibir o menu principal
// void exibirMenu()
// {
//     std::cout << "Bem-vindo! Escolha uma opção:" << std::endl;
//     std::cout << "1. Pegar livro" << std::endl;
//     std::cout << "2. Devolver livro" << std::endl;
//     std::cout << "3. Avaliar livro" << std::endl;
//     std::cout << "4. Sair" << std::endl;
// }

// // Função para obter a opção escolhida pelo usuário
// int obterOpcao()
// {
//     int opcao;
//     std::cin >> opcao;
//     std::cin.ignore(); // Ignorar o caractere de nova linha no buffer

//     return opcao;
// }

// // Função para pegar um livro
// void pegarLivro(Usuario& usuario)
// {
//     std::string titulo;
//     std::cout << "Digite o título do livro que deseja pegar: ";
//     std::getline(std::cin, titulo);

//     try
//     {
//         Livro livro(titulo, "", "", "", "", 0, 0, 0.0f, 0);
//         usuario.pegar_livro(livro);
//         std::cout << "Livro \"" << livro.getTitulo() << "\" pego com sucesso!" << std::endl;
//     }
//     catch (const LivroIndisponivel& e)
//     {
//         std::cout << "O livro está indisponível no momento." << std::endl;
//     }
//     catch (const MaximoLivros& e)
//     {
//         std::cout << "Você atingiu o número máximo de livros permitidos." << std::endl;
//     }
// }

// // Função para devolver um livro
// void devolverLivro(Usuario& usuario)
// {
//     std::string titulo;
//     std::cout << "Digite o título do livro que deseja devolver: ";
//     std::getline(std::cin, titulo);

//     try
//     {
//         Livro livro(titulo, "", "", "", "", 0, 0, 0.0f, 0);
//         usuario.devolver_livro(livro);
//         std::cout << "Livro \"" << livro.getTitulo() << "\" devolvido com sucesso!" << std::endl;
//     }
//     catch (const LivroIndisponivel& e)
//     {
//         std::cout << "O livro não foi encontrado." << std::endl;
//     }
// }

// // Função para avaliar um livro
// void avaliarLivro(Usuario& usuario)
// {
//     std::string titulo;
//     float avaliacao;
//     std::cout << "Digite o título do livro que deseja avaliar: ";
//     std::getline(std::cin, titulo);

//     std::cout << "Digite a sua avaliação (de 0 a 5): ";
//     std::cin >> avaliacao;
//     std::cin.ignore(); // Ignorar o caractere de nova linha no buffer

//     try
//     {
//         Livro livro(titulo, "", "", "", "", 0, 0, 0.0f, 0);
//         usuario.avaliar_livro(livro, avaliacao);
//         std::cout << "Livro \"" << livro.getTitulo() << "\" avaliado com sucesso!" << std::endl;
//     }
//     catch (const LivroIndisponivel& e)
//     {
//         std::cout << "O livro não foi encontrado." << std::endl;
//     }
//     catch (const std::invalid_argument& e)
//     {
//         std::cout << "Avaliação inválida. A nota deve ser entre 0 e 5." << std::endl;
//     }
// }

// int main()
// {
//     std::string nome;
//     std::string senha;
//     std::string email;

//     std::cout << "Digite seu nome: ";
//     std::getline(std::cin, nome);

//     std::cout << "Digite sua senha: ";
//     std::getline(std::cin, senha);

//     std::cout << "Digite seu email: ";
//     std::getline(std::cin, email);

//     try
//     {
//         Usuario usuario(nome, senha, email);
//         usuario.sign_in();

//         int opcao;
//         do
//         {
//             exibirMenu();
//             opcao = obterOpcao();

//             switch (opcao)
//             {
//                 case 1:
//                     pegarLivro(usuario);
//                     break;
//                 case 2:
//                     devolverLivro(usuario);
//                     break;
//                 case 3:
//                     avaliarLivro(usuario);
//                     break;
//                 case 4:
//                     std::cout << "Saindo..." << std::endl;
//                     break;
//                 default:
//                     std::cout << "Opção inválida. Tente novamente." << std::endl;
//             }
//         } while (opcao != 4);
//     }
//     catch (const EmailJaCadastrado& e)
//     {
//         std::cout << "O email já está cadastrado. Por favor, tente novamente com outro email." << std::endl;
//     }

//     return 0;
// }