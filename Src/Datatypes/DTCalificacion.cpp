#include "../../Include/DTCalificacion.h"

DTCalificacion::DTCalificacion(string emailAutor, string comentario, int  puntaje, DTFecha& fecha, string respuesta){
    this->emailAutor = emailAutor;
    this->comentario = comentario;
    this->puntaje = puntaje;
    this->fecha = fecha;
    this->respuesta = respuesta;
    this->codigoR = -1;
}

DTCalificacion::DTCalificacion(string emailAutor, string comentario, int  puntaje, DTFecha& fecha, string respuesta, int codigoR){
    this->emailAutor = emailAutor;
    this->comentario = comentario;
    this->puntaje = puntaje;
    this->fecha = fecha;
    this->respuesta = respuesta;
    this->codigoR = codigoR;
}

/* DTCalificacion::DTCalificacion(string comentario, int  puntaje, DTFecha& fecha, string respuesta){
    this->comentario = comentario;
    this->puntaje = puntaje;
    this->fecha = fecha;
    this->respuesta = respuesta;
} */

string DTCalificacion::getEmailAutor(){
    return this->emailAutor;
}

string DTCalificacion::getComentario(){
    return this->comentario;
}

int DTCalificacion::getPuntaje(){
    return this->puntaje;
}

DTFecha& DTCalificacion::getFecha(){
    return this->fecha;
}

string DTCalificacion::getRespuesta(){
    return this->respuesta;
}

int DTCalificacion::getCodigoReserva(){
    return this->codigoR;
}

DTCalificacion::~DTCalificacion(){}

ostream &operator<<(ostream &out, DTCalificacion &c){
    
    out << "Autor de la calificacion: " << c.getEmailAutor() <<endl 
        << "Puntaje: " << c.getPuntaje() <<endl
        << "Comentario: " << c.getComentario() <<endl
        << "Fecha de la calificacion: " << c.getFecha() << endl;

    if(!c.getRespuesta().empty()) {
        out << "Resuesta: " << c.getRespuesta() <<endl;
    }

    if (c.getCodigoReserva() != -1) {
        out << " CodigoReserva: " << c.getCodigoReserva() << endl;
    }
    return out;
};
//bool operator==(DTCalificacion &cali);
//DTCalificacion& operator=(DTCalificacion &cali);