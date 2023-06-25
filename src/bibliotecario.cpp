#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"

#include <ctime>

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha,
                             const std::string email,
                             int id
) : Entidadebase(nome, senha, email, id) {}

bool Bibliotecario::EstaDisponivel(Livro& livro, Acervo& acervo)
{
    // Verificar se o livro foi apagado do acervo
    Livro livroEncontrado = acervo.buscar_livro(livro.getId());
    if (livroEncontrado.getId() == 0)
    {
        return false;
    }

    // Verificar se o livro foi emprestado
    if (livro.getEstado())
    {
        return false;
    }

    // Se o livro não foi apagado nem emprestado, está disponível
    return true;
}

Livro Bibliotecario::EmprestaLivro(Livro &livro)
{
    Acervo acervo; // Criar uma instância do objeto Acervo (supondo que ele seja necessário)

    if (livro.getEstado())
    {
        //throw LivroJaEmprestado();
    }
    else
    {
        livro.setEstado(true);
    }

    // Retorno padrão (caso necessário)
    return livro; // Retorno de um objeto Livro padrão (pode ser necessário ajustar os argumentos do construtor conforme sua implementação)
}

std::string obterDataAtual()
{
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    return std::string(buffer);
}