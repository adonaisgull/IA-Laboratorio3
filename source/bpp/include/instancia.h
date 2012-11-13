#ifndef INSTANCIA_H
#define INSTANCIA_H

class Instancia
{

private:
    unsigned capacidad_contenedores;
    unsigned numero_paquetes;
    unsigned mejor_solucion;
    vector<unsigned> longitud_paquetes;

public:
    Instancia(unsigned, unsigned, unsigned, vector<unsigned>);  // Construye la instancia

    unsigned obtenerLongitud(unsigned); // Recibe el ID del paquete para devolver su longitud
    unsigned obtenerPaquete();  // devuelve el ID de un paquete segun un criterio de seleccion. Quiza se pueda poner una opcion (azar, mayor, menor)

};

#endif // INSTANCIA_H
