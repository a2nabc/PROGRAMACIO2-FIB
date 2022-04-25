/** @file Problema.cc
    @brief Implementación de la clase Problema
*/

#include "Problema.hh"
                                                    //Constructora
Problema::Problema() {
    envios_totales = 0;
    envios_correctos = 0;
}
                                                    //Consultoras
double Problema::consultar_ratio() const
{
    return double(envios_totales + 1)/(envios_correctos + 1);
}

                                                    //Modificadoras
void Problema::anadir_envio_total_problema() {
    ++envios_totales;
}

void Problema::anadir_envio_correcto_problema() {
    ++envios_correctos;
}
                                                    //Escritura
void Problema::escribir_problema() const
{
    cout << "(" << envios_totales << "," << envios_correctos << "," << this->consultar_ratio() << ")" << endl;
}
