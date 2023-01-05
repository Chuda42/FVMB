#include "../../Include/DTReserva.h"

DTReserva :: DTReserva(EstadoReserva estado,DTFecha &checkIn, DTFecha &checkOut,int codigo,float costo,int numeroHabitacion,string titular,set<string> nombreHuespedes){
    this->estado = estado;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->codigo = codigo;
    this->costo = costo;
    this->numeroHabitacion = numeroHabitacion;
    this->nombreHuespedes = nombreHuespedes;
    this->titular = titular;
}

EstadoReserva DTReserva :: getEstado(){
    return this->estado;
}

DTFecha DTReserva  :: getCheckIn(){
    return this->checkIn;
}

DTFecha DTReserva :: getCheckOut(){
    return this->checkOut;
}

int DTReserva :: getCodigo(){
    return this->codigo;
}

float DTReserva :: getCosto(){
    return this->costo;
}

int DTReserva :: getNumeroHabitacion(){
    return this->numeroHabitacion;
}

set<string> DTReserva :: getNombreHuespedes(){
    return this->nombreHuespedes;
}

string DTReserva :: getTitular(){
    return this->titular;
}

DTReserva :: ~DTReserva(){}

ostream &operator<<(ostream &out, DTReserva &res) {
    string estado = " ";
    if(res.getEstado() == Abierta){
        estado = "Abierta"; 
    }else if (res.getEstado() == Cancelada){
        estado = "Cancelada";
    }else if(res.getEstado() == Cerrada){
        estado = "Cerrada";
    }
    out << "Codigo Reserva: " << res.getCodigo() << " estado: " << estado << 
    " checkIn: " << res.getCheckIn().getHora() << "/" << res.getCheckIn().getDia() << "/" << res.getCheckIn().getMes() << "/" << res.getCheckIn().getAnio() <<
    " checkOut: " << res.getCheckOut().getHora() << "/" << res.getCheckOut().getDia() << "/" << res.getCheckOut().getMes() << "/" << res.getCheckOut().getAnio() <<
    " costo: " << res.getCosto() << " numero de habitacion: " << res.getNumeroHabitacion() << " titular :" <<
    res.getTitular() << endl;

    if (!res.getNombreHuespedes().empty())
    {
        out << " Otros huespedes: ";
        set<string> huespedes = res.getNombreHuespedes();
        set<string> :: iterator it;

        unsigned count = 1;

        for (it = huespedes.begin(); it != huespedes.end(); ++it) {
            out << *it;

            if (count < huespedes.size()) {
                out << ", ";
            } else {
                out << ".";
            }
            count++;
        }
        out << endl;
    }

    return out;
}