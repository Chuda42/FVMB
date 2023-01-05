#ifndef _USUARIO_ 
#define _USUARIO_ 

#include <set>
#include <string>
#include <iostream>

using namespace std;

class Usuario{
    private:
        std::string nombre;
        std::string email;
        std::string contrasenia;
    public:
        void setNombre(std::string nombre);
        void setEmail(std::string email);
        void setContrasenia(std::string contrasenia);

        std::string getNombre();
        std::string getEmail();
        std::string getContrasenia();

        virtual bool esEmpleado()=0;
        virtual bool esEmpleadoSinAsignar()=0;
        virtual bool esHuesped()=0;  
        virtual Usuario* seleccionarHuesped()=0;
        
        bool estaUsuarioEn(set<std::string> hSelc);

        Usuario(std::string nombre,std::string email,std::string contrasenia);
        virtual ~Usuario();
};




#endif