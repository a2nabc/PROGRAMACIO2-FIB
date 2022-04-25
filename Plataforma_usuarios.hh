/** @file Plataforma_usuarios.hh
    @brief Especificación de la clase Plataforma_usuarios
*/

#ifndef PLATAFORMA_USUARIOS_HH_
#define PLATAFORMA_USUARIOS_HH_

#include "Plataforma_material.hh"
#include "Usuario.hh"


/** @class Plataforma_usuarios
    @brief Representa la información y las operaciones asociadas al "Conjunto de usuarios" que forman la plataforma Evaluator.

    La información de la Plataforma de usuarios viene dada por una estructura que contiene todos los Usuarios, donde cada uno está asociado a un identificador distinto.

    Las operaciones son: consultora del curso en el que está inscrito un usuario dado, lectura de un conjunto de usuarios (para inicializar la plataforma), escritura de todo el conjunto de usuarios, escritura de un usuario dado, escritura de los problemas enviables de un usuario dado, escritura de los problemas correctos de un usuario dado. Las operaciones modificadoras son: dar de alta un usuario nuevo, dar de baja un usuario existente, inscribir un usuario existente en un curso dado, qu un usuario realice un envio de uno de sus problemas enviables.

*/

class Plataforma_usuarios
{

private:
      /** @brief Estructura que contiene todos los usuarios inscritos actualmente en la plataforma */
      map<string, Usuario> Cj_usuarios;

public:
      //Constructora
      /** @brief Creadora de la plataforma de usuarios.
        Se ejecuta automáticamente al declarar una plataforma de usuarios
        \pre <em>cierto</em>
        \post Se ha creado una plataforma de usuarios vacía
        \coste Constante
      */
      Plataforma_usuarios();

      //Consultoras
      /** @brief Consulta en qué curso está inscrito un usuario
        \pre u es el identifcador del usuario
        \post Si el usuario no exite en la plataforma, salta un error. Si existe, se imprime un 0 si no está en ningún curso, o el identificador del curso (si está en alguno)
        \coste Logarítmico en M (número de usuarios)
      */
      void curso_usuario(string u) const;

      //Modificadoras
      /** @brief Operación de dar de alta un usuario
        \pre u contiene el nombre de usuario que se desea dar de alta
        \post Se comprueba si el nombre u ya existe en la plataforma. Si está, salta un error. Si no está, se añade el usuario a la plataforma y se imprime el número total de usuarios después de añadirlo
        \coste Logarítmico en M (número de usuarios)
      */
      void alta_usuario(string u);

      /** @brief Operación de dar de baja un usuario
        \pre u contiene el nombre de usuario que se desea dar de baja, pm es la plataforma de material que contiene la información sobre problemas, sesiones y cursos
        \post Se comprueba si el usuario u existe en la plataforma. Si no está, salta un error. Si está, se elimina de la plataforma, se modifica el curso en cuestión (para desinscribir un usuario) y se imprime el número total de usuarios después de borrarlo
        \coste Logarítmico en M (número de usuarios)
      */
      void baja_usuario(string u, Plataforma_material& pm);

      /** @brief Operación de inscribir un usuario en un curso
        \pre c es el identificador de un curso, u es el nombre de usuario que desea inscribirse en el curso c, pm es la plataforma de material que contiene la información sobre problemas, sesiones y cursos
        \post Se comprueba si el usuario existe. Si no existe, salta un error. A continuación se comprueba si el curso existe en la plataforma pm, si no existe salta un error. También se comprueba si u está inscrito en algún curso. Si lo está, salta un error. En caso contrario, se modifica c (que pertenece a pm) para inscribir el usuario u a c, e imprime el número de usuarios inscritos en c. Además, después de modificar el curso (de Plataforma_material) también modifica el parámetro implícito inscribiéndolo al curso en cuestión y actualizando su historial de "enviables"
      */
      void inscribir_curso(string u, int c, Plataforma_material& pm);

      /** @brief Operación de procesar un envío
        \pre u es el identificador del usuario que realiza el envío; pm es la plataforma de material que contiene la información sobre problemas, sesiones y cursos; p es el identifcador del problema que envía. r vale 1 si el problema se resuelve con éxito, 0 si no
        \post Se suma uno al número de envíos totales del usuario u. Se suma uno al número de envíos totales del problema p. Si u tiene 0 envíos para el problema p (esto lo podemos hacer porque tenemos garantizado que está entre los enviables de u), se suma uno al recuento de intentados de u. Si tenía un intento o más, se suma uno al número de envíos para ese problema intentado. Si r es 0, no se hace nada más. Si r es 1: 1. se suma uno al número de envíos correctos del problema p. 2. Se elimina la pareja "problema, número de envíos" del historial de "enviables" del usuario, y se añade la misma al historial de problemas verdes del usuario. Además, se añade al historial de "enviables" el/los problemas de los cuales el problema que acaba de resolver era prerrequisito. Por último, si el historial de "enviables" de u ha quedado vacío (es decir, se ha completado el curso), se desinscribe el usuario del curso y se resta uno al número de usuarios inscritos en el curso
      */
      void envio(string u, string p, bool r, Plataforma_material& pm);

      //Lectura y escritura
      /** @brief Lectura de un conjunto de usuarios para inicializar la plataforma
        \pre <em>cierto</em>
        \post Se ha leído un entero M, seguido de M usuarios y pasan a formar parte de la plataforma
        \coste M * logM
      */
      void leer_cj_usuarios();

      /** @brief Escritura de los usuarios de la plataforma
        \pre <em>cierto</em>
        \post Se escriben en el canal de salida todos los usuarios de la plataforma, ordenados por identificador (de menor a mayor) (para cada usuario se escribe: número de envíos totales, número de problemas "verdes", número de problemas intentados, identificador del curso en el que está inscrito (si lo está en alguno) o 0 (si no está en ninguno))
        \coste Lineal en M (número de usuarios)
      */
      void listar_usuarios() const;

      /** @brief Escritura de un usuario de la plataforma
        \pre u es el identifcador del usuario que se quiere escribir
        \post Si u no está en la plataforma de usuarios, salta un error. Si está, se imprime la información del usuario (número de envíos totales, número de problemas "verdes", número de problemas intentados, identificador del curso en el que está inscrito (si lo está en alguno) o 0 (si no está en ninguno))
        \coste M * logM
      */
      void escribir_usuario(string u) const;

      /** @brief Escritura de todos los problemas correctos de un usuario
        \pre u es el identificador del usuario
        \post Se comprueba si el usuario existe en la plataforma. Si no existe, salta un error. Si existe, se imprimen los identificadores de los problemas realizados con éxito, y el número de envíos totales que u ha hecho a cada problema
        \coste (Número de problemas resueltos de u) * logM
      */
      void problemas_resueltos(string u) const;

      /** @brief Escritura de los problemas enviables de un usuario
        \pre u es el identificador del usuario
        \post Si u no existe en la plataforma, salta un error. Si u no está inscrito en ningún curso, salta un error. Si no, se escriben todos los problemas que u tiene enviados sin éxito (o sin enviar) pero tiene todos los problemas prerrequisito resueltos, es decir, todos los enviables
        \coste (Número de problemas resueltos de u) * logM
      */
      void problemas_enviables(string u) const;
};
#endif
