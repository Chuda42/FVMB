#ifndef _CONTROLADORUSUARIO_
#define _CONTROLADORUSUARIO_

//DEPENDENCIAS
//librerias estandar
#include<iostream>
#include<set>
#include<map>
//interface que implementa
#include"./IUsuario.h"
//dependencias de calses
#include "./Empleado.h"
#include "./Huesped.h"
//dependencias de datatypes
#include "./DTUsuario.h"
#include "./DTEmpleado.h"
#include "./DTHuesped.h"
#include "./ControladorHostal.h"



using namespace std;
class ControladorUsuario: public IUsuario{
    private:
        //por ser singleton
        static ControladorUsuario* instancia;
        ControladorUsuario();

        //Cache
        DTUsuario* dataUsuario;
        //colecciones que maneja
        map<string, Usuario*> usuarios;

        // // funciones del controlador
        DTUsuario* getDataNuevoUsuario();
        void setDataNuevoEmpleado(string nombreE, string emailE, string contraseniaE, TipoCargo cargoE);
        void setDataNuevoHuesped(string nombreH, string emailH, string contraseniaH, bool esFingerH);
        void setDataNuevoEmail(DTUsuario* dataUsuario, string emailN);
        bool esDTEmpleado(DTUsuario* dataUsuario);
        void releaseData();
        
        

    public:

        //sacar la instancia
        static ControladorUsuario* getInstancia();

        // funciones de la interfaz
        void nuevoEmpleado(string nombreE, string emailE, string contraseniaE , TipoCargo cargoE);
        void nuevoHuesped(string nombreH, string emailH, string contraseniaH, bool esFingerH);
        void setNuevoEmail(string emailN);
        void confirmarRegistroUsuario();
        void cancelarRegistroUsuario();
        set<string> getEmpleadosDisponibles(); 
        void asignarEmpleadoAHostal(string emailE, string nombreH, TipoCargo cargoE);
        set<string> getHuespedes();
        set<string> getUsuarios();
        DTUsuario* getUsuarioDetalle(string emailU);
        void subscribirEmpleadoANotificaciones(string email);
        set<string> getEmpleados();
        void desubscribirEmpleadoANotificaciones(string email);
        set<DTCalificacionNotificada*> getNotificacionesPendientes(string email);
        void borrarNotificacionesPendientes(string email);
        virtual ~ControladorUsuario();


        string getNombreHostalDeEmpleado(string emailE);
        set<Huesped*> getInstanciasHuespedes(set<string> hSelc);
        Huesped* getInstanciaHuesped(string email);
        
};

#endif