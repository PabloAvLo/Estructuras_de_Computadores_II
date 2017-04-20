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
int tag;
int data [8]; // The block is 32B, then contains 8 words of 32b (int type size).


Block();
~Block();

// return_type function_name(const type parameter1, type paramter2...);
};
#endif
