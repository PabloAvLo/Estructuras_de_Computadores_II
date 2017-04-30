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

Cache CPU1_L1(CACHE_L1_SIZE, 2);
Cache CPU2_L1(CACHE_L1_SIZE, 2);
Cache L2(CACHE_L2_SIZE, 1);

int main(int argc, char* argv[]){

	int contadorHit_L1, contadorMiss_L1, contadorHit_L2, contadorMiss_L2;
	contadorHit_L1 = 0;
	contadorMiss_L1 = 0;
	contadorHit_L2 = 0;
	contadorMiss_L2 = 0;

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

	for(int i=0; i< sizeCPU1; i++){
		instructionsCPU1[i][0] =	CPU1_L1.hexToBin(instructionsCPU1[i][0]);
//		cout <<"Direccion String Binario: "<< instructionsCPU1[i][0] << " Lectura/Escritura: "<< instructionsCPU1 [i][1] <<endl;
	}

	for(int i=0; i< sizeCPU2; i++){
		instructionsCPU2[i][0] =	CPU2_L1.hexToBin(instructionsCPU2[i][0]);
//		cout <<"Direccion String Binario: "<< instructionsCPU2[i][0] << " Lectura/Escritura: "<< instructionsCPU2 [i][1] <<endl;
	}

	int miss_hit_leido =CPU1_L1.read(instructionsCPU2[1][0], L2);

	switch (miss_hit_leido){
		case '0': contadorMiss_L1 +=1; contadorMiss_L2 +=1;
		case '1': contadorHit_L1 +=1;
		case '2': contadorHit_L2 +=1; contadorMiss_L1 +=1;
		default : contadorMiss_L1 +=1; contadorMiss_L2 +=1;
	}

	cout<<"Misses L1="<< contadorMiss_L1 <<", Hits L1="<< contadorHit_L1 <<", Misses L2="<< contadorMiss_L1 <<", Hits L2="<< contadorHit_L1 <<endl;

//Maquina de estados mesi
//Determinar el estado Mesi
//Iincializar en el estado invalido, sin copias de un dato en ningun cache
	int estadoL1_1 = 0;
	int estadoL1_2 = 0;
	bool copies_L1 = false;
	bool copies_L2 = false;
	int* validDirtyL1_1;
	int* validDirtyL1_2;
	validDirtyL1_1 = new int [2];
	validDirtyL1_2 = new int [2];
	string readS = "L";
	string writeS = "S";

//CPU1 ejecuta 3 instrucciones, luego CPU2 ejecuta 1, y se repite el patron
	for (int h=0; h < 3; h++){
		//CPU actual es el CPU2
		if (h == 3) {
			h = 0;
			for (int m=0; m<sizeCPU2; m++){
				//casos READ de CPU2
				if (instructionsCPU2[m][1].compare(readS) == 0){
					if (estadoL1_2 == 0){
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
							if (copies_L2 == false){
								estadoL1_2 = 1;
							}
							else {
								estadoL1_2 = 3;
							}
						}
						else {
							estadoL1_1 = 3;
						}
					}

					if (estadoL1_2 == 1){
						estadoL1_2 = 1;
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						else {
							estadoL1_1 = 3;
						}
					}

					if (estadoL1_2 == 2){
						estadoL1_2 = 0;
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						else {
							estadoL1_1 = 3;
						}
					}

					if (estadoL1_2 == 3){
						estadoL1_2 = 3;
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						else {
							estadoL1_1 = 3;
						}
					}
				}
				//casos WRITE de CPU2
				if (instructionsCPU2[m][1].compare(writeS) == 0){
					estadoL1_1 = 0;
					estadoL1_2 = 2;
				}
			}
		}

		else {
			for (int i=0; i < sizeCPU1; i++){
				//casos READ de CPU1
				if (instructionsCPU1[i][1].compare(readS) == 0){
					if (estadoL1_1 == 0){
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
							if (copies_L1 == false){
								estadoL1_1 = 1;
							}
							else {
								estadoL1_1 = 3;
							}
						}
						else {
							estadoL1_2 = 3;
						}
					}

					if (estadoL1_1 == 1){
						estadoL1_1 = 1;
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
						}
						else {
							estadoL1_2 = 3;
						}
					}

					if (estadoL1_1 == 2){
						estadoL1_1 = 0;
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
						}
						else {
							estadoL1_2 = 3;
						}
					}

					if (estadoL1_1 == 3){
						estadoL1_1 = 3;
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
						}
						else {
							estadoL1_2 = 3;
						}
					}
				}

				//casos WRITE de CPU1
				if (instructionsCPU1[i][1].compare(writeS) == 0){
					estadoL1_2 = 0;
					estadoL1_1 = 2;
				}
			}
		}

		//Determinar el valor de copies, hay copias en todo caso excepto
		//cuando el dato es invalido
		if (estadoL1_1 == 0){
			copies_L1 = 0;
		}
		else {
			copies_L1 = 1;
		}

		if (estadoL1_2 == 0){
			copies_L2 = 0;
		}
		else {
			copies_L2 = 1;
		}

		//Traslacion de estados MESI a bits de valid y dirty
		//validDirtyL1_1[0] = bit de valido de L1_1 / validDirtyL1_1[1] = bit de dirty de L1_2
		validDirtyL1_1 = CPU1_L1.mesiToValidDirty(estadoL1_1);
		validDirtyL1_2 = CPU2_L1.mesiToValidDirty(estadoL1_2);
	}
}
