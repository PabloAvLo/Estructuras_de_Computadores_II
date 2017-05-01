//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                    Cache.h
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include "Block.h"

#define CACHE_L1_SIZE 16384 //16kB = 2^14 Bytes
#define TAG_SIZE_L1 11 // Bits
#define INDEX_SIZE_L1 8 // Bits
#define OFFSET_SIZE_L1 5  // Bits

#define CACHE_L2_SIZE 131072 // 128kB = 2^17 Bytes
#define TAG_SIZE_L2 7 // Bits
#define INDEX_SIZE_L2 12 // Bits
#define OFFSET_SIZE_L2 5  // Bits

#ifndef CACHE_H
#define CACHE_H

class Cache{

public:
	Block** set;
	int LinesNumber;
	int associativity;

	Cache(int bytes, int associativity); // Size of cache in bytes, n-way associative
	~Cache();

// Esta funcion devuelve un int con la cantidad de lineas en un archivo
// @Paramentro file: Archivo el cual se le cuentan las lineas
	int getFileLines(string &file);

// La funcion getfileData devuelve un arreglo de strings, donde la primer posicion
// es el valor hexadecimal en formato string de la direccion y el segundo se refiere
// a la instriccion a realizar (Lectura o eScritura).
// @Parametro file: archivo del cual se extra la informacion.
// @Parametro	size: Numero de lineas del archivo a leer.
	string** getFileData(string &file, int &size);

// hexToBin Convierte strings de numeros hexadecimales, a strings de numero binarios.
// @Parametro sHex: String con numero hexadecimal.
	string hexToBin(string &sHex);

// binToInt Convierte un string con un numero binario, a un arreglo de enteros
// addrInt[3].
// addrInt[0]: Tag de la direccion recibida.
// addrInt[1]: Index de la direccion recibida.
// addrInt[2]: Offset de la direccion recibida.
// @Parametro tag_size: Tamano destinado al tag de la direccion en cache.
// @Parametro index_size: Tamano destinado al index de la direccion en cache.
// @Parametro offset_size: Tamano destinado al offset de la direccion en cache.
	int* binToInt(int tag_size, int index_size, int offset_size, string &strBin);

};
#endif
