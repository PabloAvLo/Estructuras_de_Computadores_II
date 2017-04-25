//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                  Simulator.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30xxx
//*********************************************************************************

#include <iostream>
#include "Block.h"
#include "Cache.h"

#define BLOCK_SIZE 32 // in bytes

//Block bloque1(BLOCK_SIZE);
//Block bloque2(BLOCK_SIZE);

Block bloque1;
Block bloque2;

Cache L1(64000,2);

int main(int argc, char* argv[]){

	bloque2.valid = 1;
	bloque2.tag = 10011;

/*
	std::cout << "Hello World" << std::endl;
	std::cout << "Valid bit bloque 1: " << bloque1.valid << std::endl;
	std::cout << "Tag bloque 1: " << bloque1.tag << std::endl << "Block 1 Data: ";
*/
	std::cout << "Tag bloque 1, set 1: " << L1.set[300][1].data[2] << std::endl;

	/*
	for(int i=0; i<8; i++){
		std::cout << bloque1.data[i];
	}
	std::cout << std::endl;
	std::cout << "Valid bit bloque 2: " << bloque2.valid << std::endl;
	std::cout << "Tag bloque 2: " << bloque2.tag << std::endl;
*/

}