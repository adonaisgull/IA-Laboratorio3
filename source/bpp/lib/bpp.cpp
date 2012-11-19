#include "../include/bpp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

Bpp::Bpp(){

}

Solucion Bpp::ILS(unsigned instancia) {

    Solucion maximo;
    Solucion maximo_local;
    Solucion vecina;
    bool maximo_local_econtrado;
    unsigned ultimo_cambio = 0;
    unsigned busquedas_de_vecina = 0;

    maximo_local = obtenerSolucionInicial(instancia); // Creamos una solucion inicial factible a partir de una instancia
    maximo = maximo_local;      // La unica solucion que tenemos, es la mejor inicialmente

    do {        
        maximo_local_econtrado = false;
        do {
            // Buscamos el maximo local
            //vecina = maximo_local.vecinaMasVacio_MenosEspacio();        // Obtenemos una vecina a partir de maximo local actual
            //vecina = maximo_local.vecinaMasVacio_Primero();
            //vecina = maximo_local.vecinaAzar_Primero();
            vecina = maximo_local.vecinaAzar_MenosEspacio();
            //vecina = maximo_local.vecinaAzar_Azar();
            busquedas_de_vecina++;

            if(vecina.getNumeroContenedores() <= maximo_local.getNumeroContenedores())  // Si se mejora o se iguala el maximo local lo cambiamos
                maximo_local = vecina;
            else
                maximo_local_econtrado = true;

        } while(!maximo_local_econtrado && busquedas_de_vecina < 1000);

        // PARA COMPROBAR SI ES MEJOR SOLUCION HACER LO DE LA SUMA DE CUADRADOS
        if(maximo_local.getNumeroContenedores() < maximo.getNumeroContenedores()){
            maximo = maximo_local;      // Aceptamos el maximo local como mejor solucion mejora el numero de contenedores
            ultimo_cambio = 0;
            //cout << "maximo mejorado: ";
            //maximo_local.mostrar();
        }
        else {
            ultimo_cambio++;
        }

        maximo_local = obtenerSolucionInicial(instancia); // Obtenemos otra solucion inicial diferente

    } while(ultimo_cambio < 10000); // este control es valido si dentro de mejorarILS, la mejor no siempre se hace igual

    return maximo;
}

Solucion Bpp::SA(unsigned instancia){

    Solucion solucion;
    Solucion vecina;
    double alfa = 0.995;
    double c = 0.999;
    double aleatorio;
    unsigned k = 1000;        // frecuencia con la que se bajara la probabilidad
    unsigned iteraciones;

    // Obtenemos una solucion inicial a partir de la instancia
    solucion = obtenerSolucionInicial(instancia);
    //mejor_solucion = solucion_inicial;

    iteraciones = 0;
    do {
        iteraciones++;
        vecina = solucion.vecinaAzar_MenosEspacio();

        // Si la vecina mejora la solucion la aceptamos
        if(vecina.getNumeroContenedores() < solucion.getNumeroContenedores()) {
            solucion = vecina;
            //solucion.mostrar();
        }
        else {  // Si no la mejora, la aceptamos con probabilidad c
            aleatorio = rand() % 1000 +1;
            aleatorio = aleatorio/1000;

            if(aleatorio <= c)
                solucion = vecina;
        }

        if(iteraciones > k){
            c = c * alfa;
            iteraciones = 0;
        }

    } while(c > 0.0001);

    return solucion;
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


















