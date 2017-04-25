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
//          Guido Armas B30xxx
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

};
#endif
