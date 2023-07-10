#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../include/livro.hpp"
#include "../include/usuario.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/db_usuarios.hpp"
#include "../include/db_acervo.hpp"

Usuario::Usuario() : Entidadebase("", "", "", bbt_def::id_usuario, 0), _n_livros_posse(0)
{
    _numerodelivros = bbt_def::max_livros_user;
}

Usuario::Usuario(const std::string nome,
                 const std::string senha,
                 const std::string email,
                 unsigned int id_db,
                 unsigned int n_livros,
                 std::vector<Livro> livrosPegos,
                 std::vector<Livro> livrosAvaliados)
    : Entidadebase(nome, senha, email, 1, id_db),
    _livrosPegos(livrosPegos),
    _livrosAvaliados(livrosAvaliados),
    _n_livros_posse(n_livros) {
        _numerodelivros = bbt_def::max_livros_user;
    }

void Usuario::pegar_livro(Livro &u)
{
    unsigned int tempnumberlivros = _numerodelivros;
    if (getqntdlivros() == tempnumberlivros)
    {
        throw MaximoLivros();
    }
    
    _numerodelivros--;
    _livrosPegos.push_back(u);
}

void Usuario::devolver_livro(Livro& u)
{
    bool livroEncontrado = false;

    // Percorrer o vetor _livrosPegos e procurar o livro desejado
    for (auto it = _livrosPegos.begin(); it != _livrosPegos.end(); ++it)
    {
        if (it->getId() == u.getId())
        {
            livroEncontrado = true;
            _numerodelivros++;
            _livrosPegos.erase(it);  // Remove o livro do vetor _livrosPegos
            break;  // Encerra o loop, já que o livro foi encontrado
        }
    }

    if (!livroEncontrado)
    {
        // Tratar o caso em que o livro não foi encontrado
        // Lançar uma exceção ou retornar um código de erro, por exemplo
    }
}

void Usuario::avaliar_livro(Livro &u, float avaliacaousuario)
{
    using namespace bbt_def;
    auto db_acervo = DbAcervo();
    auto consulta = db_acervo.consulta(
        u.getTitulo(),
        sql::schema_acervo::titulo);

    if(consulta.size() == 0) throw LivroIndisponivel();

    if(avaliacaousuario < 0 || avaliacaousuario > 5)
    {
        throw std::invalid_argument("Nota deve ser entre 0 e 5");
    }

    auto avaliacao_atual = consulta.back().getAvaliacao();
    auto qtd_atual = consulta.back().getQtdAvaliacoes();
    auto avaliacao_nova = (avaliacao_atual * qtd_atual + avaliacaousuario) / (qtd_atual + 1);

    for(auto& livro : consulta)
    {
        if(livro.getAutor() != u.getAutor()) continue;
        db_acervo.sobrescrever_em_id(
            avaliacao_nova,
            sql::schema_acervo::avaliacao,
            livro.getId());
        
        db_acervo.sobrescrever_em_id(
            qtd_atual + 1,
            sql::schema_acervo::n_avaliacoes,
            livro.getId());
    }
}

unsigned int Usuario::getqntdlivros()
{
    return _n_livros_posse;
}

std::vector<Livro> Usuario::livros_alugados()
{/*
    using namespace bbt_def;
    auto db_acervo = DbAcervo();
    return db_acervo.consulta(
        this->getIdDb(), 
        sql::schema_acervo::posse_id);*/
    return {};
}

unsigned int Usuario::get_max_livros()
{
    return _numerodelivros;
}

void Usuario::sign_in()
{
    auto db_user = DbUsuarios();
    auto consulta = db_user.consulta(
        this->getEmail(),
        bbt_def::sql::schema_usuarios::email);
    
    if(consulta.size() != 0) throw EmailJaCadastrado();

    db_user.inserir_linha(*this);
}