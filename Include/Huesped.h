#ifndef _HUESPED_
#define _HUESPED_

#include "./Usuario.h"
#include "./DTHuesped.h"
#include <string>
#include <iostream>

using namespace std;

class Huesped : public Usuario{
    private:
        bool esFinger;

    public:

        Huesped(std::string email, std::string nombre, std::string contrasenia, bool esFinger);
        Huesped(DTHuesped* dataHuesped);


        void setEsFinger(bool esFinger);

        bool getEsFinger();

        bool esEmailDeHuesped(std::string email);

        bool esEmpleado();
        bool esEmpleadoSinAsignar();
        bool esHuesped();
        Usuario* seleccionarHuesped();
        
        ~Huesped();
};




#endif