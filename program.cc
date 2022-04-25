/** @file main.cc
    @brief Programa principal del Evaluator
*/

/**
  * @mainpage Evaluator: plataforma de gestión de problemas y cursos de programación
  En este proyecto he desarrollado un programa que representa una plataforma de gestión de problemas y cursos de programación: "Evaluator".
  A fin de cubrir los objetivos y las funcionalidades que se nos proponen en el enunciado de la Práctica de Pro2 (primavera 2021), el diseño modular que he planteado para mi práctica consiste en 6 clases:
  <ul>
  <li> Problema </li>
  <li> Sesion </li>
  <li> Curso </li>
  <li> Usuario </li>
  <li> Plataforma_material </li>
  <li> Plataforma_usuarios </li>
*/

#include "Plataforma_material.hh"
#include "Plataforma_usuarios.hh"

/** @brief Mediante este programa se podrá realizar por un lado la inicialización del Evaluator y, por otro, las funcionalidades que ofrece la plataforma Evaluator
*/

int main()
{
      //inicializamos la Plataforma Evaluator
      Plataforma_material Evaluator_material;
      Plataforma_usuarios Evaluator_usuarios;

      //leemos los problemas para la inicializacion
      Evaluator_material.leer_cj_problemas();

      //leemos las sesiones para la inicializacion
      Evaluator_material.leer_cj_sesiones();

      //leemos los cursos para la inicializacion
      Evaluator_material.leer_cj_cursos();

      //leemos los usuarios para la inicializacion
      Evaluator_usuarios.leer_cj_usuarios();

      //ya tenemos la plataforma inicializada. A continuación leemos y executamos las funcionalidades
      string funcion;
      while (cin >> funcion and funcion != "fin") {
            if (funcion == "nuevo_problema" or funcion == "np") {
                  string p;
                  cin >> p;
                  cout << "#" << funcion << " " << p << endl;
                  Evaluator_material.nuevo_problema(p);
            }
            else if (funcion == "nueva_sesion" or funcion == "ns") {
                  string s;
                  cin >> s;
                  cout << "#" << funcion << " " << s << endl;
                  Evaluator_material.nueva_sesion(s);
            }

            else if (funcion == "nuevo_curso" or funcion == "nc") {
                  cout << "#" << funcion << endl;
                  Evaluator_material.nuevo_curso();
            }

            else if (funcion == "alta_usuario" or funcion == "a") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.alta_usuario(u);
            }
            else if (funcion == "baja_usuario" or funcion == "b") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.baja_usuario(u, Evaluator_material);
            }
            else if (funcion == "inscribir_curso" or funcion == "i") {
                  string u;
                  int c;
                  cin >> u >> c;
                  cout << "#" << funcion << " " << u << " " << c << endl;
                  Evaluator_usuarios.inscribir_curso(u,c,Evaluator_material);
            }
            else if (funcion == "curso_usuario" or funcion == "cu") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.curso_usuario(u);
            }
            else if (funcion == "sesion_problema" or funcion == "sp") {
                  int c;
                  string p;
                  cin >> c >> p;
                  cout << "#" << funcion << " " << c << " " << p << endl;
                  string sesion =  Evaluator_material.sesion_problema(c,p);
                  if (sesion != "0") cout << sesion << endl;
            }
            else if (funcion == "problemas_resueltos" or funcion == "pr") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.problemas_resueltos(u);
            }
            else if (funcion == "problemas_enviables" or funcion == "pe") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.problemas_enviables(u);
            }

            else if (funcion == "envio" or funcion == "e") {
                  string u, p;
                  bool r;
                  cin >> u >> p >> r;
                  cout << "#" << funcion << " " << u << " " << p << " " << r << endl;
                  Evaluator_usuarios.envio(u,p,r,Evaluator_material);
            }

            else if (funcion == "listar_problemas" or funcion == "lp") {
                  cout << "#" << funcion << endl;
                  Evaluator_material.listar_problemas();
            }
            else if (funcion == "escribir_problema" or funcion == "ep") {
                  string p;
                  cin >> p;
                  cout << "#" << funcion << " " << p << endl;
                  Evaluator_material.escribir_problema(p);
            }
            else if (funcion == "listar_sesiones" or funcion == "ls") {
                  cout << "#" << funcion << endl;
                  Evaluator_material.listar_sesiones();
                }
            else if (funcion == "escribir_sesion" or funcion == "es") {
                  string s;
                  cin >> s;
                  cout << "#" << funcion << " " << s << endl;
                  Evaluator_material.escribir_sesion(s);
            }
            else if (funcion == "listar_cursos" or funcion == "lc") {
                  cout << "#" << funcion << endl;
                  Evaluator_material.listar_cursos();
            }
            else if (funcion == "escribir_curso" or funcion == "ec") {
                  int c;
                  cin >> c;
                  cout << "#" << funcion << " " << c << endl;
                  Evaluator_material.escribir_curso(c);
            }
            else if (funcion == "listar_usuarios" or funcion == "lu") {
                  cout << "#" << funcion << endl;
                  Evaluator_usuarios.listar_usuarios();
            }
            else if (funcion == "escribir_usuario" or funcion == "eu") {
                  string u;
                  cin >> u;
                  cout << "#" << funcion << " " << u << endl;
                  Evaluator_usuarios.escribir_usuario(u);
            }
      }
}
