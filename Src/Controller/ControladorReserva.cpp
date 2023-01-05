//dependencias
#include "../../Include/ControladorReserva.h"

using namespace std;

ControladorReserva* ControladorReserva::instancia = NULL;

ControladorReserva::ControladorReserva(){
    map<int, Reserva*> reservas;
    this->reservas = reservas;
    this->cantidadReservas = 0;
};

//sacar la instancia
ControladorReserva* ControladorReserva::getInstancia(){
    if (ControladorReserva::instancia == NULL){
        ControladorReserva::instancia = new ControladorReserva();
    }
    return ControladorReserva::instancia;
};

//funciones de la interfaz ireserva
set<DTCalificacion*> ControladorReserva::getCalificacionesDeHostal(string nombreH){
    set<DTCalificacion*> resultado;

    map<int, Reserva*>::iterator iter;
    Reserva* r;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        r->getDTCalificaciones(nombreH, resultado);
    }
    return resultado;
};

set<int> ControladorReserva::getReservasNoCanceladas(string email, string nombreHostal){
    set<int> resultado;
    int codigoR;

    map<int, Reserva*>::iterator iter;
    Reserva* r;
    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        bool reservaValida = r->esReservaValida(email, nombreHostal);
        if (reservaValida){
            codigoR = r->getCodigo();
            resultado.insert(codigoR);
        }
    }
    return resultado;
};

void ControladorReserva::registrarEstadia(string emailH, int codigoR){
    ControladorFechaSistema* cFS = ControladorFechaSistema::getInstancia();
    DTFecha fecha = cFS->getFechaSistema(); 

    map<int, Reserva*>::iterator iter;
    iter = this->reservas.find(codigoR);
    Reserva * reserva = iter->second;
    reserva->registrarEstadia(emailH, fecha);
    
}; 

void ControladorReserva::finalizarEstadia(string emailH, string nombreHostal){
    ControladorFechaSistema* cFS = ControladorFechaSistema::getInstancia();
    DTFecha fecha = cFS->getFechaSistema();

    map<int, Reserva*>::iterator iter;
    Reserva* r;
    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        if (r->getNombreHostal() == nombreHostal)
        {
            r->finalizarEstadiaSiEsValida(emailH, fecha);
        }
    }
};

set<DTEstadia*> ControladorReserva::getEstadiasFinalizadas(string emailH, string nombreHostal){
    set<DTEstadia*> estadiasFinalizadas;

    map<int, Reserva*>::iterator iter;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        Reserva* reserva = iter->second;
        if (reserva->esReservaValida(emailH, nombreHostal))
        {
            if (reserva->tieneEstadiaFinalizada(emailH))
            {
                estadiasFinalizadas.insert(reserva->getDTEstadiaFinalizada(emailH));
            }
        }
    }

    return estadiasFinalizadas;
}

void ControladorReserva::calificarEstadia(string email, int codigoR, string comentario, int puntaje){
    ControladorFechaSistema* cFS = ControladorFechaSistema::getInstancia();
    DTFecha fecha = cFS->getFechaSistema();

    map<int, Reserva*>::iterator iter;
    Reserva* r;

    iter = this->reservas.find(codigoR);

    if (iter == this->reservas.end()) {
        throw invalid_argument("no existe la reserva con codigo: " + to_string(codigoR));
    }

    r = iter->second;
    r->calificarEstadia(email, fecha, comentario, puntaje);
};

void ControladorReserva::comentarCalificacion(string emailH, int codigoR, string respuesta){
    map<int, Reserva*>::iterator iter = this->reservas.find(codigoR);

    if (iter == this->reservas.end())
    {
        throw invalid_argument("No existe reserva con codigo: " + to_string(codigoR));
    }

    (iter->second)->comentarCalificacion(emailH, respuesta);
};

set<DTCalificacion*> ControladorReserva::getCalificacionesSinResponder(string emailE){
    set<DTCalificacion*> resultado;
    
    ControladorUsuario* cU = ControladorUsuario::getInstancia();
    string nombreHostalDelEmpleado = cU->getNombreHostalDeEmpleado(emailE);

    map<int, Reserva*>::iterator iter;
    Reserva* r;
    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        r->getCalificacionesSinResponderDelHostal(nombreHostalDelEmpleado, resultado);
    }
    return resultado;
};

