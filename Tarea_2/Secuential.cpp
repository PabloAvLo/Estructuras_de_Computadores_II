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
// Data obtained from: http://vpl.astro.washington.edu/spectra/stellar/proxcen.htm
//*********************************************************************************

#include "Functions.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]){

Functions Func;

	string fileData = "dataProximaCentauri.csv";
	int sizeFile = Func.getFileLines(fileData);

	float** spectrumPCentauri;
	//string* PCentauriElements;
	//PCentauriElements = new string [sizeFile];

	spectrumPCentauri = Func.getFileData(fileData, sizeFile);

	//getElement implementation
	string* PCentauriElements;
	PCentauriElements = new string [sizeFile];

	for (int i = 0; i < sizeFile; i++){
		if ((spectrumPCentauri[i][0] < Oxygen_WL + Oxygen_TL) 			&& (spectrumPCentauri[i][0] > Oxygen_WL - Oxygen_TL))
			PCentauriElements[i] = "Oxygen";
		else if ((spectrumPCentauri[i][0] < Hydro_a_WL + Hydro_a_TL) && (spectrumPCentauri[i][0] > Hydro_a_WL - Hydro_a_TL))
			PCentauriElements[i] = "Hydrogen alpha";
		else if ((spectrumPCentauri[i][0] < Sodium_WL + Sodium_TL) 	&& (spectrumPCentauri[i][0] > Sodium_WL - Sodium_TL))
			PCentauriElements[i] = "Neutral sodium";
		else if ((spectrumPCentauri[i][0] < Iron_WL + Iron_TL) 			&& (spectrumPCentauri[i][0] > Iron_WL - Iron_TL))
			PCentauriElements[i] = "Neutral iron";
		else if ((spectrumPCentauri[i][0] < Hydro_b_WL + Hydro_b_TL) && (spectrumPCentauri[i][0] > Hydro_b_WL - Hydro_b_TL))
			PCentauriElements[i] = "Hydrogen beta";
		else if ((spectrumPCentauri[i][0] < Calcium_WL + Calcium_TL) && (spectrumPCentauri[i][0] > Calcium_WL - Calcium_TL))
			PCentauriElements[i] = "Ionized calcium";
		else
			PCentauriElements[i] = "Unknown element";	//Elemento desconocido o WL no calza dentro de uno de los elementos conocidos
	}

	//PCentauriElements = Func.getElement(spectrumPCentauri, sizeFile);

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
