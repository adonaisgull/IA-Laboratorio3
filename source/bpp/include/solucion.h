#ifndef SOLUCION_H
#define SOLUCION_H

#include "instancia.h"
#include <vector>

using namespace std;

class Solucion
{
private:
    unsigned numero_contenedores;
    vector<unsigned> capacidad_contenedores;
    vector<unsigned> solucion;

    void moverPaquete(unsigned desde, unsigned hasta);
    bool esFactible();

public:
    Solucion(Instancia);    // Genera una solucion inicial. Puede que haya varias formas, entonces hacer metodos diferentes para crearla.
    Solucion generarMejorVecina();

    inline unsigned getNumeroContenedores() { return numero_contenedores; }

};

#endif // SOLUCION_H
