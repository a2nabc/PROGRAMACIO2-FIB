/** @file Plataforma_material.cc
    @brief Implementación de la clase Plataforma_material
*/

#include "Plataforma_material.hh"

typedef map<string, Problema>::iterator it_p;
typedef map<string, Problema>::const_iterator cit_p;
typedef map<string, Sesion>::iterator it_s;
typedef map<string, Sesion>::const_iterator cit_s;

Plataforma_material::Plataforma_material() {}
                                                              //Consultoras
bool Plataforma_material::esta_curso(int c) const
{
  if (c > Cj_cursos.size() or c < 1) return false;
  return true;
}

int Plataforma_material::consultar_num_sesiones(int c) const
{
    return Cj_cursos[c-1].consultar_num_sesiones_curso();
}

const Sesion& Plataforma_material::indicador_sesion(int c, int s) const
{
  string sesion = Cj_cursos[c-1].consultar_sesion_i(s);
  cit_s its = Cj_sesiones.find(sesion);
  return its->second;
}

const Sesion& Plataforma_material::indicador_sesion2(int c, string p) const {
  string sesion = Cj_cursos[c-1].encontrar_sesion_problema(p);
  cit_s its = Cj_sesiones.find(sesion);
  return its->second;
}

string Plataforma_material::sesion_problema(int c, string p) const
//aprovechamos el hecho que, por como se leen las sesiones, sabemos que no es posible que un problema tenga el identificador "0"
{
    if (not esta_curso(c)) { //coste constante
        cout << "error: el curso no existe" << endl;
        return "0";
    }
    string sesion = Cj_cursos[c-1].encontrar_sesion_problema(p); //busca dentro de "curso" (es un map pequeño)
    if (sesion != "0") return sesion;

    cit_p it = Cj_problemas.find(p); //busca en el dentro de la estructura (grande) que contiene todos los problemas
    if (it != Cj_problemas.end()) {
      cout << "error: el problema no pertenece al curso" << endl;
      return "0";
    }
    else {
      cout << "error: el problema no existe" << endl;
      return "0";
    }
}
                                                        //Modificadoras
void Plataforma_material::nuevo_problema(string p)
{
    Problema pr;
    pair<it_p, bool> nou = Cj_problemas.insert (make_pair(p,pr));
    if (nou.second) cout << Cj_problemas.size() << endl;
    else cout << "error: el problema ya existe" << endl;
}

void Plataforma_material::nueva_sesion(string s)
{
    Sesion se;
    se.leer_sesion();
    pair<it_s, bool> nou = Cj_sesiones.insert(make_pair(s,se));
    if (nou.second) cout << Cj_sesiones.size() << endl;
    else cout << "error: la sesion ya existe" << endl;
}

void Plataforma_material::nuevo_curso()
{
    bool correcto = leer_curso();
    if (correcto) cout << Cj_cursos.size() << endl; //si es correcto, el curso ya se ha anadido a la plataforma en el metodo "leer_curso"
    else cout << "error: curso mal formado" << endl;
}

void Plataforma_material::actualizar_problema_plataforma(string p, bool r)
//esta funcion se llama desde Plataforma_usuarios, cuando se hace un envio, a fin de poder actualizar los stats del problema que se envia
{
    it_p it = Cj_problemas.find(p);
    it->second.anadir_envio_total_problema();
    if (r) it->second.anadir_envio_correcto_problema();
}

int Plataforma_material::modificar_stats_curso (int c, bool completado)
//esta funcion se llama desde Plataforma_usuarios, cuando un usuario se inscribe al curso c, a fin de actualizar los stats del curso afectado
{
    //modifica los stats del curso en funcion de si el usuario ya tiene todos los problemas resueltos o no. Retorna el numero de usuarios inscritos tras las modificaciones
    return Cj_cursos[c-1].modificar_stats(completado);
}

void Plataforma_material::restar_inscritos(int c, bool completado) {
    Cj_cursos[c-1].desinscribir_usuario(completado);
}

                                                        //Lectura y escritura
void Plataforma_material::leer_cj_problemas()
//lee un entero P seguido de P problemas, que pasan a formar parte de la plataforma
{
    int P;
    cin >> P;
    string id;
    Problema pr;
    for (int i = 0; i < P; ++i) {
        cin >> id;
        Cj_problemas.insert(make_pair(id, pr));
    }
}

