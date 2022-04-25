/** @file Sesion.cc
    @brief Implementación de la clase Sesion
*/
#include "Sesion.hh"

                                                        //Constructora
Sesion::Sesion()
{
    num_problemas = 0;
}

                                                          //Consultoras
bool Sesion::interseccion(Curso& c, string s) const
//esta funcion modifica el Curso anadiendole todos los problemas del parametro implicito
//si encuentra que en el Curso hay dos problemas que se repiten, para de anadir y retorna false
{
    return interseccion_i(problemas, c, s);
}


bool Sesion::interseccion_i (const BinTree<string>& a, Curso& c, string s)
//esta funcion es de caracter private
{
    if (a.empty()) return true;
    return c.insertar_problema(a.value(), s) and interseccion_i(a.left(), c, s) and interseccion_i(a.right(), c, s);
}



void Sesion::actualizar_enviables_iniciales(Usuario& u) const
//esta funcion la utilizo para la primera vez que busco los enviables de una sesion. Es decir, cuando inscribo un usuario en un curso.
{
    enviables(problemas, u);
}

void Sesion::enviables(const BinTree<string>& a, Usuario& u)
//esta funcion es de caracter private
//recorre el BinTree de problemas del parametro implicito hasta que se encuentra con aquellos problemas que el Usuario u tiene resueltos sus prerrequisitos pero no el problema en cuestion. Se anaden dichos problemas a los enviables de u
{
  if (not a.empty()) {
      if (not u.esta_verdes_usuario(a.value())) u.anadir_problema_enviable_usuario(a.value());
      else {
          enviables(a.left(), u);
          enviables(a.right(), u);
      }
  }
}


void Sesion::actualizar_enviables(Usuario& u, const string& resuelto) const
//esta funcion la utilizo en envio, cuando el usuario ha resuelto el problema "resuelto", para buscar los enviables que se le han desbloqueado
{
    busca_y_actualiza(problemas, u, resuelto);
}

void Sesion::busca_y_actualiza(const BinTree<string>& a, Usuario& u, const string& resuelto)
//esta funcion es de caracter private
{
  if (not a.empty()) {
      if (a.value() == resuelto) enviables(a,u); //si a es el subarbol que tiene por raiz el problema "resuelto", actualizamos los enviables del usuario
      else { //si a no es el subarbol que tiene por raiz "problema", tenemos que recorrer el hijo (izquierdo o derecho) hasta encontrar el subarbol con raiz: "problema"
          busca_y_actualiza(a.left(),u,resuelto);
          busca_y_actualiza(a.right(),u,resuelto);
      }
  }
}

                                                    //Lectura y escritura
void Sesion::leer_sesion()
//lee la estructura de problemas de la sesion (en preorden)
{
    int np = 0;
    leer_estructura_problemas(problemas, np);
    num_problemas = np;
}

void Sesion::leer_estructura_problemas(BinTree<string>& a, int& np)
//esta funcion es de caracter private
{
    string id;
    cin >> id;
    if (id!="0"){
        ++np;
        BinTree<string> l;
        leer_estructura_problemas(l,np);
        BinTree<string> r;
        leer_estructura_problemas(r,np);
        a=BinTree<string>(id,l,r);
    }
}

void Sesion::escribir_sesion() const
//escribe la estructura de problemas de la sesion (en postorden)
{
    cout << num_problemas << " ";
    escribir_estructura_problemas(problemas);
}

void Sesion::escribir_estructura_problemas(const BinTree<string> &a)
//esta funcion es de caracter private
{
	if (not a.empty()) {
        cout << "(";
        string id = a.value();
        escribir_estructura_problemas(a.left());
        escribir_estructura_problemas(a.right());
        cout << id << ")";
  }
}
