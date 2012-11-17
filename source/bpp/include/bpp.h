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

    Solucion ILS();
    Solucion GA();
    Solucion SA();
    Solucion GRASP();
    Solucion TS();
    Solucion VNS();

public:
    Bpp();
    void cargarInstancias(ifstream &);

    inline void setParadaILS(int parada) { paradaILS = parada; }
    vector<Solucion> lanzarEstudio();

};

#endif // BPP_H
