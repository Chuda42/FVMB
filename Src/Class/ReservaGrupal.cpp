#include "../../Include/ReservaGrupal.h"

ReservaGrupal::ReservaGrupal(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular,set<Huesped*> hsel,Hostal* hostal,Habitacion* habitacion):Reserva(codigo, checkIn, checkOut, titular, hostal, habitacion){
    map<string, Estadia*>estadias;
    this->estadias = estadias;
    set<Huesped*>::iterator iter;
    map<string, Huesped*> huespedes;
    int cantidadFingers;
    cantidadFingers = (this->getTitular()->getEsFinger())? 1:0;

    for(iter = hsel.begin(); iter != hsel.end(); ++iter){
        pair<string, Huesped*> agregar = pair<string, Huesped*>((*iter)->getEmail(),*iter);
        huespedes.insert(agregar);
        if((*iter)->getEsFinger()){
            cantidadFingers++;
        }
    }
    this->huespedes = huespedes;
    float costo;
    int diferenciaDias = checkIn.diferenciaDeDias(checkOut);
    costo = diferenciaDias * habitacion->getPrecioPorNoche() * (this->huespedes.size() + 1);
    if(cantidadFingers >=2){
        costo = costo*0.7; //30% de descuento
    }
    this->Reserva::setCosto(costo);
};

void ReservaGrupal::sumarCalificaciones(int& puntajeTotal, int& cantidadPuntajes){
    map<string, Estadia*>::iterator iter;
    Estadia* estadia;

    for(iter = this->estadias.begin(); iter != this->estadias.end(); ++iter){
        estadia = iter->second;
        estadia->sumarPuntajeCalificacion(puntajeTotal, cantidadPuntajes);
    }
}

void ReservaGrupal::registrarEstadia(string emailH, DTFecha& fecha) {
    map<string, Huesped*>::iterator iter = this->huespedes.find(emailH);
    if(iter != this->huespedes.end()){
        Huesped* huesped =iter->second;
        if(this->estadias.find(emailH) == this->estadias.end()){
            Estadia* estadia = new Estadia(fecha, 0, huesped);
            this->setEstado(Cerrada);
            pair<string, Estadia*> agregar = pair<string, Estadia*>(emailH, estadia);
            this->estadias.insert(agregar);
        }else{
            throw std::invalid_argument("El Huesped ya había registrado su estadia");
        }
    }else if(this->getTitular()->getEmail() == emailH){
        Huesped* huesped = this->getTitular();
        if(this->estadias.find(emailH) == this->estadias.end()){
            Estadia* estadia = new Estadia(fecha, 0, huesped);
            this->setEstado(Cerrada);
            pair<string, Estadia*> agregar = pair<string, Estadia*>(emailH, estadia);
            this->estadias.insert(agregar);
        }else{
            throw std::invalid_argument("El Huesped ya había registrado su estadia");
        }
    }else{
        throw std::invalid_argument("La reserva no contiene al huesped con email " + emailH);
    }
};

void ReservaGrupal::getDTCalificaciones(set<DTCalificacion*>& total){
    map<string, Estadia*>::iterator iter;
    Estadia* estadia;
    DTCalificacion* dtC;

    for(iter = this->estadias.begin(); iter != this->estadias.end(); ++iter){
        estadia = iter->second;
        if(estadia->tieneCalificacion()){
            dtC = estadia->getDTCalificacion();
            total.insert(dtC);    
        }
    }
};

void ReservaGrupal::getDTCalificaciones(string nombreH, set<DTCalificacion*>& total){
    bool esDeHostal = this->esReservaDeHostal(nombreH);
    if(esDeHostal){
        this->getDTCalificaciones(total);
    }
};

void ReservaGrupal::finalizarEstadiaSiEsValida(string emailH, DTFecha& fecha){
    map<string, Estadia*>::iterator iter;
    Estadia* estadia;
    for(iter = this->estadias.begin(); iter != this->estadias.end(); ++iter){
        estadia = iter->second;
        if(estadia->estadiaValidaParaFinalizar(emailH)){
            estadia->finalizarEstadia(fecha);
        }
    }
}