void Plataforma_material::leer_cj_sesiones()
//lee un entero Q seguido de Q sesiones, que pasan a formar parte de la plataforma
{
    int Q;
    cin >> Q;
    string id;
    Sesion s;
    for (int i = 0; i < Q; ++i) {
        cin >> id;
        s.leer_sesion();
        Cj_sesiones.insert(make_pair(id, s));
    }
}

bool Plataforma_material::leer_curso()
//lee un curso individual y si es correcto lo guarda en la plataforma

//esta operacion se hace desde esta clase (y no desde Curso) porque es necesario tratar las Sesiones (y acceder a los problemas de cada una mediante el metodo "interseccion")
//aunque en la lectura inicial de cursos no hace falta comprobar que la interseccion de problemas sea correcta, he optado por utilizar en este caso tambien el metodo "intersession"
//puesto que permite crear en Curso una estructura de datos que contiene todos los problemas aparejados con la sesion a la que pertenecen (que sera util para funciones del Evaluator)

//coste: num_sesiones * constante * log(Q) * .. * constante
{
  int num_sesiones; cin >> num_sesiones;
  Curso c(num_sesiones);
  c.leer_sesiones_curso(num_sesiones);
  int i = 1; bool ok = true;
  while (i <= num_sesiones and ok) {
    string s = c.consultar_sesion_i(i); //busca en el curso cual es la sesion "i"
    cit_s it = Cj_sesiones.find(s); //encuentra la sesion en la plataforma
    ok = it->second.interseccion(c,s); //modifica el curso para anadirle la estructura de datos que contiene las parejas "problema-sesion"
    ++i;
  }
  if (ok) Cj_cursos.push_back(c); //si el curso leido es correcto, se anade a la plataforma
  return ok;
}

void Plataforma_material::leer_cj_cursos()
//lee un entero N seguido de N cursos, que pasan a formar parte de la plataforma
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) leer_curso();
}


bool Plataforma_material::comp_ratios(const pair <pair<string,Problema>, double>& p1, const pair <pair<string,Problema>, double>& p2) {
    if (p1.second == p2.second) return p1.first.first < p2.first.first;
    return p1.second < p2.second;
}

void Plataforma_material::listar_problemas() const
{
    cit_p it = Cj_problemas.begin();
    int mida = Cj_problemas.size();
    vector < pair <pair<string,Problema>, double> > v(mida); //construimos un vector con los problemas, identificadores y ratios, que nos servira para ordenar
    for (int i = 0; i < mida; ++i){
        v[i].first = *it;
        v[i].second = it->second.consultar_ratio();
        ++it;
    }
    sort(v.begin(), v.end(), comp_ratios);
    for(int i = 0; i < mida; ++i){
        cout << v[i].first.first;
        v[i].first.second.escribir_problema();
    }
}

void Plataforma_material::escribir_problema(string p) const
{
    cit_p it = Cj_problemas.find(p);
    if (it == Cj_problemas.end()) cout << "error: el problema no existe" << endl;
    else {
      cout << it->first;
      it->second.escribir_problema();
    }
}

void Plataforma_material::listar_sesiones() const
{
    for (cit_s it = Cj_sesiones.begin(); it != Cj_sesiones.end(); ++it) {
        cout << it->first << " ";
        it->second.escribir_sesion();
        cout << endl;
    }
}

void Plataforma_material::escribir_sesion(string s) const
{
    cit_s it = Cj_sesiones.find(s);
    if (it == Cj_sesiones.end()) cout << "error: la sesion no existe" << endl;
    else {
      cout << it->first << " ";
      it->second.escribir_sesion();
      cout << endl;
    }
}

void Plataforma_material::listar_cursos() const
{
    int mida = Cj_cursos.size();
    for (int i = 0; i < mida; ++i) {
        cout << i+1 << " ";
        Cj_cursos[i].escribir_curso();
    }
}

void Plataforma_material::escribir_curso(int c) const
{
    if (not esta_curso(c)) cout << "error: el curso no existe" << endl;
    else {
      cout << c << " ";
      Cj_cursos[c-1].escribir_curso();
    }
}
