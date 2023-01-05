#ifndef DTRESERVAINDIVIDUAL_H_INCLUDED
#define DTRESERVAINDIVIDUAL_H_INCLUDED

#include "DTReserva.h"
#include "ReservaIndividual.h"

class DTReservaIndividual : public DTReserva{

private:
    bool pagado;
public:
    DTReservaIndividual(int codigo, DTFecha& checkIn, DTFecha& checkOut, EstadoReserva estado, float costo, int habitacion, bool pagado);
    DTReservaIndividual(ReservaIndividual* reservaI);
    bool getPagado();

    bool operator==(DTReservaIndividual &dtri);
};

#endif