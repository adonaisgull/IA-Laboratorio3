#include "../include/solucion.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

Solucion::Solucion(Instancia instancia) {

    unsigned longitud_paquete_actual;
    unsigned contenedor_actual;
    unsigned aleatorio;
    unsigned indice_paquete_actual;
    vector<unsigned> paquetes_por_insertar;

    // Inicializamos la solucion con un unico contenedor con capacidad maxima
    this->instancia = instancia;
    solucion = vector<unsigned>(instancia.getNumeroPaquetes(), 0);
    capacidad_contenedores = vector<unsigned>(1, instancia.getCapacidadContenedores());
    numero_contenedores = 1;

    for(unsigned i=0; i<instancia.getNumeroPaquetes(); i++)
        paquetes_por_insertar.push_back(i);

    contenedor_actual = 0;

    while(paquetes_por_insertar.size() > 0) {

        aleatorio = rand() % paquetes_por_insertar.size();      // Obtenemos un indice aleatorio de los que quedan
        indice_paquete_actual = paquetes_por_insertar[aleatorio];
        longitud_paquete_actual = instancia.getLongitudPaquete(indice_paquete_actual);

        paquetes_por_insertar.erase(paquetes_por_insertar.begin() + aleatorio); // Eliminamos el indice de los paquetes que quedan

        if(longitud_paquete_actual > capacidad_contenedores[contenedor_actual]){
            contenedor_actual++;
            numero_contenedores++;
            capacidad_contenedores.push_back(instancia.getCapacidadContenedores());
        }

        solucion[indice_paquete_actual] = contenedor_actual;
        capacidad_contenedores[contenedor_actual] -= longitud_paquete_actual;
    }

    // Actualizamos el numero de contenedores para tener una solucion inicializada
    //numero_contenedores = contenedor_actual+1;
}

// METODO BUSCAR VECINA. SEL PAQ: CONTENEDOR MAS VACIO; SEL CONT: MENOS ESPACIO TRAS CAMBIO
Solucion Solucion::vecinaMasVacio_MenosEspacio(){

    unsigned contenedor_origen = 0;                         // contenedor mas vacio
    vector<unsigned> paquetes_del_contenedor;               // paqutes del contenedor mas vacio
    unsigned paquete;                             // paquete mas largo del contenedor mas vacio
    unsigned contenedor_destino;                            // contenedor al que moveremos el paquete
    unsigned capacidad_minima;
    unsigned capacidad_contenedor_origen;
    Solucion vecina = this->getCopia();

    // Buscar el contenedor con mayor capacidad libre
    for(unsigned i=0; i<capacidad_contenedores.size(); i++)
        if(capacidad_contenedores[i] > capacidad_contenedores[contenedor_origen])
            contenedor_origen = i;

    // Obtenemos mayor paquete del contenedor mas vacio
    paquetes_del_contenedor = paquetesDelContenedor(contenedor_origen);
    paquete = paquetes_del_contenedor[0];
    for(unsigned i=0; i<paquetes_del_contenedor.size(); i++) {
        if(instancia.getLongitudPaquete(paquetes_del_contenedor[i]) > instancia.getLongitudPaquete(paquete)){
            paquete = paquetes_del_contenedor[i];
        }
    }

    // Buscamos el contenedor de destino, que sera aquel en el que el paquete seleccionado deje menos espacio libre
    capacidad_contenedor_origen = capacidad_contenedores[contenedor_origen];
    capacidad_minima = capacidad_contenedor_origen;

    for(unsigned i=0; i<capacidad_contenedores.size(); i++){
        if(i != contenedor_origen){
            if(instancia.getLongitudPaquete(paquete) <= capacidad_contenedores[i]){
                if((capacidad_contenedores[i] - instancia.getLongitudPaquete(paquete)) < capacidad_minima){
                    contenedor_destino = i;
                    capacidad_minima = capacidad_contenedores[i]-instancia.getLongitudPaquete(paquete);
                }
            }
        }
    }

    // Si el paquete cabe en otro contenedor minimizando su capacidad, lo metemos
    if(capacidad_minima < capacidad_contenedor_origen){
        vecina.moverPaquete(paquete, contenedor_destino);
    }
    else {      // Si no cabe en ninguno, se genera un nuevo contenedor y se mete
        vecina.meterPaqueteEnContenedorNuevo(paquete);
    }

    vecina.setUltimoPaqueteMovido(paquete); // Guardamos el ultimo paquete movido

    return vecina;
}

