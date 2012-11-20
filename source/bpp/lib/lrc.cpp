
#include "../include/lrc.h"
#include "../include/paso.h"
#include <stdlib.h>

void Lrc::insertarPaso(Paso paso) {

    // Los mejores pasos estarán al final del vector y los peores al principio

    Paso aux;
    pasos.push_back(paso);  // Lo metemos por detrás suponiendo que será mejor

    for(unsigned i=pasos.size()-1; i>=1; i--){      // Lo movemos hasta su sitio real en el vector
        if(pasos[i].getCapacidad() > pasos[i-1].getCapacidad()){
            aux = pasos[i];
            pasos[i] = pasos[i-1];
            pasos[i-1] = aux;
        }
    }

    // Si hemos metido mas pasos del limite eliminamos el primero del vector, que será el peor

    if(pasos.size() > t)
        pasos.erase(pasos.begin());
}

Paso Lrc::obtenerMejorPaso(){

    return pasos[pasos.size()-1];       // El ultimo paso del vector será el mejor

}

Paso Lrc::obtenerPasoAleatorio(){

    return pasos[rand() % size()];
}
