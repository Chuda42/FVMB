#ifndef _DTCALIFICACION_
#define _DTCALIFICACION_

#include<iostream>
#include "./DTFecha.h"

using namespace std;
class DTCalificacion{
    private:
        int codigoR;
        string emailAutor;
        string comentario;
        int puntaje;
        DTFecha fecha;
        string respuesta;
    public:
        DTCalificacion(string emailAutor, string comentario, int  puntaje, DTFecha& fecha, string respuesta);
        DTCalificacion(string emailAutor, string comentario, int  puntaje, DTFecha& fecha, string respuesta, int codigoR);
        string getEmailAutor();
        string getComentario();
        int getPuntaje();
        DTFecha& getFecha();
        string getRespuesta();
        int getCodigoReserva();
        ~DTCalificacion();
};

ostream &operator<<(ostream &out, DTCalificacion &c);

#endif
