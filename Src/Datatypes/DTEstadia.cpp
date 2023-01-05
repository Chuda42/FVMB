#include "../../Include/DTEstadia.h"

DTEstadia :: DTEstadia(int codigoR, DTFecha checkIn, DTFecha checkOut, int promo, string nombreHuesped, string emailHuesped, string nombreHostal, int numeroHabitacion){
    this->codigoR = codigoR;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->promo = promo;
    this->nombreHuesped = nombreHuesped;
    this->emailHuesped = emailHuesped;
    this->nombreHostal = nombreHostal;
    this->numeroHabitacion = numeroHabitacion;
}

DTEstadia :: DTEstadia(int codigoR, DTFecha checkIn, DTFecha checkOut, int promo)
{
    this->codigoR = codigoR;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->promo = promo;

    this->nombreHuesped = "";
    this->emailHuesped = "";
    this->nombreHostal = "";
    this->numeroHabitacion = -1;
}

int DTEstadia :: getCodigoR(){
    return this->codigoR;
}

DTFecha DTEstadia :: getCheckIn(){
    return this->checkIn;
}

DTFecha DTEstadia :: getCheckOut(){
    return this->checkOut;
}

int DTEstadia :: getPromo(){
    return this->promo;
}

string DTEstadia :: getNombreHuesped(){
    return this->nombreHuesped;
}

string DTEstadia :: getEmailHuesped(){
    return this->emailHuesped;
}

string DTEstadia :: getNombreHostal(){
    return this->nombreHostal;
}

int DTEstadia :: getNumeroHabitacion(){
    return this->numeroHabitacion;
}

DTEstadia :: ~DTEstadia(){}

ostream &operator<<(ostream &out, DTEstadia &estadia)
{
    if(!(estadia.getEmailHuesped().empty() ||estadia.getNombreHuesped().empty() || estadia.getNombreHostal().empty() || estadia.getNumeroHabitacion() == -1)){
        if(estadia.getCheckOut().getDia() == 0){
            out<<"CodigoR: "<<estadia.getCodigoR()<< " CheckIn: " << estadia.getCheckIn().getHora() << "/" << estadia.getCheckIn().getDia() << "/" << estadia.getCheckIn().getMes() << "/" << estadia.getCheckIn().getAnio() << " CheckOut: No se realizo el checkOut" << " Promo: " <<estadia.getPromo()<< " Email huesped: "<< estadia.getEmailHuesped() << ". Nombre huesped: "<< estadia.getNombreHuesped() << ". Nombre hostal: " << estadia.getNombreHostal()<< ". Numero habitacion: "<< to_string(estadia.getNumeroHabitacion())<<endl;
        }else{
            out<<"CodigoR: "<<estadia.getCodigoR()<< " CheckIn: " << estadia.getCheckIn().getHora() << "/" << estadia.getCheckIn().getDia() << "/" << estadia.getCheckIn().getMes() << "/" << estadia.getCheckIn().getAnio() << " CheckOut: " << estadia.getCheckOut().getHora() << "/" << estadia.getCheckOut().getDia() << "/" << estadia.getCheckOut().getMes() << "/" << estadia.getCheckOut().getAnio() << " Promo: " <<estadia.getPromo()<< " Email huesped: "<< estadia.getEmailHuesped() << ". Nombre huesped: "<< estadia.getNombreHuesped() << ". Nombre hostal: " << estadia.getNombreHostal()<< ". Numero habitacion: "<< to_string(estadia.getNumeroHabitacion())<<endl;
        }
        
    } else{
        if(estadia.getCheckOut().getDia() == 0){
            out<<"CodigoR: "<<estadia.getCodigoR()<< " CheckIn: " << estadia.getCheckIn().getHora() << "/" << estadia.getCheckIn().getDia() << "/" << estadia.getCheckIn().getMes() << "/" << estadia.getCheckIn().getAnio() << " CheckOut: No se realizo el checkOut" << " Promo: " <<estadia.getPromo() << endl;
        }else{
            out<<"CodigoR: "<<estadia.getCodigoR()<< " CheckIn: " << estadia.getCheckIn().getHora() << "/" << estadia.getCheckIn().getDia() << "/" << estadia.getCheckIn().getMes() << "/" << estadia.getCheckIn().getAnio() << " CheckOut: " << estadia.getCheckOut().getHora() << "/" << estadia.getCheckOut().getDia() << "/" << estadia.getCheckOut().getMes() << "/" << estadia.getCheckOut().getAnio() << " Promo: " <<estadia.getPromo() << endl;
        }    
    }
    return out;
};

