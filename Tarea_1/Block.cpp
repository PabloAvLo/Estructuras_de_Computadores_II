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
//          Guido Armas B30xxx
//*********************************************************************************

#include "Block.h"
 
#define WORD_SIZE 32   // In bits
#define BLOCK_SIZE 32  // In Bytes
#define BYTE 8
 
Block::Block(){
	valid = 0;
	tag = 0;
	dirty = 0;

	int words = (BLOCK_SIZE*BYTE)/WORD_SIZE;

	data = new int [words];
	
	for(int i=0; i<words; i++){
		data[i] = 0;
	}
}
 
Block::~Block(){
	delete []data;
}
