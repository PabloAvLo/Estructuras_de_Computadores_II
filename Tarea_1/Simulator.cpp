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

using namespace std;

Cache L1(64000,2);

int main(int argc, char* argv[]){
	
	string fileCPU1 = "mem_trace_core1.txt";
	string fileCPU2 = "mem_trace_core2.txt";

	int sizeCPU1 = L1.getFileLines(fileCPU1);
	int sizeCPU2 = L1.getFileLines(fileCPU2);
	
	string** instructionsCPU1;
	string** instructionsCPU2;

	instructionsCPU1 = L1.getFileData(fileCPU1, sizeCPU1);
	instructionsCPU2 = L1.getFileData(fileCPU2, sizeCPU2);

/*
	for(int i=0; i<sizeCPU1; i++){
		cout <<"Direccion String Hexadecimal: "<< instructionsCPU1[i][0] << " Lectura/Escritura: "<< instructionsCPU1 [i][1] <<endl; 
	}
*/

string hexAddr;

int** Address;
Address = new int* [sizeCPU1];

	for(int i=0; i< sizeCPU1; i++){
	
		hexAddr =	L1.hexToBin(instructionsCPU1[i][0]);
		Address[i] = L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, hexAddr);	
		
		cout<<"Tag: "<< Address[i][0] <<" Index: "<< Address[i][1] <<" Offset: "<< Address[i][2]<<endl;  
	}		
} 

