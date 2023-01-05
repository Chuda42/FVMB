#ifndef _DTCALIFICACIONNOTIFICADA_
#define _DTCALIFICACIONNOTIFICADA_

#include<iostream>

using namespace std;

class DTCalificacionNotificada{
    private:
        string autor;
        string comentario;
        int puntaje;
    public:
        DTCalificacionNotificada(string autor, string comentario, int  puntaje);
        string getAutor();
        string getComentario();
        int getPuntaje();
        ~DTCalificacionNotificada();
};

ostream &operator<<(ostream &out, DTCalificacionNotificada &calif);

#endif
