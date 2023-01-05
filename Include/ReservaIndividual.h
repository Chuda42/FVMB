#ifndef _RESERVAINDIVIDUAL_
#define _RESERVAINDIVIDUAL_

#include "./Reserva.h"

class Estadia;

using namespace std;

class ReservaIndividual : public Reserva {
    private:
        Estadia* estadia;

    public:
        ReservaIndividual(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular,Hostal* hostal,Habitacion* habitacion);

        DTReserva* getDTReserva();
        //set<string> getNombreHuespedes();
        void getDataEstadias(map<pair<int,string>, DTEstadia*>& total);
        void getDTCalificaciones(set<DTCalificacion*>& total);
        void getDTCalificaciones(string nombreH, set<DTCalificacion*>& total);
        DTCalificacion* getDataCalificacion(string emailH);
        DTEstadia* getDTEstadiaFinalizada(string email);
        void getCalificacionesSinResponderDelHostal(string nombreH, set<DTCalificacion*>& total);
        void finalizarEstadiaSiEsValida(string emailH, DTFecha& fecha);
        void sumarCalificaciones(int& puntajeTotal, int& cantidadPuntajes);
        bool tieneEstadiaFinalizada(string email);
        void registrarEstadia(string emailH, DTFecha& fecha);
        void calificarEstadia(string emailH, DTFecha& fecha, string comentario, int puntaje);
        void comentarCalificacion(string emailH, string respuesta);
        ~ReservaIndividual();
};

#endif