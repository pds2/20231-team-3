#ifndef DB_ACERVO
#define DB_ACERVO

#include "../include/bbt_wrapper_sql.hpp"
#include "../include/livro.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbAcervo : public BbtWrapperSQL<Livro>
{
    protected:
        virtual void _diretriz(sqlite::database_binder& ps_binder, Livro obj) override;
        
        virtual Livro _diretriz(
            sqlite::row_iterator::value_type linha_binder) override;

    public:
        DbAcervo();

        std::string data_sql_para_padrao(std::string& data);
        std::string data_padrao_para_sql(std::string& data);
};

#endif