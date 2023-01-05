#include "../../Include/Hostal.h"
using namespace std;

Hostal::Hostal(std::string nombre,std::string direccion,std::string telefono){
    this->nombre = nombre;
    this->direccion = direccion;
    this->telefono = telefono;
    map<int, Habitacion*> habitaciones;
    this->habitaciones = habitaciones;
};

Hostal::~Hostal(){
    map<int, Habitacion*>::iterator iter;
    for(iter = this->habitaciones.begin(); iter != this->habitaciones.end(); ++iter){
        delete iter->second;
    }
    this->habitaciones.clear();
};

void Hostal::setNombre(std::string nombre){};
void Hostal::setDireccion(std::string direccion){};
void Hostal::setTelefono(std::string telefono){};

std::string Hostal::getNombre(){
    return this->nombre;
};

std::string Hostal::getDireccion(){
    return this->direccion;
};

std::string Hostal::getTelefono(){
    return this->telefono;
};


float Hostal::getPromedio(){
    ControladorReserva* cR = ControladorReserva::getInstancia();
    return cR->calcularCalificacionPromedio(this->nombre);
};

set<DTHabitacion*> Hostal::getHabitaciones(){
    set<DTHabitacion*> resultado;
    DTHabitacion* dTHab;
    ControladorReserva* cR = ControladorReserva::getInstancia();
    map<int,Habitacion*>::iterator iter;
    set<DTCalificacion*> calif;
    for(iter = this->habitaciones.begin(); iter != this->habitaciones.end(); ++iter){
        calif = cR->getCalificacionPorHabitacion(iter->second);
        dTHab = iter->second->getDTHabitacion(calif);
        resultado.insert(dTHab);
    }
    return resultado;
};

map<pair<int,string>, DTEstadia*> Hostal::getEstadias(){
    ControladorReserva* cR = ControladorReserva::getInstancia(); 
    return cR->getDataEstadias(this);
};

Habitacion* Hostal::getInstanciaHabitacion(int numeroHabitacion){
   map<int, Habitacion*>::iterator iter = this->habitaciones.find(numeroHabitacion);
   return iter->second;
};

DTHostal* Hostal::getDataHostal(){
    ControladorReserva* cR = ControladorReserva::getInstancia();
    float promCal = cR->calcularCalificacionPromedio(this->nombre);
    DTHostal* dTH = new DTHostal(this->nombre,this->direccion,this->telefono,promCal);
    return dTH;
};


void Hostal::agregarHabitacion(DTHabitacion* dataHabitacion){
    map<int, Habitacion*>::iterator iter;
    iter = this->habitaciones.find(dataHabitacion->getNumero());
    if(iter == this->habitaciones.end()){
        Habitacion * nuevaHabit = new Habitacion(dataHabitacion);
        pair<int, Habitacion*> habitNueva = pair<int, Habitacion*>(dataHabitacion->getNumero(), nuevaHabit);
        this->habitaciones.insert(habitNueva);
    }else{
        throw std::invalid_argument("Ya existe una habitacion registrada con el número ingresado");
    }
    
};
//void Hostal::create(std::string nombre,std::string direccion, std::string telefono){};
set<DTHabitacion*> Hostal::getHabitacionesDisponibles(set<int> habNDis){
    set<DTHabitacion*> resultado; 
    map<int, Habitacion*>::iterator iter;
    bool estaEnLista;
    Habitacion* habit;
    DTHabitacion * dataHabit;

    for(iter = this->habitaciones.begin(); iter != this->habitaciones.end(); ++iter){
        habit = iter->second;
        estaEnLista = habit->estaHabitacionEnLista(habNDis);
        if(!estaEnLista){
            dataHabit = habit->getDatosHabitacion();
            resultado.insert(dataHabit);
        }
    }
    return resultado;
};
