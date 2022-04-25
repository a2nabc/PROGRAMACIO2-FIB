/** @file Plataforma_usuarios.cc
    @brief Implementación de la clase Plataforma_usuarios
*/

#include "Plataforma_usuarios.hh"
#include "Plataforma_material.hh"

typedef map<string, Usuario>::iterator it_u;
typedef map<string, Usuario>::const_iterator cit_u;
typedef map<string, Problema>::iterator it_p;
typedef map<string, Problema>::const_iterator cit_p;
typedef map<string, Sesion>::iterator it_s;
typedef map<string, Sesion>::const_iterator cit_s;

Plataforma_usuarios::Plataforma_usuarios() {}
                                                        //Consultoras
void Plataforma_usuarios::curso_usuario(string u) const
{
    cit_u it = Cj_usuarios.find(u);
    if (it == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
    else cout << it->second.consultar_curso_usuario() << endl;
}

                                                        //Modificadoras
void Plataforma_usuarios::alta_usuario(string u)
{
    Usuario us;
    pair<it_u, bool> nou = Cj_usuarios.insert (make_pair(u,us));
    if (nou.second) cout << Cj_usuarios.size() << endl;
    else cout << "error: el usuario ya existe" << endl;
}

void Plataforma_usuarios::baja_usuario(string u, Plataforma_material& pm)
{
    it_u it = Cj_usuarios.find(u);
    if (it == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
    else{
        int curso = it->second.consultar_curso_usuario();
        if (curso != 0) pm.restar_inscritos(curso,false); //le pasamos "false" porque el usuario NO ha completado ningun curso, sino que se da de baja (y deja a medias el curso en el que estaba inscrito)
        Cj_usuarios.erase(it);
        cout << Cj_usuarios.size() << endl;
    }
}

void Plataforma_usuarios::inscribir_curso(string u, int c, Plataforma_material& pm)
//coste (Cuadrático en el número de sesiones del curso) * log(M)
{
    it_u itu = Cj_usuarios.find(u);
    if (itu == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
    else if (not pm.esta_curso(c)) cout << "error: el curso no existe" << endl;
    else if (itu->second.consultar_curso_usuario() != 0) cout << "error: usuario inscrito en otro curso" << endl;

    //el curso y el usuario son correctos: a continuacion modificamos el curso y el usuario
    else {
        int sesiones = pm.consultar_num_sesiones(c); //busca el Curso (coste constante) y retorna el numero de sesiones que tiene
        for (int i = 1; i <= sesiones; ++i) {
            const Sesion& s_i = pm.indicador_sesion(c,i); //busca cual es la sesion numero "i" dentro del curso c, y retorna la Sesion en s_i
            s_i.actualizar_enviables_iniciales(itu->second); // va a la sesion, desde alli añade a u los enviables que le faltaban
        }

        // ahora solo nos queda mirar si el usuario ya tenia todos los problemas del curso resueltos previamente, y actualizar los stats del curso en funcion de esto
        bool completado = itu->second.ha_completado_curso();
        if (not completado) itu->second.inscribir_usuario(c);
        cout << pm.modificar_stats_curso(c, completado) << endl; //accede al curso, y lo modifica
    }
}

void Plataforma_usuarios::envio(string u, string p, bool r, Plataforma_material& pm)
//coste (logM) * (logP) * (log (número de problemas del curso)) * (número de problemas de la sesión) * (log (núm prob sesión))
{
    it_u it = Cj_usuarios.find(u);
    it->second.actualizar_problemas(p, r); //busca el problema enviable dentro del usuario u y hace las actualizaciones necesarias
    pm.actualizar_problema_plataforma(p, r);
    //busca el problema en pm y actualiza los stats del problema
    if (r) {
        const Sesion& s_i = pm.indicador_sesion2(it->second.consultar_curso_usuario(), p); // devuelve la sesion (coste constante)
        s_i.actualizar_enviables(it->second, p); //es un metodo de Sesion que modifica los enviables del usuario
        bool completado = it->second.ha_completado_curso();
        if (completado) {
          int curso = it->second.desinscribir();
          pm.restar_inscritos(curso, completado); //busca el curs (coste constante) i l'actualitza
        }
    }
}
                                                     //Lectura y escritura
void Plataforma_usuarios::leer_cj_usuarios() //OK
//lee un entero M seguido de M usuarios, que pasan a formar parte de la plataforma
{
  int M; cin >> M;
  Usuario u;
  string id;
  for (int i = 0; i < M; ++i) {
      cin >> id;
      Cj_usuarios.insert(make_pair(id,u));
  }
}

void Plataforma_usuarios::listar_usuarios() const
{
  for (cit_u it = Cj_usuarios.begin(); it != Cj_usuarios.end(); ++it) {
    cout << it->first;
    it->second.escribir_usuario();
  }
}

void Plataforma_usuarios::escribir_usuario(string u) const
{
  cit_u it = Cj_usuarios.find(u);
  if (it == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
  else {
    cout << it->first;
    it->second.escribir_usuario();
  }
}


void Plataforma_usuarios::problemas_resueltos(string u) const
{
  cit_u it = Cj_usuarios.find(u);
  if (it == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
  else it->second.escribir_problemas_verdes_usuario();

}

void Plataforma_usuarios::problemas_enviables(string u) const
{
  cit_u it = Cj_usuarios.find(u);
  if (it == Cj_usuarios.end()) cout << "error: el usuario no existe" << endl;
  else if (it->second.consultar_curso_usuario() == 0) cout << "error: usuario no inscrito en ningun curso" << endl;
  else it->second.escribir_problemas_enviables_usuario();
}
