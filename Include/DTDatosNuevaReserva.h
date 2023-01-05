#ifndef _DTDATOSNUEVARESERVA_
#define _DTDATOSNUEVARESERVA_

#include "./DTFecha.h"

class DTDatosNuevaReserva {
    private:
        DTFecha checkIn;
        DTFecha checkOut;
        bool esGrupal;

    public:
        DTDatosNuevaReserva(DTFecha& checkIn, DTFecha& checkOut,bool esGrupal);
        
        DTFecha& getCheckIn();
        DTFecha& getCheckOut();
        bool getEsGrupal();
        
        ~DTDatosNuevaReserva();
};

#endif