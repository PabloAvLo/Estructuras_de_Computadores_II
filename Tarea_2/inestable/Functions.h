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

//Obtenido de http://www.columbia.edu/~vjd1/Solar%20Spectrum%20Ex.html
//Wavelength de los elementos conocidos
#define Oxygen_WL 	723.05
#define Hydro_a_WL 	656.30
#define Sodium_WL 	589.33
#define Iron_WL 		527.00
#define Hydro_b_WL  486.10
#define Calcium_WL 	393.40

//Tolerancia de wavelength de los elementos conocidos
#define Oxygen_TL 	51.55
#define Hydro_a_TL 	33.35
#define Sodium_TL 	31.30
#define Iron_TL 		21.50
#define Hydro_b_TL  19.40
#define Calcium_TL 	36.65

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
	float* getFileData(string &file, int &size);
};
#endif
