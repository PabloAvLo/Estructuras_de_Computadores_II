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

#ifndef CACHE_H
#define CACHE_H

class Cache{

public:
	Block** set;
	int LinesNumber;

	Cache(int bytes, int associativity); // Size of cache in bytes, n-way associative
	~Cache();
	
	int getFileLines(string file);
	string** getFileData(string file, int size);
	string hexToBin(string sHex);
	int* binToInt(int tag_size, int index_size, int offset_size, string strBin);	

};
#endif
