#ifndef _DTHABITACION_
#define _DTHABITACION_

#include<iostream>
#include<set>


#include "./DTCalificacion.h"

class Habitacion;

class DTHabitacion{
    private:
        int numero;
        float precioPorNoche;
        int capacidad;
        set<DTCalificacion*> calificaciones;
    public:
        int getNumero();
        float getPrecioPorNoche();
        int getCapacidad();
        set<DTCalificacion*> getCalificaciones();

        DTHabitacion(int numero, float precioPorNoche, int capacidad, set<DTCalificacion*> calificaciones);
        DTHabitacion(int numero, float precioPorNoche, int capacidad);
        DTHabitacion(Habitacion* habitacion);
        ~DTHabitacion();
};

#include "./Habitacion.h"

ostream &operator<<(ostream &out, DTHabitacion &habit);

#endif