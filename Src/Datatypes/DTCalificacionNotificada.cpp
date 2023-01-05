#include "../../Include/DTCalificacionNotificada.h"

DTCalificacionNotificada :: DTCalificacionNotificada(string autor, string comentario, int  puntaje){
    this->autor = autor;
    this->comentario = comentario;
    this->puntaje = puntaje;
}

string DTCalificacionNotificada :: getAutor(){
    return this->autor;
}

string DTCalificacionNotificada :: getComentario(){
    return this->comentario;
}

int DTCalificacionNotificada :: getPuntaje(){
    return this->puntaje;
}

DTCalificacionNotificada :: ~DTCalificacionNotificada(){}

ostream &operator<<(ostream &out, DTCalificacionNotificada &calif)
{
    out<<"Autor: "<<calif.getAutor()<< " Comentario: " <<calif.getComentario() << " Puntaje: " <<calif.getPuntaje() <<endl;
    return out;
};