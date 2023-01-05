#include "../../Include/Estadia.h"
Estadia::Estadia(DTFecha& checkIn, int promo, Huesped* huesped){
    this->checkIn = checkIn;
    this->checkOut = DTFecha();
    this->promo = promo;
    this->huesped = huesped;
    this->calificacion = NULL;
}

DTEstadia* Estadia ::getDTEstadia(int codigoR) {
    return new DTEstadia(codigoR, this->checkIn, this->checkOut, this->promo);
}

string Estadia::getNombreHuesped(){
    return this->huesped->getNombre();
}

string Estadia::getEmailHuesped(){
    return this->huesped->getEmail();
}

bool Estadia::tieneCalificacion(){
    return this->calificacion != NULL;
}

DTFecha& Estadia::getCheckIn(){
    return this->checkIn;
}

DTFecha& Estadia::getCheckOut(){
    return this->checkOut; 
}

int Estadia::getPromo(){
    return this->promo;
}

DTCalificacion* Estadia::getDTCalificacion(){
    return this->calificacion->getDataCalificacion(this->getEmailHuesped());   
}

DTCalificacion* Estadia::getDTCalificacion(int codigoR){
    if(this->calificacion == NULL){
        throw std::invalid_argument("La estadia no ha sido calificada aun.");
    }
    return this->calificacion->getDataCalificacion(this->getEmailHuesped(), codigoR);   
}

void Estadia::sumarPuntajeCalificacion(int& puntajeTotal, int& cantidadPuntajes){
    if(!this->tieneCalificacion()){
        return;
    }
    puntajeTotal += this->calificacion->getPuntaje();
    cantidadPuntajes++;
};

bool Estadia::estaFinalizadaEstadia(){
    return !(this->checkOut.getAnio() == 0 && this->checkOut.getDia() == 0);
}

bool Estadia::estadiaValidaParaFinalizar(string email){
    return this->getEmailHuesped() == email && !this->estaFinalizadaEstadia();
}

void Estadia::finalizarEstadia(DTFecha& fecha){
    this->checkOut = fecha;
}

void Estadia ::calificarEstadia(DTFecha& fecha, string comentario,int puntaje) {
    if (this->tieneCalificacion())
    {
        throw std::invalid_argument("La estadia ya ha sido calificada");
    }

    this->calificacion = new Calificacion(puntaje, comentario, fecha);
    string nombreH = this->huesped->getNombre();

    DTCalificacionNotificada* notificacion = new DTCalificacionNotificada(nombreH, comentario, puntaje);

    CalificacionObserver* obs = CalificacionObserver::getInstancia();
    obs->notificarObserver(notificacion);
}

bool Estadia :: tieneCalificacionSinResponder() {
    return this->tieneCalificacion() && this->calificacion->estaSinResponder();
}

void Estadia :: comentarCalificacion(string respuesta){
    if (!this->tieneCalificacion()) {
        throw invalid_argument("La estadia no tiene calificacion.");
    }

    this->calificacion->setRespuesta(respuesta);
}

Estadia :: ~Estadia() {
    delete this->calificacion;
}