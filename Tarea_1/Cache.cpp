//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                  Cache.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30xxx
//*********************************************************************************

#include "Cache.h"
#include "Block.h"

Cache::Cache(int bytes, int associativity){

	LinesNumber = 900; // tenemos que calcularlo 
	set = new Block* [LinesNumber]; 
	
	for (int i=0; i<LinesNumber; i++){
		set[i] = new Block [associativity];	

		for (int j=0; j<associativity; j++){
			set [i][j].data[2] = 590;
		}
	}
}
	
	
//Destructor
Cache::~Cache(){
	for (int i=0; i < LinesNumber; i++){
		delete[] set [i];
	}
	delete[] set;
}
