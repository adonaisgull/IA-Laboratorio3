#include "../include/bpp.h"
#include <iostream>
#include <fstream>


using namespace std;

Bpp::Bpp(){

}

/*
Solucion Bpp::ILS(unsigned indice) {

    Solucion mejor;
    Solucion candidata;
    unsigned ultimo_cambio = 0;

    mejor=obtenerSolucionInicial(indice);

    do {

        candidata = mejor.mejorVecina();

        if(candidata.getNumeroContenedores < mejor.getNumeroContenedores){
        	mejor = candidata;
        	ultimo_cambio = 0;
        }
        else {
        	ultimo_cambio++;
        }

    } while(ultimo_cambio < paradaILS);
}
*/

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


















