#ifndef _DTRESERVA_
#define _DTRESERVA_

#include "./Const.h"
#include "./DTFecha.h"
#include<iostream>
#include<set>

using namespace std;

class DTReserva{
    private:
        EstadoReserva estado;
        DTFecha checkIn;
        DTFecha checkOut;
        int codigo;
        float costo;
        int numeroHabitacion;
        string titular;
        set<string> nombreHuespedes;
    public:
        EstadoReserva getEstado();
        DTFecha getCheckIn();
        DTFecha getCheckOut();
        int getCodigo();
        float getCosto();
        int getNumeroHabitacion();
        set<string> getNombreHuespedes();
        string getTitular();

        DTReserva(EstadoReserva estado,DTFecha &checkIn, DTFecha &checkOut,int codigo,float costo,int numeroHabitacion,string titular, set<string> nombreHuespedes);
        ~DTReserva();
};

ostream &operator<<(ostream &out, DTReserva &res);

#endif