//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//               Tarea 2: Paralelizacion de Clustering Data Mining
//                                  I Ciclo 2017
//
//                                 Secuential.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//
// Data obtained of: http://vpl.astro.washington.edu/spectra/stellar/proxcen.htm
//*********************************************************************************

#include "Functions.h"
using namespace std;

int main(int argc, char* argv[]){

Functions Func;

	string fileData = "dataProximaCentauri.csv";
	float** spectrumPCentauri;

	int sizeFile = Func.getFileLines(fileData);
	spectrumPCentauri = Func.getFileData(fileData, sizeFile);

	for(int i=0; i<sizeFile; i++){
		// WL [nm], Flux [W/m2/nm]
		cout <<"Wave Length [nm]: "<< spectrumPCentauri[i][0] << " Irradiance [W/m2/nm]: "<< spectrumPCentauri[i][1] <<endl;
	}
}
