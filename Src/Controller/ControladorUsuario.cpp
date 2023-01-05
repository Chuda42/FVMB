#include "../../Include/ControladorUsuario.h"

using namespace std;

ControladorUsuario * ControladorUsuario::instancia = NULL;

ControladorUsuario::ControladorUsuario(){
    map<string, Usuario*> usuarios;
    this->usuarios = usuarios;
    this->dataUsuario = NULL;
}

ControladorUsuario* ControladorUsuario::getInstancia(){
    if (ControladorUsuario::instancia == NULL){
        ControladorUsuario::instancia = new ControladorUsuario();
    }
    return ControladorUsuario::instancia;
}

/* Funciones de la interfaz */
void ControladorUsuario::nuevoEmpleado(string nombreE, string emailE, string contraseniaE , TipoCargo cargoE){
    map<string, Usuario*>::iterator iter;
    iter  = this->usuarios.find(emailE);
    this->setDataNuevoEmpleado(nombreE, emailE, contraseniaE, cargoE);
    if(iter != this->usuarios.end()){
        throw std::invalid_argument("Ya existe un usuario con ese email indica lo que desea hacer: ");
    } 
};

void ControladorUsuario::nuevoHuesped(string nombreH, string emailH, string contraseniaH, bool esFingerH){
    map<string, Usuario*>::iterator iter;
    iter  = this->usuarios.find(emailH);
    this->setDataNuevoHuesped(nombreH, emailH, contraseniaH, esFingerH);
    if(iter != this->usuarios.end()){
         throw std::invalid_argument("Ya existe un usuario con ese email indica lo que desea hacer: ");      
    }   
};

void ControladorUsuario::setNuevoEmail(string emailN){
    map<string, Usuario*>::iterator iter;
    iter  = this->usuarios.find(emailN);
    if(iter == this->usuarios.end()){
        DTUsuario * dataAnterior = this->getDataNuevoUsuario();
        this->setDataNuevoEmail(dataAnterior, emailN);
        delete dataAnterior;        
    }else{
        throw std::invalid_argument("Ya existe un usuario con ese email indica lo que desea hacer: ");
    }
    
};

void ControladorUsuario::confirmarRegistroUsuario(){
    DTUsuario * dataUsuario = this->getDataNuevoUsuario();
    bool esEmpleado = this->esDTEmpleado(dataUsuario);
    Usuario* nuevo;
    if(esEmpleado){
        DTEmpleado *dataEmpleado = dynamic_cast<DTEmpleado*>(dataUsuario);
        nuevo = new Empleado(dataEmpleado);
    }else{
        DTHuesped *dataHuesped = dynamic_cast<DTHuesped*>(dataUsuario);
        nuevo = new Huesped(dataHuesped);
    }
    
    pair<string, Usuario*> elementoAInsertar= pair<string, Usuario*>(dataUsuario->getEmail(), nuevo);
    this->usuarios.insert(elementoAInsertar);
    
    releaseData();
};

void ControladorUsuario::cancelarRegistroUsuario(){
    releaseData();
};

set<string> ControladorUsuario::getEmpleadosDisponibles(){
    set<string> resultado;
    map<string, Usuario*>::iterator iter;
    
    for (iter = this->usuarios.begin(); iter != this->usuarios.end(); ++iter){

        if(iter->second->esEmpleadoSinAsignar()){
            resultado.insert(iter->first);
        }
    }
    return resultado;
};


void ControladorUsuario::asignarEmpleadoAHostal(string emailE, string nombreH, TipoCargo cargoE){
    ControladorHostal* cH = ControladorHostal::getInstancia();
    Hostal* hostalAAsignar = cH->getInstanciaHostal(nombreH);
    map<string,Usuario*>::iterator it = this->usuarios.find(emailE);
    if(it != this->usuarios.end()){
        Empleado* empleadoDisponible = dynamic_cast<Empleado*> (it->second);
        empleadoDisponible->setHostalAsignadoYCargo(hostalAAsignar, cargoE); 
    }else{
        throw std::invalid_argument("No hay un empleado registrado con ese email.");
    }   
};

set<string> ControladorUsuario::getHuespedes(){
    set<string> emailHuespedes;
    for (std::map<string,Usuario*>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it){
    	if(it->second->esHuesped()){
		    emailHuespedes.insert(it->second->getEmail());
        }
	}
    return emailHuespedes;
};

set<string> ControladorUsuario::getUsuarios(){
    set<string> usuarios;
    map<string, Usuario*>::iterator iter;
    for (iter = this->usuarios.begin(); iter != this->usuarios.end(); ++iter){
            usuarios.insert(iter->first);
    }
    return usuarios;
};

DTUsuario* ControladorUsuario::getUsuarioDetalle(string emailU){
    map<string, Usuario*>::iterator iter;
    iter = this->usuarios.find(emailU);
    if(iter != this->usuarios.end()){
        string email = iter->first;
        string nombre = iter->second->getNombre();
        if(iter->second->esEmpleado()){
            Empleado* empleado = dynamic_cast<Empleado*>(iter->second);
            TipoCargo cargo = empleado->getCargo();
            string nombreHostal = empleado->getNombreHostal();
            DTUsuario* dtEmpleado = new DTEmpleado(email, nombre, "no usar", cargo, nombreHostal);
            return dtEmpleado;
        }else{
            Huesped* huesped = dynamic_cast<Huesped*>(iter->second);
            bool esFinger = huesped->getEsFinger();
            DTUsuario* dtHuesped = new DTHuesped(email, nombre, "no usar", esFinger);
            return dtHuesped;
        }
    }else{
        throw std::invalid_argument("El email ingresado no es el email de un Usuario valido");
    }
};

