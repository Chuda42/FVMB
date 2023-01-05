#include "../../Include/ControladorHostal.h"

using namespace std;

ControladorHostal* ControladorHostal::instancia = NULL;


ControladorHostal::ControladorHostal(){
    this->cacheDatosHabitacion = NULL;
    this->cacheDatosReserva = NULL;
    this->cacheTitularSeleccionado = NULL;
    //set<int> codigoCache;
    //this->cacheCodigo = codigoCache;
    set<string> cacheHuspedesSeleccionados;
    this->cacheHuespedesSeleccionados = cacheHuspedesSeleccionados;
    map<string, Hostal*> hostales;
    this->hostales = hostales;
};

ControladorHostal* ControladorHostal::getInstancia(){
    if(ControladorHostal::instancia == NULL){
        ControladorHostal::instancia = new ControladorHostal();
    }
    return ControladorHostal::instancia;
};

ControladorHostal::~ControladorHostal(){
    this->releaseData();

    map<string, Hostal*>::iterator iter;
    Hostal* borrar;

    for(iter = this->hostales.begin(); iter != this->hostales.end(); iter++){
        borrar = iter->second;
        delete borrar;
    }
    this->hostales.clear();
    ControladorHostal::instancia = NULL;
};

//funciones de la interfaz ihostal
void ControladorHostal::agregarHostal(string nombre,string direccion, string telefono){
    map<string, Hostal*>::iterator iter;
    iter = this->hostales.find(nombre);
    if(iter == this->hostales.end()){
        Hostal* nuevoHostal = new Hostal(nombre,direccion,telefono);
        pair<string, Hostal*> nuevoElem = pair<string, Hostal*> (nombre, nuevoHostal);
        this->hostales.insert(nuevoElem);
    }else{
        throw std::invalid_argument("Ya existe un hostal registrado con ese nombre");
    }  
};

set<string> ControladorHostal::getHostales(){
    set<string> resultado;
    string agregar;
    map<string, Hostal*>::iterator iter;

    for (iter = this->hostales.begin(); iter != this->hostales.end(); ++iter){
        agregar = iter->first;
        resultado.insert(agregar);
    }
    return resultado;
};

void ControladorHostal::nuevaHabitacion(int numero,float precio, int capacidad){
    this->setDatosHabitacion(numero, precio, capacidad);
};

void ControladorHostal::confirmarRegistroHabitacion(string nombreHostal){
    //obtengo datos de la habitacion en el cache
    DTHabitacion * dataHabit = this->getDatosHabitacion();
    //busco el hostal si esta registrado
    map<string, Hostal*>::iterator iter;
    Hostal* host;
    iter = this->hostales.find(nombreHostal);
    if(iter != this->hostales.end()){
        host = iter->second;
        host->agregarHabitacion(dataHabit);
    }else{
        throw std::invalid_argument("No existe un hostal registrado con ese nombre");
    }
    DTHabitacion * borrar = this->cacheDatosHabitacion;
    this->cacheDatosHabitacion = NULL;
    delete borrar;
};

void ControladorHostal::cancelarRegistroHabitacion(){
    DTHabitacion * borrar = this->cacheDatosHabitacion;
    this->cacheDatosHabitacion = NULL;
    delete borrar;
};

set<DTHostal*> ControladorHostal::getHostalesConCalificacion(){
    set<DTHostal*> resultado;
    DTHostal * agregar;

    map<string, Hostal*>::iterator iter;
    Hostal* host;

    for(iter = this->hostales.begin(); iter != this->hostales.end(); ++iter){
        host = iter->second;
        agregar = host->getDataHostal();
        resultado.insert(agregar);
    }
    return resultado;
};

void ControladorHostal::setDatosReserva(DTFecha& checkIn, DTFecha& checkOut, bool esGrupal){
    this->setDatosNuevaReserva(checkIn, checkOut, esGrupal);
};

set<DTHabitacion*> ControladorHostal::getHabitacionesDisponibles( string nombreHostal){
    set<DTHabitacion*> resultado;
    //Busco el hostal
    map<string, Hostal*>::iterator iter;
    iter = this->hostales.find(nombreHostal);
    Hostal* host = iter->second;
    //obtengo habitaciones no disponibles
    DTDatosNuevaReserva * dNR = this->getDatosNuevaReserva();
    ControladorReserva * cR = ControladorReserva::getInstancia();
    set<int> habitNDis = cR->getHabitacionesNoDisponibles(nombreHostal, dNR);
    //obtengo las habitaciones disponibles
    resultado = host->getHabitacionesDisponibles(habitNDis);
    return resultado;
};

void ControladorHostal::seleccionarHuesped(string email){
    this->addHuespedSeleccionado(email);
};

