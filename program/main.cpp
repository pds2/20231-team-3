#include <iostream>

#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/coluna_sql.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_administradores.hpp"
#include "../include/db_usuarios.hpp"
#include "../include/usuario.hpp"
#include "../include/entidadebase.hpp"
#include "../include/livro.hpp"

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
    std::cout << "4. Buscar livro" << std::endl;
    std::cout << "5. Listar livros" << std::endl;
    std::cout << "6. Voltar ao menu principal" << std::endl;
}

void exibirMenuAdministrador()
{
    std::cout << "========== Menu do Administrador ==========" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Inserir livro" << std::endl;
    std::cout << "2. Remover livro" << std::endl;
    std::cout << "3. Listar livros" << std::endl;
    std::cout << "4. Voltar ao menu principal" << std::endl;
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
    
    std::string titulo;
    std::cout << "Digite o título do livro que deseja pegar emprestado: ";
    std::getline(std::cin, titulo);

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

    std::string titulo;
    std::cout << "Digite o título do livro que deseja devolver: ";
    std::getline(std::cin, titulo);

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

    std::string titulo;
    std::cout << "Digite o título do livro que deseja avaliar: ";
    std::getline(std::cin, titulo);
    float avaliacao;
    std::cout << "Digite a sua avaliação (de 0 a 5): ";
    std::cin >> avaliacao;
    std::cin.ignore();

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

void buscarLivroUsuario()
{
    Livro livro;
    std::cout << "Opção selecionada: Buscar livro" << std::endl;

    std::string titulo;
    std::cout << "Digite o título do livro que deseja buscar: ";
    std::getline(std::cin, titulo);

    std::vector<Livro> livrosEncontrados;
    livrosEncontrados.push_back(livro);

    if (livrosEncontrados.empty()) {
        std::cout << "Nenhum livro encontrado com o título informado." << std::endl;
    } else {
        std::cout << "Livros encontrados:" << std::endl;
        for (const auto& livro : livrosEncontrados) {
            std::cout << "Título: " << livro.getTitulo() << std::endl;
            std::cout << "Autor: " << livro.getAutor() << std::endl;
            std::cout << "Gênero: " << livro.getGenero() << std::endl;
            std::cout << "Resumo: " << livro.getResumo() << std::endl;
            std::cout << "Idioma: " << livro.getIdioma() << std::endl;
            std::cout << "Número de páginas: " << livro.getNumPaginas() << std::endl;
            std::cout << "Ano de publicação: " << livro.getAno() << std::endl;
            std::cout << "Avaliação: " << livro.getAvaliacao() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }
}

void listarLivros() {
    Livro livro;
    std::cout << "Opção selecionada: Listar livros" << std::endl;

    std::vector<Livro> todosLivros;
    todosLivros.push_back(livro);
    if (todosLivros.empty()) {
        std::cout << "Não há livros cadastrados." << std::endl;
    } else {
        std::cout << "Lista de livros:" << std::endl;
        for (const auto& livro : todosLivros) {
            std::cout << "Título: " << livro.getTitulo() << std::endl;
            std::cout << "Autor: " << livro.getAutor() << std::endl;
            std::cout << "Gênero: " << livro.getGenero() << std::endl;
            std::cout << "Resumo: " << livro.getResumo() << std::endl;
            std::cout << "Idioma: " << livro.getIdioma() << std::endl;
            std::cout << "Número de páginas: " << livro.getNumPaginas() << std::endl;
            std::cout << "Ano de publicação: " << livro.getAno() << std::endl;
            std::cout << "Avaliação: " << livro.getAvaliacao() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }
}

void inserirLivro() {
    std::cout << "Opção selecionada: Inserir livro" << std::endl;

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

    Livro livro(titulo, autor, genero, resumo, idioma, numPaginas, ano, avaliacao);
    administrador.InserirLivro(livro);
    std::cout << "Livro inserido com sucesso!" << std::endl;
}

void removerLivro() {
    std::cout << "Opção selecionada: Remover livro" << std::endl;

    std::string titulo;
    std::cout << "Digite o título do livro que deseja remover: ";
    std::getline(std::cin, titulo);

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

std::string titulo;
std::cout << "Digite o título do livro que deseja emprestar: ";
std::getline(std::cin, titulo);

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

std::string titulo;
std::cout << "Digite o título do livro que deseja devolver: ";
std::getline(std::cin, titulo);

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

std::string nome;
std::cout << "Digite o nome do usuário que deseja buscar: ";
std::getline(std::cin, nome);

try {
    Usuario usuario = bibliotecario.BuscaUsuario(usuario);
    std::cout << "Usuário encontrado: " << usuario.getNome() << std::endl;

} catch (const UsuarioNaoEncontrado& e) {
    std::cout << "Usuário não encontrado." << std::endl;
}

}

int main()
{
    std::cout << "                                          " << std::endl;
    std::cout << "          Sistema de Bibliotecas          " << std::endl;
    std::string asciiArt = R"(
       .--.                   .---.
   .---||           .-.     |~|
.--|===|--|          ||     |~|--.
|  |===|  |'\     .---!~|  .--|   |--|
|%%|   |  |.'\    |===| |--|%%|   |  |
|%%|   |  |.'\   |   | ||  |   |  |
|  |   |  | \  \  |===| |==|  |   |  |
|  |   ||  .'\ |   |_||  |~|__|
|  |===|--|   .'|===|~|--|%%|~|--|
^--^---'--^    -'---^-^--^--^---'--' )";

    std::cout << asciiArt << std::endl;

int opcao;
do
{
exibirMenuPrincipal();
opcao = obterOpcao();
 switch (opcao)
    {
        case 1: 
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
                        buscarLivroUsuario();
                        break;
                    case 5:
                        listarLivros();
                        break;
                    case 6:
                        std::cout << "Voltando ao menu principal..." << std::endl;
                        break;
                    default:
                        std::cout << "Opção inválida. Tente novamente." << std::endl;
                }
            } while (opcaoUsuario != 6);

            break;
        }
        case 2: 
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
                        listarLivros();
                        break;
                    case 4:
                        std::cout << "Voltando ao menu principal..." << std::endl;
                        break;
                    default:
                        std::cout << "Opção inválida. Tente novamente." << std::endl;
                }
            } while (opcaoAdmin != 4);

            break;
        }
        case 3:
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
