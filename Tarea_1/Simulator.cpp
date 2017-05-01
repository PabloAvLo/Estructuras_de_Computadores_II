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

	int contadorHit_L1_1, contadorMiss_L1_1, contadorHit_L2, contadorMiss_L2;
	int contadorHit_L1_2, contadorMiss_L1_2;
	contadorHit_L1_1 = 0;
	contadorMiss_L1_1 = 0;
	contadorHit_L1_2 = 0;
	contadorMiss_L1_2 = 0;
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
	//addrInt[x]
	int** intInstructionsCPU1;
	intInstructionsCPU1 = new int *[3];

	for(int i=0; i< sizeCPU1; i++){
		instructionsCPU1[i][0] = CPU1_L1.hexToBin(instructionsCPU1[i][0]);
		//for (int j=0; j<2 ; j++){
		//}
//		cout <<"Direccion String Binario: "<< instructionsCPU1[i][0] << " Lectura/Escritura: "<< instructionsCPU1 [i][1] <<endl;
	}

	for(int i=0; i< sizeCPU2; i++){
		instructionsCPU2[i][0] =	CPU2_L1.hexToBin(instructionsCPU2[i][0]);
	//	intInstructionsCPU2[i] = CPU2_L1.binToInt(TAG_SIZE_L2, INDEX_SIZE_L2, OFFSET_SIZE_L2, instructionsCPU2[i][0]);

//		cout <<"Direccion String Binario: "<< instructionsCPU2[i][0] << " Lectura/Escritura: "<< instructionsCPU2 [i][1] <<endl;
	}

	cout<<"Misses L1_1="<< contadorMiss_L1_1 <<", Hits L1_1="<< contadorHit_L1_1 <<", Misses L2="<< contadorMiss_L2 <<", Hits L2="<< contadorHit_L2 <<endl;
	cout<<"Misses L1_2="<< contadorMiss_L1_2 <<", Hits L1_2="<< contadorHit_L1_2 <<endl;

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
	int * addrIntCPU1;
	addrIntCPU1 = new int [3];
	int * addrIntCPU2;
	addrIntCPU2 = new int [3];
	int* addrIntL2;
	addrIntL2 = new int [3];

