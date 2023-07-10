#include <fstream>

#include "../include/adm.hpp"
#include "../include/entidadebase.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_administradores.hpp"

Administrador::Administrador() : Entidadebase() {}

Administrador::Administrador(
    const std::string nome,
    const std::string senha,
    const std::string email,
    unsigned int id_db
) : Entidadebase(nome, senha, email, 4, id_db) {}

void Administrador::InserirLivro(Livro& livro)
{
   auto db = DbAcervo();
   db.inserir_linha(livro);
}

void Administrador::RemoverLivro(Livro& livro)
{
   auto db = DbAcervo();
   auto alugado = livro.getEstado();
   if(alugado) throw LivroAlugado();
   db.deletar_linha_id(livro.getId());
}

void Administrador::sign_in()
{
    auto db_adm = DbAdministradores();
    auto consulta = db_adm.consulta(
        this->getEmail(),
        bbt_def::sql::schema_administradores::email);
    
    if(consulta.size() != 0) throw EmailJaCadastrado();

    db_adm.inserir_linha(*this);
}

void Administrador::carregarLivros(std::string arq)
{
    std::fstream fin;
    fin.open(arq, std::ios::in);

    std::vector<std::string> linha;
    std::string linha_str, palavra;

    auto db_acervo = DbAcervo();

    while(std::getline(fin, linha_str))
    {
        linha.clear();

        std::stringstream s(linha_str);

        while(std::getline(s, palavra, ';'))
        {
            linha.push_back(palavra);
        }
        
        try
        {
            auto&& livro = Livro(
                linha.at(0),
                linha.at(1),
                linha.at(2),
                linha.at(3),
                linha.at(4),
                std::stoi(linha.at(5)),
                std::stoi(linha.at(6)),
                std::stoi(linha.at(7)));
            
            db_acervo.inserir_linha(livro);
        }
        catch(const std::exception& e)
        {
            throw LivrosNaoImportados();
        }
    }
}