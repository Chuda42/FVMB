#ifndef _IRESERVA_
#define _IRESERVA_

#include "./DTCalificacion.h"
#include "./DTReserva.h"
#include "./DTEstadia.h"

#include<iostream>
#include<set>

using namespace std;

class IReserva{
    public:
        virtual set<DTCalificacion*> getCalificacionesDeHostal(string nombreH)=0;
        virtual set<int> getReservasNoCanceladas(string email, string nombreHostal)=0;
        virtual void registrarEstadia(string emailH, int codigoR)=0;
        virtual void finalizarEstadia(string emailH, string nombreHostal)=0;
        virtual set<DTEstadia*> getEstadiasFinalizadas(string emailH, string nombreHostal) = 0;
        virtual void comentarCalificacion(string emailH, int codigoR, string respuesta) = 0;
        virtual void calificarEstadia(string email, int codigoR, string comentario, int puntaje)=0;
        virtual set<DTCalificacion*> getCalificacionesSinResponder(string emailH)=0;
        virtual set<DTReserva*> getReservas(string nombreH)=0;
        virtual DTCalificacion* getCalificacionEstadia(string emailH, int codigoR)=0;
        virtual DTReserva* getReserva(int codigoR)=0;
        virtual void eliminarReserva(int codigoR)=0;
};


#endif