//CPU1 ejecuta 3 instrucciones, luego CPU2 ejecuta 1, y se repite el patron
	for (int h=0; h < 4; h++){
		//CPU actual es el CPU2
		if (h == 3) {
			//cout << "CPU2" << endl;
			h = 0;
			for (int m=0; m<sizeCPU2; m++){
				//casos READ de CPU2
				if (instructionsCPU2[m][1].compare(readS) == 0){
					if (estadoL1_2 == 0){ //invalid
						contadorMiss_L1_2 +=1;
						//if (estadoL1_1 == 0){
							//Revisar si el bloque esta en otro cache como Modified
							if (estadoL1_1 == 2){
								//actualizar dato del otro cache escribiendo
								//addrIntCPU1 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								addrIntL2 = L2.binToInt(TAG_SIZE_L2, INDEX_SIZE_L2, OFFSET_SIZE_L2, instructionsCPU2[m][0]);

								if((addrIntL2[0] == L2.set[m][addrIntL2[1]].tag) && (L2.set[m][addrIntL2[1]].valid == true) && (L2.set[m][addrIntL2[1]].dirty == false)){
									contadorHit_L2 += 1;
								}
								else contadorMiss_L2 += 1;

								for (int p = 0; p < 8; p++){
									CPU2_L1.set[0][addrIntCPU2[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
									CPU1_L1.set[0][addrIntL2[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
								}
								CPU2_L1.set[0][addrIntCPU2[1]].tag = L2.set[0][addrIntL2[1]].tag;
								CPU1_L1.set[0][addrIntL2[1]].tag = L2.set[0][addrIntL2[1]].tag;
								CPU2_L1.set[0][addrIntCPU2[1]].estado = 3;
								CPU1_L1.set[0][addrIntL2[1]].estado = 3;
								estadoL1_1 = 3;
							}

							if (estadoL1_1 == 1){
								addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								for (int p = 0; p < 8; p++){
									//Paso los datos de CPU2 a CPU1
									CPU2_L1.set[0][addrIntCPU1[2]].data[p] = CPU1_L1.set[0][addrIntCPU1[2]].data[p];
								}
								CPU2_L1.set[0][addrIntCPU2[1]].tag = CPU1_L1.set[0][addrIntCPU1[1]].tag;
								CPU2_L1.set[0][addrIntCPU2[1]].estado = 3;
							}

							if (estadoL1_1 == 0){
								addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								addrIntL2 = L2.binToInt(TAG_SIZE_L2, INDEX_SIZE_L2, OFFSET_SIZE_L2, instructionsCPU2[m][0]);

								if((addrIntL2[0] == L2.set[m][addrIntL2[1]].tag) && (L2.set[m][addrIntL2[1]].valid == true) && (L2.set[m][addrIntL2[1]].dirty == false)){
									contadorHit_L2 += 1;
								}
								else contadorMiss_L2 += 1;

								for (int p = 0; p < 8; p++){
									CPU2_L1.set[0][addrIntL2[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
								}
								CPU2_L1.set[0][addrIntCPU2[1]].tag = L2.set[0][addrIntL2[1]].tag;
								CPU2_L1.set[0][addrIntCPU2[1]].estado = 1;
								estadoL1_1 = 1;
							}

							if (estadoL1_1 == 3){
								addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
								for (int p = 0; p < 8; p++){
									CPU2_L1.set[0][addrIntCPU2[2]].data[p] = CPU1_L1.set[0][addrIntCPU1[2]].data[p];
								}
								CPU2_L1.set[0][addrIntCPU2[1]].tag = CPU1_L1.set[0][addrIntCPU1[1]].tag;
								CPU2_L1.set[0][addrIntCPU2[1]].estado = 3;
								estadoL1_1 = 3;
							}
						}

					if (estadoL1_2 == 1){
						contadorHit_L2 +=1;
						estadoL1_2 = 1;
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						else {
							estadoL1_1 = 3;
						}
					}

					if (estadoL1_2 == 2){
						estadoL1_2 = 2;
						contadorMiss_L1_2 +=1;

						//tengo que buscar el dato en el otro cache
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						else {
							estadoL1_1 = 3;
						}
					}

					if (estadoL1_2 == 3){
						contadorHit_L2 +=1;
						estadoL1_2 = 3;
						if (estadoL1_1 == 0){
							estadoL1_1 = 0;
						}
						//Si L1_2 esta en shared, es porque L1_1 esta en shared tambien
						else {
							estadoL1_1 = 3;
						}
					}
				}

				//casos WRITE de CPU2
				if (instructionsCPU2[m][1].compare(writeS) == 0){
						//nuevos estados, iguales independientes de los casos
						estadoL1_1 = 0;
						estadoL1_2 = 2;
						//obtengo tag, index y offset
						addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
						for (int p = 0; p < 8; p++){
							CPU2_L1.set[0][addrIntCPU2[1]].data[p] = addrIntCPU2[2];
						}
						CPU2_L1.set[0][addrIntCPU2[1]].tag = addrIntCPU2[0];
						CPU2_L1.set[0][addrIntCPU2[1]].estado = estadoL1_2;
				}
			}
		}
//-----------------------------------------CPU1
		else {
			for (int i=0; i < sizeCPU1; i++){
				//cout << "ESTADO L1_1: " << estadoL1_1 << endl;
				//cout << "ESTADO L1_2: " << estadoL1_2 << endl;
				//casos READ de CPU1
				if (instructionsCPU1[i][1].compare(readS) == 0){

					if (estadoL1_1 == 0){
						contadorMiss_L1_1 +=1;
						//Revisar si el bloque esta en otro cache como Modified
						if (estadoL1_2 == 2){
							//actualizar dato del otro cache escribiendo
							//addrIntCPU1 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU2[m][0]);
							addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							addrIntL2 = L2.binToInt(TAG_SIZE_L2, INDEX_SIZE_L2, OFFSET_SIZE_L2, instructionsCPU1[i][0]);

							if((addrIntL2[0] == L2.set[i][addrIntL2[1]].tag) && (L2.set[i][addrIntL2[1]].valid == true) && (L2.set[i][addrIntL2[1]].dirty == false)){
								contadorHit_L2 += 1;
							}
							else contadorMiss_L2 += 1;

							for (int p = 0; p < 8; p++){
								CPU1_L1.set[0][addrIntCPU1[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
								CPU2_L1.set[0][addrIntL2[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
							}
							CPU1_L1.set[0][addrIntCPU1[1]].tag = L2.set[0][addrIntL2[1]].tag;
							CPU2_L1.set[0][addrIntL2[1]].tag = L2.set[0][addrIntL2[1]].tag;
							CPU1_L1.set[0][addrIntCPU1[1]].estado = 3;
							CPU2_L1.set[0][addrIntL2[1]].estado = 3;
							estadoL1_2 = 3;
						}

						if (estadoL1_2 == 1){
							addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							for (int p = 0; p < 8; p++){
								//Paso los datos de CPU2 a CPU1
								CPU1_L1.set[0][addrIntCPU1[1]].data[p] = CPU2_L1.set[0][addrIntCPU2[2]].data[p];
							}
							CPU1_L1.set[0][addrIntCPU1[1]].tag = CPU2_L1.set[0][addrIntCPU2[1]].tag;
							CPU1_L1.set[0][addrIntCPU1[1]].estado = 3;
						}

						if (estadoL1_2 == 0){
							addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							addrIntL2 = L2.binToInt(TAG_SIZE_L2, INDEX_SIZE_L2, OFFSET_SIZE_L2, instructionsCPU1[i][0]);

							if((addrIntL2[0] == L2.set[i][addrIntL2[1]].tag) && (L2.set[i][addrIntL2[1]].valid == true) && (L2.set[i][addrIntL2[1]].dirty == false)){
								contadorHit_L2 += 1;
							}
							else contadorMiss_L2 += 1;

							for (int p = 0; p < 8; p++){
								CPU1_L1.set[0][addrIntCPU1[2]].data[p] = L2.set[0][addrIntL2[2]].data[p];
							}
							CPU1_L1.set[0][addrIntCPU1[1]].tag = L2.set[0][addrIntL2[1]].tag;
							CPU1_L1.set[0][addrIntCPU1[1]].estado = 1;
							estadoL1_2 = 1;
						}

						if (estadoL1_2 == 3){
							addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							addrIntCPU2 = CPU2_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
							for (int p = 0; p < 8; p++){
								CPU1_L1.set[0][addrIntCPU1[2]].data[p] = CPU2_L1.set[0][addrIntCPU2[2]].data[p];
							}
							CPU1_L1.set[0][addrIntCPU1[1]].tag = CPU2_L1.set[0][addrIntCPU2[1]].tag;
							CPU1_L1.set[0][addrIntCPU1[1]].estado = 3;
							estadoL1_2 = 3;
						}
					}

//OK
					if (estadoL1_1 == 1){
						contadorHit_L1_1 +=1;
						estadoL1_1 = 1;
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
						}
						else {
							estadoL1_2 = 3;
						}
					}

					if (estadoL1_1 == 2){
						contadorMiss_L1_1 +=1;
						estadoL1_1 = 0;
						if (estadoL1_2 == 0){
							estadoL1_2 = 0;
						}
						else {
							estadoL1_2 = 3;
						}
					}

					if (estadoL1_1 == 3){
						contadorHit_L1_1 +=1;
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
					//nuevos estados, iguales independientes de los casos
					estadoL1_2 = 0;
					estadoL1_1 = 2;
					//obtengo tag, index y offset
					addrIntCPU1 = CPU1_L1.binToInt(TAG_SIZE_L1, INDEX_SIZE_L1, OFFSET_SIZE_L1, instructionsCPU1[i][0]);
					for (int p = 0; p < 8; p++){
						CPU1_L1.set[0][addrIntCPU1[1]].data[p] = addrIntCPU1[2];
					}
					CPU1_L1.set[0][addrIntCPU1[1]].tag = addrIntCPU1[0];
					CPU1_L1.set[0][addrIntCPU1[1]].estado = estadoL1_1;
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
	}
}
