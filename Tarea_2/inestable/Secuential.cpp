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
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){

clock_t start;
double duration;
start = clock();

Functions Func;

//Archivo a leer
string fileData = "dataProximaCentauri.csv";

//Se cuentan las lineas del archivo
int sizeFile = Func.getFileLines(fileData);

// Arreglo que contiene la longitud de onda de una medicion
// en cada fila, con un numero "sizeFile" de filas.
float* spectrumPCentauri;
spectrumPCentauri = Func.getFileData(fileData, sizeFile);

// Se hace una arraglo clasificando cada medicion como un elemento quimico
string PCentauriElements[sizeFile];

int oxygen =0;
int hydrogenAlpha =0;
int sodium =0;
int iron =0;
int hydrogenbeta =0;
int calcium =0;
int unknown =0;

	for (int i = 0; i < sizeFile; i++){
		if ((spectrumPCentauri[i] < Oxygen_WL + Oxygen_TL) 		  	&& (spectrumPCentauri[i] > Oxygen_WL - Oxygen_TL)){
			PCentauriElements[i] = "Oxygen";
			oxygen +=1;
		}
		else if ((spectrumPCentauri[i] < Hydro_a_WL + Hydro_a_TL) && (spectrumPCentauri[i] > Hydro_a_WL - Hydro_a_TL)){
			PCentauriElements[i] = "Hydrogen alpha";
			hydrogenAlpha +=1;
		}
		else if ((spectrumPCentauri[i] < Sodium_WL + Sodium_TL) 	&& (spectrumPCentauri[i] > Sodium_WL - Sodium_TL)){
			PCentauriElements[i] = "Neutral sodium";
			sodium +=1;
		}
		else if ((spectrumPCentauri[i] < Iron_WL + Iron_TL) 			&& (spectrumPCentauri[i] > Iron_WL - Iron_TL)){
			PCentauriElements[i] = "Neutral iron";
			iron +=1;
		}
		else if ((spectrumPCentauri[i] < Hydro_b_WL + Hydro_b_TL) && (spectrumPCentauri[i] > Hydro_b_WL - Hydro_b_TL)){
			PCentauriElements[i] = "Hydrogen beta";
			hydrogenbeta +=1;
		}
		else if ((spectrumPCentauri[i] < Calcium_WL + Calcium_TL) && (spectrumPCentauri[i] > Calcium_WL - Calcium_TL)){
			PCentauriElements[i] = "Ionized calcium";
			calcium +=1;
		}
		else{
			PCentauriElements[i] = "Unknown element";	//Elemento desconocido o WL no calza dentro de uno de los elementos conocidos
			unknown +=1;
		}
	}

	// for(int i=0; i<sizeFile; i++){
	// 	// WL [nm], Flux [W/m2/nm]
	// 	cout << "\nWave Length [nm]: " << spectrumPCentauri[i]<<endl;
	// 	cout << "Element: ";
	// 		cout << PCentauriElements[i]<<endl;
	// }

	cout <<endl<< "-----Serial Algorithm STATS-----" <<endl<<endl;
	cout <<"     Oxygen:          "<< oxygen << endl;
	cout <<"     Hydrogen Alpha:  "<< hydrogenAlpha << endl;
	cout <<"     Neutral Sodium:  "<< sodium << endl;
	cout <<"     Neutral Iron:    "<< iron << endl;
	cout <<"     Hydrogen Beta:   "<< hydrogenbeta << endl;
	cout <<"     Ionized Calcium: "<< calcium << endl;
	cout <<"     Unknown Element: "<< unknown << endl;

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	cout<<endl<<"     Total Serial Time:     "<< duration <<" [s]" <<endl<<endl;
	return 0;
}
