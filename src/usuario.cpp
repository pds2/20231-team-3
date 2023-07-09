#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../include/livro.hpp"
#include "../include/usuario.hpp"

// TODO: Implementar

/**
 * @brief Classe responsavel por criar um Usuario
 */

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
        _numerodelivros = 3;
    }

void Usuario::pegar_livro(Livro &u)
{
    int tempnumberlivros = _numerodelivros;
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

void Usuario::avaliar_livro(Livro &u, float &avaliacaousuario) const
{
    using namespace bbt_def;
    auto db_acervo = DbAcervo();
    auto consulta = db_acervo.consulta(u.getTitulo(), sql::id);
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
    return _livrosPegos.size();
}

std::vector<Livro> Usuario::livros_alugados()
{
    using namespace bbt_def;
    auto db_acervo = DbAcervo();
    return db_acervo.consulta(
        this->getIdDb(), 
        sql::schema_acervo::posse_id);
}