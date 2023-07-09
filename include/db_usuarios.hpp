#ifndef DB_USUARIOS
#define DB_USUARIOS

#include "../include/bbt_wrapper_sql.hpp"
#include "../include/usuario.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbUsuarios : public BbtWrapperSQL<Usuario>
{
    protected:
        virtual void _diretriz(sqlite::database_binder& ps_binder, Usuario obj) override;
        
        virtual Usuario _diretriz(
            sqlite::row_iterator::value_type linha_binder) override;

    public:
        DbUsuarios();        
};

#endif