#include "../../Include/DTHabitacion.h"

//Constructores y destructor
DTHabitacion::DTHabitacion(int numero, float precioPorNoche, int capacidad, set<DTCalificacion*> calificaciones){
    this->numero = numero;
    this->precioPorNoche = precioPorNoche;
    this->capacidad = capacidad;
    this->calificaciones = calificaciones;
}

DTHabitacion::DTHabitacion(int numero, float precioPorNoche, int capacidad){
    this->numero = numero;
    this->precioPorNoche = precioPorNoche;
    this->capacidad = capacidad;

    set<DTCalificacion*> calificaciones;
    this->calificaciones = calificaciones;
}

DTHabitacion::DTHabitacion(Habitacion* habitacion){
    this->numero = habitacion->getNumero();
    this->precioPorNoche = habitacion->getPrecioPorNoche();
    this->capacidad = habitacion->getCapacidad();

    set<DTCalificacion*> calificaciones;
    this->calificaciones = calificaciones;
}

DTHabitacion::~DTHabitacion(){
    while (!this->calificaciones.empty()) {
     set<DTCalificacion*>::iterator it = this->calificaciones.begin();
     this->calificaciones.erase(it);
     delete *it;
}
}

//Getters
int DTHabitacion::getNumero(){
    return this->numero;
}

float DTHabitacion::getPrecioPorNoche(){
    return this->precioPorNoche;
}

int DTHabitacion::getCapacidad(){
    return this->capacidad;
}


set<DTCalificacion*> DTHabitacion::getCalificaciones(){
    return this->calificaciones;
}

//istream& operator>>(istream& i, DTHabitacion &habit){};

ostream &operator<<(ostream &out, DTHabitacion &habit){
    out << "Numero de la habitacion: " << habit.getNumero() << ". Precio por noche de la habitacion: " << habit.getPrecioPorNoche() << ". Capacidad de la habitacion: " << habit.getCapacidad() << endl;
    
    if(!(habit.getCalificaciones().empty())){
        out << "Calificaciones de la habitacion: " << endl;
        set<DTCalificacion*>::iterator iter;
        set<DTCalificacion*> calif = habit.getCalificaciones();
        for(iter = calif.begin(); iter != calif.end(); ++iter){
            out << *(*iter) << endl;
        }
    }
    return out;
};
