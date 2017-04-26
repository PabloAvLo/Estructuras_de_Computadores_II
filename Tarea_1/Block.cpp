//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                  Block.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include "Block.h"
 
Block::Block(){
	valid = 0;
	tag = 0;
	dirty = 0;

	int words = BLOCK_SIZE/WORD_SIZE;

	data = new int [words];
	
	for(int i=0; i<words; i++){
		data[i] = 0;
	}
}
 
Block::~Block(){
	delete []data;
}
