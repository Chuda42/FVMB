#ifndef _DTESTADIA_
#define _DTESTADIA_

#include<iostream>
#include "./DTFecha.h"


using namespace std;

class DTEstadia{
    private:
        int codigoR;
        DTFecha checkIn;
        DTFecha checkOut;
        int promo;
        string nombreHuesped;
        string emailHuesped;
        string nombreHostal;
        int numeroHabitacion;
    public:
        DTEstadia(int codigoR, DTFecha checkIn, DTFecha checkOut, int promo, string nombreHuesped, string emailHuesped, string nombreHostal, int numeroHabitacion);
        DTEstadia(int codigoR, DTFecha checkIn, DTFecha checkOut, int promo);
        
        int getCodigoR();
        DTFecha getCheckIn();
        DTFecha getCheckOut();
        int getPromo();
        string getNombreHuesped();
        string getEmailHuesped();
        string getNombreHostal();
        int getNumeroHabitacion();
        ~DTEstadia();

};

ostream &operator<<(ostream &out, DTEstadia &estadia);


#endif