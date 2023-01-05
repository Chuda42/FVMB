#ifndef  _DTEMPLEADO_
#define _DTEMPLEADO_

#include "./DTUsuario.h"

class DTEmpleado : public DTUsuario{
    private:
        TipoCargo cargo;
        string nombreHostal;
    public:
        DTEmpleado(string email, string nombre, string contrasenia, TipoCargo cargo, string nombreHostal);
        TipoCargo getCargo();
        string getNombreHostal();
        ~DTEmpleado();

        virtual void print(std::ostream& out);
};


#endif