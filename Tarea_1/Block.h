//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                    Block.h
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30xxx
//*********************************************************************************

#ifndef BLOCK_H
#define BLOCK_H

class Block{

public:
	bool valid;
	bool dirty;
	int tag;
	int *data; // The block is 32B, then contains 8 words of 32b (int type size).

	Block();
	~Block();
};
#endif