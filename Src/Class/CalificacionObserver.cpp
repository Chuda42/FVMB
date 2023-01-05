#include "../../Include/CalificacionObserver.h"

CalificacionObserver * CalificacionObserver :: instancia = NULL;

CalificacionObserver :: CalificacionObserver(){
    set<ICalificacionObserver *> observers;
    this->observers = observers;
}

CalificacionObserver* CalificacionObserver :: getInstancia(){
    if(instancia == NULL){
        instancia = new CalificacionObserver();
    }
    return instancia;
}

void CalificacionObserver :: agregarObserver(ICalificacionObserver* observer){
    this->observers.insert(observer);
}

void CalificacionObserver :: eliminarObserver(ICalificacionObserver* observer){
    this->observers.erase(observer);
}

void CalificacionObserver :: notificarObserver(DTCalificacionNotificada* calificacion){
    set<ICalificacionObserver*>::iterator it;
    for (it = this->observers.begin(); it != this->observers.end(); ++it){
        (*it)->notificar(calificacion);
    }
    delete calificacion;
}

DTCalificacionNotificada CalificacionObserver :: crearDTCalificacionNotificada(string autor, string comentario, int puntaje){
    return DTCalificacionNotificada(autor, comentario, puntaje);
}

CalificacionObserver :: ~CalificacionObserver(){
    this->observers.clear();
    CalificacionObserver::instancia = NULL;
}