// Dependencias
#include "../../Include/Empleado.h"

using namespace std;

Empleado::Empleado(string nombre,string email,string contrasenia, TipoCargo cargo): Usuario(nombre, email, contrasenia){
    this->cargo = cargo;
    this->suscrito = false;
    set<DTCalificacionNotificada*> calificacionesPendientes;
    this->calificacionesPendientes = calificacionesPendientes;
    this->hostal = NULL;
};

Empleado::Empleado(DTEmpleado* dataEmpleado): Usuario(dataEmpleado->getNombre(), dataEmpleado->getEmail(), dataEmpleado->getContrasenia()){
    this->cargo = dataEmpleado->getCargo();
    this->suscrito = false;
    set<DTCalificacionNotificada*> calificacionesPendientes;
    this->calificacionesPendientes = calificacionesPendientes;
    this->hostal = NULL;
};

Empleado::~Empleado(){
    this->borrarNotificacionesPendientes();
};

void Empleado::setCargo(TipoCargo cargo){
    this-> cargo = cargo;
};

void Empleado::setSuscrito(bool suscrito){
    this->suscrito = suscrito;
};

void Empleado::setHostalAsignadoYCargo(Hostal* hostal, TipoCargo cargoE){
    this->hostal = hostal;
    this->cargo  = cargoE;
};

TipoCargo Empleado::getCargo(){
    return this->cargo;
};

bool Empleado::getSuscrito(){
    return this->suscrito;
};

set<DTCalificacionNotificada*> Empleado::getNotificacionesPendientes(){
    return this->calificacionesPendientes;
};

void Empleado::subscribirEmpleadoANotificaciones(){
    CalificacionObserver* sCO = CalificacionObserver::getInstancia();
    sCO->agregarObserver(this);
    this->setSuscrito(true);
};

void Empleado::desuscribirEmpleadoANotificaciones(){
    CalificacionObserver* sCO = CalificacionObserver::getInstancia();
    sCO->eliminarObserver(this);
    this->setSuscrito(false);
};

void Empleado::borrarNotificacionesPendientes(){
    while (!this->calificacionesPendientes.empty()) {
        set<DTCalificacionNotificada*>::iterator iter = this->calificacionesPendientes.begin();
        DTCalificacionNotificada* borrar = *iter;
        this->calificacionesPendientes.erase(iter);
        delete borrar;
    }
    this->calificacionesPendientes.clear();
};

string Empleado::getNombreHostal(){
    if(this->hostal != NULL){
        return this->hostal->getNombre();
    }
    return "Desempleado";
};

bool Empleado::esEmpleado() {
    return true;
};

bool Empleado::esEmpleadoSinAsignar() {
    return this->hostal == NULL;
};

bool Empleado::esHuesped() {
    return false;
};

Usuario* Empleado::seleccionarHuesped(){
    return NULL;
}

void Empleado::notificar(DTCalificacionNotificada* calificacion){
    DTCalificacionNotificada * agregar = new DTCalificacionNotificada(calificacion->getAutor(), calificacion->getComentario(), calificacion->getPuntaje());
    this->calificacionesPendientes.insert(agregar);
};
