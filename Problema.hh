/** @file Problema.hh
    @brief Especificación de la clase Problema
*/
#ifndef _PROBLEMA_HH_
#define _PROBLEMA_HH_

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Problema
    @brief Representa la información y las operaciones asociadas a un problema.

     La información de un problema viene dada por el número de envíos totales al problema, y por el número de envíos correctos que se le han hecho

     Las operaciones son: la consultora de la ratio, las modificadoras de añadir un envio total y un envio correcto, y la escritura de un problema.

*/

class Problema
{

private:
    /** @brief Número de veces que se ha hecho un envío a este problema */
    int envios_totales;
    /** @brief Número de envíos al problema que han sido juzgados como correctos */
    int envios_correctos;

public:
                                                    //Constructora
    /** @brief Creadora por defecto.
        Se ejecuta automáticamente al declarar un problema
        \pre <em>cierto</em>
        \post Se ha creado un problema sin identificador, ni envíos totales, ni envíos verdes
    */
    Problema();

                                                    //Consultoras
    /** @brief Consultora de ratio
        \pre <em>cierto</em>
        \post El resultado es el valor de la ratio (t+1)/(e+1) del parámetro implícito
        \coste Constante
    */
    double consultar_ratio() const;

                                                    //Modificadoras
    /** @brief Añade un envío al número total de envíos hechos al problema
        \pre <em>cierto</em>
        \post Se ha añadido en el parámetro implícito un envío más al número total de envíos que los usuarios de la plataforma han hecho a este problema
        \coste Constante
    */
    void anadir_envio_total_problema();

    /** @brief Añade un envío correcto al número total de envíos correctos hechos al problema
        \pre <em>cierto</em>
        \post Se ha añadido en el parámetro implícito un envío correcto más al número de envíos correctos que los usuarios de la plataforma han hecho a este problema
        \coste Constante
    */
    void anadir_envio_correcto_problema();


                                                    //Escritura
    /** @brief Operación de escritura de un problema
        \pre <em>cierto</em>
        \post Se ha escrito el contenido del parámetro implícito (identificador, envíos totales, envíos correctos y ratio)
        \coste Constante
    */
    void escribir_problema() const;
};
#endif