void ControladorHostal::confirmarReserva(string nombreHostal, int numeroHabitacion){
    set<string> hSel = this->getHuespedesSeleccionados();
    DTDatosNuevaReserva* dNR = this->getDatosNuevaReserva(); 

    map<string, Hostal*>::iterator iter;
    Hostal* hostal = this->hostales.find(nombreHostal)->second;
    Habitacion* habitacion = hostal->getInstanciaHabitacion(numeroHabitacion);

    ControladorReserva* cR = ControladorReserva::getInstancia();
    cR->crearReserva(dNR,*this->cacheTitularSeleccionado, hSel, hostal, habitacion);
    this->releaseData();
};

void ControladorHostal::cancelarReserva(){
    this->releaseData();
};

map<int, string> ControladorHostal::getTop3Hostales(){
    map<int, string> resultado;
    map<string, Hostal*>::iterator iterHostales;
    pair<string, float> puntajes [3];
    puntajes[0] = pair<string, float>("", 0);
    puntajes[1] = pair<string, float>("", 0);
    puntajes[2] = pair<string, float>("", 0);

    for(iterHostales = this->hostales.begin(); iterHostales != this->hostales.end(); ++iterHostales){
        DTHostal* dTH = iterHostales->second->getDataHostal();

        for (int i = 0; i < 3; i++) {
            pair<string, float> nuevo = pair<string, float>(dTH->getNombre(), dTH->getCalificacionPromedio());
            
            if (puntajes[i].first.empty()) { // Ingresar por primera vez.
                puntajes[i] = nuevo;
                break;
            }
            else if (puntajes[i].second < dTH->getCalificacionPromedio()) { // Correr arreglo.
                for (int x = i; x < 3; x++) {
                    pair<string, float> temp = puntajes[x];
                    puntajes[x] = nuevo;
                    nuevo = temp;
                }
                break;
            }
        }
        delete dTH;
    }

    for (int i = 0; i < 3; i++)
    {
        resultado.insert(pair<int, string> (i, puntajes[i].first));
    }
    
    return resultado;
};

set<DTHabitacion*> ControladorHostal::getHabitaciones(string nombreH){
    map<string, Hostal*>::iterator iter = this->hostales.find(nombreH);
    Hostal* hostal = iter->second;
    return hostal->getHabitaciones();
}

DTHostal* ControladorHostal::getInfoBasicaHostal(string nombreH){  
    map<string, Hostal*>::iterator iter = this->hostales.find(nombreH);
    float prom = iter->second->getPromedio();
    DTHostal* dTH = new DTHostal(nombreH,iter->second->getDireccion(),iter->second->getTelefono(),prom);
    return dTH;
}

map<pair<int,string>, DTEstadia*> ControladorHostal::getEstadias(string nombreH){
    map<string,Hostal*>::iterator iter = this->hostales.find(nombreH);
    return iter->second->getEstadias();
}


//set<DTEstadia>* ControladorHostal::getEstadiasFinalizadas(string emailH, string nombreHostal){}



//funciones del controlador
//void ControladorHostal::addCodigo(int codigo){}
void ControladorHostal::addHuespedSeleccionado(string email){
    if(this->cacheTitularSeleccionado == NULL){
        this->cacheTitularSeleccionado = new string(email);
    }else{
         this->cacheHuespedesSeleccionados.insert(email);
    }
};

void ControladorHostal::setDatosHabitacion(int numero, float precio, int capacidad){
    DTHabitacion * habit = new DTHabitacion(numero, precio, capacidad);
    this->cacheDatosHabitacion = habit;
};

DTHabitacion* ControladorHostal::getDatosHabitacion(){
    return this->cacheDatosHabitacion;
};

void ControladorHostal::setDatosNuevaReserva(DTFecha& checkIn, DTFecha& checkOut, bool esGrupal){
    DTDatosNuevaReserva * dataNR = new DTDatosNuevaReserva(checkIn, checkOut, esGrupal);
    this->cacheDatosReserva = dataNR;
};

Hostal* ControladorHostal::getInstanciaHostal(string nombre){
   map<string, Hostal*>::iterator iter = this->hostales.find(nombre);
   if(iter == this->hostales.end()){
        throw std::invalid_argument("No hay un Hostal registrado con ese nombre.");
   }
   return iter->second;
};

DTDatosNuevaReserva* ControladorHostal::getDatosNuevaReserva(){
    return this->cacheDatosReserva;
};

set<string> ControladorHostal::getHuespedesSeleccionados(){
    return this->cacheHuespedesSeleccionados;
};

void ControladorHostal::releaseData(){
    DTHabitacion* borrar1 = this->cacheDatosHabitacion; 
    DTDatosNuevaReserva* borrar2 = this->cacheDatosReserva;
    set<string> clear3 = this->cacheHuespedesSeleccionados;
    string* borrar4 = this->cacheTitularSeleccionado;
    this->cacheDatosHabitacion = NULL;
    this->cacheDatosReserva = NULL;
    this->cacheTitularSeleccionado = NULL;
    delete borrar1;
    delete borrar2;
    clear3.clear();
    delete borrar4;
};