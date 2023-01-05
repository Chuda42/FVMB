#ifndef _CONTROLADORRESERVA_
#define _CONTROLADORRESERVA_

//DEPENDENCIAS
//librerias estandar
#include<iostream>
#include<set>
#include<map>
//interface que implementa
#include "./IReserva.h"
//dependencias de calses
#include "./ControladorUsuario.h"
#include "./ControladorFechaSistema.h"
#include "./ReservaGrupal.h"
#include "./ReservaIndividual.h"


using namespace std;
class ControladorReserva: public IReserva{
    private:
        //por ser singleton
        static ControladorReserva* instancia;
        ControladorReserva();

        //Colecciones que maneja
        map<int, Reserva*> reservas;
        int cantidadReservas;

    public:
        //sacar la instancia
        static ControladorReserva* getInstancia();

        //funciones de la interfaz ireserva
        set<DTCalificacion*> getCalificacionesDeHostal(string nombreH);
        set<int> getReservasNoCanceladas(string email, string nombreHostal);
        void registrarEstadia(string emailH, int codigoR);
        void finalizarEstadia(string emailH, string nombreHostal);
        set<DTEstadia*> getEstadiasFinalizadas(string emailH, string nombreHostal);
        void calificarEstadia(string email, int codigoR, string comentario, int puntaje);
        void comentarCalificacion(string emailH, int codigoR, string respuesta);
        set<DTCalificacion*> getCalificacionesSinResponder(string emailE);
        set<DTReserva*> getReservas(string nombreH);
        DTCalificacion* getCalificacionEstadia(string emailH, int codigoR);
        DTReserva* getReserva(int codigoR);
        void eliminarReserva(int codigoR);
        virtual ~ControladorReserva();

        //funciones del controlador
        set<int> getHabitacionesNoDisponibles(string nombreHostal, DTDatosNuevaReserva* dNR);
        float calcularCalificacionPromedio(string n);
        set<DTCalificacion*> getCalificacionPorHabitacion(Habitacion* habitacion);
        map<pair<int,string>, DTEstadia*> getDataEstadias(Hostal* hostal);
        void crearReserva(DTDatosNuevaReserva* dRes,string emailTitular, set<string> hsel, Hostal* hostal,Habitacion* habitacion);
        int getCantidadReservas();
        
};




#endif