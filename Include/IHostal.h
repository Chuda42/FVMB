#ifndef _IHOSTAL_
#define _IHOSTAL_

#include<iostream>
#include<set>
#include<map>

#include "./Const.h"
#include "./DTHostal.h"
#include "./DTFecha.h"
#include "./DTCalificacion.h"
#include "./DTHabitacion.h"
#include "./DTEstadia.h"

using namespace std;

class IHostal{
    public:
        virtual void agregarHostal(string nombre,string direccion, string telefono) =0;
        virtual set<string> getHostales()=0;
        virtual void nuevaHabitacion(int numero,float precio, int capacidad)=0;
        virtual void confirmarRegistroHabitacion(string nombreHostal)=0;
        virtual void cancelarRegistroHabitacion()=0;
        virtual set<DTHostal*> getHostalesConCalificacion()=0;
        virtual void setDatosReserva(DTFecha& checkIn, DTFecha& checkOut, bool esGrupal)=0;
        virtual set<DTHabitacion*> getHabitacionesDisponibles( string nombreHostal)=0;
        virtual void seleccionarHuesped(string email)=0;
        virtual void confirmarReserva(string nombreHostal, int numeroHabitacion)=0;
        virtual void cancelarReserva()=0;
        virtual map<int, string> getTop3Hostales()=0;
        virtual set<DTHabitacion*> getHabitaciones(string nombreH)=0;
        virtual DTHostal* getInfoBasicaHostal(string nombreH)=0;
        virtual map<pair<int,string>, DTEstadia*> getEstadias(string nombreH)=0;
};


#endif