#include "../../Include/Calificacion.h"

Calificacion::Calificacion(int puntaje, string comentario, DTFecha& fecha){
    if(puntaje < 1){
        this->puntaje = 1;
    }else if (puntaje > 5){
        this->puntaje = 5;
    }else{
        this->puntaje = puntaje;
    }
    this->comentario = comentario;
    this->fecha = fecha;
    this->respuesta = "";
}

int Calificacion::getPuntaje(){
    return this->puntaje;
};

string Calificacion::getComentario(){
    return this->comentario;
}


DTFecha& Calificacion::getFecha(){
    return this->fecha;
}

string Calificacion::getRespuesta(){
    return this->respuesta;
}
bool Calificacion::estaSinResponder(){
    return this->respuesta.empty();
}

DTCalificacion* Calificacion::getDataCalificacion(string email){
    return new DTCalificacion(email,this->comentario,this->puntaje,this->fecha,this->respuesta);
}

DTCalificacion* Calificacion::getDataCalificacion(string email, int codigoR){
    return new DTCalificacion(email,this->comentario,this->puntaje,this->fecha,this->respuesta, codigoR);
}

void Calificacion::setRespuesta(string respuesta){
    this->respuesta = respuesta;
}

Calificacion::~Calificacion(){
}