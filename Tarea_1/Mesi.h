//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                    Mesi.h
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include "Mesi.h"

class Mesi{

public:
	int 	estado;
	bool 	copies;
	bool	ubicacion;
	char	evento;

	Mesi(int estado, char evento, int * vdArray);
	~Mesi();
}
