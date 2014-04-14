SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c

all: $(BIN)/pruebarotacion $(BIN)/pruebapegado


# ************ Compilación de módulos ************
$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o
	
$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/pruebarotacion.o: $(SRC)/pruebarotacion.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/pruebarotacion.cpp -o $(OBJ)/pruebarotacion.o
	
$(OBJ)/pruebapegado.o: $(SRC)/pruebapegado.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $(SRC)/pruebapegado.cpp -o $(OBJ)/pruebapegado.o
	
	
# ************ Compilación de librerias ************
$(LIB)/libimagen.a : $(OBJ)/imagenES.o $(OBJ)/imagen.o 
	ar -rvs $(LIB)/libimagen.a $(OBJ)/imagenES.o $(OBJ)/imagen.o
	

# ************ Compilación de ejecutables binarios ************
$(BIN)/pruebarotacion: $(OBJ)/pruebarotacion.o $(LIB)/libimagen.a
	$(CXX) -o $(BIN)/pruebarotacion $(OBJ)/pruebarotacion.o -Llib/ -limagen 
	
$(BIN)/pruebapegado: $(OBJ)/pruebapegado.o $(LIB)/libimagen.a
	$(CXX) -o $(BIN)/pruebapegado $(OBJ)/pruebapegado.o -Llib/ -limagen 

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
