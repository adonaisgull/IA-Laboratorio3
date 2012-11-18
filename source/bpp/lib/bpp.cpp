#include "../include/bpp.h"
#include <iostream>
#include <fstream>

using namespace std;

Bpp::Bpp(){

}

Solucion Bpp::ILS(unsigned indice) {

    // El indice es el indice de la instancia con la que se va a trabajar
    Solucion mejor;
    Solucion candidata;
    unsigned ultimo_cambio = 0;

    candidata = obtenerSolucionInicial(indice); // Creamos una solucion inicial factible
    mejor = candidata;      // La unica solucion que tenemos, es la mejor inicialmente

    do {
        //cout << "-> Solucion Inicial: ";
        //candidata.mostrar();

        while(candidata.mejorarILS());  // mejoramos la candidata hasta obtener maximo local
        //cout << "   Maximo local: ";
        //candidata.mostrar();

        if(candidata.getNumeroContenedores() < mejor.getNumeroContenedores()){
            mejor = candidata;  // Aceptamos el maximo local como mejor solucion si igual o mejor el numero de contenedores
            ultimo_cambio = 0;
        }
        else {
            ultimo_cambio++;
        }

        candidata = obtenerSolucionInicial(indice); // Obtenemos otra solucion inicial diferente

    } while(ultimo_cambio < 100); // este control es valido si dentro de mejorarILS, la mejor no siempre se hace igual

    return mejor;
}

void Bpp::cargarInstancias(ifstream &fichero){

    unsigned numero_instancias;
    unsigned capacidad_contenedor;
    unsigned numero_paquetes;
    unsigned mejor_solucion;
    string nombre_instancia;
    vector<unsigned> longitud_paquetes = vector<unsigned>(0);
    unsigned longitud;

    fichero >> numero_instancias;

    this->numero_instancias = numero_instancias;

    for(unsigned i=0; i<numero_instancias; i++){     // bucle para leer las diez instancias
        fichero >> nombre_instancia;
        fichero >> capacidad_contenedor;
        fichero >> numero_paquetes;
        fichero >> mejor_solucion;

        for(unsigned j=0; j<numero_paquetes; j++){       // leemos el numero de paquetes
            fichero >> longitud;
            longitud_paquetes.push_back(longitud);
        }

        instancias.push_back(Instancia(nombre_instancia, capacidad_contenedor, numero_paquetes, mejor_solucion, longitud_paquetes));        // Añadimos la instancia
        longitud_paquetes.clear();
    }
}

Solucion Bpp::obtenerSolucionInicial(unsigned indice){

    Solucion solucion(instancias[indice]);

    return solucion;
}


















