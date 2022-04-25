/** @file Plataforma_material.hh
    @brief Especificación de la clase Plataforma_material
*/

#ifndef PLATAFORMA_MATERIAL_HH_
#define PLATAFORMA_MATERIAL_HH_

#include "Problema.hh"
#include "Sesion.hh"
#include "Curso.hh"

#ifndef NO_DIAGRAM
#include <algorithm>
#include <set>
#endif

/** @class Plataforma_material
    @brief Representa la información y las operaciones asociadas al "Material Docente" (problemas, sesiones y cursos) de la plataforma Evaluator.

    La información viene dada por un conjunto que contiene parejas de un identificador y un problema, otro conjunto que contiene parejas identificador - sesión, y otro que contiene parejas número de curso - curso.

    Las operaciones son: consultoras de si un curso está en la plataforma, del numero de sesiones que tiene un curso dado, de la Sesion que ocupa cierta posición dentro de un curso, de la Sesion que contiene cierto problema dentro de un curso, o del identificador de la Sesion que contiene cierto problema. Las modificadoras permiten añadir un problema, o una sesión, o un curso a la plataforma, o bien actualizar la información de un problema dado (cuando algún usuario hace envíos, por ejemplo), o la de un curso dado (cuando un usuario se inscribe / desinscribe, por ejemplo). Las de lectura permiten leer o bien el conjunto de problemas, de sesiones o de cursos, o también permiten leer un curso particular. Las de escritura permiten escribir o bien un problema, una sesión o un curso dado, o bien el conjunto entero de problemas, sesiones o cursos.

    */

class Plataforma_material
{
private:
    /** @brief Estructura que contiene todos los problemas disponibles en la plataforma */
    map<string, Problema> Cj_problemas;
    /** @brief Estructura que contiene todas las sesiones disponibles en la plataforma */
    map<string, Sesion> Cj_sesiones;
    /** @brief Estructura que contiene todos los cursos disponibles en la plataforma (ordenados por orden en que se añadieron a la plataforma) */
    vector<Curso> Cj_cursos;

public:
    //Constructora
    /** @brief Creadora de la plataforma de material docente
        Se ejecuta automáticamente al declarar una plataforma de material
        \pre <em>cierto</em>
        \post Se ha creado una plataforma de material vacía
        \coste Constante
    */
    Plataforma_material();

    //Consultoras
    /** @brief Consulta si c es un curso existente
        \pre c es el identificador del curso que buscamos si existe
        \post Se comprueba si el curso existe en la plataforma. Si no existe, retorna false. En caso contrario, retorna true
        \coste Constante
    */
    bool esta_curso(int c) const;

    /** @brief Consulta el número de sesiones que tiene un curso
        \pre c es un identificador válido del curso que se quiere consultar
        \post Retorna el número de sesiones que tiene el curso c
        \coste Constante
    */
    int consultar_num_sesiones(int c) const;

    /** @brief Consulta cuál es la sesión número "s" (respecto el orden en el que se han leído) del curso c
        \pre c es un identificador válido de curso, s es un número entre 1 y el número total de sesiones de ese curso
        \post Retorna la Sesion que se encuentra en la posición "s" dentro del curso c
        \coste Logarítmico en Q (número de sesiones)
    */
    const Sesion& indicador_sesion(int c, int s) const;

    /** @brief Consulta cuál es la sesión que contiene un problema dado
        \pre c es un identificador válido de curso, p un identificador de un problema válido que pertenece al curso c
        \post Retorna la Sesion que contiene el problema p
        \coste Logarítmico en Q (número de sesiones)
    */
    const Sesion& indicador_sesion2(int c, string p) const;

    /** @brief Consulta, dentro de un curso, a qué sesión pertenece el problema p
        \pre c es el identificador del curso, p el identifcador del problema que estamos consultando
        \post Si el curso c no existe, o si el problema p no existe en la plataforma, o si p no pertenece al curso, salta un error. Si no, se busca en cuál de las sesiones del curso está el problema, y retorna el identificador de la sesión
        \coste Logarítmico en P (número de problemas)
    */
    string sesion_problema(int c, string p) const;


    //Modificadoras
    /** @brief Operación de leer y añadir un problema a la plataforma
        \pre p es el identificador del problema que se quiere añadir
        \post Si el problema con identificador p está en la plataforma, salta un error. Si no está, se ha añadido el problema de identificador p y se imprime el número de problemas de la plataforma después de añadirlo
        \coste Logarítmico en P (número de problemas)
    */
    void nuevo_problema(string p);


    /** @brief Operación de leer y añadir una sesión a la plataforma
        \pre s es el identificador de la sesión que se quiere añadir
        \post Si la sesión con identificador s está en la plataforma, salta un error. Si no está, se ha añadido la sesión de identificador s y se imprime el número de sesiones de la plataforma después de añadirla
        \coste (número de problemas de la sesión)*log(Q)
    */
    void nueva_sesion(string s);

    /** @brief Operación de leer y añadir un curso a la plataforma
        \pre <em>cierto</em>
        \post Se lee el curso que se desea añadir. La lectura nos proporciona información sobre si es correcto. Si lo es, se ha añadido a la plataforma (con el identificador "número de problemas que había en la plataforma" + 1). Si no es correcto, salta un error
    */
    void nuevo_curso();

