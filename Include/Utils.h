#ifndef _UTILS_
#define _UTILS_

#include <iostream>
#include <set>
#include <map>
#include <limits>

#include "./Factory.h"
#include "./DTFecha.h"
#include "./DTHostal.h"
#include "./DTHabitacion.h"
#include "./DTReserva.h"
#include "./DTCalificacion.h"
#include "./DTEstadia.h"

#include "./Const.h"

using namespace std;

class Utils
{
private:
    static Utils *instancia;
    Utils();

    bool shouldIgnore;

public:
    static Utils *getInstancia();
    ~Utils();

    void leerString(string &out);
    void leerInt(int &out);
    void leerFloat(float &out);
    void leerBool(bool &out);
    void leerCargo(TipoCargo &out);
    void leerFecha(DTFecha &out);

    void imprimirHostales(set<string> hostalesRegistrados);
    void ingresarNombreDeHostal(set<string> hostales, string& nombreH, string config);
    void ingresarNombreDeHostal(set<DTHostal*> hostales, string& nombreH);

    void eliminarSet(set<DTHostal*>& hostales);
    void eliminarSet(set<DTHabitacion*>& habitaciones);
    void eliminarSet(set<DTReserva*>& reservas);
    void eliminarSet(set<DTCalificacion*>& calificaciones);
    void eliminarSet(set<DTEstadia*>& estadias);


    void eliminarMap(map<pair<int, string>, DTEstadia*>& estadias);

    void cargarDatosDePrueba(bool yaCargados);
};

#endif