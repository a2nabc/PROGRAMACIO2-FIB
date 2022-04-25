/** @file Curso.cc
    @brief Implementación de la clase Curso
*/
#include "Curso.hh"

                                                    //Constructoras
Curso::Curso(int num_sesiones)
{
  num_completado = 0;
  num_usuarios_inscritos = 0;
  sesiones = vector<string> (num_sesiones);
}
                                                    //Consultoras

string Curso::encontrar_sesion_problema(string p) const
{
    map<string, string>::const_iterator it = problemas.find(p); //busca en el map de "curso" donde tenemos guardados todos los problemas (es un map pequeñito)
    if (it != problemas.end()) return it->second;
    return "0"; //aprovechamos el hecho que, por como se leen las sesiones, sabemos que no es posible que un problema tenga el identificador "0"
}

string Curso::consultar_sesion_i(int i) const
{
  return sesiones[i-1];
}

int Curso::consultar_num_sesiones_curso() const
{
  return sesiones.size();
}

                                                    //Modificadoras
bool Curso::insertar_problema(string p, string s)
//esta funcion solo se llama (desde Sesion) cuando se esta leyendo un curso nuevo, en particular cuando se lee la estructura de problemas de una sesion del curso
//permite actualizar el curso anadiendole un problema (que proviene de la sesion), al mismo tiempo que permite detectar si el parametro implicito ya contenia dicho problema
{
    pair<map<string,string>::iterator, bool> insertat = problemas.insert(make_pair(p,s));
    return insertat.second;
}

int Curso::modificar_stats(bool completado)
//esta funcion se llama solo cuando un usuario se inscribe al parametro implicito
//permite actualizar los stats del curso
{
    if (completado) ++num_completado; //aqui miramos el caso excepcional en que el usuario en cuestion ya tiene todos los problemas resueltos a priori
    else ++num_usuarios_inscritos;
    return num_usuarios_inscritos;
}

void Curso::desinscribir_usuario(bool completado)
{
    --num_usuarios_inscritos;
    if (completado) ++num_completado;
}
                                                    //Lectura y escritura
void Curso::leer_sesiones_curso(int num_sesiones)
{
    for(int i = 0; i < num_sesiones; ++i) {
        string id;
        cin >> id;
        sesiones[i] = id;
    }
}

void Curso::escribir_curso() const
{
    cout << num_completado << " " << num_usuarios_inscritos << " " << sesiones.size() << " ";
    int size = sesiones.size();
    for (int i = 0; i < size; ++i) {
        if (i == 0) cout << "(" << sesiones[i];
        else cout << " " << sesiones[i];
    }
    cout << ")" << endl;
}
