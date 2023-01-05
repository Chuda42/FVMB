#include "../../Include/DTDatosNuevaReserva.h"

DTDatosNuevaReserva :: DTDatosNuevaReserva(DTFecha& checkIn, DTFecha& checkOut,bool esGrupal){
        this->checkIn = checkIn;
        this->checkOut = checkOut;
        this->esGrupal = esGrupal;
}

DTFecha& DTDatosNuevaReserva :: getCheckIn(){
    return this->checkIn;
}

DTFecha& DTDatosNuevaReserva :: getCheckOut(){
    return this->checkOut;
}

bool DTDatosNuevaReserva :: getEsGrupal(){
    return this->esGrupal;
} 

DTDatosNuevaReserva :: ~DTDatosNuevaReserva(){}