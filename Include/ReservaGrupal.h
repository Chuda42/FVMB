#ifndef _RESERVAGRUPAL_
#define _RESERVAGRUPAL_

#include "./Reserva.h"

class Estadia;

#include <map>


class ReservaGrupal: public Reserva {
    private:
        map<string, Huesped*> huespedes; // La clave de ambos map es el email del huésped correspondiente
        map<string, Estadia*> estadias;

    public:
        //CONSTRUCTOR Y DESTRUCTOR
        ReservaGrupal(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular,set<Huesped*> hsel,Hostal* hostal,Habitacion* habitacion);
        
        //POLIMORFICAS DE RESERVA
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
        bool esReservaValida(string email, string nombreHostal);
        ~ReservaGrupal();
};

#endif