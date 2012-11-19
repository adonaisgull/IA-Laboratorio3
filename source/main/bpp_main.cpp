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
    Solucion solILS, solSA;

    //cout << "Introduzca ruta fichero instancias: ";
    //cin >> ruta_fichero;

    ifstream fichero("data.txt", ifstream::in);
    bpp.cargarInstancias(fichero);
    fichero.close();

    srand(time(NULL));

    cout << "Calculando ILS..."<< endl;
    solILS = bpp.ILS(1);
    cout << "Solucion ILS: ";
    solILS.mostrar();

    cout << "Calculando SA..."<< endl;
    solSA = bpp.SA(2);
    cout << "Solucion SA: ";
    solSA.mostrar();

}
