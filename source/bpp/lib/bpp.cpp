#include "../include/bpp.h"
#include <iostream>
#include <fstream>

using namespace std;

Bpp::Bpp(){

}

Solucion Bpp::ILS(unsigned indice) {

    // El indice es el indice de la instancia con la que se va a trabajar
    Solucion maximo;
    Solucion maximo_local;
    Solucion vecina;
    bool maximo_local_econtrado;
    unsigned ultimo_cambio = 0;
    unsigned busquedas_de_vecina = 0;

    maximo_local = obtenerSolucionInicial(indice); // Creamos una solucion inicial factible
    maximo = maximo_local;      // La unica solucion que tenemos, es la mejor inicialmente

    cout << "maximo inicial: ";
    maximo.mostrar();

    do {        
        maximo_local_econtrado = false;
        do {
            // Buscamos el maximo local
            vecina = maximo_local.vecinaMasVacio_menosEspacio();        // Obtenemos una vecina a partir de maximo local actual
            busquedas_de_vecina++;

            if(vecina.getNumeroContenedores() <= maximo_local.getNumeroContenedores())  // Si se mejora o se iguala el maximo local lo cambiamos
                maximo_local = vecina;
            else
                maximo_local_econtrado = true;

        } while(!maximo_local_econtrado && busquedas_de_vecina < 100000);

        if(maximo_local.getNumeroContenedores() <= maximo.getNumeroContenedores()){
            maximo = maximo_local;  // Aceptamos el maximo local como mejor solucion si igual o mejor el numero de contenedores
            ultimo_cambio = 0;
            cout << "maximo mejorado: ";
            maximo_local.mostrar();
        }
        else {
            ultimo_cambio++;
        }

        maximo_local = obtenerSolucionInicial(indice); // Obtenemos otra solucion inicial diferente

    } while(ultimo_cambio < 100000); // este control es valido si dentro de mejorarILS, la mejor no siempre se hace igual

    return maximo;
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


















