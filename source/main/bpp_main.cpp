/*
 *
 */

#include "../bpp/include/instancia.h"
#include "../bpp/include/solucion.h"
#include "../bpp/include/bpp.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(void){

    //char ruta_fichero[255];
    Bpp bpp;

    //cout << "Introduzca ruta fichero instancias: ";
    //cin >> ruta_fichero;

    ifstream fichero("data.txt", ifstream::in);
    bpp.cargarInstancias(fichero);
    fichero.close();

    srand(time(NULL));

    bpp.lanzarEstudio();
}
