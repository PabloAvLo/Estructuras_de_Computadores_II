//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//               Tarea 2: Paralelizacion de Clustering Data Mining
//                                  I Ciclo 2017
//
//                                  Functions.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include "Functions.h"
using namespace std;

//Constructor
Functions::Functions(){}

//Destructor
Functions::~Functions(){}

int Functions::getFileLines(string &file){

	ifstream data(file);
	char c;
	int count = 0;
	while (data.get(c)){
    if (c == '\n'){
        ++count;
    }
  }
	data.close();
	return count;
}

float** Functions::getFileData(string &file, int &size){

	float** dataArray;
	dataArray = new float* [size];

	for (int i=0; i<size; i++){
		dataArray[i] = new float [2];
	}

	string line;
	string waveLenght;
	string irradiance;
	int pos;

	ifstream data(file);

	if(data.is_open()){
		int j=0;

  	while(!data.eof()){ // To get you all the lines.

  		getline(data,line); // Saves the line in STRING.
			pos = line.find(",");

			waveLenght = "";
			irradiance ="";
			if (line.length() > 1){
				for(int i=0; i< pos; i++) {
					waveLenght = waveLenght + line.at(i);
				}
				for(int i=(pos+1); i< ((signed) line.length()); i++) {
					irradiance = irradiance + line.at(i);
			  }

			  dataArray [j][0] = std::stof (waveLenght,nullptr);
			  dataArray [j][1] = std::stof (irradiance,nullptr);

   		}
   		j++;
    }
		data.close();
	}

	return dataArray;
}

string* Functions::getElement(float** dataArray, int &size){
	string* element;
	element = new string [size];

	for (int i = 0; i < size; i++){
		if ((dataArray[i][0] < Oxygen_WL + Oxygen_TL) 			&& (dataArray[i][0] > Oxygen_WL - Oxygen_TL))
			element[i] = "Oxygen";
		else if ((dataArray[i][0] < Hydro_a_WL + Hydro_a_TL) && (dataArray[i][0] > Hydro_a_WL - Hydro_a_TL))
			element[i] = "Hydrogen alpha";
		else if ((dataArray[i][0] < Sodium_WL + Sodium_TL) 	&& (dataArray[i][0] > Sodium_WL - Sodium_TL))
			element[i] = "Neutral sodium";
		else if ((dataArray[i][0] < Iron_WL + Iron_TL) 			&& (dataArray[i][0] > Iron_WL - Iron_TL))
			element[i] = "Neutral iron";
		else if ((dataArray[i][0] < Hydro_b_WL + Hydro_b_TL) && (dataArray[i][0] > Hydro_b_WL - Hydro_b_TL))
			element[i] = "Hydrogen beta";
		else if ((dataArray[i][0] < Calcium_WL + Calcium_TL) && (dataArray[i][0] > Calcium_WL - Calcium_TL))
			element[i] = "Ionized calcium";
		else
			element[i] = "Unknown element";	//Elemento desconocido o WL no calza dentro de uno de los elementos conocidos
	}
	return element;
}
