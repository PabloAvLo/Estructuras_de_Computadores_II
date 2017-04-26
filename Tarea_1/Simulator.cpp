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
//          Guido Armas B30647
//*********************************************************************************

#include "Cache.h"

#define CACHE_L1_SIZE 16384 //16kB = 2^14 Bytes
#define TAG_SIZE_L1 11 // Bits
#define INDEX_SIZE_L1 8 // Bits
#define OFFSET_SIZE_L1 5  // Bits

#define CACHE_L2_SIZE 131072 // 128kB = 2^17 Bytes
#define TAG_SIZE_L2 7 // Bits
#define INDEX_SIZE_L2 12 // Bits
#define OFFSET_SIZE_L2 5  // Bits

using namespace std;

Cache CPU1_L1(CACHE_L1_SIZE, 2);
Cache CPU2_L1(CACHE_L1_SIZE, 2);
Cache L2(CACHE_L2_SIZE, 1);

int main(int argc, char* argv[]){
//	cout<<"Numero de lineas del cache L1: "<< CPU1_L1.LinesNumber <<endl;	
//	cout<<"Numero de lineas del cache L2: "<< L2.LinesNumber <<endl;
	
	string fileCPU1 = "mem_trace_core1.txt";
	string fileCPU2 = "mem_trace_core2.txt";

	int sizeCPU1 = CPU1_L1.getFileLines(fileCPU1);
	int sizeCPU2 = CPU2_L1.getFileLines(fileCPU2);
	
	string** instructionsCPU1;
	string** instructionsCPU2;

	instructionsCPU1 = CPU1_L1.getFileData(fileCPU1, sizeCPU1);
	instructionsCPU2 = CPU2_L1.getFileData(fileCPU2, sizeCPU2);

/*
		for(int i=0; i<sizeCPU1; i++){
			cout <<"Direccion String Hexadecimal: "<< instructionsCPU1[i][0] << " Lectura/Escritura: "<< instructionsCPU1 [i][1] <<endl; 
		}
*/

	int** AddressCPU1;
	int** AddressCPU2;
	AddressCPU1 = new int* [sizeCPU1];
	AddressCPU2 = new int* [sizeCPU2];

	string hexAddr="";
	
	for(int i=0; i< sizeCPU1; i++){
		hexAddr =	CPU1_L1.hexToBin(instructionsCPU1[i][0]);
		AddressCPU1[i] = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, hexAddr);	
//		cout<<"CPU1   Tag: "<< AddressCPU1[i][0] <<" Index: "<< AddressCPU1[i][1] <<" Offset: "<< AddressCPU1[i][2]<<endl;  
	}
	
	hexAddr="";

	for(int i=0; i< sizeCPU2; i++){
		hexAddr =	CPU2_L1.hexToBin(instructionsCPU1[i][0]);
		AddressCPU2[i] = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, hexAddr);	
//		cout<<"CPU2   Tag: "<< AddressCPU2[i][0] <<" Index: "<< AddressCPU2[i][1] <<" Offset: "<< AddressCPU2[i][2]<<endl;  
	}				
} 

