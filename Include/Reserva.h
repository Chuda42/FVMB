#ifndef _RESERVA_
#define _RESERVA_

#include <iostream>
#include <set>
#include <map>

#include "./Const.h"
#include "./DTFecha.h"
#include "./DTReserva.h"
#include "./DTDatosNuevaReserva.h"
#include "./Habitacion.h"
#include "./Huesped.h"
#include "./Estadia.h"

class Hostal;


using namespace std;

class Reserva {
    private:
        Hostal* hostal;
        Habitacion* habitacion;
        Huesped* titular;
        
        int codigo;
        DTFecha checkIn;
        DTFecha checkOut;
        EstadoReserva estado; // EstadoReserva = Abierta
        float costo;

    public:
        //CONSTRUCTROES Y DESTRUCTOR
        Reserva(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular, Hostal* hostal, Habitacion* habitacion);
        virtual ~Reserva();
    
        //GETTERS
        string getNombreHostal();
        int getNumeroHabitacion();        
        int getCodigo();
        Huesped* getTitular();
        DTFecha& getCheckIn();
        DTFecha& getCheckOut();
        EstadoReserva getEstado();
        float getCosto();
        
        //SETTERS
        void setCosto(float costo);
        void setEstado(EstadoReserva estado);
        
        //VIRTUAL
        virtual DTReserva* getDTReserva() = 0;
        //virtual set<string> getNombreHuespedes() = 0;
        virtual void getDTCalificaciones(set<DTCalificacion*>& total) = 0;
        virtual void getDTCalificaciones(string nombreH, set<DTCalificacion*>& total) = 0;
        virtual DTCalificacion* getDataCalificacion(string emailH) = 0;
        virtual DTEstadia* getDTEstadiaFinalizada(string email) = 0;
        virtual void getCalificacionesSinResponderDelHostal(string nombreH, set<DTCalificacion*>& total) = 0;
        virtual void finalizarEstadiaSiEsValida(string emailH, DTFecha& fecha) = 0;
        virtual void sumarCalificaciones(int& puntajeTotal, int& cantidadPuntajes)=0;
        virtual bool tieneEstadiaFinalizada(string email) = 0;
        virtual void registrarEstadia(string emailH, DTFecha& fecha)  = 0;
        virtual void calificarEstadia(string emailH, DTFecha& fecha, string comentario, int puntaje)  = 0;
        virtual void comentarCalificacion(string emailH, string respuesta)  = 0;
        virtual void getDataEstadias(map<pair<int,string>, DTEstadia*>& total)=0;

        //BOOLEANOS
        bool esReservaDeHostal(Hostal* hostal);
        bool esReservaDeHostal(string nombreH);
        bool reservaEnRango(DTDatosNuevaReserva* dNR, string nombreHostal);
        virtual bool esReservaValida(string email, string nombreHostal); 
        bool estaCancelada(); 
        bool esReservaDeHabitacion(Habitacion* habitacion);
};

#include "./Hostal.h"

#endif