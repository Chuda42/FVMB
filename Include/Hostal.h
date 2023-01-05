#ifndef _HOSTAL_
#define _HOSTAL_

//#include "./Usuario.h"
//#include "./Huesped.h"
//#include "./Empleado.h"
#include "./Habitacion.h"
#include "./DTHostal.h"
//#include "./DTEstadia.h"
#include "./Const.h"
#include "./ControladorReserva.h"

class DTEstadia;

#include <set>
#include <map>
#include <iostream>

using namespace std;

class Hostal{
    private:
        string nombre;
        string direccion;
        string telefono;

        //Coleccion de habitaciones que maneja
        map<int, Habitacion*> habitaciones;

    public:

        Hostal(string nombre,string direccion,string telefono);
        ~Hostal();

        void setNombre(string nombre);
        void setDireccion(string direccion);
        void setTelefono(string telefono);

        string getNombre();
        string getDireccion();
        string getTelefono();

        float getPromedio();
        set<DTHabitacion*> getHabitaciones();
        map<pair<int,string>, DTEstadia*> getEstadias();
        Habitacion* getInstanciaHabitacion(int numeroHabitacion);
        DTHostal* getDataHostal();
        void agregarHabitacion(DTHabitacion* dataHabitacion);
        set<DTHabitacion*> getHabitacionesDisponibles(set<int> habNDis);
  
};




#endif