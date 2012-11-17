/*
 *
 */

#include "../bpp/include/instancia.h"
#include "../bpp/include/solucion.h"
#include "../bpp/include/bpp.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(void){

    char ruta_fichero[255];

    cout << "Introduzca ruta fichero instancias: ";
    cin >> ruta_fichero;

    ifstream fichero(ruta_fichero, ifstream::in);
    Bpp bpp;
    bpp.cargarInstancias(fichero);

}