void ControladorUsuario::subscribirEmpleadoANotificaciones(string email){
    map<string, Usuario*>::iterator iter;
    iter = this->usuarios.find(email);
    if(iter != this->usuarios.end() && iter->second->esEmpleado()){
        Empleado* emp = dynamic_cast<Empleado*>(iter->second);
        if(!emp->getSuscrito()){
            emp->subscribirEmpleadoANotificaciones();
        }else{
            throw std::invalid_argument("El Empleado ya estaba suscrito");
        }
    }else{
        throw std::invalid_argument("El email ingresado no es el email de un Empleado valido");
    }
};

set<string> ControladorUsuario::getEmpleados(){
    set<string> emailEmpleados;
    for (std::map<string,Usuario*>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it){
    	if(it->second->esEmpleado()){
		    emailEmpleados.insert(it->second->getEmail());
        }
	}
    return emailEmpleados;
};

void ControladorUsuario::desubscribirEmpleadoANotificaciones(string email){
    map<string, Usuario*>::iterator iter;
    iter = this->usuarios.find(email);
    if(iter != this->usuarios.end() && iter->second->esEmpleado()){
        Empleado* emp = dynamic_cast<Empleado*>(iter->second);
        if(emp->getSuscrito()){
         emp->desuscribirEmpleadoANotificaciones();   
        }else{
            throw std::invalid_argument("El Empleado no estaba suscrito");
        }
    }else{
        throw std::invalid_argument("El email ingresado no es el email de un Empleado valido");
    }
};

set<DTCalificacionNotificada*> ControladorUsuario::getNotificacionesPendientes(string email){ 
    map<string, Usuario*>::iterator iter;
    iter = this->usuarios.find(email);
    if(iter != this->usuarios.end() && iter->second->esEmpleado()) {
        Empleado* emp = dynamic_cast<Empleado*>(iter->second);
        return emp->getNotificacionesPendientes();
    }else{
        throw std::invalid_argument("El email ingresado no es el email de un Empleado valido");
    }
};

void ControladorUsuario::borrarNotificacionesPendientes(string email) {
    map<string, Usuario*>::iterator iter = this->usuarios.find(email);
    if(iter != this->usuarios.end() && iter->second->esEmpleado()) {
        Empleado* emp = dynamic_cast<Empleado*>(iter->second);
        
        emp->borrarNotificacionesPendientes();
    }
}

// /* Funciones del controlador */
void ControladorUsuario::setDataNuevoEmpleado(string nombreE, string emailE, string contraseniaE, TipoCargo cargoE){
    DTEmpleado* empleado = new DTEmpleado(emailE, nombreE, contraseniaE, cargoE, "no usar");
    this->dataUsuario = empleado;
};

void ControladorUsuario::setDataNuevoHuesped(string nombreH, string emailH, string contraseniaH, bool esFingerH){
    DTHuesped* huesped = new DTHuesped(emailH, nombreH, contraseniaH, esFingerH);
    this->dataUsuario = huesped;
};

DTUsuario* ControladorUsuario::getDataNuevoUsuario(){
    return this->dataUsuario;
};

bool ControladorUsuario::esDTEmpleado(DTUsuario* dataUsuario){
    DTUsuario * auxiliar = dynamic_cast<DTEmpleado*>(dataUsuario);
    return auxiliar != NULL;
};

void ControladorUsuario::setDataNuevoEmail(DTUsuario* dataUsuario, string emailN){
    DTEmpleado * dataEmpleado = dynamic_cast<DTEmpleado*>(dataUsuario);
    if(dataEmpleado == NULL){
        DTHuesped * dataHuesped = dynamic_cast<DTHuesped*>(dataUsuario);
        setDataNuevoHuesped(dataHuesped->getNombre(), emailN, dataHuesped->getContrasenia(), dataHuesped->getEsFinger());
    }else{
        setDataNuevoEmpleado(dataEmpleado->getNombre(), emailN, dataEmpleado->getContrasenia(), dataEmpleado->getCargo());
    }
};
void ControladorUsuario::releaseData(){
    DTUsuario * borrar = this->dataUsuario;
    this->dataUsuario = NULL;
    delete borrar;
};
string ControladorUsuario::getNombreHostalDeEmpleado(string emailE){
    map<string, Usuario*>::iterator iter = this->usuarios.find(emailE);

    if (iter == this->usuarios.end())
    {
        throw invalid_argument("No existe un Empleado con email: " + emailE);
    }
    else if (!iter->second->esEmpleado())
    {
        throw invalid_argument("El usuario con email: " + emailE + " es un Huesped");
    }

    return dynamic_cast<Empleado*>(iter->second)->getNombreHostal();
};
set<Huesped*> ControladorUsuario::getInstanciasHuespedes(set<string> hSelc){
    set<Huesped*> resultado;
    map<string, Usuario*>::iterator iter;
    Usuario* usuario;

    for(iter = this->usuarios.begin(); iter != this->usuarios.end(); ++iter){
        usuario = iter->second;
        bool esHuespedYContenido = usuario->esHuesped() &&  usuario->estaUsuarioEn(hSelc);
        if (esHuespedYContenido){
            resultado.insert(dynamic_cast<Huesped*>(usuario));
        }   
    }
    return resultado;
};

Huesped* ControladorUsuario::getInstanciaHuesped(string email){
    map<string, Usuario*>::iterator iter = this->usuarios.find(email);
    return dynamic_cast<Huesped*>(iter->second);
};

ControladorUsuario::~ControladorUsuario(){
    map<string, Usuario*>::iterator iter;
    Usuario* borrar;

    this->releaseData();
    for(iter = this->usuarios.begin(); iter != this->usuarios.end(); iter++){
        borrar = iter->second;
        delete borrar;
    }
    this->usuarios.clear();
    ControladorUsuario::instancia = NULL;
};


