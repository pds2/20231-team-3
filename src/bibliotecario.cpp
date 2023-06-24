#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"

// passar valor id

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha, 
                             const std::string email,
                             unsigned int id = 3)
    : _nome(nome), _email(email), _id(id), _senha(senha) {}

bool Bibliotecario::EstaDisponivel(Livro &livro) {
    if (Acervo::buscar_livro(livro) == NULL)
    {
        throw busca_vazia();
    }
    return Acervo::buscar_livro(livro);
}

Livro Bibliotecario::EmprestaLivro(Livro& livro) {
    if (!Acervo::buscar_livro(livro)) {
        throw LivroNaoEncontradoException(); // Lança exceção se o livro não estiver disponível
    }

    if (livro.isEmprestado()) {
        throw LivroJaEmprestadoException(); // Lança exceção se o livro já estiver emprestado
    }

    // Realiza o empréstimo
    // livro.setEmprestado(true);
    // ponteiro pro acervo
    livro.setUsuarioEmprestimo(_id); // Define o usuário que pegou o livro (neste caso, o bibliotecário)
    livro.setDataEmprestimo(obterDataAtual()); // Define a data de empréstimo (implementação fictícia)

    return livro;
}