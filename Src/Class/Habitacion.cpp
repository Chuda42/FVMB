#include "../../Include/Habitacion.h"

//constructora y destructora
Habitacion::Habitacion(int numero, float precioPorNoche, int capacidad){
    this->numero = numero;
    this->precioPorNoche = precioPorNoche;
    this->capacidad=capacidad;
}

Habitacion::Habitacion(DTHabitacion* dataHabitacion){
    this->numero = dataHabitacion->getNumero();
    this->precioPorNoche = dataHabitacion->getPrecioPorNoche();
    this->capacidad = dataHabitacion->getCapacidad();
}

Habitacion::~Habitacion(){}

//setters
void Habitacion::setNumero(int numero){
    this->numero = numero;
}

void Habitacion::setPrecioPorNoche(float precioPorNoche){
    this->precioPorNoche = precioPorNoche;
}

void Habitacion::setCapacidad(int capacidad){
    this->capacidad = capacidad;
}

//getters
int Habitacion::getNumero(){
    return this->numero;
}

float Habitacion::getPrecioPorNoche(){
    return this->precioPorNoche;
}

int Habitacion::getCapacidad(){
    return this->capacidad;
}

//sistema


bool Habitacion::estaHabitacionEnLista(set<int> habNDis){
    int num = this->getNumero();
    set<int>::iterator iter = habNDis.find(num);
    return iter != habNDis.end();
}

DTHabitacion* Habitacion::getDTHabitacion(set<DTCalificacion *>calif){
    DTHabitacion* nuevoDT = new DTHabitacion(this->numero,this->precioPorNoche,this->capacidad, calif);
    return nuevoDT;
} 

DTHabitacion* Habitacion::getDatosHabitacion(){ 
    DTHabitacion* nuevoDato = new DTHabitacion(this->numero,this->precioPorNoche,this->capacidad);
    return nuevoDato;
};


