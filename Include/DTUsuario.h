#ifndef _DTUSUARIO_
#define _DTUSUARIO_

#include<iostream>
#include "./Const.h"

using namespace std;

class DTUsuario{
    private:
        string email;
        string nombre;
        string contrasenia;
    public:
        DTUsuario(string email, string  nombre, string contrasenia);
        string getNombre();
        string getEmail();
        string getContrasenia();
        virtual ~DTUsuario();

        virtual void print(std::ostream& out)= 0;
        friend std::ostream& operator<<(std::ostream &out,DTUsuario &usuario);
};


#endif