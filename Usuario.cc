/** @file Usuario.cc
    @brief Implementación de la clase Usuario
*/
#include "Usuario.hh"
typedef map<string,int>::iterator it;
typedef map<string,int>::const_iterator c_it;

                                            //Constructora
Usuario::Usuario() {
    curso = 0;
    envios_totales = 0;
    intentados = 0;
}
                                            //Consultoras
int Usuario::consultar_curso_usuario() const
{
    return curso;
}

bool Usuario::ha_completado_curso() const
{
  return enviables.empty();
}

bool Usuario::esta_verdes_usuario(string id) const
{
    c_it it = verdes.find(id);
    if (it == verdes.end()) return false;
    return true;
}

                                          //Modificadoras
void Usuario::inscribir_usuario(int id_curso) {
    curso = id_curso;
}

int Usuario::desinscribir() {
    int aux = curso;
    curso = 0;
    return aux;
}

void Usuario::actualizar_problemas(string p, int r) {
    ++envios_totales;
    it it_p = enviables.find(p);
    if (it_p->second == 0) ++intentados; //miramos si es la primera vez que lo intenta. si lo es, incrementamos el numero de "problemas intentados" del parametro implicito
    ++it_p->second;
    if (r) { //si el parametro implicito ha resuelto el problema correctamente, lo quitamos de "enviables" y lo ponemos a "verdes"
      verdes.insert(*it_p);
      enviables.erase(it_p);
    }
}

void Usuario::anadir_problema_enviable_usuario(string p)
//este metodo lo necesitamos para actualizar los enviables del usuario, lo llamamos desde la clase Sesion
//(ya que desde alli comparamos los problemas de la sesion con los ya resueltos del usuario, y modificamos desde alli mismo los enviables del usuario)
{
    enviables.insert(make_pair(p, 0));
}

                                          //Escritura
void Usuario::escribir_usuario() const
{
    cout << "(" << envios_totales << "," << verdes.size() << "," << intentados << "," << curso << ")" << endl;
}

void Usuario::escribir_problemas_verdes_usuario() const
{
    for (c_it it = verdes.begin(); it != verdes.end(); ++it) cout << it->first << "(" << it->second << ")" << endl;
}

void Usuario::escribir_problemas_enviables_usuario() const
{
    for (c_it it = enviables.begin(); it != enviables.end(); ++it) cout << it->first << "(" << it->second << ")" << endl;
}