bool ReservaGrupal::tieneEstadiaFinalizada(string email) {
    map<string, Estadia*>::iterator iter = this->estadias.find(email);

    if (iter == this->estadias.end())
    {
        return false;
    }

    return iter->second->estaFinalizadaEstadia();
}

bool ReservaGrupal::esReservaValida(string emailH, string nombreHostal)
{
    if (!this->esReservaDeHostal(nombreHostal) || this->estaCancelada())
    {
        return false;
    }
    map<string, Huesped*>::iterator iter;

    for(iter = this->huespedes.begin(); iter != this->huespedes.end(); ++iter)
    {
        if (iter->second->getEmail() == emailH)
        {
            return true;
        }
    }

    return this->getTitular()->getEmail() == emailH;
}

DTEstadia* ReservaGrupal::getDTEstadiaFinalizada(string email) {
    return this->estadias.find(email)->second->getDTEstadia(this->getCodigo());
}

void ReservaGrupal ::calificarEstadia(string emailH, DTFecha& fecha, string comentario, int puntaje) {
    if (this->estadias.find(emailH) == this->estadias.end()) {
        throw invalid_argument("El usuario: " + emailH + " no tiene estadia.");
    }

    (this->estadias.find(emailH)->second)->calificarEstadia(fecha, comentario, puntaje);
}

DTReserva* ReservaGrupal::getDTReserva(){
    EstadoReserva estado = this->getEstado();
    DTFecha checkIn = this->getCheckIn();
    DTFecha checkOut = this->getCheckOut();
    int codigo = this->getCodigo();
    float costo = this->getCosto();
    int numeroHabitacion = this->getNumeroHabitacion();
    string titular = this->getTitular()->getNombre();
    set<string> nombreHuespedes;
    map<string, Huesped*>::iterator iter;
    for(iter = this->huespedes.begin(); iter != this->huespedes.end(); ++iter){
        nombreHuespedes.insert(iter->second->getNombre());
    }
    DTReserva * resultado = new DTReserva(estado, checkIn, checkOut, codigo, costo, numeroHabitacion, titular, nombreHuespedes);

    return resultado;
};

void ReservaGrupal::getCalificacionesSinResponderDelHostal(string nombreH, set<DTCalificacion*>& total){
    if (!this->esReservaDeHostal(nombreH))
    {
        return;
    }

    map<string, Estadia*>::iterator iter;

    Estadia* estadia;
    for (iter = this->estadias.begin(); iter != this->estadias.end(); ++iter)
    {
        estadia = iter->second;

        if (estadia->tieneCalificacionSinResponder()) {
            total.insert(estadia->getDTCalificacion(this->getCodigo()));
        }
    }
}

void ReservaGrupal ::comentarCalificacion(string emailH, string respuesta) {
    map<string, Estadia*>::iterator iter = this->estadias.find(emailH);

    if (iter == this->estadias.end()) {
        throw invalid_argument("No existe estadia asociada al Huesped con email: " + emailH);
    }

    (iter->second)->comentarCalificacion(respuesta);
}

void ReservaGrupal::getDataEstadias(map<pair<int,string>, DTEstadia*>& total){
    map<string, Estadia*>::iterator iter;
    for(iter = this->estadias.begin(); iter != this->estadias.end(); ++iter){
        pair<int,string> id = pair<int,string>(this->getCodigo(), iter->second->getEmailHuesped());
        pair<pair<int,string>, DTEstadia*> agregar =  pair<pair<int,string>, DTEstadia*>(id, iter->second->getDTEstadia(this->getCodigo()));
        total.insert(agregar);
    }

};

DTCalificacion* ReservaGrupal::getDataCalificacion(string emailH){
    map<string, Estadia*>::iterator iter = this->estadias.find(emailH);
    return iter->second->getDTCalificacion(this->getCodigo());
};

ReservaGrupal :: ~ReservaGrupal(){
    this->huespedes.clear();

    map<string, Estadia*>::iterator iter;
    for(iter = this->estadias.begin(); iter != this->estadias.end(); ++iter){
        delete iter->second;
    }
    this->estadias.clear();
}