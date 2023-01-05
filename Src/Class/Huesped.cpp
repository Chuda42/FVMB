#include "../../Include/Huesped.h"

Huesped::Huesped(std::string email, std::string nombre, std::string contrasenia, bool esFinger):Usuario(nombre, email, contrasenia){
  this->esFinger = esFinger;  
}

Huesped::Huesped(DTHuesped* dataHuesped): Usuario(dataHuesped->getNombre(), dataHuesped->getEmail(), dataHuesped->getContrasenia()){
    this->esFinger = dataHuesped->getEsFinger();
}

void Huesped::setEsFinger(bool esFinger){
    this->esFinger = esFinger;
}

bool Huesped::getEsFinger(){
    return this->esFinger;
}

bool Huesped::esEmailDeHuesped(std::string email){
    return this->getEmail() == email;
}

bool Huesped::esEmpleado(){
    return false;
};

bool Huesped::esEmpleadoSinAsignar(){
    return false;
};

bool Huesped::esHuesped(){
    return true;
};

Usuario* Huesped::seleccionarHuesped(){
    return NULL; // Por implementar.
};

Huesped::~Huesped(){}