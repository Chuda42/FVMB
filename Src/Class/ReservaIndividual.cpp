#include "../../Include/ReservaIndividual.h"


ReservaIndividual::ReservaIndividual(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular,Hostal* hostal,Habitacion* habitacion):Reserva(codigo, checkIn, checkOut, titular, hostal, habitacion){
    this->estadia = NULL;
    float costo;
    int diferenciaDias = checkIn.diferenciaDeDias(checkOut);
    costo = diferenciaDias * habitacion->getPrecioPorNoche();
    this->Reserva::setCosto(costo);
    
};

void ReservaIndividual::sumarCalificaciones(int& puntajeTotal, int& cantidadPuntajes){
    if(this->estadia != NULL){
        this->estadia->sumarPuntajeCalificacion(puntajeTotal, cantidadPuntajes);
    }
};

void ReservaIndividual::registrarEstadia(string emailH, DTFecha& fecha) {
    if(this->getTitular()->getEmail() == emailH){
        if(this->estadia == NULL){
        {
            this->estadia = new Estadia(fecha, 0, this->getTitular());
            this->setEstado(Cerrada);
        }
        }else{
            throw std::invalid_argument("El titular ya había registrado su estadia");
        }
    }else{
        throw std::invalid_argument("La reserva no contiene al huesped con email " + emailH);
    }
};

void ReservaIndividual::getDTCalificaciones(set<DTCalificacion*>& total){
    DTCalificacion* dtC;
    if(this->estadia != NULL){
        if(this->estadia->tieneCalificacion()){
            dtC = this->estadia->getDTCalificacion();
            total.insert(dtC);
        }   
    }
};

void ReservaIndividual::getDTCalificaciones(string nombreH, set<DTCalificacion*>& total){
    bool esDeHostal = this->esReservaDeHostal(nombreH);
    if(esDeHostal){
        this->getDTCalificaciones(total);
    }
};

void ReservaIndividual::getCalificacionesSinResponderDelHostal(string nombreH, set<DTCalificacion*>& total){
    if (!this->esReservaDeHostal(nombreH) || this->estadia == NULL || !this->estadia->tieneCalificacionSinResponder())
    {
        return;
    }

    total.insert(this->estadia->getDTCalificacion(this->getCodigo()));
}

void ReservaIndividual::finalizarEstadiaSiEsValida(string emailH, DTFecha& fecha){
    if(this->estadia != NULL && this->estadia->estadiaValidaParaFinalizar(emailH)){
            this->estadia->finalizarEstadia(fecha);
    }
}

bool ReservaIndividual::tieneEstadiaFinalizada(string email) {
    return this->estadia->getEmailHuesped() == email && this->estadia->estaFinalizadaEstadia();
}

DTEstadia* ReservaIndividual::getDTEstadiaFinalizada(string email) {
    return this->estadia->getDTEstadia(this->getCodigo());
}

void ReservaIndividual ::calificarEstadia(string emailH, DTFecha& fecha, string comentario, int puntaje) {
    if (this->estadia == NULL) {
        throw invalid_argument("El usuario: " + emailH + " no tiene estadia.");
    }

    this->estadia->calificarEstadia(fecha, comentario, puntaje);
}

DTReserva* ReservaIndividual::getDTReserva(){
    EstadoReserva estado = this->getEstado();
    DTFecha checkIn = this->getCheckIn();
    DTFecha checkOut = this->getCheckOut();
    int codigo = this->getCodigo();
    float costo = this->getCosto();
    int numeroHabitacion = this->getNumeroHabitacion();
    string titular = this->getTitular()->getNombre();
    set<string> nombreHuespedes;

    DTReserva * resultado = new DTReserva(estado, checkIn, checkOut, codigo, costo, numeroHabitacion, titular, nombreHuespedes);

    return resultado;
};

void ReservaIndividual ::comentarCalificacion(string emailH, string respuesta) {
    if (this->estadia == NULL) {
        throw invalid_argument("La reserva no tiene estadia");
    }
    else if (this->getTitular()->getEmail() != emailH) {
        throw invalid_argument("El huesped con email: " + emailH + " no pertenece a esta reserva.");
    }
    
    this->estadia->comentarCalificacion(respuesta);
}

void ReservaIndividual::getDataEstadias(map<pair<int,string>, DTEstadia*>& total){
    if(this->estadia == NULL){
        return;
    }
    pair<int,string> id = pair<int,string>(this->getCodigo(), this->getTitular()->getEmail());
    pair<pair<int,string>, DTEstadia*> agregar =  pair<pair<int,string>, DTEstadia*>(id, this->estadia->getDTEstadia(this->getCodigo()));
    total.insert(agregar);
};

DTCalificacion* ReservaIndividual::getDataCalificacion(string emailH){
    return this->estadia->getDTCalificacion(this->getCodigo());
};

ReservaIndividual ::~ReservaIndividual() {
    delete this->estadia;
}