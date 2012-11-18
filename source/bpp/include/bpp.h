#ifndef BPP_H
#define BPP_H

#include "instancia.h"
#include "solucion.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Bpp {

private:

    unsigned paradaILS;
    vector<Instancia> instancias;
    unsigned numero_instancias;



    // Métodos que implementan las heuristicas. Reciben el indice de la instancia y devuelven una solucion
    Solucion ILS(unsigned);
    Solucion GA(unsigned);
    Solucion SA(unsigned);
    Solucion GRASP(unsigned);
    Solucion TS(unsigned);
    Solucion VNS(unsigned);

public:
    Bpp();
    void cargarInstancias(ifstream &);
    Solucion obtenerSolucionInicial(unsigned);  // Devuelve una solucion inicial a partir del indice de la instancia que se le pasa

    inline unsigned getNumeroInstancias() { return numero_instancias; }
    inline void setParadaILS(int parada) { paradaILS = parada; }
    vector<Solucion> lanzarEstudio();

};

#endif // BPP_H
