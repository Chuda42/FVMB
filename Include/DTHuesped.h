#ifndef  _DTHUESPED_
#define _DTHUESPED_

#include "./DTUsuario.h"

class DTHuesped : public DTUsuario{
    private:
        bool esFinger;

    public:
        DTHuesped(string email, string nombre, string contrasenia, bool esFinger);
        bool getEsFinger();
        ~DTHuesped();

        virtual void print(std::ostream& out);
};


#endif