set<DTReserva*> ControladorReserva::getReservas(string nombreH){
    set<DTReserva*> resultado;
    
    map<int, Reserva*>::iterator iter;
    Reserva* r;
    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        bool esDeHostal = r->esReservaDeHostal(nombreH);
        if(esDeHostal){
            DTReserva* reserva = r->getDTReserva();
            resultado.insert(reserva);
        }
    }
    return resultado;
};

DTCalificacion* ControladorReserva::getCalificacionEstadia(string emailH, int codigoR){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    iter = this->reservas.find(codigoR);
    r = iter->second;
    return r->getDataCalificacion(emailH);
};

DTReserva* ControladorReserva::getReserva(int codigoR){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    iter = this->reservas.find(codigoR);
    r = iter->second;
    return r->getDTReserva();
};

void ControladorReserva::eliminarReserva(int codigoR){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    iter = this->reservas.find(codigoR);

    if (iter == this->reservas.end()) {
        throw invalid_argument("No existe la reserva con codigo: " + to_string(codigoR));
    }
    r = iter->second;
    this->reservas.erase(codigoR);
    delete r;
};

ControladorReserva::~ControladorReserva(){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        delete r;
    }
    this->reservas.clear();
    ControladorReserva::instancia = NULL;
};


//funciones del controlador
set<int> ControladorReserva::getHabitacionesNoDisponibles(string nombreHostal, DTDatosNuevaReserva* dNR){
    set<int> resultado;
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        bool rEnRango = r->reservaEnRango(dNR, nombreHostal);
        if(rEnRango){
            int numeroHabitacion = r->getNumeroHabitacion();
            resultado.insert(numeroHabitacion);
        }
    }
    return resultado;
};

float ControladorReserva::calcularCalificacionPromedio(string n){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    int puntajeTotal= 0;
    int cantidadPuntajes = 0;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        if(r->esReservaDeHostal(n)){
            r->sumarCalificaciones(puntajeTotal, cantidadPuntajes);
        }
    }
    //Control para no dividir por cero;

    return cantidadPuntajes == 0 ? 0 : float(puntajeTotal)/float(cantidadPuntajes);
};

set<DTCalificacion*> ControladorReserva::getCalificacionPorHabitacion(Habitacion* habitacion){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    set<DTCalificacion*> resultado;
    //set<DTCalificacion*> calificaciones;

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        bool esValida = r->esReservaDeHabitacion(habitacion);
        if(esValida){
            r->getDTCalificaciones(resultado);
            //this->concatenarSetsDTCalificacion(&resultado, &calificaciones);
        }
    }
    //calificaciones.clear();
    return resultado;
};

map<pair<int,string>, DTEstadia*> ControladorReserva::getDataEstadias(Hostal* hostal){
    map<int, Reserva*>::iterator iter;
    Reserva* r;

    map<pair<int,string>, DTEstadia*> resultado;
    set<DTEstadia*> estadiasDeR;
    

    for (iter = this->reservas.begin(); iter != this->reservas.end(); ++iter){
        r = iter->second;
        bool esDeHostal = r->esReservaDeHostal(hostal);
        if(esDeHostal){
            r->getDataEstadias(resultado);
        }
    }
    return resultado;
};

void ControladorReserva::crearReserva(DTDatosNuevaReserva* dRes, string emailTitular, set<string> hsel, Hostal* hostal,Habitacion* habitacion){
    ControladorUsuario* cU = ControladorUsuario::getInstancia();
    Huesped* titular = cU->getInstanciaHuesped(emailTitular);
    Reserva* reserva;
    this->cantidadReservas++;
    int codigoR = this->cantidadReservas;
    if(dRes->getEsGrupal()){
        set<Huesped*> huespedes = cU->getInstanciasHuespedes(hsel);
        reserva = new ReservaGrupal(codigoR,dRes->getCheckIn(), dRes->getCheckOut(),titular, huespedes, hostal, habitacion);   
    }else{
        reserva = new ReservaIndividual(codigoR,dRes->getCheckIn(), dRes->getCheckOut(),titular, hostal, habitacion);
    }
    pair<int, Reserva*> elementoAInsertar= pair<int, Reserva*>(codigoR, reserva);
    this->reservas.insert(elementoAInsertar);
};

int ControladorReserva :: getCantidadReservas(){
    return this->cantidadReservas;
}