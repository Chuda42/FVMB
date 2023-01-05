#include "../../Include/Reserva.h"

Reserva::Reserva(int codigo, DTFecha& checkIn, DTFecha& checkOut,Huesped* titular, Hostal* hostal, Habitacion* habitacion){
    this->codigo = codigo;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->titular = titular;
    this->hostal = hostal;
    this->habitacion = habitacion;
    this->estado = Abierta;

    //TODO para que no de problemas
    this->costo = 0;
}

void Reserva::setCosto(float costo){
    this->costo = costo;
};

void Reserva::setEstado(EstadoReserva estado){
    this->estado = estado;
}

string Reserva::getNombreHostal(){
    return this->hostal->getNombre();
}

int Reserva::getNumeroHabitacion(){
    return this->habitacion->getNumero();
}

int Reserva::getCodigo(){
    return this->codigo;
}

DTFecha& Reserva::getCheckIn(){
    return this->checkIn;
}

DTFecha& Reserva::getCheckOut(){
    return this->checkOut;
}


EstadoReserva Reserva::getEstado(){
    return this->estado;
}

float Reserva::getCosto(){
    return this->costo;
}

Huesped* Reserva::getTitular(){
    return this->titular;
}

bool Reserva::esReservaDeHostal(Hostal* hostal){
    return this->getNombreHostal() == hostal->getNombre();
}

bool Reserva::esReservaDeHostal(string nombreH){
    return this->getNombreHostal() == nombreH;
}

bool Reserva::reservaEnRango(DTDatosNuevaReserva* dNR, string nombreHostal){
    bool caso1= this->checkOut <= dNR->getCheckIn();
    bool caso2= this->checkIn >= dNR->getCheckOut();
    return (this->esReservaDeHostal(nombreHostal)) && !(caso1 || caso2);
}

bool Reserva::esReservaValida(string email, string nombreHostal){
    return (this->esReservaDeHostal(nombreHostal) && !this->estaCancelada()) && (this->titular->getEmail() == email);
}

bool Reserva::estaCancelada(){
    return this->estado == Cancelada;
} 

bool Reserva::esReservaDeHabitacion(Habitacion* habitacion){
    return this->habitacion == habitacion;
}

Reserva :: ~Reserva() {
}
