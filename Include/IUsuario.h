#ifndef _IUSUARIO_
#define _IUSUARIO_

#include<iostream>
#include<set>

#include "./Const.h"
#include "./DTUsuario.h"
#include "./DTCalificacionNotificada.h"

using namespace std;

class IUsuario{
    public:
        virtual void nuevoEmpleado(string nombreE, string emailE, string contraseniaE , TipoCargo cargoE) = 0;
        virtual void nuevoHuesped(string nombreH, string emailH, string contraseniaH, bool esFingerH) = 0;
        virtual void setNuevoEmail(string emailN) = 0;
        virtual void confirmarRegistroUsuario() = 0;
        virtual void cancelarRegistroUsuario() = 0;
        virtual set<string> getEmpleadosDisponibles() = 0; 
        virtual void asignarEmpleadoAHostal(string emailE, string nombreH, TipoCargo cargoE) = 0;
        virtual set<string> getHuespedes() = 0;
        virtual set<string> getUsuarios() = 0;
        virtual DTUsuario* getUsuarioDetalle(string emailU) = 0;
        virtual void subscribirEmpleadoANotificaciones(string email) = 0;
        virtual set<string> getEmpleados() = 0;
        virtual void desubscribirEmpleadoANotificaciones(string email) = 0;
        virtual set<DTCalificacionNotificada*> getNotificacionesPendientes(string email) = 0;
        virtual void borrarNotificacionesPendientes(string email) = 0;
        //virtual ~IUsuario();
};


#endif