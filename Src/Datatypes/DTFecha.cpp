#include "../../Include/DTFecha.h"
using namespace std;

DTFecha:: DTFecha()
{
    this->hora = 0;
    this->dia  = 0;
    this->mes  = 0;
    this->anio = 0;
}

DTFecha::DTFecha(int anio,int mes,int dia, int hora)
{
    if (dia>31) {
        throw std::invalid_argument("El dia no puede ser mayor a 31.");
    }
    if (dia<1) {
        throw std::invalid_argument("El dia no puede ser menor a 1.");
    }

    if (mes>12) {
        throw std::invalid_argument("El mes no puede ser mayor a 12.");
    }
    if (mes<1) {
        throw std::invalid_argument("El mes no puede ser menor a 1.");
    }

    if(anio<1900) {
        throw std::invalid_argument("El anio no puede ser menor a 1900.");
    }

    if(hora < 1 || hora > 24){
         throw std::invalid_argument("La hora no puede ser menor a 1 y mayor a 24.");
    }

    this->hora = hora;
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
};

DTFecha::DTFecha(string fecha){
    unsigned int i = 0;
    unsigned int flagHora = 0, flagDia = 0, flagMes = 0, flagAnio = 0;
    int hora = 0 , dia= 0, mes = 0, anio = 0;
    string aux;
    while(i < fecha.length()){
        if(flagHora == 0){
            if (fecha[i] == '/'){
                aux = fecha.substr(0,i);
                hora = stoi(aux);
                flagHora = i + 1;
            }
        }else if (flagDia == 0){
            if (fecha[i] == '/'){
                aux = fecha.substr(flagHora,i - flagHora);
                dia = stoi(aux);
                flagDia = i+1;
            }
        }else if (flagMes == 0){
            if (fecha[i] == '/'){
                aux = fecha.substr(flagDia,i - flagDia);
                mes = stoi(aux);
                flagMes = i+1;
            }
        }else if (flagAnio == 0){
            aux = fecha.substr(flagMes,fecha.length() - i);
            anio = stoi(aux);
            flagAnio = 1; 
        }
        i++;
    };
    if (dia>31) {
        throw std::invalid_argument("El dia no puede ser mayor a 31.");
    }
    if (dia<1) {
        throw std::invalid_argument("El dia no puede ser menor a 1.");
    }

    if (mes>12) {
        throw std::invalid_argument("El mes no puede ser mayor a 12.");
    }
    if (mes<1) {
        throw std::invalid_argument("El mes no puede ser menor a 1.");
    }

    if(anio<1900) {
        throw std::invalid_argument("El anio no puede ser menor a 1900.");
    }

    if(hora < 1 || hora > 24){
         throw std::invalid_argument("La hora no puede ser menor a 1 y mayor a 24.");
    }

    this->hora = hora;
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
};

DTFecha::DTFecha(DTFecha &f){
    this->hora = f.getHora();
    this->dia = f.getDia();
    this->mes = f.getMes();
    this->anio = f.getAnio();
};

int DTFecha:: getAnio()
{
    return this->anio;
}

int DTFecha:: getMes()
{
    return this->mes;
}

int DTFecha:: getDia()
{
    return this->dia;
}

int DTFecha:: getHora()
{
    return this->hora;
}

DTFecha:: ~DTFecha(){}

int DTFecha::diferenciaDeDias(DTFecha &fecha){
    int anioMesThis = this->anio*12;
    int mesDiaThis =(this->mes + anioMesThis)*31;
    int diasThis = this->dia + mesDiaThis;

    int anioMesFecha = fecha.anio*12;
    int mesDiaFecha =(fecha.mes + anioMesFecha)*31;
    int diasFecha = fecha.dia + mesDiaFecha;

    return diasFecha - diasThis;

};

bool DTFecha::operator==(DTFecha &fecha){
    return ((this->anio == fecha.anio)&&(this->hora == fecha.hora))&&((this->mes == fecha.mes)&&(this->dia == fecha.dia));
}

int DTFecha::totalHoras(){
    int anioMesThis = this->anio*12;
    int mesDiaThis =(this->mes + anioMesThis)*31;
    int diaHoraThis=(this->dia + mesDiaThis)*24;
    int horaThis = this->hora + diaHoraThis;
    return horaThis;

}

bool DTFecha::operator>(DTFecha &fecha){
    return this->totalHoras() > fecha.totalHoras();
};

bool DTFecha::operator>=(DTFecha &fecha){
    return this->totalHoras() >= fecha.totalHoras(); 
};

bool DTFecha::operator<(DTFecha &fecha){
    return this->totalHoras() < fecha.totalHoras(); 
};

bool DTFecha::operator<=(DTFecha &fecha){
    return this->totalHoras() <= fecha.totalHoras(); 
};

istream& operator>>(istream& i, DTFecha &f){
    string fecha;
    i >> fecha;
    f = DTFecha(fecha);
    return i;
};

ostream &operator<<(ostream &out, DTFecha &f){
    out << f.getHora() << "/" << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() <<endl;
    return out;
};

//DTFecha& operator=(DTFecha &fecha);
