#include "../../Include/Factory.h"

Factory * Factory::instancia = NULL;

Factory::Factory(){}

Factory * Factory::getInstancia(){
    if(Factory::instancia == NULL){
        Factory::instancia = new Factory();
    }
    return Factory::instancia;
}

IUsuario* Factory::getIUsuario(){
    return ControladorUsuario::getInstancia();
};

IHostal* Factory::getIHostal(){
    return ControladorHostal::getInstancia(); 
};

IReserva* Factory::getIReserva(){
    return ControladorReserva::getInstancia(); 
};

IFechaSistema* Factory::getIFechaSistema(){
    return ControladorFechaSistema::getInstancia(); 
};


Factory::~Factory(){
    ControladorFechaSistema * cF = ControladorFechaSistema::getInstancia();
    ControladorUsuario * cU = ControladorUsuario::getInstancia();
    ControladorHostal * cH = ControladorHostal::getInstancia();
    ControladorReserva * cR = ControladorReserva::getInstancia();
    CalificacionObserver * cO = CalificacionObserver::getInstancia();


    delete cF;
    delete cU;
    delete cH;
    delete cR;
    delete cO;
    Factory::instancia = NULL;
};
