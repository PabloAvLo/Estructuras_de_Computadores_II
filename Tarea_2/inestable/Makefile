#*********************************************************************************
#                           Universidad de Costa Rica
#                   Estructuras de Computadores Digitales II
#               Tarea 2: Paralelizacion de Clustering Data Mining
#                                  I Ciclo 2017
#
#                                   Makefile
#
# Prof: Francisco Rivera
# Authors: Pablo Avila B30724
#          Guido Armas B30647
#*********************************************************************************

OBJS_1= Secuential.cpp Functions.cpp Functions.h
OBJS_2= Parallel.cpp Functions.cpp Functions.h

CC_1=g++ -std=c++0x

TARGET_1 = Secuential
TARGET_2 = Parallel

all: $(TARGET_1) $(TARGET_2)

$(TARGET_1): $(OBJS_1)
	$(CC_1) -o $(TARGET_1) $(OBJS_1)

$(TARGET_2): $(OBJS_2)
	$(CC_1) $(OBJS_2) -o $(TARGET_2) -lpthread
run:
	./$(TARGET_1)
	./$(TARGET_2)

clean:
	rm -f -R *.o *.out *~ *.db *.aux *.gch *.log $(TARGET_1) $(TARGET_2)
