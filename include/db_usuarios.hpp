#ifndef DB_USUARIOS
#define DB_USUARIOS

#include "bbt_wrapper_sql.hpp"
#include "usuario.hpp"
#include "usuariovip.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbUsuarios : public BbtWrapperSQL<Entidadebase>
{
    protected:
        virtual void _diretriz(sqlite::database_binder& ps_binder, Entidadebase obj) override;
        
        virtual Entidadebase _diretriz(
            sqlite::row_iterator::value_type linha_binder) override;

    public:
        DbUsuarios();        
};

#endif