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
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]){

clock_t start;
double duration;
start = clock();

  // Declaro variables para paralelizar
int procs; 												 // Cantidad de procesos a utilizar
int id; 	 												 // Identificador del proceso actaul
int largo; 												 // Longitud del proceso actual
int rc;														 // Grupo al que pertenecen los procesos
char host[MPI_MAX_PROCESSOR_NAME]; // Nombre del proceso principal

	// Inicializo el "Mundo" que contiene los procesos
rc = MPI_Init(&argc, &argv);

MPI_Status stat;

MPI_Comm_size(MPI_COMM_WORLD, &procs);
MPI_Comm_rank(MPI_COMM_WORLD, &id);
MPI_Get_processor_name(host, &largo);

Functions Func;
int oxygen =0;
int hydrogenAlpha =0;
int sodium =0;
int iron =0;
int hydrogenbeta =0;
int calcium =0;
int unknown =0;

	string fileData = "dataProximaCentauri.csv";
	int sizeFile = Func.getFileLines(fileData);

	int procLength = sizeFile/procs; // Cantidad de elementos para cada proceso.

	// Matriz que contiene la longitud de onda e irrandianza de una medicion
	// en cada fila, con un numero "sizeFile" de filas.
	float** spectrumPCentauri;
	spectrumPCentauri = Func.getFileData(fileData, sizeFile);

	// Creamos la sub matriz
	float** procData;
	procData = new float* [procLength];
	for (int i=0; i<procLength; i++){
		procData[i] = new float [2];
	}

	//getElement implementation
	string* PCentauriElements;
	PCentauriElements = new string [sizeFile];

	for (int i = 0; i < sizeFile; i++){
		if ((spectrumPCentauri[i][0] < Oxygen_WL + Oxygen_TL) 			&& (spectrumPCentauri[i][0] > Oxygen_WL - Oxygen_TL)){
			PCentauriElements[i] = "Oxygen";
			oxygen +=1;
		}
		else if ((spectrumPCentauri[i][0] < Hydro_a_WL + Hydro_a_TL) && (spectrumPCentauri[i][0] > Hydro_a_WL - Hydro_a_TL)){
			PCentauriElements[i] = "Hydrogen alpha";
			hydrogenAlpha +=1;
		}
		else if ((spectrumPCentauri[i][0] < Sodium_WL + Sodium_TL) 	&& (spectrumPCentauri[i][0] > Sodium_WL - Sodium_TL)){
			PCentauriElements[i] = "Neutral sodium";
			sodium +=1;
		}
		else if ((spectrumPCentauri[i][0] < Iron_WL + Iron_TL) 			&& (spectrumPCentauri[i][0] > Iron_WL - Iron_TL)){
			PCentauriElements[i] = "Neutral iron";
			iron +=1;
		}
		else if ((spectrumPCentauri[i][0] < Hydro_b_WL + Hydro_b_TL) && (spectrumPCentauri[i][0] > Hydro_b_WL - Hydro_b_TL)){
			PCentauriElements[i] = "Hydrogen beta";
			hydrogenbeta +=1;
		}
		else if ((spectrumPCentauri[i][0] < Calcium_WL + Calcium_TL) && (spectrumPCentauri[i][0] > Calcium_WL - Calcium_TL)){
			PCentauriElements[i] = "Ionized calcium";
			calcium +=1;
		}
		else{
			PCentauriElements[i] = "Unknown element";	//Elemento desconocido o WL no calza dentro de uno de los elementos conocidos
			unknown +=1;
		}
	}

	cout <<endl<< "----Parallel Algorithm STATS----" <<endl<<endl;
	cout <<"     Oxygen:          "<< oxygen << endl;
	cout <<"     Hydrogen Alpha:  "<< hydrogenAlpha << endl;
	cout <<"     Neutral Sodium:  "<< sodium << endl;
	cout <<"     Neutral Iron:    "<< iron << endl;
	cout <<"     Hydrogen Beta:   "<< hydrogenbeta << endl;
	cout <<"     Ionized Calcium: "<< calcium << endl;
	cout <<"     Unknown Element: "<< unknown << endl;

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	cout<<endl<<"     Parallel Time:   "<< duration <<" [s]" <<endl<<endl;

	MPI_Finalize();
	return 0;
}
