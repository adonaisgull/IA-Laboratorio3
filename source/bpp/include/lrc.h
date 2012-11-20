#ifndef LRC_H
#define LRC_H

#include <vector>
#include <iostream>
#include "paso.h"

using namespace std;

class Lrc {

private:
    unsigned t;                 // tamaño maximo de la lista
    vector<Paso> pasos;         // lista mejores pasos

public:

    inline Lrc(unsigned _t){ t = _t; pasos = vector<Paso>(0); }
    unsigned size() { return pasos.size(); }

    void insertarPaso(Paso paso);   // intenta insertar un candidato
    Paso obtenerMejorPaso();
    Paso obtenerPasoAleatorio();
    inline void borrar() { pasos  =vector<Paso>(0); }
};


#endif // LRC_H
