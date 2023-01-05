#ifndef _ESTADIA_
#define _ESTADIA_

#include "./CalificacionObserver.h"
#include "./DTEstadia.h"
#include "./Calificacion.h"
#include "./Huesped.h"
#include "./DTFecha.h"

class Estadia {
    private:
        Huesped* huesped;
        Calificacion* calificacion;

        DTFecha checkIn;
        DTFecha checkOut;
        int promo;
    
    public:
        Estadia(DTFecha& checkIn, int promo, Huesped* huesped);

        string getNombreHuesped();
        string getEmailHuesped();
        bool tieneCalificacion();

        DTFecha& getCheckIn();
        DTFecha& getCheckOut();
        int getPromo();

        DTCalificacion* getDTCalificacion();
        DTCalificacion* getDTCalificacion(int codigoR);
        DTEstadia* getDTEstadia(int codigoR);

        bool estadiaValidaParaFinalizar(string email);
        bool estaFinalizadaEstadia();
        bool tieneCalificacionSinResponder();

        void finalizarEstadia(DTFecha& fecha);
        void calificarEstadia(DTFecha& fecha, string comentario,int puntaje);
        void comentarCalificacion(string respuesta);
        void sumarPuntajeCalificacion(int& puntajeTotal, int& cantidadPuntajes);

        ~Estadia();
};

#endif