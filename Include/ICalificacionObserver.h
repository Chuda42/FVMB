#ifndef _ICALIFICACIONOBSERVER_
#define _ICALIFICACIONOBSERVER_

#include "./DTCalificacionNotificada.h"

class ICalificacionObserver{
    public:
        virtual void notificar(DTCalificacionNotificada* calificacion) = 0;
};

#endif