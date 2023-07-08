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
                 std::vector<Livro> livrosPegos,
                 std::vector<Livro> livrosAvaliados)
    : Entidadebase(nome, senha, email, 1, id_db), _livrosPegos(livrosPegos), _livrosAvaliados(livrosAvaliados) {
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
    u.setAvaliacao(avaliacaousuario);
}
// calcular por media aritmética, fazendo uma soma dinâmica e contabilizando o número de avaliações para dividir depois

int Usuario::getqntdlivros()
{
    return _livrosPegos.size();
}