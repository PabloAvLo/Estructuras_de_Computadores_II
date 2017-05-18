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
