#include "../../Include/Utils.h"

using namespace std;

Utils * Utils::instancia = NULL;

Utils::Utils(){
    this->shouldIgnore= false;
};

Utils::~Utils(){};

Utils *Utils::getInstancia(){
    if(Utils::instancia == NULL){
        Utils::instancia = new Utils();
    }
    return Utils::instancia;
};

void Utils::leerString(string& out) {
    if (this->shouldIgnore) {
        cin.ignore(); 
        this->shouldIgnore = false;
    }
    getline(cin, out);
}

void Utils::leerInt(int& out) {
    while (!(cin >> out)) {
        std::cout << "Ingrese un integer \n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    this->shouldIgnore = true;
}

void Utils::leerFloat(float& out) {
    while (!(cin >> out)) {
        std::cout << "Ingrese un float \n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    this->shouldIgnore = true;
}

void Utils::leerBool(bool& out) {
    while (!(cin >> out)) {
        std::cout << "Ingrese un bool \n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    this->shouldIgnore = true;
}

void Utils::leerCargo(TipoCargo& out) {
    while (!(cin >> out)) {
        std::cout << "Ingrese un TipoCargo (Administracion/Limpieza/Recepcion/Infraestructura)\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    this->shouldIgnore = true;
}

void Utils::leerFecha(DTFecha& out) {
    while (!(cin >> out)) {
        std::cout << "Ingrese una fecha (hh/dd/mm/aaaa)\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    this->shouldIgnore = true;
}

void Utils::imprimirHostales(set<string> hostalesRegistrados){
    set<string>::iterator iterHostales;
    if(hostalesRegistrados.empty()){
        throw std::invalid_argument("No hay hostales registrados por el momento");
    }
    cout << "Hostales registrados"<<endl;
    for(iterHostales = hostalesRegistrados.begin(); iterHostales != hostalesRegistrados.end(); ++iterHostales){
        cout << *iterHostales <<endl;
    }
}

void Utils::ingresarNombreDeHostal(set<string> hostales, string& nombreH, string config){
    string mensaje = "Ingrese el nombre del hostal";
    if(config == "+habitacion"){
        mensaje = mensaje + " donde quiera agaregar la habitacion: ";
    }else if(config == "selec"){
        mensaje = mensaje + " seleccionado: ";
    }else if(config == "verInfo"){
        mensaje = mensaje + " que se desea ver la informacion: ";
    }else if(config == "+estadia"){
        mensaje = mensaje + " en el que se quiere registrar la estadia: ";
    }else if(config == "-estadia"){
        mensaje = mensaje + " en el que se quiere finalizar la estadia: ";
    }else if(config == "califEstadia"){
        mensaje = mensaje + " en el que se quiere calificar la estadia: ";
    }else if(config == "verDetalles"){
        mensaje = mensaje + " que se quiere ver detalle: ";
    }else if(config == "verReservas"){
        mensaje = mensaje + " que quiere ver las reservas: ";
    }else if(config == "verEstadias"){
        mensaje = mensaje + " que quiere ver las estaidas: ";
    }else {
        mensaje = mensaje + ": ";
    }
    cout <<mensaje;
    this->leerString(nombreH);

     if(hostales.find(nombreH) == hostales.end()){
        throw std::invalid_argument("El hostal ingresado "+nombreH+" no es un hostal valido");
    }
};

void Utils::ingresarNombreDeHostal(set<DTHostal*> hostales, string& nombreH){
    string mensaje = "Ingrese el nombre del hostal seleccionado: ";
    cout << mensaje;
    this->leerString(nombreH);

    set<DTHostal*>::iterator iterHost;

    bool esHostalValido = false;
    for (iterHost = hostales.begin(); iterHost != hostales.end(); ++iterHost){
        esHostalValido = esHostalValido || (*iterHost)->getNombre() == nombreH;
    }
    if(!esHostalValido){
        throw std::invalid_argument("El nombre "+nombreH+" no corresponde a un hostal valido");
    }
};

void Utils::cargarDatosDePrueba(bool yaCargados){
    if(yaCargados){
        throw std::invalid_argument("Los datos ya fueron cargados anteriormente");
    }

    Factory  * fact = Factory::getInstancia();
    IUsuario * iU   = fact->getIUsuario();
    IReserva * iR   = fact->getIReserva();
    IHostal  * iH   = fact->getIHostal();
    IFechaSistema * iF = fact->getIFechaSistema();
    ControladorReserva * cR = ControladorReserva::getInstancia();
    
    //empleados
    iU->nuevoEmpleado("Emilia", "emilia@mail.com", "123", Recepcion);
    iU->confirmarRegistroUsuario();

    iU->nuevoEmpleado("Leonardo", "leo@mail.com", "123", Recepcion);
    iU->confirmarRegistroUsuario();

    iU->nuevoEmpleado("Alina", "alina@mail.com", "123", Administracion);
    iU->confirmarRegistroUsuario();

    iU->nuevoEmpleado("Barliman", "barli@mail.com", "123", Recepcion);
    iU->confirmarRegistroUsuario();

    iU->nuevoEmpleado("Leonel Penia", "emailProfe", "pass", Administracion);
    iU->confirmarRegistroUsuario();

    iU->nuevoEmpleado("Oscarito", "emailOscar", "pass", Infraestructura);
    iU->confirmarRegistroUsuario();

    
    //huespedes
    iU->nuevoHuesped("Sofía","sofia@mail.com", "123", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Frodo","frodo@mail.com", "123", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Sam","sam@mail.com", "123", false);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Merry","merry@mail.com", "123", false);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Pippin","pippin@mail.com", "123", false);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Seba","seba@mail.com", "123", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Manu Rodriguez", "emailManu", "pass", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Fran Mauri", "emailFran", "pass", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Fede Mello", "emailFede", "pass", true);
    iU->confirmarRegistroUsuario();

    iU->nuevoHuesped("Ailen Monroy", "emailAilen", "pass", true);
    iU->confirmarRegistroUsuario();
    
    //hostels
    iH->agregarHostal("La posada del finger","Av de la playa 123, Maldonado","099111111");
    iH->agregarHostal("Mochileros","Rambla Costera 333, Rocha","42579512");
    iH->agregarHostal("El Pony Pisador","Bree (preguntar por Gandalf)","000");
    iH->agregarHostal("Altos de Fing","Av del Toro 1424","099892992");
    iH->agregarHostal("Caverna Lujosa","Amaya 2515","233233235");
    iH->agregarHostal("El radison", "Plaza independencia", "123");
    iH->agregarHostal("la comarca", "la calle 13", "1235");
    iH->agregarHostal("Hogwarts", "Inglaterra", "manda una lechuza");
    
    //habitaciones
    iH->nuevaHabitacion(1, 40, 2);
    iH->confirmarRegistroHabitacion("La posada del finger");

    iH->nuevaHabitacion(2, 10, 7);
    iH->confirmarRegistroHabitacion("La posada del finger");

    iH->nuevaHabitacion(3, 30, 3);
    iH->confirmarRegistroHabitacion("La posada del finger");

    iH->nuevaHabitacion(4, 5, 12);
    iH->confirmarRegistroHabitacion("La posada del finger");

    iH->nuevaHabitacion(1, 3, 2);
    iH->confirmarRegistroHabitacion("Caverna Lujosa");

    iH->nuevaHabitacion(1, 9, 5);
    iH->confirmarRegistroHabitacion("El Pony Pisador");

    iH->nuevaHabitacion(2, 5, 8);
    iH->confirmarRegistroHabitacion("El radison");

    iH->nuevaHabitacion(3, 6, 9);
    iH->confirmarRegistroHabitacion("El radison");

    iH->nuevaHabitacion(5, 5, 11);
    iH->confirmarRegistroHabitacion("El radison");

    iH->nuevaHabitacion(2, 5, 8);
    iH->confirmarRegistroHabitacion("la comarca");

    iH->nuevaHabitacion(3, 6, 9);
    iH->confirmarRegistroHabitacion("la comarca");

    iH->nuevaHabitacion(5, 5, 11);
    iH->confirmarRegistroHabitacion("la comarca");

    iH->nuevaHabitacion(2, 5, 8);
    iH->confirmarRegistroHabitacion("Hogwarts");

    iH->nuevaHabitacion(3, 6, 9);
    iH->confirmarRegistroHabitacion("Hogwarts");

    iH->nuevaHabitacion(5, 5, 11);
    iH->confirmarRegistroHabitacion("Hogwarts");

    //asignacion de empleados a hostels
    iU->asignarEmpleadoAHostal("emilia@mail.com", "La posada del finger", Recepcion);
    iU->asignarEmpleadoAHostal("leo@mail.com", "Mochileros", Recepcion);
    iU->asignarEmpleadoAHostal("alina@mail.com", "Mochileros", Administracion);
    iU->asignarEmpleadoAHostal("barli@mail.com", "El Pony Pisador", Recepcion);
    iU->asignarEmpleadoAHostal("emailProfe", "El radison", Administracion);
    iU->asignarEmpleadoAHostal("emailOscar", "la comarca", Limpieza);

    //Suscribir empleado a notificaciones
    iU->subscribirEmpleadoANotificaciones("emailProfe");
    iU->subscribirEmpleadoANotificaciones("emailOscar");



    //Reservas
    int cantReservas = cR->getCantidadReservas();

    DTFecha f1a("14/01/05/2022");
    DTFecha f1b("10/10/05/2022");
    iH->setDatosReserva(f1a , f1b, false);
    iH->seleccionarHuesped("sofia@mail.com");
    iH->confirmarReserva("La posada del finger", 1);    //codigo cantReservas + 1

    DTFecha f2a("20/04/01/2001");
    DTFecha f2b("02/05/01/2001");
    iH->setDatosReserva(f2a , f2b, true);
    iH->seleccionarHuesped("frodo@mail.com");
    iH->seleccionarHuesped("sam@mail.com");
    iH->seleccionarHuesped("merry@mail.com");
    iH->seleccionarHuesped("pippin@mail.com");
    iH->confirmarReserva("El Pony Pisador", 1);         //codigo cantReservas + 2

    DTFecha f3a("14/07/06/2022");
    DTFecha f3b("11/30/06/2022");
    iH->setDatosReserva(f3a , f3b, false);
    iH->seleccionarHuesped("sofia@mail.com");
    iH->confirmarReserva("La posada del finger", 3);    //codigo cantReservas + 3

    DTFecha f4a("14/10/06/2022");
    DTFecha f4b("11/30/06/2022");
    iH->setDatosReserva(f4a , f4b, false);
    iH->seleccionarHuesped("seba@mail.com");
    iH->confirmarReserva("Caverna Lujosa", 1);          //codigo cantReservas + 4

     //estadias

    iF->setFechaSistema(2022, 5, 1, 18);
    iR->registrarEstadia("sofia@mail.com", cantReservas + 1);

    iF->setFechaSistema(2001, 1, 4, 21);
    iR->registrarEstadia("frodo@mail.com", cantReservas + 2);
    iR->registrarEstadia("sam@mail.com", cantReservas + 2);
    iR->registrarEstadia("merry@mail.com", cantReservas + 2);
    iR->registrarEstadia("pippin@mail.com", cantReservas + 2);

    iF->setFechaSistema(2022, 6, 7, 18);
    iR->registrarEstadia("seba@mail.com", cantReservas + 4);

    //finalizacion de estadias
    iF->setFechaSistema(2022, 5, 10, 9);
    iR->finalizarEstadia("sofia@mail.com", "La posada del finger");

    iF->setFechaSistema(2001, 1, 5, 2);
    iR->finalizarEstadia("frodo@mail.com", "El Pony Pisador");

    iF->setFechaSistema(2022, 6, 15, 22);
    iR->finalizarEstadia("seba@mail.com", "Caverna Lujosa");

    //calificar estadia
    iF->setFechaSistema(2022, 5, 11, 18);
    iR->calificarEstadia("sofia@mail.com", cantReservas + 1, "Un poco caro para lo que ofrecen. El famoso gimnasio era una caminadora (que hacía tremendoruido) y 2 pesas, la piscina parecía el lago del Parque Rodó y el desayuno eran 2 tostadas con mermelada. Internet se pasaba cayendo. No vuelvo.", 3);
    
        //desuscribo a un empleado
        iU->desubscribirEmpleadoANotificaciones("emailOscar");
    
    iF->setFechaSistema(2001, 1, 5, 3);
    iR->calificarEstadia("frodo@mail.com", cantReservas + 2, "Se pone peligroso de noche, no recomiendo. Además no hay caja fuerte para guardar anillos.", 2);
    
    
    iF->setFechaSistema(2022, 6, 15, 23);
    iR->calificarEstadia("seba@mail.com", cantReservas + 4, "Había pulgas en la habitación. Que lugar más mamarracho!!", 1);

    //comentar calificacion
    iF->setFechaSistema(2001, 1, 6, 15);
    iR->comentarCalificacion("frodo@mail.com", cantReservas + 2, "Desapareció y se fue sin pagar.");


    cout<< "Los datos fueron cargados con exito"<< endl;
} 

void Utils::eliminarSet(set<DTHostal*>& hostales){
    set<DTHostal*>::iterator iter;
    for(iter = hostales.begin(); iter != hostales.end(); ++iter){
        delete *iter;
    }
    hostales.clear();
};

void Utils::eliminarSet(set<DTHabitacion*>& habitaciones){
    set<DTHabitacion*>::iterator iter;
    for(iter = habitaciones.begin(); iter != habitaciones.end(); ++iter){
        delete *iter;
    }
    habitaciones.clear();   
};

void Utils::eliminarSet(set<DTReserva*>& reservas){
    set<DTReserva*>::iterator iter;
    for(iter = reservas.begin(); iter != reservas.end(); ++iter){
        delete *iter;
    }
    reservas.clear(); 
};

void Utils::eliminarSet(set<DTCalificacion*>& calificaciones){
    set<DTCalificacion*>::iterator iter;
    for(iter = calificaciones.begin(); iter != calificaciones.end(); ++iter){
        delete *iter;
    }
    calificaciones.clear(); 
};

void Utils::eliminarSet(set<DTEstadia*>& estadias){
    set<DTEstadia*>::iterator iter;
    for(iter = estadias.begin(); iter != estadias.end(); ++iter){
        delete *iter;
    }
    estadias.clear();    
};

void Utils::eliminarMap(map<pair<int, string>, DTEstadia*>& estadias){
    map<pair<int, string>, DTEstadia*>::iterator iter;
    for(iter = estadias.begin(); iter != estadias.end(); ++iter){
        delete iter->second;
    }
    estadias.clear(); 
};
