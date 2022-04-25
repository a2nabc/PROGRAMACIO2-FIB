/** @file Sesion.hh
    @brief Especificación de la clase Sesion
*/

#ifndef _SESION_HH_
#define _SESION_HH_

#include "Usuario.hh"
#include "Curso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include "BinTree.hh"
using namespace std;
#endif

/** @class Sesion
    @brief Representa la información y las operaciones asociadas a una sesión.

     La información de una sesión viene dada por los atributos: estructura de problemas que la forman, número de problemas que la forman.

     Las operaciones son: lectura y escritura de una sesión, consultora de intersección (con un curso) (mira si hay coincidencia entre los problemas de un curso dado y la sesión), consultora de enviables iniciales (de un Usuario) (mira cuáles son los problemas de la sesión que un usuario dado tiene los prerrequisitos resueltos),  consultora de enviables (de un Usuario) (mira, a partir de un problema dado acabado de resolver, cuáles son los problemas de la sesión que un usuario dado ha desbloqueado).
*/

class Sesion
{
private:
    /** @brief Estructura de los identificadores de problemas de la Sesion */
    BinTree <string> problemas;
    /** @brief Número de problemas totales que contiene la Sesion */
    int num_problemas;

public:
    //Constructora
    /** @brief Creadora por defecto.
        Se ejecuta automáticamente al declarar una sesión.
        \pre En el canal de entrada se encuentra un string con el identificador de la sesión
        \post Se ha creado una sesión vacía, sin estructura de problemas
        \coste Constante
    */
    Sesion();

    //Consultoras
    /** @brief Informa de si hay intersección de problemas entre el parámetro implícito y el Curso c
        \pre c es un Curso, s es el string que identifica el parámetro implícito
        \post Si hay alguna coincidencia entre los problemas del parámetro implícito y los del Curso c, retorna false. Si no, retorna true y además se ha modificado c y se le han añadido todos los problemas de la sesión, cada uno aparejado con el identificador de sesión "s"
    */
    bool interseccion(Curso& c, const string s) const;

    /** @brief Función de comparación de los problemas del parámetro implícito con los del Usuario u
        \pre u es un Usuario que se acaba de inscribir en un curso. El parámetro implícito es una de las sesiones del curso en cuestión
        \post Se han añadido a u todos los problemas que puede intentar resolver (enviables) de esta Sesion
    */
    void actualizar_enviables_iniciales(Usuario& u) const;

    /** @brief Función de comparación de los problemas del Usuario u con los del parámetro implícito (solamente comparando a partir del problema "resuelto")
        \pre u es un Usuario inscrito en un curso que acaba de hacer un envio correcto del problema "resuelto". El parámetro implícito es la Sesion del curso que contiene el problema que acaba de resolver
        \post Se han añadido a u todos los problemas enviables que ha desbloqueado al haber resuelto el problema "resuelto"
    */
    void actualizar_enviables(Usuario& u, const string& resuelto) const;

    //Lectura y escritura
    /** @brief Lectura de una sesión.
        Permite leer el id y los problemas de una sesión
        \pre En el canal de entrada se encuentra una secuencia de problemas (en preorden según los prerrequisitos)
        \post Se ha realizado la lectura de la sesión (y ahora el parámetro implícito ha pasado a tener la secuencia de problemas)
        \coste Lineal en el número de problemas de la sesión
    */
    void leer_sesion();

    /** @brief Escritura de una sesión.
        Permite escribir el contenido de una sesión
        \pre <em>cierto</em>
        \post Se ha escrito en el canal de salida el número de problemas del parámetro implícito, y la secuencia de identificadores de los problemas que la forman (en postorden)
        \coste Lineal en el número de problemas de la sesión
    */
    void escribir_sesion() const;

private:
    /** @brief Lectura de la estructura de problemas de una sesión
        \pre En el canal de entrada se encuentra una secuencia de problemas (en preorden según los prerrequisitos)
        \post Se ha realizado la lectura de los problemas y se han guardado en el BinTree que contiene los problemas
    */
    static void leer_estructura_problemas(BinTree<string>& a, int& np);

    /** @brief Escritura de la estructura de problemas de una sesión
        \pre a es el BinTree que contiene los problemas de la sesion ordenados por prerrequisitos
        \post Se ha escrito el contenido de a en el canal de salida (en postorden)
    */
    static void escribir_estructura_problemas(const BinTree<string>& a);

    /** @brief Inmersión de la consultora de si hay intersección de problemas entre el parámetro implícito y el Curso c
        \pre c es un Curso, s es el string que identifica el parámetro implícito, a es el BinTree de probemas del parámetro implícito
        \post Si hay alguna coincidencia entre los problemas del parámetro implícito y los del Curso c, retorna false. Si no, retorna true y además modifica c añadiendole todos los problemas de la sesión, cada uno aparejado con el identificador de sesión "s"
    */
    static bool interseccion_i (const BinTree<string>& a, Curso& c, string s);

    /** @brief Inmersión de función de comparación de los problemas del parámetro implícito con los del Usuario u
        \pre u es un Usuario que se acaba de inscribir en un curso. El parámetro implícito es una de las sesiones del curso en cuestión. a es el BinTree de problemas del parámetro implícito
        \post Se ha recorrido el BinTree a hasta encontrar los problemas que u tiene resueltos los prerrequisitos, pero no el problema (es decir, los problemas enviables). Además, se ha modificado u añadiendole dichos problemas
    */
    static void enviables(const BinTree<string>& a, Usuario& u);

    /** @brief Inmersión de función de comparación de los problemas del Usuario u con los del parámetro implícito (solamente comparando a partir del problema "resuelto")
        \pre u es un Usuario inscrito en un curso que acaba de hacer un envio correcto del problema "resuelto". El parámetro implícito es la Sesion del curso que contiene el problema que acaba de resolver. a es un BinTree que contiene el subárbol que tiene por raíz el problema "resuelto"
        \post Se han añadido a u todos los problemas enviables que ha desbloqueado al haber resuelto el problema "resuelto"
    */
    static void busca_y_actualiza(const BinTree<string>& a, Usuario& u, const string& resuelto); //OK
};
#endif
