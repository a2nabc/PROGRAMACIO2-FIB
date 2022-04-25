/** @file Curso.hh
    @brief Especificación de la clase Curso
*/

#ifndef _CURSO_HH_
#define _CURSO_HH_
#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#endif

/** @class Curso
    @brief Representa la información y las operaciones asociadas a un curso.

    La información viene dada por: el conjunto de sesiones (ordenadas) que lo forman, el conjunto de problemas que lo forman (asociados cada uno con la sesión a que pertenecen), número de usuarios que lo han completado, y el número de usuarios inscritos actualmente.

    Las operaciones son: las consultoras de la sesión asociada a un problema, de la sesión que ocupa una cierta posición dada, y del número de sesiones del curso; las modificadoras de añadir un problema al conjunto de problemas del curso, de actualizar el número de inscritos y completados, y la de desinscribirle un usuario; la de lectura de las sesiones de un curso; y la de escritura de un curso.

*/

class Curso
{

private:
    /** @brief Estructura donde se guardan los identificadores de las sesiones que lo forman (en orden en que se leyeron) */
    vector<string> sesiones;
    /** @brief Estructura donde se guardan los problemas del curso (juntamente con el string de la sesión a la que pertenecen) */
    map <string,string> problemas;
    /** @brief Número de usuarios que actualmente están registrados en el curso */
    int num_usuarios_inscritos;
    /** @brief Número de usuarios que han completado el curso (actuales o pasados) */
    int num_completado;

public:
    //Constructoras
    /** @brief Creadora de cursos por defecto
        Se ejecuta automáticamente al declarar un curso
        \pre num_sesiones contiene el número de sesiones que forman el curso
        \post Se ha creado un curso vacío
        \coste Lineal en el número de sesiones del curso
    */
    Curso(int num_sesiones);

    //Consultoras
    /** @brief Consulta cuál es la sesión a la que pertenece un problema del parámetro implícito
        \pre p es el identificador del problema que estamos buscando.
        \post Retorna el identificador de la sesión a la que pertenece el problema p. Si p no pertenece al curso, retorna el string "0"
        \coste Logarítmico en el número de problemas del curso
    */
    string encontrar_sesion_problema(string p) const;

    /** @brief Consulta cuál es la sesión que ocupa la posición i (respecto al orden en que se leyeron) de entre todas las sesiones del curso
        \pre i es un entero entre 1 y el número total de sesiones que contiene el curso
        \post Retorna el identificador de la sesión que ocupa la posición i (respecto el orden en que fueron leídas al leer el curso)
        \coste Constante
    */
    string consultar_sesion_i(int i) const;

    /** @brief Consulta el número de sesiones que forman el curso
        \pre <em>cierto</em>
        \post Retorna el valor del número de sesiones que forman el curso
        \coste Constante
    */
    int consultar_num_sesiones_curso() const;


    //Modificadoras
    /** @brief Añadir problema en un curso
        \pre Se está leyendo un curso nuevo, y se está comprobando, sesión por sesión, si es correcto (ie si hay intersección de problemas o no). s es el id de la sesión que se está tratando. p es un problema de dicha sesión
        \post Si el problema p ya estaba entre los problemas del parámetro implícito, retorna false y no se ha modificado nada. Si no estaba, retorna true y se ha añadido al parámetro implícito la pareja "problema-sesión" (p,s)
        \coste Logarítmico en el número de problemas del curso
    */
    bool insertar_problema(string p, string s);

    /** @brief Modificar los stats
        \pre Un usuario se acaba de matricular correctamente en el parámetro implícito. "completado" es true si el usuario en cuestión tiene todos los problemas del curso resueltos a priori
        \post Si el usuario tenía todos los problemas resueltos, el parámetro implícito contiene un usuario más en el recuento de usuarios que lo han completado. Si no, el parámetro implícito contiene un usuario menos. En ambos casos, retorna el número de usuarios inscritos en el curso tras las modificaciones
        \coste Constante
    */
    int modificar_stats(bool completado);

    /** @brief Desinscribir un usuario del curso
        \pre Un usuario se acaba de desmatricular del parámetro implícito. "completado" es true si el usuario en cuestión ha completado el curso con éxito, false si no lo ha completado
        \post El parámetro implícito contiene un usuario menos. Además, si el usuario lo había completado con éxito, el parámetro implícito tendrá uno más al número de usuarios que lo han completado
        \coste Constante
    */
    void desinscribir_usuario(bool completado);


    //Lectura y escritura
    /** @brief Lectura de un curso
        \pre En el canal de entrada tenemos el numero de sesiones que formaran el curso, y una secuencia de identificadores de las sesiones en cuestión
        \post Se han guardado en el parámetro implícito los identificadores de las sesiones por orden
        \coste Lineal en el número de sesiones del curso
    */
    void leer_sesiones_curso(int num_sesiones);

    /** @brief Escritura de un curso
        \pre <em>cierto</em>
        \post En el canal de salida tenemos el número total de usuarios (actuales o pasados) que han completado el curso, el número de usuarios inscritos actualmente, el número de sesiones que lo forman, y la secuencia de identificadores de las sesiones
        \coste Lineal en el número de sesiones del curso
    */
    void escribir_curso() const;
};
#endif
