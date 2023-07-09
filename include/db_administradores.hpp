#ifndef DB_ADMINISTRADORES
#define DB_ADMINISTRADORES

#include "../include/bbt_wrapper_sql.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/adm.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbAdministradores : public BbtWrapperSQL<Entidadebase>
{
    protected:
        virtual void _diretriz(sqlite::database_binder& ps_binder, Entidadebase obj) override;
        
        virtual Entidadebase _diretriz(
            sqlite::row_iterator::value_type linha_binder) override;

    public:
        DbAdministradores();
        
              
};

#endif