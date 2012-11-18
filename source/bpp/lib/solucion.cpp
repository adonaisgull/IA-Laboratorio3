#include "../include/solucion.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

Solucion::Solucion(){


}

Solucion::Solucion(Instancia instancia) {

    unsigned longitud_paquete_actual;
    unsigned contenedor_actual;
    unsigned aleatorio;
    unsigned indice_paquete_actual;
    vector<unsigned> paquetes_por_insertar;

    // Inicializamos la solucion con un unico contenedor con capacidad maxima
    solucion = vector<unsigned>(instancia.getNumeroPaquetes(), 0);
    capacidad_contenedores = vector<unsigned>(1, instancia.getCapacidadContenedores());

    for(unsigned i=0; i<instancia.getNumeroPaquetes(); i++)
        paquetes_por_insertar.push_back(i);

    contenedor_actual = 0;

    while(paquetes_por_insertar.size() > 0) {

        aleatorio = rand() % paquetes_por_insertar.size();      // Obtenemos un indice aleatorio de los que quedan
        indice_paquete_actual = paquetes_por_insertar[aleatorio];
        longitud_paquete_actual = instancia.getLongitudPaquetes()[indice_paquete_actual];

        paquetes_por_insertar.erase(paquetes_por_insertar.begin() + aleatorio); // Eliminamos el indice de los paquetes que quedan

        if(longitud_paquete_actual > capacidad_contenedores[contenedor_actual]){
            contenedor_actual++;
            capacidad_contenedores.push_back(instancia.getCapacidadContenedores());
        }

        solucion[indice_paquete_actual] = contenedor_actual;
        capacidad_contenedores[contenedor_actual] -= longitud_paquete_actual;
    }

    // Actualizamos el numero de contenedores para tener una solucion inicializada
    numero_contenedores = contenedor_actual+1;
}

void Solucion::mostrar(){

    cout << "Numero de contenedores: " << numero_contenedores << endl;
/*
    for(unsigned i=0; i<solucion.size(); i++){
        cout << i << " -> " << solucion[i] << endl;
    }
    */
}
