#include "../../Include/DTHuesped.h"

DTHuesped::DTHuesped(string email, string nombre, string contrasenia, bool esFinger):DTUsuario(email,nombre,contrasenia){
    this->esFinger = esFinger;
}

bool DTHuesped::getEsFinger(){
    return this->esFinger;
}

DTHuesped::~DTHuesped(){}

void DTHuesped :: print(std::ostream& out){
    string esDeLaFing;
    if(this->esFinger){
        esDeLaFing = "Es Finger";
    }else{
        esDeLaFing = "No es Finger";
    }
    cout<<endl;
    out<<"Nombre: "<< this->getNombre() <<endl
        <<"Email: "<< this->getEmail() <<endl
        <<"Es Finger: "<< esDeLaFing <<endl;
};