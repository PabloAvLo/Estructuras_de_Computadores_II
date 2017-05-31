//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//               Tarea 2: Paralelizacion de Clustering Data Mining
//                                  I Ciclo 2017
//
//                                 Parallel.cpp
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
#include <thread>
using namespace std;

void clustering(float* procData, float elements[], int x, int length){
	// La siguiente funcionalidad devuelve un arreglo de strings, compuesto por los
	// nombres de los elementos encontrados al procesar los datos de Wavelength
	for (int i = x*length; i < ((x+1)*length+1); i++){
		if ((procData[i] < Oxygen_WL + Oxygen_TL) 			&& (procData[i] > Oxygen_WL - Oxygen_TL)){
			elements[0] +=1;
		}
		else if ((procData[i] < Hydro_a_WL + Hydro_a_TL) && (procData[i] > Hydro_a_WL - Hydro_a_TL)){
			elements[1] +=1;
		}
		else if ((procData[i] < Sodium_WL + Sodium_TL) 	&& (procData[i] > Sodium_WL - Sodium_TL)){
			elements[2] +=1;
		}
		else if ((procData[i] < Iron_WL + Iron_TL) 			&& (procData[i] > Iron_WL - Iron_TL)){
			elements[3] +=1;
		}
		else if ((procData[i] < Hydro_b_WL + Hydro_b_TL) && (procData[i] > Hydro_b_WL - Hydro_b_TL)){
			elements[4] +=1;
		}
		else if ((procData[i] < Calcium_WL + Calcium_TL) && (procData[i] > Calcium_WL - Calcium_TL)){
			elements[5] +=1;
		}
		else{
			elements[6] +=1;
		}
	}
}

int main(int argc, char* argv[]){

	// Contador de tiempos se inicia para indicar el tiempo de ejecucion final
	clock_t start;
	double duration;
	start = clock();

	Functions Func;
	int sizeFile;

	//Archivo a leer
	string fileData = "dataProximaCentauri.csv";
	sizeFile = Func.getFileLines(fileData);
	int procLength = sizeFile/4; // Cantidad de elementos para cada proceso.

	// Arreglo que contiene la longitud de onda de una medicion
	// en cada fila, con un numero "sizeFile" de filas.
	float* spectrumPCentauri;

	// Se cuentan las lineas del archivo
	spectrumPCentauri = Func.getFileData(fileData, sizeFile);

	float elements1[7];
	float elements2[7];
	float elements3[7];
	float elements4[7];

	// Se inicializan los vectores a usar por cada thread
	for(int i=0; i<7; i++){
		elements1[i] =0;
		elements2[i] =0;
		elements3[i] =0;
		elements4[i] =0;
	}

	// Se divide la lectura de las longitudes de ondas en 4 threads
	std::thread first(clustering, spectrumPCentauri, elements1,0, procLength);
	std::thread second(clustering, spectrumPCentauri,elements2, 1, procLength);
	std::thread third(clustering, spectrumPCentauri, elements3,2, procLength);
	std::thread fourth(clustering, spectrumPCentauri,elements4, 3, procLength);

	// Se indica que se ha terminado el threading y se pueden destruir los threads
	first.join();
	second.join();
	third.join();
	fourth.join();

	// Concatenacion de los datos de los 4 threads en uno solo (elements1)
	for(int i=0; i<7; i++){
		elements1[i] += elements2[i] + elements3[i] + elements4[i];
	}

	// Despliegue de elementos encontrados y tiempo de ejecucion
	cout <<endl<< "----Parallel Algorithm STATS----" <<endl<<endl;
	cout <<"     Oxygen:          "<< elements1[0] << endl;
	cout <<"     Hydrogen Alpha:  "<< elements1[1] << endl;
	cout <<"     Neutral Sodium:  "<< elements1[2] << endl;
	cout <<"     Neutral Iron:    "<< elements1[3] << endl;
	cout <<"     Hydrogen Beta:   "<< elements1[4] << endl;
	cout <<"     Ionized Calcium: "<< elements1[5] << endl;
	cout <<"     Unknown Element: "<< elements1[6] << endl;

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	cout<<endl<<"     Total Parallel Time:   "<< duration <<" [s]" <<endl<<endl;

	return 0;
}
