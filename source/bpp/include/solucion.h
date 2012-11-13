#ifndef SOLUCION_H
#define SOLUCION_H

#include "instancia.h"

class Solucion
{
private:
    unsigned numero_contenedores;
    vector<unsigned> capacidad_contenedores;
    vector<unsigned> solucion;

    void moverPaquete(unsigned desde, unsigned hasta);
    bool esFactible();

public:
    Solucion(Instancia); // Genera una solucion inicial. Puede que haya varias formas, entonces hacer metodos diferentes para crearla.
    Solucion generarMejorVecina();

};

#endif // SOLUCION_H
