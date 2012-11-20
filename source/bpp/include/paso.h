#ifndef PASO_H
#define PASO_H

class Paso {

private:
    unsigned paquete;       // paquete que se movera
    unsigned contenedor;    // contenedor al que se moverá
    unsigned capacidad;     // capacidad que dejará

public:
    inline Paso() {}
    inline Paso(unsigned _paquete, unsigned _contenedor, unsigned _capacidad){ paquete=_paquete; contenedor=_contenedor; capacidad=_capacidad; }
    inline unsigned getPaquete() { return paquete; }
    inline unsigned getContenedor() { return contenedor; }
    inline unsigned getCapacidad() { return capacidad; }
};

#endif // PASO_H
