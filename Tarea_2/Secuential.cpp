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
#include <string>
using namespace std;

int main(int argc, char* argv[]){

Functions Func;

	string fileData = "dataProximaCentauri.csv";
	int sizeFile = Func.getFileLines(fileData);

	float** spectrumPCentauri;
	string* PCentauriElements;
	PCentauriElements = new string [sizeFile];

	spectrumPCentauri = Func.getFileData(fileData, sizeFile);
	PCentauriElements = Func.getElement(spectrumPCentauri, sizeFile);

	for(int i=0; i<sizeFile; i++){
		// WL [nm], Flux [W/m2/nm]
		cout << "\nWave Length [nm]: " << spectrumPCentauri[i][0] << " Irradiance [W/m2/nm]: " << spectrumPCentauri[i][1] <<endl;
		cout << "Element: ";
		for (int j = 0; j < 15; j++){
			cout << PCentauriElements[i][j];
		}
		cout << endl;
	}
}
