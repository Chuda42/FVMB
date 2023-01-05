#ifndef _EMPLEADO_
#define _EMPLEADO_

#include "./Usuario.h"
#include "./Hostal.h"
//#include "./DTCalificacionNotificada.h"
#include "./Const.h"
#include "./CalificacionObserver.h"
#include "./ICalificacionObserver.h"
#include "./DTEmpleado.h"

class Hostal;

using namespace std;

class Empleado : public Usuario,  ICalificacionObserver {
    private:
        TipoCargo cargo;
        bool suscrito;
        set<DTCalificacionNotificada *> calificacionesPendientes;
        Hostal* hostal;
        void setSuscrito(bool suscrito);
        
    public:
        
        Empleado(string nombre,string email,string contrasenia, TipoCargo cargo);
        Empleado(DTEmpleado* dataEmpleado);
        ~Empleado();

        void setCargo(TipoCargo cargo);
        void setHostalAsignadoYCargo(Hostal* hostal ,TipoCargo cargoE);

        TipoCargo getCargo();
        bool getSuscrito();
        set<DTCalificacionNotificada*> getNotificacionesPendientes();

        void subscribirEmpleadoANotificaciones();
        void desuscribirEmpleadoANotificaciones();
        void borrarNotificacionesPendientes();
        string getNombreHostal();

        bool esEmpleado();
        bool esEmpleadoSinAsignar();
        bool esHuesped();
        Usuario* seleccionarHuesped(); 

        // Metodo de ICalificacionObserver.
        void notificar(DTCalificacionNotificada* calificacion);
        
};


#endif