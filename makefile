all: main
.PHONY: clean  

#Directorios
HDIR   = ./Include
CPPDIR_CLASS = ./Src/Class
CPPDIR_CONTROLLER = ./Src/Controller
CPPDIR_DATATYPE = ./Src/Datatypes
CPPDIR = ./Src
CPPDIR_MAIN = ./
ODIR   = ./Obj

#compilador
GCC     = g++
CCFLAGS = -Wall -Werror -I$(HDIR) -g

#Modulos
MODULOS_CLASS = Utils CalificacionObserver Calificacion Empleado Estadia Factory Habitacion Hostal Huesped Reserva ReservaGrupal ReservaIndividual Usuario

MODULOS_CONTROLLER = ControladorFechaSistema ControladorHostal ControladorReserva ControladorUsuario

MODULOS_DATATYPES = Const DTCalificacion DTCalificacionNotificada DTDatosNuevaReserva DTEmpleado DTHuesped DTEstadia DTUsuario DTFecha DTHabitacion DTHostal DTReserva


MODULO_MAIN = main

CONST_MODULOS = Const

#Lista con los archivos con sus directorios y extension
HS_CLASS           = $(MODULOS_CLASS:%=$(HDIR)/%.h)
HS_CONTROLLER      = $(MODULOS_CONTROLLER:%=$(HDIR)/%.h)
HS_DATATYPES       = $(MODULOS_DATATYPES:%=$(HDIR)/%.h)


CONSTHS = $(CONST_MODULOS:%=$(HDIR)/%.h)

CPPS_CLASS        = $(MODULOS_CLASS :%=$(CPPDIR_CLASS)/%.cpp)
CPPS_CONTROLLER   = $(MODULOS_CONTROLLER:%=$(CPPDIR_CONTROLLER)/%.cpp)
CPPS_DATATYPES    = $(MODULOS_DATATYPES:%=$(CPPDIR_DATATYPE)/%.cpp)
CPPS_MAIN   	  = $(MODULOS_MAIN:%=$(CPPDIR_MAIN)/%.cpp)

OS_CLASS           = $(MODULOS_CLASS:%=$(ODIR)/%.o) #esto es lo mismo que hacer main.o DTFecha.o ...
OS_CONTROLLER      = $(MODULOS_CONTROLLER:%=$(ODIR)/%.o)
OS_DATATYPES       = $(MODULOS_DATATYPES:%=$(ODIR)/%.o)
OS_MAIN            = $(MODULOS_MAIN:%=$(ODIR)/%.o)


MAIN       = main
EJECUTABLE = main

#Reglas
$(ODIR)/$(MAIN).o: $(CPPDIR_MAIN)/main.cpp | objfolder
	@printf 'compilando $(<) \n'; \
	$(GCC) $(CCFLAGS) -c $< -o $@

#$(ODIR)/Const.o: $(CPPDIR_DATATYPE)/Const.cpp $(HDIR)/Const.h | objfolder
#	$(GCC) $(CCFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CPPDIR_CLASS)/%.cpp $(HS_CLASS) $(CONSTHS) | objfolder
	$(GCC) $(CCFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CPPDIR_CONTROLLER)/%.cpp $(HS_CONTROLLER) $(CONSTHS) | objfolder
	$(GCC) $(CCFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CPPDIR_DATATYPE)/%.cpp $(HS_DATATYPES) $(CONSTHS) | objfolder
	$(GCC) $(CCFLAGS) -c $< -o $@
	

$(EJECUTABLE): $(ODIR)/$(MAIN).o $(OS_CLASS) $(OS_CONTROLLER) $(OS_DATATYPES) #$(OS_PRUEBA)
	@printf 'Compilando y enlazando $(@) \n'
	$(GCC) $(CCFLAGS) $^ -o $@



#Crear las carpetas
objfolder:
	mkdir -p $(ODIR)




#Elimina todo para volver a compilar
clean:
	@rm -r $(ODIR)
	@rm -f $(EJECUTABLE)