// METODO BUSCAR VECINA. SEL PAQ: CONTENEDOR MAS VACIO; SEL CONT: PRIMERO DONDE QUEPA
Solucion Solucion::vecinaMasVacio_Primero(){

    unsigned contenedor_origen;                         // contenedor mas vacio
    vector<unsigned> paquetes_del_contenedor;           // paqutes del contenedor mas vacio
    unsigned paquete;                                   // paquete mas largo del contenedor mas vacio
    Solucion vecina = this->getCopia();

    // Buscar el contenedor con mayor capacidad libre
    contenedor_origen = 0;
    for(unsigned i=0; i < numero_contenedores; i++)
        if(capacidad_contenedores[i] > capacidad_contenedores[contenedor_origen])
            contenedor_origen = i;

    // Obtenemos mayor paquete del contenedor mas vacio
    paquetes_del_contenedor = paquetesDelContenedor(contenedor_origen);
    paquete = paquetes_del_contenedor[0];
    for(unsigned i=0; i<paquetes_del_contenedor.size(); i++) {
        if(instancia.getLongitudPaquete(paquetes_del_contenedor[i]) > instancia.getLongitudPaquete(paquete)){
            paquete = paquetes_del_contenedor[i];
        }
    }

    // Intentamos meter ese paquete en el primero contenedor que quepa
    for(unsigned i= 0; i<numero_contenedores; i++){
        if(i != contenedor_origen){
            if(capacidad_contenedores[i] >= instancia.getLongitudPaquete(paquete)){
                vecina.moverPaquete(paquete, i);
                return vecina;
            }
        }
    }

    // Si no cupo en ningun contenedor creamos uno nuevo
    vecina.meterPaqueteEnContenedorNuevo(paquete);

    vecina.setUltimoPaqueteMovido(paquete); // Guardamos el ultimo paquete movido

    return vecina;
}

// METODO BUSCAR VECINA. SEL PAQ: AZAR; SEL CONT: MENOS ESPACIO TRAS CAMBIO
Solucion Solucion::vecinaAzar_MenosEspacio(){

    Solucion vecina = this->getCopia();
    unsigned paquete;
    unsigned contenedor_origen;
    unsigned contenedor_destino;
    unsigned capacidad_minima;
    unsigned capacidad_contenedor_origen;

    // Obtenemos un paquete al azar
    paquete = rand() % instancia.getNumeroPaquetes();
    contenedor_origen = getContenedorDelPaquete(paquete);

    // Buscamos el contenedor en que el deje menos espacio libre
    capacidad_contenedor_origen = capacidad_contenedores[contenedor_origen];
    capacidad_minima = capacidad_contenedor_origen;

    for(unsigned i=0; i<capacidad_contenedores.size(); i++){
        if(i != contenedor_origen){
            if(capacidad_contenedores[i] >= instancia.getLongitudPaquete(paquete)){     // Comprobamos si cabe el paquete
                if((capacidad_contenedores[i] - instancia.getLongitudPaquete(paquete)) < capacidad_minima){
                    contenedor_destino = i;     // Actualizamos el contenedor candidato
                    capacidad_minima = capacidad_contenedores[i]-instancia.getLongitudPaquete(paquete); // Actualizamos la capacidad minima encontrada
                }
            }
        }
    }

    if(capacidad_minima < capacidad_contenedor_origen)
        vecina.moverPaquete(paquete, contenedor_destino);
    else
        vecina.meterPaqueteEnContenedorNuevo(paquete);

    vecina.setUltimoPaqueteMovido(paquete); // Guardamos el ultimo paquete movido

    return vecina;
}

// METODO BUSCAR VECINA. SEL PAQ: AZAR; SEL CONT: PRIMERO DONDE QUEPA
Solucion Solucion::vecinaAzar_Primero(){

    Solucion vecina = this->getCopia();
    unsigned paquete = rand() % instancia.getNumeroPaquetes();  // Obtenemos un paqute al azar
    unsigned contenedor_origen = getContenedorDelPaquete(paquete);

    // Intentamos meter ese paquete en el primero contenedor que quepa
    for(unsigned i= 0; i<numero_contenedores; i++){
        if(i != contenedor_origen){
            if(capacidad_contenedores[i] >= instancia.getLongitudPaquete(paquete)){
                vecina.moverPaquete(paquete, i);
                return vecina;
            }
        }
    }

    // Si no se pudo meter, entonces lo metemos en un contenedor nuevo
    vecina.meterPaqueteEnContenedorNuevo(paquete);

    vecina.setUltimoPaqueteMovido(paquete); // Guardamos el ultimo paquete movido

    return vecina;
}

