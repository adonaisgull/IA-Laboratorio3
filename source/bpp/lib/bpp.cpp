#include "../include/bpp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// METODO PARA REALIZAR LA BUSQUEDA 'ITERATED LOCAL SEARCH'
Solucion Bpp::ILS(unsigned instancia) {

    Solucion maximo;
    Solucion maximo_local;
    Solucion vecina;
    bool maximo_local_econtrado;
    unsigned ultimo_cambio = 0;
    unsigned busquedas_de_vecina = 0;

    maximo_local = obtenerSolucionInicial(instancia);   // Creamos una solucion inicial factible a partir de una instancia
    maximo = maximo_local;                              // La unica solucion que tenemos, es la mejor inicialmente

    do {        
        maximo_local_econtrado = false;
        do {
            // Buscamos el maximo local
            vecina = maximo_local.vecinaAzar_MenosEspacio();
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
        }
        else {
            ultimo_cambio++;
        }
        maximo_local = obtenerSolucionInicial(instancia); // Obtenemos otra solucion inicial diferente

    } while(ultimo_cambio < 10000); // este control es valido si dentro de mejorarILS, la mejor no siempre se hace igual

    return maximo;
}

// METODO PARA REALIZAR BUSQUEDA 'SIMULATED ANNELING'
Solucion Bpp::SA(unsigned instancia){

    Solucion solucion;
    Solucion vecina;
    double alfa = 0.995;        // Factor de reduccion para la constante C
    double c = 0.987;           // Probabilidad de aceptacion de vecinas peores
    unsigned k = 233;           // frecuencia con la que se bajara la probabilidad
    double aleatorio;
    unsigned iteraciones;

    // Obtenemos una solucion inicial a partir de la instancia
    solucion = obtenerSolucionInicial(instancia);

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

// METODO PARA REALIZAR LA BUSQUEDA 'TABU SEARCH'
Solucion Bpp::TS(unsigned instancia){

    Solucion solucion;
    Solucion vecina;
    unsigned t = 7;             // Tamaño maximo de la memoria
    vector<unsigned> tabu;      // Memoria de los ultimos paquetes movidos
    bool en_tabu;
    unsigned ultimo_paquete;
    unsigned ultimo_cambio;

    solucion = obtenerSolucionInicial(instancia);

    do {
        vecina = solucion.vecinaAzar_MenosEspacio();

        if(vecina.getNumeroContenedores() <= solucion.getNumeroContenedores()){
            en_tabu = false;
            ultimo_paquete = vecina.getUltimoPaqueteMovido();
            for(unsigned i=0; i<tabu.size(); i++){
                if(tabu[i] == ultimo_paquete)
                    en_tabu = true;
            }
            if(!en_tabu){
                solucion = vecina;                  // Aceptamos la solucion vecina
                tabu.push_back(ultimo_paquete);     // Añadimos el ultimo paquete movido al final de la lista tabu
                ultimo_cambio = 0;

                if(tabu.size() > t){                // Si la lista ya esta llena, quitamos el primer elemnto
                    tabu.erase(tabu.begin());
                }
            }
        }

        ultimo_cambio++;

    } while(ultimo_cambio < 1000);

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

// METODO PARA OBETENER UNA SOLUCION INICIAL
Solucion Bpp::obtenerSolucionInicial(unsigned indice){

    Solucion solucion(instancias[indice]);

    return solucion;
}

// METODO PARA LANZAR TODAS LAS BUSQUEDAS CON CADA UNA DE LAS INSTANCIAS
void Bpp::lanzarEstudio(){

    Solucion solucion;

    for(unsigned i=0; i<numero_instancias; i++){
        cout << "Instancia:      " << instancias[i].getNombre() << endl;
        cout << "Mejor solucion: " << instancias[i].getMejorSolucion() << endl;

        cout << "-> Calculando ILS... ";
        solucion = ILS(i);
        solucion.mostrar();
        cout << endl;

        cout << "-> Calculando SA...  ";
        solucion = SA(i);
        solucion.mostrar();
        cout << endl;

        cout << "-> Calculando TS...  ";
        solucion = TS(i);
        solucion.mostrar();
        cout << endl;

        cout << "--------------------------------------" << endl;
    }
}
















