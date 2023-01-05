#ifndef _DTFECHA_
#define _DTFECHA_

#include <iostream>
using namespace std;
class DTFecha{
    private:
        int dia;
        int mes;
        int anio;
        int hora;
    public:
        DTFecha();
        DTFecha(int anio, int mes, int dia, int hora);
        DTFecha(DTFecha& f);
        DTFecha(string fecha);
        int getAnio();
        int getMes();
        int getDia();
        int getHora();
        ~DTFecha();

        int totalHoras();
        int diferenciaDeDias(DTFecha &fecha);
        bool operator==(DTFecha &fecha);
        bool operator>(DTFecha &fecha);
        bool operator>=(DTFecha &fecha);
        bool operator<(DTFecha &fecha);
        bool operator<=(DTFecha &fecha);
        
};

istream& operator>>(istream& i, DTFecha &f);
ostream &operator<<(ostream &out, DTFecha &f);

#endif