// METODO BUSCAR VECINA. SEL PAQ: AZAR; SEL CONT: AZAR
Solucion Solucion::vecinaAzar_Azar(){

    Solucion vecina = this->getCopia();
    unsigned paquete;
    unsigned contenedor_origen;
    unsigned contenedor_destino;

    // Obtenemos un paquete al azar
    paquete = rand() % instancia.getNumeroPaquetes();
    contenedor_origen = getContenedorDelPaquete(paquete);

    // Obtenemos un contenedor de destino al azar
    do {
        contenedor_destino = rand() % numero_contenedores;
    } while(contenedor_destino == contenedor_origen);

    if(capacidad_contenedores[contenedor_destino] >= instancia.getLongitudPaquete(paquete))
        vecina.moverPaquete(paquete, contenedor_destino);
    else
        vecina.meterPaqueteEnContenedorNuevo(paquete);

    vecina.setUltimoPaqueteMovido(paquete); // Guardamos el ultimo paquete movido

    return vecina;
}

// METODO PARA CAMBIAR UN PAQUETE POR OTRO
void Solucion::cambiarPaquete(unsigned paquete_a, unsigned paquete_b){

    unsigned contenedor_a = solucion[paquete_a];
    unsigned contenedor_b = solucion[paquete_b];

    solucion[paquete_a] = contenedor_b;
    capacidad_contenedores[contenedor_a] += instancia.getLongitudPaquete(paquete_a);
    capacidad_contenedores[contenedor_b] -= instancia.getLongitudPaquete(paquete_a);

    solucion[paquete_b] = contenedor_a;
    capacidad_contenedores[contenedor_b] += instancia.getLongitudPaquete(paquete_b);
    capacidad_contenedores[contenedor_a] -= instancia.getLongitudPaquete(paquete_b);
}

// METODO PARA METER UN PAQUETE EN UN CONTENEDOR NUEVO
void Solucion::meterPaqueteEnContenedorNuevo(unsigned paquete){

    unsigned origen = solucion[paquete];

    // Sacamos el paquete de su origen
    capacidad_contenedores[origen] += instancia.getLongitudPaquete(paquete);
    if(contenedorVacio(origen))
        eliminarContenedor(origen);

    // Metemos el paquete en el contenedor nuevo
    numero_contenedores++;
    capacidad_contenedores.push_back(instancia.getCapacidadContenedores() - instancia.getLongitudPaquete(paquete));
    solucion[paquete] = numero_contenedores-1;
}

// METODO PARA MOVER UN PAQUETE A UN CONTENEDOR EXISTENTE
void Solucion::moverPaquete(unsigned paquete, unsigned contenedor_destino){

    unsigned origen = solucion[paquete];

    // Realizamos el cambio y actualizamos las capacidades
    solucion[paquete] = contenedor_destino;
    capacidad_contenedores[origen] += instancia.getLongitudPaquete(paquete);
    capacidad_contenedores[contenedor_destino] -= instancia.getLongitudPaquete(paquete);

    // Comprobamos si hemos vaciado el contenedor de origen
    if(contenedorVacio(origen))
        eliminarContenedor(origen);
}

// METODO PARA ELIMINAR UN CONTENEDOR
void Solucion::eliminarContenedor(unsigned contenedor){

    capacidad_contenedores.erase(capacidad_contenedores.begin()+contenedor);  // eliminamos el contenedor
    // Recorremos la solucion y cambiamos los contenedores que sean mayores que el borrado
    for(unsigned i=0; i<solucion.size(); i++)
        if(solucion[i] > contenedor)
            solucion[i] -= 1;

    numero_contenedores -= 1;
}

// METODO PARA PREGUNTAR SI UN CONTENEDOR ESTA VACIO
bool Solucion::contenedorVacio(unsigned contenedor){

    if(capacidad_contenedores[contenedor] == instancia.getCapacidadContenedores())
        return true;

    return false;
}

// METODO PARA OBTENER LOS PAQUETES QUE HAY EN UN CONTENEDOR
vector<unsigned> Solucion::paquetesDelContenedor(unsigned contenedor){

    vector<unsigned> paquetes;

    for(unsigned i=0; i<solucion.size(); i++)
        if(solucion[i] == contenedor)
            paquetes.push_back(i);

    return paquetes;
}

// METODO PARA OBTENER UNA COPIA DE LA SOLUCION
Solucion Solucion::getCopia(){

    Solucion copia;
    copia.setNumeroContenedores(numero_contenedores);
    copia.setCapacidadContenedores(capacidad_contenedores);
    copia.setSolucion(solucion);
    copia.setInstancia(instancia);
    return copia;
}


// METODO PARA MOSTRAR LA SOLUCION
void Solucion::mostrar(){

    cout << numero_contenedores;
    for(unsigned i=0; i<solucion.size(); i++){
        if(solucion[i] > 120)
            cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        //cout << i << " -> " << solucion[i] << " ("<< capacidad_contenedores[solucion[i]] << ")"<<endl;
    }

}
