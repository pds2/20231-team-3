#include <regex>

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

        if(data_aluguel != nullptr) temp_obj.setDataAluguel(data_sql_para_padrao(*data_aluguel));

        if(data_devolucao != nullptr) temp_obj.setDataDevolucao(data_sql_para_padrao(*data_devolucao));

        return temp_obj;
    }
    catch(const std::exception& e)
    {
        _sql_excecao(std::current_exception());
    }
    return Livro();
}

std::string DbAcervo::data_sql_para_padrao(std::string& data)
{
    std::regex reg("\\d{4}-\\d{2}-\\d{2}");
    std::smatch match;
    std::regex_search(data, match, reg);
    auto str_data_sql = match.str();

    auto ano = str_data_sql.substr(0, 4);
    auto mes = str_data_sql.substr(5, 2);
    auto dia = str_data_sql.substr(8, 2);

    std::ostringstream str_buffer;
    str_buffer << dia << "/" << mes << "/" << ano;
    return str_buffer.str();
}

std::string DbAcervo::data_padrao_para_sql(std::string& data)
{
    std::regex reg("\\d{2}\\/\\d{2}\\/\\d{4}");
    std::smatch match;
    std::regex_search(data, match, reg);
    auto str_data_sql = match.str();
//    30/04/1999
    auto dia = str_data_sql.substr(0, 2);
    auto mes = str_data_sql.substr(3, 2);
    auto ano = str_data_sql.substr(6, 4);

    std::ostringstream str_buffer;
    str_buffer << ano << "-" << mes << "-" << dia << " 00:00:00";
    return str_buffer.str();
}