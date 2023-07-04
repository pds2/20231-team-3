#include "../include/bibliotecario.hpp"
#include "../include/usuario.hpp"
#include "db_acervo.hpp"
#include "db_usuarios.hpp"

#include <ctime>

Bibliotecario::Bibliotecario(const std::string nome,
                             const std::string senha,
                             const std::string email,
                             int id
) : Entidadebase(nome, senha, email, id) {}

bool Bibliotecario::EstaDisponivel(Livro& livro)
{
    /*
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
    */
    using namespace bbt_def;
    auto db = DbAcervo();
    auto ad_data = std::get<2>(db.consulta(livro.getId(), sql::id).back());
    
    if (ad_data.long_data.size() != 0)
        return false;
    return true;
}

void Bibliotecario::EmprestaLivro(Livro &livro, Usuario& user)
{
    /*
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
    */

    auto disponivel = EstaDisponivel(livro);

    if (!disponivel) throw std::invalid_argument("Livro não disponível");

    using namespace bbt_def::sql;
    auto db_users = DbUsuarios();
    auto db_acervo = DbAcervo();
    auto user_id = std::get<0>(db_users.consulta(user.getEmail(), schema_usuarios::email).back());

    db_acervo.sobrescrever_em_id(user_id, schema_acervo::posse_id, livro.getId());
}

std::string obterDataAtual()
{
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, 32, "%d/%m/%Y", ptm);
    return std::string(buffer);
}