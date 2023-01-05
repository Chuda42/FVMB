#include "../../Include/DTHostal.h"
using namespace std;

DTHostal :: DTHostal(string nombre, string direccion, string telefono, float calificacionPromedio){
    this->nombre = nombre;
    this->direccion = direccion;
    this->telefono = telefono;
    this->calificacionPromedio = calificacionPromedio;
}

string DTHostal :: getNombre(){
    return this->nombre;
}

string DTHostal :: getDireccion(){
    return this->direccion;
}

string DTHostal :: getTelefono(){
    return this->telefono;
}

float DTHostal :: getCalificacionPromedio(){
    return this->calificacionPromedio;
}

DTHostal ::~DTHostal(){}

ostream &operator<<(ostream &out, DTHostal &h){
    out << "Nombre Hostal: " << h.getNombre() << ". Direccion del hostal: " << h.getDireccion() << ". Telefono: " << h.getTelefono() << ". Calificacion del hostal: "<< h.getCalificacionPromedio()<<endl;
    return out;
};