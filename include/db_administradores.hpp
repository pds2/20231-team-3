#ifndef DB_ADMINISTRADORES
#define DB_ADMINISTRADORES

#include "bbt_wrapper_sql.hpp"
#include "bibliotecario.hpp"
#include "adm.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbAdministradores : public BbtWrapperSQL<Entidadebase>
{
    protected:
        virtual void _diretriz(sqlite::database_binder& ps_binder, Entidadebase obj) override;
        
        virtual std::pair<Entidadebase, AdtDataSQL> _diretriz(
            sqlite::row_iterator::value_type linha_binder) override;

    public:
        DbAdministradores();
        
              
};

#endif