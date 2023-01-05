#ifndef _FACTORY_
#define _FACTORY_

//Intefaces
#include "./IReserva.h"
#include "./IHostal.h"
#include "./IUsuario.h"
#include "./IFechaSistema.h"

//Controladores
#include "./ControladorReserva.h"
#include "./ControladorHostal.h"
#include "./ControladorUsuario.h"
#include "./ControladorFechaSistema.h"
#include "./CalificacionObserver.h"

class Factory{
    private:
        //sigleton
        static Factory* instancia;
        Factory();
    public:
        static Factory* getInstancia();

        IUsuario* getIUsuario();
        IHostal* getIHostal();
        IReserva* getIReserva();
        IFechaSistema* getIFechaSistema();
        ~Factory();
};

#endif