#ifndef _HABITACION_
#define _HABITACION_


#include "./DTHabitacion.h"

#include <set>
#include<iostream>



using namespace std;

class Habitacion{
    private:
        int numero;
        float precioPorNoche;
        int capacidad;

    public:
        void setNumero(int numero);
        void setPrecioPorNoche(float precioPorNoche);
        void setCapacidad(int capacidad);

        int getNumero();
        float getPrecioPorNoche();
        int getCapacidad();

        
        bool estaHabitacionEnLista(set<int> habNDis);
        DTHabitacion* getDTHabitacion(set<DTCalificacion*> calif);// devuelve numero, precio, capacidad y im set de calificaciones
        DTHabitacion* getDatosHabitacion();//solo devuelve numero, precio y capacidad

        Habitacion(int numero, float precioPorNoche, int capacidad);
        Habitacion(DTHabitacion* dataHabitacion);
        ~Habitacion();
};




#endif