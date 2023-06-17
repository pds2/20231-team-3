#ifndef DB_USUARIOS
#define DB_USUARIOS

#include "bbt_wrapper_sql.hpp"

// classe que herda da classe base BbtWrapperSQL
class DbUsuarios : public BbtWrapperSQL
{
    public:
        DbUsuarios();        
};

#endif