#ifndef _CONS_
#define _CONS_

#include <iostream>
using namespace std;

enum TipoCargo{
    Administracion = 0,
    Limpieza = 1,
    Recepcion =  2,
    Infraestructura = 3
};
istream& operator>>(istream& i, TipoCargo &c);
ostream &operator<<(ostream &out, TipoCargo &c);

enum EstadoReserva{
    Abierta  = 0,
    Cerrada= 1,
    Cancelada= 2
};
ostream &operator<<(ostream &out, EstadoReserva &e);

#endif