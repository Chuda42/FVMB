#include "../../Include/DTUsuario.h"

DTUsuario::DTUsuario(string email, string  nombre, string contrasenia){
    this->email = email;
    this->nombre = nombre;
    this->contrasenia = contrasenia;
}

string DTUsuario::getNombre(){
    return this->nombre;
}

string DTUsuario::getEmail(){
    return this->email;
}

string DTUsuario::getContrasenia(){
    return this->contrasenia;
}

DTUsuario::~DTUsuario(){};

ostream &operator<<(std::ostream &out,DTUsuario &usuario){
   usuario.print(out);
   return out;
};