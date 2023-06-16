#include "../include/acervo.hpp"

Livro Acervo::buscar_livro(std::string titulo) {
    auto it = acervo.find(titulo);  // Buscar o livro pelo título

    if (it != acervo.end())
    {
        Livro& livroEncontrado = it->second;
        // ponteiro para percorrer o mapa
    }
}