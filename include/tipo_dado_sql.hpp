#ifndef TIPO_DADO_SQL
#define TIPO_DADO_SQL

#include <string>
// arquivo para generalizar os tipos de dados para inserção no banco de dados

// exceção que impede o uso indevido de métodos não destinados ao seu tipo
// tentei de tudo para usar herança/interface, mas para manter o polimorfismo foi necessário
class metodo_incompativel_e {};

// classe wrapper com os tipos de dados presentes no banco de dados
class TipoDadoSQL
{
    private:
        int _dado_int;
        double _dado_double;
        std::string _dado_string;
        std::string _tipo_sql;
    
    public:
        // construtor caso seja do tipo nulo
        TipoDadoSQL();

        // construtor caso seja do tipo inteiro
        TipoDadoSQL(int integer);

        // construtor caso seja do tipo double
        TipoDadoSQL(double real);
        
        // construtor caso seja do tipo string
        TipoDadoSQL(std::string text);
        
        // getter para o tipo SQL equivalente
        std::string get_tipo_sql();
        
        // getter para tipo int
        int get_int() const;
        
        // getter para tipo double
        double get_double() const;
        
        // getter para tipo string
        std::string get_string() const;

        // método para debug
        void imprime_valor();
};

#endif