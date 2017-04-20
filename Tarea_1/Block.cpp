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

Block::Block(){
	valid = 0;
	tag = 0;
	
	for(int i=0; i<8; i++){
		data[i] = 0;
	}
}
 
Block::~Block(){}