    /** @brief Actualiza la información de un problema de la plataforma
        \pre p es un problema correcto de la plataforma, r indica si p se ha resuelto con éxito o no
        \post Se ha modificado el problema p de la plataforma, añadiéndole uno al número de envío total. Además, se ha añadido un envío más al número de envíos correctos si r era true
        \coste Logarítmico en P (número de problemas)
    */
    void actualizar_problema_plataforma(string p, bool r);

    /** @brief Operación de actualizar los stats de un curso
        \pre c es el identificador del curso. Un usuario de Plataforma_usuarios se acaba de inscribir un el curso. "completado" es true si el usuario en cuestión ya tiene resueltos todos los problemas del curso resueltos, false si no
        \post Se ha modificado el curso c de la plataforma, añadiendo uno al número total de inscritos (si el usuario no tenía todos los problemas resueltos), o bien añadiendo uno al número total de completados (si lo tenía todo resuelto). En ambos casos, retorna el número de usuarios inscritos en el curso tras las modificaciones
        \coste Constante
    */
    int modificar_stats_curso (int c, bool completado);

    /** @brief Operación de modificar un curso para desinscribir un usuario
        \pre c es el identificador del curso. Un usuario de Plataforma_usuarios acaba de completar el curso (si completado es true), o se ha dado de baja (si completado es false)
        \post Se ha modificado el curso c de la plataforma, restándole uno al número de usuarios inscritos en él. Además, se ha sumado uno al número de completados del curso en cuestión si el usuario había resuelto todos los problemas de éste
        \coste Constante
    */
    void restar_inscritos(int c, bool completado);


    //Lectura y escritura
    /** @brief Lectura de un conjunto de problemas para inicializar la plataforma
        \pre <em>cierto</em>
        \post Se ha leído un número entero P, seguido de P problemas y estos pasan a formar parte de la plataforma de material
        \coste P * logP
    */
    void leer_cj_problemas();

    /** @brief Lectura de un conjunto de sesiones para inicializar la plataforma
        \pre <em>cierto</em>
        \post Se ha leído un número entero Q, seguido de Q sesiones y pasan a formar parte de la plataforma
        \coste Q * logQ
    */
    void leer_cj_sesiones();

    /** @brief Lectura de un conjunto de cursos para inicializar la plataforma
        \pre <em>cierto</em>
        \post Se ha leído un número entero N, seguido los N cursos y pasan a formar parte de la plataforma
    */
    void leer_cj_cursos();

    /** @brief Lectura de un curso
        \pre <em>cierto</em>
        \post Se ha leído un curso y se ha comprobado que sea correcto (es decir, que no haya ningún problema repetido entre las sesiones). Si es correcto, retorna true y se ha añadido el curso a la plataforma. Si no, retorna false y no lo ha añadido
    */
    bool leer_curso();

    /** @brief Escritura de los problemas de la plataforma
        \pre <em>cierto</em>
        \post Se escriben en el canal de salida todos los problemas de la plataforma, ordenados por ratio (de menor a mayor) (para cada problema se escribe: identificador, envíos totales, envíos correctos y ratio)
    */
    void listar_problemas() const;

    /** @brief Escritura de un problema de la plataforma
        \pre p es el identificador del problema que se quiere escribir
        \post Si p no está en la plataforma, salta un error. Si está, se imprime la información del problema (identificador, envíos totales, envíos correctos y ratio)
        \coste Logarítmico
    */
    void escribir_problema(string p) const;

    /** @brief Escritura de las sesiones de la plataforma
        \pre <em>cierto</em>
        \post Se escriben en el canal de salida todas las sesiones de la plataforma, ordenadas por identificador (de menor a mayor) (para cada sesión se escribe también el número de problemas que la forman y la secuencia de identificadores de estos(en postorden))
        \coste Cuadrático: (Número de sesiones) * (Número de problemas de la sesión)
    */
    void listar_sesiones() const;

    /** @brief Escritura de una sesión de la plataforma
        \pre s es el identifcador de la sesión que se quiere escribir
        \post Si s no está en la plataforma, salta un error. Si está, se imprime la información de la sesión s (identificador, número de problemas, e identificadores (en postorden) de los problemas)
        \coste (número de problemas de la sesión) * (logQ)
    */
    void escribir_sesion(string s) const;

    /** @brief Escritura de los cursos de la plataforma
        \pre <em>cierto</em>
        \post Se escriben en el canal de salida todos los cursos de la plataforma, ordenados por identificador (de menor a mayor) (para cada curso se escribe: el número de usuarios que lo han completado, el número de usuarios inscritos, número de sesiones que lo forman y los identificadores de las sesiones)
        \coste Lineal en N (numero de cursos)
    */
    void listar_cursos() const;

    /** @brief Escritura de un curso de la plataforma
        \pre c es el identifcador del curso que se quiere escribir
        \post Si c no está en la plataforma, salta un error. Si está, se imprime la información del curso (número de usuarios que lo han completado, número de usuarios inscritos, número de sesiones que lo forman y los identificadores de las sesiones)
        \coste Constante
    */
    void escribir_curso(int c) const;

private:
    /** @brief Función de ordenación del vector de Problemas por ratio
        \pre p1 y p2 son dos elementos del vector que se quieren comparar
        \post Retorna true si el ratio del primer problema es mayor al del segundo, o si los ratios son iguales pero el string del primero es mayor
    */
    static bool comp_ratios(const pair <pair<string,Problema>, double>& p1, const pair <pair<string,Problema>, double>& p2);
};
#endif
