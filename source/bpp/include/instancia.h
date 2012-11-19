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
    Instancia() {};
    Instancia(string, unsigned, unsigned, unsigned, vector<unsigned>);

    inline string getNombre() { return nombre; }
    inline unsigned getCapacidadContenedores() { return capacidad_contenedores; }
    inline unsigned getNumeroPaquetes() { return numero_paquetes; }
    inline unsigned getMejorSolucion() { return mejor_solucion; }
    inline vector<unsigned> getLongitudPaquetes(){ return longitud_paquetes; }

    inline unsigned getLongitudPaquete(unsigned indice) { return longitud_paquetes[indice]; } // Recibe el ID del paquete para devolver su longitud
};

#endif // INSTANCIA_H
