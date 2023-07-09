#include <iostream>

#include "../include/adm.hpp"
#include "../include/bibliotecario.hpp"
#include "../include/db_acervo.hpp"
#include "../include/db_administradores.hpp"
#include "../include/db_usuarios.hpp"

void reset()
{
    DbUsuarios().reset();
    DbAcervo().reset();
    DbAdministradores().reset();
    auto db_user = DbUsuarios();
    auto db_ac = DbAcervo();
    auto db_adm = DbAdministradores();
}

int main() {
    reset();
    Livro l1("titulo","autor","teste","teste","teste",1,1,0);
    Livro l2("titulo","autor","teste","teste","teste",1,1,0);
    Livro l3("titulo2","autor","teste","teste","teste",1,1,0);
    Livro l4("titulo3","autor2","teste","teste","teste",1,1,0);

    Administrador adm("fulano","teste","teste");
    adm.sign_in();

    adm.InserirLivro(l1);
    adm.InserirLivro(l2);
    adm.InserirLivro(l3);
    adm.InserirLivro(l4);
    
    Usuario user1("Fulano", "teste", "teste");
    user1.sign_in();

    Bibliotecario bbt("fulano", "teste", "teste2");
    bbt.sign_in();
    auto livro_consulta = bbt.consultaLivros(l3.getTitulo(), bbt_def::sql::schema_acervo::titulo).back();
    auto user_consulta = bbt.BuscaUsuario(user1);
    bbt.EmprestaLivro(livro_consulta, user_consulta);
    bbt.EmprestaLivro(l1, user_consulta);
    bbt.EmprestaLivro(l1, user_consulta);

    auto livro_delete = adm.consultaLivros(l4.getTitulo(), bbt_def::sql::schema_acervo::titulo).back();
    adm.RemoverLivro(livro_delete);

    bbt.DevolveLivro(l1, user_consulta);

    user1.avaliar_livro(l1, 2);
    user1.avaliar_livro(l1, 3);

    std::cout << "Hello" << std::endl;
    return 0;
}