#ifndef _DTHOSTAL_
#define _DTHOSTAL_

#include<iostream>

using namespace std;

class DTHostal{
    private:
        string nombre;
        string direccion;
        string telefono;
        float calificacionPromedio;
    public:
        DTHostal(string nombre, string direccion, string telefono, float calificacionPromedio);
        string getNombre();
        string getDireccion();
        string getTelefono();
        float getCalificacionPromedio();
        ~DTHostal();

};

ostream &operator<<(ostream &out, DTHostal &c);

#endif