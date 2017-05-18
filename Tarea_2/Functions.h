//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//               Tarea 2: Paralelizacion de Clustering Data Mining
//                                  I Ciclo 2017
//
//                                  Functions.h
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#define Helium_WL 587.5618 // [nm]

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions{

public:
	Functions();
	~Functions();

// Esta funcion devuelve un int con la cantidad de lineas en un archivo
// @Paramentro file: Archivo el cual se le cuentan las lineas
	int getFileLines(string &file);

// La funcion getfileData devuelve un arreglo de floats, donde la primer posicion
// es la longitud de onda obtenida y el segundo se refiere a la irradianza de esa
// longitud de onda, datos obtenidos con espectroscopia de absorsion.
// @Parametro file: archivo del cual se extrae la informacion.
// @Parametro	size: Numero de lineas del archivo a leer.
	float** getFileData(string &file, int &size);

};
#endif
