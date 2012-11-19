#ifndef SOLUCION_H
#define SOLUCION_H

#include "instancia.h"
#include <vector>

using namespace std;

class Solucion
{
private:
    unsigned numero_contenedores;
    vector<unsigned> capacidad_contenedores;
    vector<unsigned> solucion;
    Instancia instancia; // De momento accedo asi a los datos de los paquetes

    void moverPaquete(unsigned paquete, unsigned contenedor_destino);
    void cambiarPaquete(unsigned paquete_a, unsigned paquete_b);
    bool esFactible();
    vector<unsigned> paquetesDelContenedor(unsigned);

public:
    Solucion(){};
    Solucion(Instancia);        // Genera una solucion inicial. Puede que haya varias formas, entonces hacer metodos diferentes para crearla.

    Solucion vecinaAzar_Primero();
    Solucion vecinaAzar_MenosEspacio();
    Solucion vecinaAzar_Azar();
    Solucion vecinaMasVacio_MenosEspacio();
    Solucion vecinaMasVacio_Primero();
    Solucion vecinaMasVacio_Azar();

    void eliminarContenedor(unsigned contenedor);
    void meterPaqueteEnContenedorNuevo(unsigned paquete);
    Solucion getCopia();

    bool contenedorVacio(unsigned contenedor);

    // Getters
    inline unsigned getNumeroContenedores() { return numero_contenedores; }
    inline vector<unsigned> getCapacidadContenedores(){ return capacidad_contenedores; }
    inline vector<unsigned> getSolucion(){ return solucion; }
    inline Instancia getInstancia(){ return instancia; }

    // Setters
    inline void setNumeroContenedores(unsigned _numero_contenedores) { numero_contenedores = _numero_contenedores; }
    inline void setCapacidadContenedores(vector<unsigned> _capacidad_contenedores) { capacidad_contenedores = _capacidad_contenedores; }
    inline void setSolucion(vector<unsigned> _solucion) { solucion = _solucion; }
    inline void setInstancia(Instancia _instancia) { instancia = _instancia; }

    // PARA BORRAR O NO
    void mostrar();

    inline unsigned getContenedorDelPaquete(unsigned paquete) { return solucion[paquete]; }
};

#endif // SOLUCION_H
