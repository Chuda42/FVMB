#include "../../Include/ControladorFechaSistema.h"

ControladorFechaSistema* ControladorFechaSistema :: instancia = NULL;

ControladorFechaSistema :: ControladorFechaSistema(){
    fechaSistema = DTFecha(2022, 6, 22, 18);
}

ControladorFechaSistema* ControladorFechaSistema :: getInstancia(){
    if (ControladorFechaSistema::instancia == NULL){
        ControladorFechaSistema::instancia = new ControladorFechaSistema();
    }
    return ControladorFechaSistema::instancia;
}

DTFecha& ControladorFechaSistema :: getFechaSistema(){
    return this->fechaSistema;
}


void ControladorFechaSistema :: setFechaSistema(int anio, int mes, int dia, int hora){
    this->fechaSistema = DTFecha(anio, mes, dia, hora);
}

ControladorFechaSistema :: ~ControladorFechaSistema(){
    ControladorFechaSistema::instancia = NULL;
}