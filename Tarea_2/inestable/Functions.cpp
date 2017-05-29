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

float* Functions::getFileData(string &file, int &size){

	float* dataArray;
	dataArray = new float [size];

	string line;
	string waveLenght;
	int pos;

	ifstream data(file);

	if(data.is_open()){
		int j=0;

  	while(!data.eof()){ // To get you all the lines.

  		getline(data,line); // Saves the line in STRING.
			pos = line.find(",");

			waveLenght = "";
			if (line.length() > 1){
				for(int i=0; i< pos; i++) {
					waveLenght = waveLenght + line.at(i);
				}
			  dataArray [j] = std::stof (waveLenght,nullptr);
   		}
   		j++;
    }
		data.close();
	}

	return dataArray;
}
