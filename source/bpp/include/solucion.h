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
    unsigned ultimo_paquete_movido;

    // Metodos
    void moverPaquete(unsigned paquete, unsigned contenedor_destino);
    void meterPaqueteEnContenedorNuevo(unsigned paquete);
    void cambiarPaquete(unsigned paquete_a, unsigned paquete_b);

    vector<unsigned> paquetesDelContenedor(unsigned);

    inline unsigned getContenedorDelPaquete(unsigned paquete) { return solucion[paquete]; }
    bool contenedorVacio(unsigned contenedor);
    void eliminarContenedor(unsigned contenedor);

    Solucion getCopia();

public:
    Solucion(){};
    Solucion(Instancia);        // Genera una solucion inicial. Puede que haya varias formas, entonces hacer metodos diferentes para crearla.

    Solucion vecinaAzar_Primero(unsigned k=1);
    Solucion vecinaAzar_MenosEspacio();
    Solucion vecinaAzar_Azar();
    Solucion vecinaMasVacio_MenosEspacio();
    Solucion vecinaMasVacio_Primero();

    // Getters
    inline unsigned getNumeroContenedores() { return numero_contenedores; }
    inline vector<unsigned> getCapacidadContenedores(){ return capacidad_contenedores; }
    inline vector<unsigned> getSolucion(){ return solucion; }
    inline Instancia getInstancia(){ return instancia; }
    inline unsigned getUltimoPaqueteMovido() { return ultimo_paquete_movido; }

    // Setters
    inline void setNumeroContenedores(unsigned _numero_contenedores) { numero_contenedores = _numero_contenedores; }
    inline void setCapacidadContenedores(vector<unsigned> _capacidad_contenedores) { capacidad_contenedores = _capacidad_contenedores; }
    inline void setSolucion(vector<unsigned> _solucion) { solucion = _solucion; }
    inline void setInstancia(Instancia _instancia) { instancia = _instancia; }
    inline void setUltimoPaqueteMovido(unsigned paquete) { ultimo_paquete_movido = paquete; }

    // PARA BORRAR O NO
    void mostrar();
};

#endif // SOLUCION_H
