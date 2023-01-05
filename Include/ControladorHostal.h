#ifndef _CONTROLADORHOSTAL_
#define _CONTROLADORHOSTAL_

//DEPENDENCIAS
//librerias estandar
#include<iostream>
#include<set>
#include<map>
//interface que implementa
#include "./IHostal.h"
//dependencias de clases
#include "./ControladorReserva.h"
#include "./Hostal.h"
#include "./DTDatosNuevaReserva.h"

class Hostal;

using namespace std;
class ControladorHostal: public IHostal{
    private:
        //por ser singleton
        static ControladorHostal* instancia;
        ControladorHostal();

        //guarda memoria temporal del sistema
        DTHabitacion* cacheDatosHabitacion;
        DTDatosNuevaReserva* cacheDatosReserva;
        set<string> cacheHuespedesSeleccionados;
        string* cacheTitularSeleccionado;

        //Colecciones que maneja
        map<string, Hostal*> hostales;

    public:

        

        static ControladorHostal* getInstancia();

        //funciones de la interfaz ihostal
        void agregarHostal(string nombre,string direccion, string telefono) ;
        set<string> getHostales();
        void nuevaHabitacion(int numero,float precio, int capacidad);
        void confirmarRegistroHabitacion(string nombreHostal);
        void cancelarRegistroHabitacion();
        set<DTHostal*> getHostalesConCalificacion();
        void setDatosReserva(DTFecha& checkIn, DTFecha& checkOut, bool esGrupal);
        set<DTHabitacion*> getHabitacionesDisponibles( string nombreHostal);
        void seleccionarHuesped(string email);
        void confirmarReserva(string nombreHostal, int numeroHabitacion);
        void cancelarReserva();
        map<int, string> getTop3Hostales();
        set<DTHabitacion*> getHabitaciones(string nombreH);
        DTHostal* getInfoBasicaHostal(string nombreH);
        map<pair<int,string>, DTEstadia*> getEstadias(string nombreH);
        virtual ~ControladorHostal();

        //funciones del controlador
        void addHuespedSeleccionado(string email);
        void setDatosHabitacion(int numero, float precio, int capacidad);
        DTHabitacion* getDatosHabitacion();
        void setDatosNuevaReserva(DTFecha& checkIn, DTFecha& checkOut, bool esGrupal);
        Hostal* getInstanciaHostal(string nombre);
        DTDatosNuevaReserva* getDatosNuevaReserva();
        set<string> getHuespedesSeleccionados();
        void releaseData();
};





#endif