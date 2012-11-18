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
    Instancia instancia; // De momento accedo asi a los datos de los paquetes

    void moverPaquete(unsigned paquete, unsigned contenedor_destino);
    bool esFactible();
    vector<unsigned> paquetesDelContenedor(unsigned);

public:
    Solucion(){};
    Solucion(Instancia);    // Genera una solucion inicial. Puede que haya varias formas, entonces hacer metodos diferentes para crearla.
    bool mejorarILS();

    // PARA BORRAR O NO
    void mostrar();

    // Getters
    inline unsigned getNumeroContenedores() { return numero_contenedores; }

};

#endif // SOLUCION_H
