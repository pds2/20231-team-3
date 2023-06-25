#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"

#include <ctime>

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha,
                             const std::string email,
                             int id
) : Entidadebase(nome, senha, email, id) {}

bool Bibliotecario::EstaDisponivel(Livro &livro, Acervo &acervo)
{
    Livro livroEncontrado = acervo.buscar_livro(livro.getId());

    if (livroEncontrado.getId() == 0 || livroEncontrado.isEmprestado())
    {
        return false;
    }

    return true;
}

Livro Bibliotecario::EmprestaLivro(Livro &livro)
{
    Acervo acervo; // Criar uma instância do objeto Acervo

    Livro livroEncontrado = acervo.buscar_livro(livro.getId()); // Buscar o livro no acervo usando o ID

    if (livroEncontrado.getId() == 0) // Verificar se o livro foi encontrado no acervo
    {
        //throw LivroNaoEncontradoException(); // Lança exceção se o livro não estiver disponível
    }

    if (livroEncontrado.isEmprestado())
    {
        //throw LivroJaEmprestadoException(); // Lança exceção se o livro já estiver emprestado
    }

    // Realiza o empréstimo
    livroEncontrado.setEmprestado(true); // Define o status do empréstimo como verdadeiro

    return livroEncontrado;
}

std::string obterDataAtual()
{
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    return std::string(buffer);
}