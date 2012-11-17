#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <vector>
#include <string>

using namespace std;

class Instancia
{

private:
    string nombre;
    unsigned capacidad_contenedores;
    unsigned numero_paquetes;
    unsigned mejor_solucion;
    vector<unsigned> longitud_paquetes;

public:
    Instancia(string, unsigned, unsigned, unsigned, vector<unsigned>);

    // BORRAR
    void mostrar();

    unsigned obtenerLongitud(unsigned); // Recibe el ID del paquete para devolver su longitud
    unsigned obtenerPaquete();  // devuelve el ID de un paquete segun un criterio de seleccion. Quiza se pueda poner una opcion (azar, mayor, menor)

};

#endif // INSTANCIA_H
