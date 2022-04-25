/** @file Usuario.hh
    @brief Especificación de la clase Usuario
*/

#ifndef USUARIO_HH_
#define USUARIO_HH_

#include "Curso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <utility>
#endif

/** @class Usuario
    @brief Representa la información y las operaciones asociadas a un usuario.

     La información de un usuario viene dada por los atributos: curso en el que está inscrito (si lo está), conjunto de problemas verdes (identifcador de problema y número de intentos), conjunto de problemas enviables (identificador de problema y número de intentos), stats (número de envíos que el usuario ha hecho en total, y número de problemas distintos que ha intentado).

     Las operaciones son: consultora del curso en el que el usuario está inscrito, consultora de si el usuario ha completado el curso en el que estaba inscrito, consultora de si un problema dado está resuelto por el usuario, escritura de un usuario, escritura de los problemas enviables o escritura de los problemas resueltos correctamente. Las operaciones modificadoras son: inscribir el usuario en un curso dado, desinscribirlo del curso en el que estaba, actualizar los stats de los problemas (tras haber realizado un envío), añadir un problema dado a los enviables.
*/

class Usuario
{
private:
    /** @brief Identificador del curso en que está inscrito, (el atributo vale 0 si no está en ningún curso) */
    int curso;
    /** @brief Número de envíos que el usuario ha hecho en total */
    int envios_totales;
    /** @brief Número de problemas distintos que el usuario ha intentado (es decir, ha hecho almenos un envío) */
    int intentados;
    /** @brief Estructura que contiene los identificadores de todos los problemas distintos que el usuario tiene los prerrequisitos cumplidos, con el número de envíos que ha hecho para cada problema */
    map<string, int> enviables;
    /** @brief Estructura que contiene los identificadores de todos los problemas resueltos correctamente, y el número de envíos para cada uno */
    map<string, int> verdes;

public:
    //Constructora
    /** @brief Creadora por defecto
      Se ejecuta automáticamente al declarar una cubeta.
      \pre <em>cierto</em>
      \post El resultado es un usuario no inscrito en ningún curso, y sin stats
      \coste Constante
    */
    Usuario();

    //Consultoras
    /** @brief Comprueba si actualmente el usuario está inscrito o no en algún curso
        \pre <em>cierto</em>
        \post Retorna el número del curso en el que el parámetro implícito está inscrito actualmente (si lo está), retorna 0 si no está inscrito en ninguno
        \coste Constante
    */
    int consultar_curso_usuario() const;

    /** @brief Consulta si el usuario ha completado el curso en el que está inscrito
        \pre el parámetro implícito está inscrito en algún curso (o bien lo estamos inscribiendo)
        \post Retorna true si el usuario tiene todos los problemas del curso resueltos
        \coste Constante
    */
    bool ha_completado_curso() const;

    /** @brief Informa sobre si un usuario ha resuelto un problema con éxito
        \pre p es el identificador del problema que queremos saber si está solucionado con éxito
        \post Retorna true si el problema con identificador p está entre los que el parámetro implícito ha solucionado con éxito. Si no, retorna false
        \coste Logarítmico en el número de problemas resueltos correctamente
    */
    bool esta_verdes_usuario(string id) const;

    //Modificadoras
    /** @brief Operación de inscripción en un curso
        \pre el parámetro implícito no está inscrito en ningún curso
        \post el parámetro implícito pasa a estar inscrito en el curso que tiene identificador "id_curso"
        \coste Constante
    */
    void inscribir_usuario(int id_curso);

    /** @brief Operación de desinscripción en un curso
        \pre el parámetro implícito está inscrito en un curso (y lo acaba de completar)
        \post el parámetro implícito ya no está inscrito en ningún curso. Retorna el id del último curso en el que estaba inscrito
        \coste Constante
    */
    int desinscribir();

    /** @brief Operación de desinscripción en un curso
        \pre el parámetro implícito está inscrito en un curso (y lo acaba de completar)
        \post el parámetro implícito ya no está inscrito en ningún curso. Retorna el id del último curso en el que estaba inscrito
        \coste Logarítmico en el número de problemas enviables
    */
    void actualizar_problemas(string p, int r);

    /** @brief Operación de añadir un problema al historial de problemas enviables
        \pre el problema p es enviable (ie, el parámetro implícito tiene resuelto correctamente su prerrequisito pero no el problema p)
        \post se ha añadido el problema (con cero intentos) en el historial de enviables
        \coste Logarítmico en el número de problemas enviables
    */
    void anadir_problema_enviable_usuario(string p);


    //Escritura
    /** @brief Operación de escritura de un usuario
        \pre <em>cierto</em>
        \post Se ha escrito el contenido del parámetro implícito (envíos totales, envíos correctos, número de problemas intentados e identificador del curso (si está en alguno) o "0" (si no está en ninguno))
        \coste Constante
    */
    void escribir_usuario() const;

    /** @brief Operación de escritura de los problemas realizados con éxito por un usuario
        \pre <em>cierto</em>
        \post Se ha escrito el listado de los identificadores de todos los problemas "verdes" del parámetro implícito, y junto a cada identificador se ha escrito el número total de envíos que el parámetro implícito ha hecho al problema
        \coste Lineal en el número de problemas correctos
    */
    void escribir_problemas_verdes_usuario() const;

    /** @brief Operación de escritura de los problemas enviables de un usuario
        \pre <em>cierto</em>
        \post Se ha escrito (en preorden) el listado de los identificadores de todos los problemas "enviables" del parámetro implícito, y junto a cada identificador se ha escrito el número total de envíos que el parámetro implícito ha hecho al problema
        \coste Lineal en el número de problemas enviables
    */
    void escribir_problemas_enviables_usuario() const;
};
#endif
