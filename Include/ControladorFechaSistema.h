#ifndef _CONTROLADORFECHASISTEMA_
#define _CONTROLADORFECHASISTEMA_

//DEPENDENCIAS
//librerias estandar
#include<iostream>
#include<set>
#include<map>
//interface que implementa
#include "./IFechaSistema.h"
//dependencias de clases
#include "./DTFecha.h"


using namespace std;

class ControladorFechaSistema : public IFechaSistema{
    private:
        DTFecha fechaSistema;
        //por ser singleton
        static ControladorFechaSistema* instancia;
        ControladorFechaSistema();

    public:
        //sacar la instancia
        static ControladorFechaSistema* getInstancia();

        DTFecha& getFechaSistema();

        void setFechaSistema(int anio, int mes, int dia, int hora);
        virtual ~ControladorFechaSistema();
};



#endif
