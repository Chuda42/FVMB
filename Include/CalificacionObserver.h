#ifndef _CALIFICACIONOBSERVER_
#define _CALIFICACIONOBSERVER_

//Dependencia de librerias 
#include <set>
//Interfaz que implementa
#include "./ICalificacionObserver.h"
//Dependencia de datatypes
#include "./DTCalificacionNotificada.h"

class CalificacionObserver{
    private:
        //por ser singleton
        static CalificacionObserver* instancia;
        CalificacionObserver();

        set<ICalificacionObserver *> observers;
    public:
        static CalificacionObserver* getInstancia();
        
        DTCalificacionNotificada crearDTCalificacionNotificada(string autor, string comentario, int puntaje);

        void agregarObserver(ICalificacionObserver* observer);
        void eliminarObserver(ICalificacionObserver* observer);
        void notificarObserver(DTCalificacionNotificada* calificacion);

        ~CalificacionObserver();
};




#endif
