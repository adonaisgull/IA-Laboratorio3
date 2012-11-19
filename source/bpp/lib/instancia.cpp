#include "../include/instancia.h"

#include <iostream>

using namespace std;

Instancia::Instancia(string _nombre, unsigned _capacidad_contenedores, unsigned _numero_paquetes, unsigned _mejor_solucion, vector<unsigned> _longitud_paquetes){

    nombre = _nombre;
    capacidad_contenedores = _capacidad_contenedores;
    numero_paquetes = _numero_paquetes;
    mejor_solucion= _mejor_solucion;
    longitud_paquetes= _longitud_paquetes;
}
