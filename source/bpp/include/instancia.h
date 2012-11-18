#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <vector>
#include <string>

using namespace std;

class Instancia
{

private:
    string nombre;
    unsigned capacidad_contenedores;
    unsigned numero_paquetes;
    unsigned mejor_solucion;
    vector<unsigned> longitud_paquetes;

public:
    Instancia(string, unsigned, unsigned, unsigned, vector<unsigned>);

    inline string getNombre() { return nombre; }
    inline unsigned getCapacidadContenedores() { return capacidad_contenedores; }
    inline unsigned getNumeroPaquetes() { return numero_paquetes; }
    inline unsigned getMejorSolucion() { return mejor_solucion; }
    inline vector<unsigned> getLongitudPaquetes(){ return longitud_paquetes; }

    // BORRAR
    void mostrar();

    unsigned obtenerLongitud(unsigned); // Recibe el ID del paquete para devolver su longitud
    unsigned obtenerPaquete();  // devuelve el ID de un paquete segun un criterio de seleccion. Quiza se pueda poner una opcion (azar, mayor, menor)

};

#endif // INSTANCIA_H
