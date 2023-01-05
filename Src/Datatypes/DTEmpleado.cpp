#include "../../Include/DTEmpleado.h"

DTEmpleado::DTEmpleado(string email, string nombre, string contrasenia, TipoCargo cargo, string nombreHostal):DTUsuario(email,nombre,contrasenia){
    this->cargo =cargo;
    this->nombreHostal = nombreHostal;
}

TipoCargo DTEmpleado::getCargo(){
    return this->cargo;
}

string DTEmpleado::getNombreHostal(){
    return this->nombreHostal;
}

DTEmpleado::~DTEmpleado(){}

void DTEmpleado :: print(std::ostream& out){
    cout<<endl;
    out<<"Nombre: "<< this->getNombre() <<endl
        <<"Email: "<< this->getEmail() <<endl
        <<"Cargo: "<< this->cargo <<endl
        <<"Hostal donde trabaja: "<< this->nombreHostal <<endl;
};