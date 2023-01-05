#ifndef _CALIFICACION_
#define _CALIFICACION_

//Dependencias de librerias
#include <iostream>
//Dependencias de datatypes
#include "./DTFecha.h"
#include "./DTCalificacion.h"

using namespace std;

class Calificacion {
    private:
        int puntaje; // vale entre [1..5]
        string comentario;
        DTFecha fecha;
        string respuesta; // puede o no haber respuesta [0..1]

    public:
        Calificacion(int puntaje, string comentario, DTFecha& fecha);

        int getPuntaje();
        string getComentario();
        DTFecha& getFecha();
        
        string getRespuesta();
        bool estaSinResponder();

        DTCalificacion* getDataCalificacion(string email);
        DTCalificacion* getDataCalificacion(string email, int codigoR);

        void setRespuesta(string respuesta);

        ~Calificacion();
};

#endif