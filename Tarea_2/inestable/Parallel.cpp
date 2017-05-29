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
	clock_t start_Parallel;
	double duration;
	double duration_Parallel;
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
	int sizeFile;

	//Archivo a leer
	string fileData = "dataProximaCentauri.csv";
	sizeFile = Func.getFileLines(fileData);
	int procLength = sizeFile/procs; // Cantidad de elementos para cada proceso.

	// Se hace una arraglo clasificando cada medicion como un elemento quimico
	string PCentauriElements[sizeFile];
	float procData[procLength+1];

		// Arreglo que contiene la longitud de onda de una medicion
		// en cada fila, con un numero "sizeFile" de filas.
		float* spectrumPCentauri;

		//Se cuentan las lineas del archivo
		spectrumPCentauri = Func.getFileData(fileData, sizeFile);
	MPI_Scatter(spectrumPCentauri, procLength, MPI_FLOAT, &procData, procLength, MPI_FLOAT, 0, MPI_COMM_WORLD);

	start_Parallel = clock();
	int oxygen =0;
	int hydrogenAlpha =0;
	int sodium =0;
	int iron =0;
	int hydrogenbeta =0;
	int calcium =0;
	int unknown =0;

	// La siguiente funcionalidad devuelve un arreglo de strings, compuesto por los
	// nombres de los elementos encontrados al procesar los datos de Wavelength
	for (int i = 0; i < procLength; i++){
		if ((procData[i] < Oxygen_WL + Oxygen_TL) 			&& (procData[i] > Oxygen_WL - Oxygen_TL)){
			PCentauriElements[i] = "Oxygen";
			oxygen +=1;
		}
		else if ((procData[i] < Hydro_a_WL + Hydro_a_TL) && (procData[i] > Hydro_a_WL - Hydro_a_TL)){
			PCentauriElements[i] = "Hydrogen alpha";
			hydrogenAlpha +=1;
		}
		else if ((procData[i] < Sodium_WL + Sodium_TL) 	&& (procData[i] > Sodium_WL - Sodium_TL)){
			PCentauriElements[i] = "Neutral sodium";
			sodium +=1;
		}
		else if ((procData[i] < Iron_WL + Iron_TL) 			&& (procData[i] > Iron_WL - Iron_TL)){
			PCentauriElements[i] = "Neutral iron";
			iron +=1;
		}
		else if ((procData[i] < Hydro_b_WL + Hydro_b_TL) && (procData[i] > Hydro_b_WL - Hydro_b_TL)){
			PCentauriElements[i] = "Hydrogen beta";
			hydrogenbeta +=1;
		}
		else if ((procData[i] < Calcium_WL + Calcium_TL) && (procData[i] > Calcium_WL - Calcium_TL)){
			PCentauriElements[i] = "Ionized calcium";
			calcium +=1;
		}
		else{
			PCentauriElements[i] = "Unknown element";	//Elemento desconocido o WL no calza dentro de uno de los elementos conocidos
			unknown +=1;
		}
	}

	int *oxygenT;
	int *hydrogenAlphaT;
	int *sodiumT;
	int *ironT;
	int *hydrogenbetaT;
	int *calciumT;
	int *unknownT;

	if(id == 0) {
		oxygenT 			 = new int;
		hydrogenAlphaT = new int;
		sodiumT 			 = new int;
		ironT 				 = new int;
		hydrogenbetaT  = new int;
		calciumT 			 = new int;
		unknownT 			 = new int;
	}

	MPI_Reduce(&oxygen, oxygenT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&hydrogenAlpha, hydrogenAlphaT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&sodium, sodiumT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&iron, ironT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&hydrogenbeta, hydrogenbetaT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&calcium, calciumT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&unknown, unknownT, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Finalize();
	if(id==0){
		cout <<endl<< "----Parallel Algorithm STATS----" <<endl<<endl;
		cout <<"     Oxygen:          "<< *oxygenT << endl;
		cout <<"     Hydrogen Alpha:  "<< *hydrogenAlphaT << endl;
		cout <<"     Neutral Sodium:  "<< *sodiumT << endl;
		cout <<"     Neutral Iron:    "<< *ironT << endl;
		cout <<"     Hydrogen Beta:   "<< *hydrogenbetaT << endl;
		cout <<"     Ionized Calcium: "<< *calciumT << endl;
		cout <<"     Unknown Element: "<< *unknownT << endl;

		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		cout<<endl<<"     Parallel Time:   "<< duration <<" [s]" <<endl<<endl;
		duration_Parallel = ( std::clock() - start_Parallel ) / (double) CLOCKS_PER_SEC;
		cout<<endl<<"     Parallel Time:   "<< duration_Parallel <<" [s]" <<endl<<endl;
	}
	return 0;
}
