#include "definicoes.hpp"
#include "db_acervo.hpp"
#include "db_usuarios.hpp"

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
        << obj.getAvaliacao()
        << nullptr << nullptr << nullptr;    
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
}

std::pair<Livro, AdtDataSQL> DbAcervo::_diretriz(
    sqlite::row_iterator::value_type linha_binder)
{
    std::unique_ptr<std::string> titulo, autor, genero, resumo, idioma, data_aluguel, data_devolucao;
    std::unique_ptr<unsigned int> numpag, ano, posse_id;
    std::unique_ptr<double> avaliacao;
    try
    {
        linha_binder
        >> titulo >> autor >> genero >> resumo
        >> idioma >> numpag >> ano >> avaliacao
        >> posse_id >> data_aluguel >> data_devolucao;

        auto temp_obj = Livro(*titulo, *autor, *genero, *resumo, *idioma, *numpag, *ano, *avaliacao);
        AdtDataSQL temp_adt_data;

        if(posse_id != nullptr) temp_adt_data.long_data.push_back(*posse_id);

        if(data_aluguel != nullptr) temp_adt_data.text_data.push_back(*data_aluguel);

        if(data_devolucao != nullptr) temp_adt_data.text_data.push_back(*data_devolucao);

        return {temp_obj, temp_adt_data};
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
    return {};
}