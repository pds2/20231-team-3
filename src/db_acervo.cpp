#include "../include/definicoes.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_usuarios.hpp"

DbAcervo::DbAcervo() : BbtWrapperSQL(
    bbt_def::sql::schema_acervo::nome_tabela,
    bbt_def::sql::schema_acervo::colunas,
    bbt_def::sql::schema_acervo::clausula_adicional) {}

void DbAcervo::_diretriz(sqlite::database_binder& ps_binder, Livro obj)
{
    try
    {
        ps_binder
        << obj.getTitulo()
        << obj.getAutor()
        << obj.getGenero()
        << obj.getResumo()
        << obj.getIdioma()
        << obj.getNumPaginas()
        << obj.getAno()
        << obj.getAvaliacao();

        if(obj.getEstado() == 0) ps_binder << nullptr;
        else ps_binder << obj.getEstado();

        try
        {
            ps_binder << obj.getDataAluguel();
        }
        catch(const DataNaoSettada& e)
        {
            ps_binder << nullptr;
        }

        try
        {
            ps_binder << obj.getDataDevolucao();
        }
        catch(DataNaoSettada& e)
        {
            ps_binder << nullptr;
        }
           
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
}

Livro DbAcervo::_diretriz(
    sqlite::row_iterator::value_type linha_binder)
{
    std::unique_ptr<std::string> titulo, autor, genero, resumo, idioma, data_aluguel, data_devolucao;
    std::unique_ptr<unsigned int> numpag, ano, id, posse_id, n_avaliacoes;
    std::unique_ptr<double> avaliacao;
    try
    {
        linha_binder >> id
        >> titulo >> autor >> genero >> resumo
        >> idioma >> numpag >> ano >> avaliacao
        >> posse_id >> data_aluguel >> data_devolucao >> n_avaliacoes;

        if(posse_id == nullptr) posse_id = std::make_unique<unsigned int>(0);
        if(n_avaliacoes == nullptr) n_avaliacoes = std::make_unique<unsigned int>(0);

        auto temp_obj = Livro
        (
            *titulo,
            *autor,
            *genero,
            *resumo,
            *idioma,
            *numpag,
            *ano,
            *avaliacao,
            *id,
            *posse_id,
            *n_avaliacoes
        );

        if(data_aluguel != nullptr) temp_obj.setDataAluguel(*data_aluguel);

        if(data_devolucao != nullptr) temp_obj.setDataDevolucao(*data_devolucao);

        return temp_obj;
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
    return Livro("","","","","",1,1,1);
}