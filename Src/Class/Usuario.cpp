// Dependencias
#include "../../Include/Usuario.h"

using namespace std;

Usuario::Usuario(string nombre, string email, string contrasenia){
    this->nombre = nombre;
    this->email = email;
    this->contrasenia = contrasenia;
};

void Usuario::setNombre(string nombre){
    this->nombre = nombre;
};

void Usuario::setEmail(string email){
    this->email = email;
};

void Usuario::setContrasenia(string contrasenia){
    this->contrasenia = contrasenia;
};

string Usuario::getNombre(){
    return this->nombre;
};

string Usuario::getEmail(){
    return this->email;
};

string Usuario::getContrasenia(){
    return this->contrasenia;
};

bool Usuario::estaUsuarioEn(set<string> hSelc){
    string email = this->email;
    set<string>::iterator emailEncontrado = hSelc.find(email);
    return emailEncontrado != hSelc.end();
};



Usuario::~Usuario(){

};