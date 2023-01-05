#include <iostream>
#include "../../Include/Const.h"

using namespace std;

istream& operator>>(istream& i, TipoCargo &c){
    int a;
    i >> a;
    c = static_cast<TipoCargo>(a);
    return i;
};

ostream &operator<<(ostream &out, TipoCargo &c){
    if(c == Administracion){
        out << "Administracion";
    }else if(c== Limpieza){
        out << "Limpieza";
    }else if(c == Recepcion){
        out << "Recepcion";
    }else if(c == Infraestructura){
        out << "Infraestructura";
    }
    return out;
};

ostream &operator<<(ostream &out, EstadoReserva &e) {
    switch (e)
    {
    case Abierta :
        out << "Abierta";
    break;
    case Cancelada :
        out << "Cancelada";
    break;
    case Cerrada :
        out << "Cerrada";
    break;
    default:{}break;
    }
    return out;
}