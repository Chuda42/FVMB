//dependencias 
#include "./Include/Factory.h"
#include "./Include/Const.h"
#include "./Include/Utils.h"
#include <iostream>

using namespace std;

bool yaCargados = false;

int main()
{
    Factory  * fact = Factory::getInstancia();
    IUsuario * iU   = fact->getIUsuario();
    IReserva * iR   = fact->getIReserva();
    IHostal  * iH   = fact->getIHostal();
    IFechaSistema * iF = fact->getIFechaSistema();
    Utils * utils = Utils::getInstancia();
    
    bool salir = false;
    int comando = -1;

    do{
        switch (comando)
        {
        case 1:{
            string nombreU, emailU, contraseniaU;
            cout << "1. Agregar Empleado"<<endl;
            cout << "2. Agregar Huésped"<<endl;
            cout << "3. Atrás" << endl;
            utils->leerInt(comando);

            try{
                if(comando != 3){
                    cout << "Ingrese el nombre: "; utils->leerString(nombreU);
                    cout << "Ingrese el email: "; utils->leerString(emailU);
                    cout << "Ingrese la contraseña: "; utils->leerString(contraseniaU);
                    if(emailU.empty()){
                        throw std::invalid_argument("El email del nuevo usuario no puede ser vacío.");
                        comando = 0;
                    }
                    if (comando == 1){
                        TipoCargo cargoE;

                        cout << "Ingrese el cargo del empleado" << endl;
                        cout << "0. Administracion " << endl;
                        cout << "1. Limpieza " << endl;
                        cout << "2. Recepcion" << endl;
                        cout << "3. Infraestructura" << endl;
                        utils->leerCargo(cargoE);

                        iU->nuevoEmpleado(nombreU, emailU, contraseniaU, cargoE);
                    }else if (comando == 2){
                        bool esFinger;
                        cout << "¿El huésped es Finger?" << endl;
                        cout << "1. Si " << endl;
                        cout << "0. No " << endl;
                        utils->leerBool(esFinger);

                        iU->nuevoHuesped(nombreU, emailU, contraseniaU, esFinger);
                    }
                    cout << "Confirmar registro" << endl;
                    cout << "1. Confirmar" << endl;
                    cout << "2. Cancelar" << endl;
                    utils->leerInt(comando);

                    if (comando == 1){
                        iU->confirmarRegistroUsuario();
                        cout << "Registrado con éxito." << endl;

                    }else if (comando == 2){
                        iU->cancelarRegistroUsuario();
                        cout << "El registro fue cancelado." << endl;
                    }
                }
            }catch(const std::invalid_argument& e){
              
                while(comando != 0){
                    cout << e.what()<<endl;
                    cout << "1. Ingresar otro email"<<endl;
                    cout << "2. Cancelar registro"<<endl;
                    utils->leerInt(comando);
                    if(comando == 1){
                        try{
                            cout << "Ingrese un nuevo email: "; utils->leerString(emailU);
                            iU->setNuevoEmail(emailU);
                            cout << "Confirmar registro"<<endl;
                            cout << "1. Confirmar"<<endl;
                            cout << "2. Cancelar"<<endl;
                            utils->leerInt(comando);
                            if(comando == 1){
                                iU->confirmarRegistroUsuario();
                                cout << "Registrado con éxito."<<endl;
                            }else if (comando == 2){
                                iU->cancelarRegistroUsuario();
                                cout << "El registro fue cancelado."<<endl;
                            }
                            comando = 0;
                        }catch(const std::invalid_argument& e){
                            comando = 1;
                        }
                    }else if (comando == 2){
                        comando = 0;
                    }
                }
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 2:{
            try{
                string nombreH, direccionH, telefonoH;
                cout << "Agregar Hostal" <<endl;
                cout << "Ingrese nombre del hostal: "; utils->leerString(nombreH);
                cout << "Ingrese direccion del hostal: "; utils->leerString(direccionH);
                cout << "Ingrese telefono del hostal: "; utils->leerString(telefonoH);
                iH->agregarHostal(nombreH, direccionH, telefonoH);
                cout << "Se registró el hostal satisfactoriamente." << nombreH <<endl;
            }catch(const std::invalid_argument& e){
                cout << "Error: " << e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 3:{
            try{
                string nombreH;
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "+habitacion");
                




                int numero, capacidad;
                float precio;
                cout << "Ingrese los datos de la nueva habitación" << endl;
                cout << "Ingrese el numero de la habitación: "; utils->leerInt(numero);
                if(numero < 0){
                    throw invalid_argument("El número de la habitacion no puede ser menor a 0.");
                }

                cout << "Ingrese el precio por noche de la habitación: "; utils->leerFloat(precio);
                cout << "Ingrese la capacidad maxima de la habitación: "; utils->leerInt(capacidad);
                cout << endl;
                cout << "1. Confirmar registro" << endl;
                cout << "2. Cancelar registro" <<endl;
                utils->leerInt(comando);
                iH->nuevaHabitacion(numero, precio, capacidad);

                if(comando == 1){
                    iH->confirmarRegistroHabitacion(nombreH);
                    cout << "Se registró la habitación " <<numero << " en el hostal "<< nombreH <<"exitosamente."<<endl;
                }else{
                    cout << "El registro fue cancelado."<<endl;
                    iH->cancelarRegistroHabitacion();
                }
                
            }catch(const std::invalid_argument& e){
                cout << e.what() << endl;
                iH->cancelarRegistroHabitacion();
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 4:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                set<string>::iterator iter = hostalesRegistrados.begin();
                if(iter == hostalesRegistrados.end()){
                    cout << "No hay hostales registrados de momento." <<endl;
                }else{
                    cout << "Hostales registrados: "<< endl;
                    for (iter = hostalesRegistrados.begin(); iter != hostalesRegistrados.end(); ++iter){
                        cout << *iter << endl;
                    }
                    set<string> empleadosD;
                    set<string>::iterator it;
                    string emailE, nombreH;
                    TipoCargo cargoE;
                    utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "selc");
                    do{
                        cout<< "1. Agregar empleado."<< endl;
                        cout<< "2. No agregar más empleados." << endl;
                        utils->leerInt(comando);
                        if(comando == 1){
                            empleadosD = iU->getEmpleadosDisponibles();
                            if(empleadosD.empty()){
                                cout << "No hay empleados disponibles por el momento." << endl;
                            }else{
                                cout << "Los empleados disponibles son: " << endl;
                                for(it = empleadosD.begin(); it != empleadosD.end(); ++it){
                                    cout << *it <<endl;
                                }

                                cout << "Ingrese el email de empleado seleccionado: "; utils->leerString(emailE);
                                cout << "Ingrese el cargo del empleado: "<<endl;
                                cout << "0. Administracion " << endl;
                                cout << "1. Limpieza " << endl;
                                cout << "2. Recepcion" << endl;
                                cout << "3. Infraestructura" << endl;
                                utils->leerCargo(cargoE);
                                
                                
                                try{
                                    iU->asignarEmpleadoAHostal(emailE,nombreH,cargoE);
                                }catch(const std::invalid_argument& e){
                                    cout << e.what() << endl;
                                }
                            }
                        }else{
                            comando = 0;
                        }
                    }while(comando != 0);
                }
            }catch(const std::invalid_argument& e){
                cout << e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 5:{
            try{
                string nombreH;
                set<DTHostal*>::iterator iterHost;

                set<DTHostal*> hostalesRegistrados = iH->getHostalesConCalificacion();
                cout<< "Hostales disponibles: " << endl;
                for (iterHost = hostalesRegistrados.begin(); iterHost != hostalesRegistrados.end(); ++iterHost){
                        cout << **iterHost <<endl;
                }

                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH);
                utils->eliminarSet(hostalesRegistrados);

                DTFecha checkIn, checkOut;
                bool esGrupal;
            
                cout << "Ingrese los datos de la nueva reserva" << endl;
                cout << "ingrese la fecha de check-in (hh/dd/mm/aaaa): "; utils->leerFecha(checkIn);
                cout << "Ingrese la fecha de check-out (hh/dd/mm/aaaa): "; utils->leerFecha(checkOut);
                cout << "¿La reserva es grupal? "<< endl;
                cout << "0. No" << endl;
                cout << "1. Si" << endl;
                utils->leerBool(esGrupal);
                iH->setDatosReserva(checkIn, checkOut, esGrupal);

                cout << "Habitaciones Disponibles:"<< endl;
                int numeroHabitacion;
                set<DTHabitacion *> habitacionesDisponibles = iH->getHabitacionesDisponibles(nombreH);
                set<DTHabitacion *>::iterator iterHabit;
                if(habitacionesDisponibles.empty()){
                    throw std::invalid_argument("No hay habitaciones disponibles para la fecha ingresada.");
                }
                for (iterHabit = habitacionesDisponibles.begin(); iterHabit != habitacionesDisponibles.end(); ++iterHabit){
                    cout << **iterHabit <<endl;
                }
                cout << "Ingrese el número de la habitación seleccionada: "; utils->leerInt(numeroHabitacion);

                bool esHabitacionValida = false;
                for (iterHabit = habitacionesDisponibles.begin(); iterHabit != habitacionesDisponibles.end(); ++iterHabit){
                    esHabitacionValida = esHabitacionValida || (*iterHabit)->getNumero() == numeroHabitacion;
                }
                utils->eliminarSet(habitacionesDisponibles);
                if(!esHabitacionValida){
                    throw std::invalid_argument("El número de habitación ingresado no corresponde a una habitación válida.");
                }
                
                cout << "Los huéspedes registrados en el sistema: " << endl;
                set<string> huespedes = iU->getHuespedes();
                set<string>::iterator iterHuespedes;
                string huespedSeleccionado;
                for(iterHuespedes = huespedes.begin(); iterHuespedes != huespedes.end(); ++iterHuespedes){
                    cout << *iterHuespedes <<endl;
                }
                cout<<endl;
                cout << "Ingrese el email del huésped titular de la reserva: "; utils->leerString(huespedSeleccionado);

                iterHuespedes = huespedes.find(huespedSeleccionado);
                if(iterHuespedes == huespedes.end()) {
                    throw std::invalid_argument("El huésped " + huespedSeleccionado + " no pertenece a la lista de huésped registrados.");
                }

                iH->seleccionarHuesped(huespedSeleccionado);
                comando = 1;
                while (comando == 1 && esGrupal){
                    cout << "Agregar otro huésped" << endl;
                    cout << "Ingrese el email del otro huésped: "; utils->leerString(huespedSeleccionado);
                    if(iterHuespedes == huespedes.end()) {
                        throw std::invalid_argument("El huésped " + huespedSeleccionado + "no pertenece a la lista de huésped registrados.");
                    }
                    iH->seleccionarHuesped(huespedSeleccionado);

                    cout << "¿Quiere agregar otro huésped?"<< endl;
                    cout << "1. Si"<< endl;
                    cout << "2. No"<< endl;
                    utils->leerInt(comando);
                }

                cout << "Confirmación"<< endl;
                cout << "1. Confirmar reserva"<< endl;
                cout << "2. Cancelar reserva"<< endl;
                utils->leerInt(comando);

                if(comando == 1){
                    iH->confirmarReserva(nombreH, numeroHabitacion);
                    cout << "la reserva fue registrada con éxito." << endl;
                }else{
                    iH->cancelarReserva();
                    cout << "La reserva fue cancelada." << endl;
                }
            }catch(const std::invalid_argument& e){
                iH->cancelarReserva();
                cout<< "Error: "<< e.what() << endl;
                cout << "La reserva fue cancelada." << endl;
            }
            
            comando = -1;
            cout<<endl <<endl;
        }break;
        case 6: {
            try{
                //string hostales [3] = {"", "", ""};
                map<int, string> top3Hostales = iH->getTop3Hostales();
                if(top3Hostales.empty()){
                    throw std::invalid_argument("No hay hostales registrados por el momento");
                }

                cout << "Los hostales que estan en el top 3 son: " << endl;
                set<string> hostales;
                for(map<int, string>::iterator iter = top3Hostales.begin(); iter != top3Hostales.end(); ++iter) {
                    cout << iter->second <<endl;
                    hostales.insert(iter->second);
                }
                
                cout << "1. Ver detalle de hostal" << endl;
                cout << "2. Atrás" << endl;
                utils->leerInt(comando);

                string nombreH;
                if(comando == 1){

                    utils->ingresarNombreDeHostal(hostales, nombreH, "verInfo");

                    
                    set<DTCalificacion *> calificacionesHostal = iR->getCalificacionesDeHostal(nombreH);
                    set<DTCalificacion *>::iterator iterCalificaciones;
                    cout << "Detalles del hostal " << nombreH << ":"<< endl; 
                    for(iterCalificaciones = calificacionesHostal.begin(); iterCalificaciones != calificacionesHostal.end(); ++iterCalificaciones){
                        cout << **iterCalificaciones << endl;
                    }
                    utils->eliminarSet(calificacionesHostal);
                }
            }catch(const std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }

            
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 7:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                
                string nombreH, emailH;
                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "+estaidas");




                cout << "Ingrese el email del huesped que registra su estadia: ";  utils->leerString(emailH);

                set<string> huespedes = iU->getHuespedes();
                if(huespedes.find(emailH) == huespedes.end()){
                    throw std::invalid_argument("No existe un huésped registrado con el email " +emailH);
                }
                
                set<int> reservasNoCanceladas = iR->getReservasNoCanceladas(emailH, nombreH);
                set<int>::iterator iterReservas;
                cout<< "El código de las reservas del usuario que no estan canceladas son: "<<endl;
                for(iterReservas = reservasNoCanceladas.begin(); iterReservas != reservasNoCanceladas.end(); ++iterReservas){
                    cout << *iterReservas << endl;
                }
                
                int codigoSeleccionado;
                cout << "Ingrese el código de la reserva correspondiente para ingresar su estadía: "; utils->leerInt(codigoSeleccionado);
                if(reservasNoCanceladas.find(codigoSeleccionado) == reservasNoCanceladas.end()){
                    throw std::invalid_argument("El código ingresado no es válido.");
                }

                iR->registrarEstadia(emailH, codigoSeleccionado);
                cout << "Estadía del huésped "<<emailH<< " en la reserva con código "<<codigoSeleccionado << " registrada con éxito."<< endl;

            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 8:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                string nombreH, emailH;
                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "-estaidas");
                
                cout << "Ingrese el email del huesped que finaliza su estadia: ";  utils->leerString(emailH);

                set<string> huespedes = iU->getHuespedes();
                if(huespedes.find(emailH) == huespedes.end()){
                    throw std::invalid_argument("No existe un huésped registrado con el email " +emailH);
                }

                iR->finalizarEstadia(emailH, nombreH);
                cout << "La estadía del huésped "<< emailH <<" fue finalizada correctamente."<<endl; 

            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 9:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                string nombreH, emailH;
                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "califEstadia");
                
                cout << "Ingrese el email del huesped que califica su estadia: ";  utils->leerString(emailH);

                set<string> huespedes = iU->getHuespedes();
                if(huespedes.find(emailH) == huespedes.end()){
                    throw std::invalid_argument("No existe un huésped registrado con el email " +emailH);
                }

                set<DTEstadia*> estadiasFinalizadas;
                estadiasFinalizadas = iR->getEstadiasFinalizadas(emailH, nombreH);
                set<DTEstadia*>::iterator iterEstadia;
                for (iterEstadia = estadiasFinalizadas.begin(); iterEstadia != estadiasFinalizadas.end(); ++iterEstadia){
                    cout << **iterEstadia << endl;
                }

                utils->eliminarSet(estadiasFinalizadas);

                string comentario;
                int codigoR, puntaje;
                cout << "Ingrese el código de reserva a calificar: "; utils->leerInt(codigoR);
                cout << "Ingrese el comentario: ";  utils->leerString(comentario);
                cout << "Ingrese el puntaje del 1 al 5: "; utils->leerInt(puntaje);

                iR->calificarEstadia(emailH, codigoR, comentario, puntaje);
                cout<< "La estadía de la resrva de código "<<codigoR<< " fue calificada con éxito."<<endl;


            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 10:{
            try{
                cout << "Comentar Calificaciones."<<endl;

                string emailEmpelado;
                cout << "Ingrese el correo del empleado: ";  utils->leerString(emailEmpelado);
                cout << endl;

                set<DTCalificacion*> calificacionesSinResponder = iR->getCalificacionesSinResponder(emailEmpelado);
                
                if(calificacionesSinResponder.empty()){
                    throw std::invalid_argument("No hay calificaciones pendientes para el empleado indicado.");
                }
                set<DTCalificacion*>::iterator iter;
                for(iter = calificacionesSinResponder.begin(); iter != calificacionesSinResponder.end(); ++iter){
                    cout << **iter <<endl;
                }
                utils->eliminarSet(calificacionesSinResponder);
                string emailH, respuesta;
                int codigoR;
                cout << "Ingrese los datos de la calificacion que se desea comentar." << endl;
                cout << "Código de reserva: "; utils->leerInt(codigoR);
                cout << "Email de huésped: ";  utils->leerString(emailH);
                cout << "Ingrese la respuesta: ";  utils->leerString(respuesta);

                iR->comentarCalificacion(emailH, codigoR, respuesta);
                cout << "Se ha comentado la calificacion satisfactoriamente." << endl;

            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 11:{
            try{
                set<string> usuarios = iU->getUsuarios();
                set<string>::iterator iterUsuarios;
                cout << "Usuarios registrados en sistema: " << endl;
                for(iterUsuarios = usuarios.begin(); iterUsuarios != usuarios.end(); ++iterUsuarios){
                    cout << *iterUsuarios <<endl;
                }
                cout << endl;

                string emailU;
                cout << "1. Ver detalles de un usuario" << endl;
                cout << "2. Atrás" << endl;
                utils->leerInt(comando);

                if(comando ==1){
                    cout << "Ingrese el email del usuario del que quiere ver detalles: ";
                     utils->leerString(emailU);

                    if(usuarios.find(emailU) == usuarios.end()){
                        throw std::invalid_argument("El email ingresado no es válido.");
                    }
                    cout << "Detalles del usuario seleccionado:" << endl;
                    DTUsuario * dtU= iU->getUsuarioDetalle(emailU);
                    cout << *dtU <<endl;
                    delete dtU;
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 12:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);   


                cout << endl;



                string nombreH;
                cout << "1. Ver detalles de un hostal" << endl;
                cout << "2. Atrás" << endl;
                utils->leerInt(comando);

                if(comando ==1){
                    utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "verDetalles");
                    




                    cout << "Detalles del hostal seleccionado" << endl;
                    cout << "Información básica del hostal" << endl;
                    DTHostal * dtH= iH->getInfoBasicaHostal(nombreH);
                    cout << *dtH <<endl;
                    delete dtH;

                    set<DTHabitacion *> habitacionesHostal = iH->getHabitaciones(nombreH);
                    if (!habitacionesHostal.empty()) {
                        cout<< "Información sobre las habitaciones del hostal:" << endl;
                        set<DTHabitacion *>::iterator iterHabitacion;
                        for(iterHabitacion = habitacionesHostal.begin(); iterHabitacion != habitacionesHostal.end(); ++iterHabitacion){
                            cout << **iterHabitacion << endl;
                        }
                    }
                    

                    utils->eliminarSet(habitacionesHostal);

                    set<DTReserva *> reservasHostal = iR->getReservas(nombreH);
                    if (reservasHostal.empty())
                    {
                        cout << "No contiene reservas." << endl;
                    }
                    else
                    {
                        cout << "Información sobre las reservas del Hostal." << endl;
                        set<DTReserva *>::iterator iterReservas;
                        for(iterReservas = reservasHostal.begin(); iterReservas != reservasHostal.end(); ++iterReservas){
                            cout << **iterReservas << endl;
                        }
                    }

                    utils->eliminarSet(reservasHostal);
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 13:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                cout << endl;





                string nombreH;
                cout << "1. Ver reservas de un hostal" << endl;
                cout << "2. Atrás" << endl;
                utils->leerInt(comando);

                if(comando ==1){
                    utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "verReservas");
                    




                    cout << "Reservas del hostal seleccionado" << endl;

                    set<DTReserva *> reservasHostal = iR->getReservas(nombreH);
                    if (reservasHostal.empty())
                    {
                        cout << "No contiene reservas." << endl;
                    }
                    else
                    {
                        cout << "Información sobre las reservas del Hostal." << endl;
                        set<DTReserva *>::iterator iterReservas;
                        for(iterReservas = reservasHostal.begin(); iterReservas != reservasHostal.end(); ++iterReservas){
                            cout << **iterReservas << endl;
                        }
                    }

                    utils->eliminarSet(reservasHostal);
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 14:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                cout << endl;


                string nombreH;
                cout << "1. Ver estadías de un hostal" << endl;
                cout << "2. Atrás" << endl;
                utils->leerInt(comando);

                if(comando ==1){
                    utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "verEstaidas");
                    




                    map<pair<int, string>, DTEstadia*> estadias = iH->getEstadias(nombreH);
                    map<pair<int, string>, DTEstadia*>::iterator iterEstadias;
                    if(estadias.empty()){
                        throw std::invalid_argument("El hostal aún no tiene estadías registradas.");
                    };

                    cout << "Estadías del hostal seleccionado:" << endl;
                    for(iterEstadias = estadias.begin(); iterEstadias != estadias.end(); ++iterEstadias){
                        cout << "Código de la reserva: "<< (iterEstadias->first).first << ". Email del huésped: "<< (iterEstadias->first).second <<endl;
                    }
                    int codigoR;
                    string emailH;
                    cout <<"Ingrese el código de la reserva: "; utils->leerInt(codigoR);
                    cout <<"Ingrese el email del huésped: "; utils->leerString(emailH);
                    pair<int, string> id = pair<int, string>(codigoR, emailH);
                    iterEstadias = estadias.find(id);
                    if(iterEstadias == estadias.end()){
                        throw std::invalid_argument("Los datos ingresados no son correctos.");
                    }
                    cout<<"Información de la estadía solicitada:"<< endl;
                    cout<< *iterEstadias->second << endl;

                    utils->eliminarMap(estadias);

                    cout<< "1. Ver calificación de la estadía" << endl;
                    cout <<"2. No ver la calificación" << endl;
                    utils->leerInt(comando);

                    if(comando == 1){
                        DTCalificacion * caliEstadia = iR->getCalificacionEstadia(emailH, codigoR);
                        cout<< *caliEstadia <<endl;
                        delete caliEstadia;
                    }
                    cout<< "1. Ver la informacin de la reserva asociada a la estadía." << endl;
                    cout <<"2. No ver la información de la reserva asociada." << endl;
                    utils->leerInt(comando);

                    if(comando == 1){
                        DTReserva * reservaEstadia = iR->getReserva(codigoR);
                        cout << "La información de la reserva:" << endl;
                        cout << *reservaEstadia <<endl;
                        delete reservaEstadia;
                    }
                }  
                    
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 15:{
            try{
                set<string> hostalesRegistrados = iH->getHostales();
                utils->imprimirHostales(hostalesRegistrados);
                cout << endl;
                string nombreH;
                utils->ingresarNombreDeHostal(hostalesRegistrados, nombreH, "verReservas");


                set<DTReserva*> reservas = iR->getReservas(nombreH);
                set<DTReserva*>::iterator iter;

                cout << "Reservas asociadas al hostal: " << endl;
                for (iter = reservas.begin(); iter != reservas.end(); ++iter) {
                    cout << **iter << endl;
                }

                utils->eliminarSet(reservas);

                int codigoR;
                cout << "Ingrese el código de reserva a dar de baja: "; utils->leerInt(codigoR);

                cout<< "1. Confirmar baja de reserva." << endl;
                cout <<"2. Cancelar baja de reserva." << endl;
                utils->leerInt(comando);

                if (comando == 1) {
                    iR->eliminarReserva(codigoR);
                    cout <<"Se ha eliminado la reserva satisfactoriamente." << endl;
                }   
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 16:{
            try{
                set<string>  empleados;
                empleados = iU->getEmpleados();
                if(empleados.empty()){
                    cout << "No hay empleados ingresados." << endl;
                }else{
                    set<string>::iterator it;
                    cout << "Los empleados disponibles son: " << endl;
                    for(it = empleados.begin(); it != empleados.end(); ++it){
                        cout << *it <<endl;
                    }
                    string email;
                    cout << "Ingrese el email del empleado a suscribir: "; 
                     utils->leerString(email);
                    iU->subscribirEmpleadoANotificaciones(email);
                    cout << "El empleado se ha suscrito satisfactoriamente." << endl;
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 17:{
            try{
                set<string>  empleados;
                empleados = iU->getEmpleados();
                if(empleados.empty()){
                    cout << "No hay empleados ingresados." << endl;
                }else{
                    set<string>::iterator it;
                    cout << "Los empleados disponibles son: " << endl;
                    for(it = empleados.begin(); it != empleados.end(); ++it){
                        cout << *it <<endl;
                    }
                    string email;
                    cout << "Ingrese el email del empleado para ver sus notificaciones: "; 
                     utils->leerString(email);
                    set<DTCalificacionNotificada*> calificacionesPendientes = iU->getNotificacionesPendientes(email);
                    if(calificacionesPendientes.empty()){
                        cout << "No hay notificaciones pendientes." << endl;
                    } else {
                        set<DTCalificacionNotificada*>::iterator itCalif;
                        for(itCalif = calificacionesPendientes.begin(); itCalif != calificacionesPendientes.end(); ++itCalif){
                            cout << **itCalif <<endl;
                        }
                    }

                    iU->borrarNotificacionesPendientes(email);
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 18:{
            try{
                set<string>  empleados;
                empleados = iU->getEmpleados();
                if(empleados.empty()){
                    cout << "No hay empleados ingresados." << endl;
                }else{
                    set<string>::iterator it;
                    cout << "Los empleados disponibles son: " << endl;
                    for(it = empleados.begin(); it != empleados.end(); ++it){
                        cout << *it <<endl;
                    }
                    string email;
                    cout << "Ingrese el email de empleado a desuscribir: "; 
                     utils->leerString(email);
                    iU->desubscribirEmpleadoANotificaciones(email);
                    cout << "El empleado se ha desuscrito satisfactoriamente." << endl;
                }
            }catch(std::invalid_argument& e){
                cout<< "Error: "<< e.what() << endl;
            }
            comando=-1;
            cout<<endl <<endl;
        }break;
        case 19:{
            int hora,dia,mes,anio;
            cout << "Ingrese la hora: "; utils->leerInt(hora);
            cout << "Ingrese el día: "; utils->leerInt(dia);
            cout << "Ingrese el mes: "; utils->leerInt(mes);
            cout << "Ingrese el anio: "; utils->leerInt(anio);

            try{
                iF->setFechaSistema(anio,mes,dia,hora);
            }catch(const std::exception& e){
                std::cout << e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 20:{
            //Datos de prueba
            try{
                utils->cargarDatosDePrueba(yaCargados);
                yaCargados = true;
            }catch(const std::exception& e){
                std::cout << e.what() << endl;
            }
            comando = -1;
            cout <<endl <<endl;
        }break;
        case 0:{
            delete utils;
            delete fact;
            salir = true;
        }break;
        default:{
            cout << "1. Alta de Usuario" << endl;
            cout << "2. Alta de Hostal" << endl;
            cout << "3. Alta de Habitación" << endl;
            cout << "4. Asignar Empleado a Hostal" << endl;
            cout << "5. Realizar reserva" << endl;
            cout << "6. Consutar el top 3 de Hostales" << endl;
            cout << "7. Registrar Estadía" <<endl;
            cout << "8. Finalizar Estadía" << endl;
            cout << "9. Calificar Estadía" << endl;
            cout << "10. Comentar Calificación" << endl;
            cout << "11. Consulta de Usuario" << endl;
            cout << "12. Consulta de Hostal" << endl;
            cout << "13. Consulta de Reservas" << endl;
            cout << "14. Consulta de Estadía" << endl;
            cout << "15. Baja de Reserva" << endl;
            cout << "16. Suscribirse a Notificaciones" << endl;
            cout << "17. Consulta de Notificaciones" << endl;
            cout << "18. Desuscribirse a Notificaciones" << endl;
            cout << "19. Confirgurar fecha del sistema"<< endl;
            cout << "20. Cargar datos" << endl;
            cout << "0. Salir"<< endl;
            utils->leerInt(comando);
        }break;
        }
    }while(!salir);
}