//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                  Cache.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include "Cache.h"

Cache::Cache(int bytes, int associativity){

	LinesNumber = bytes/ (BLOCK_SIZE * associativity); 

	set = new Block* [LinesNumber]; 
	
	for (int i=0; i<LinesNumber; i++){
		set[i] = new Block [associativity];	

		for (int j=0; j<associativity; j++){
			set [i][j].data[2] = 590;
		}
	}
}
	
	
//Destructor
Cache::~Cache(){
	for (int i=0; i < LinesNumber; i++){
		delete[] set [i];
	}
	delete[] set;
}


int Cache::getFileLines(string file){
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

string** Cache::getFileData(string file, int size){

	string** dataArray;
		
	dataArray = new string* [size];
	for (int i=0; i<size; i++){
		dataArray[i] = new string [2];
	}

	string line;
	string hexa;	

	ifstream data(file);
	
	if(data.is_open()){ 
		int j=0;
  	
  	while(!data.eof()){ // To get you all the lines.
  
  		getline(data,line); // Saves the line in STRING.      
			hexa = "";
			if (line.length() > 1){
				for(int i=2; i< ( line.length() -3); i++) {				
					hexa = hexa + line.at(i);  
			  }
			  
			  // int value = stoi(hexa, nullptr,16);
			  dataArray [j][0] = hexa;
			  dataArray [j][1] = line.at(line.length() -2);
			 
   		}
   		j++;
    }
		data.close();
	}	

return dataArray;
}

string Cache::hexToBin(string sHex){
	string sReturn = "";
	
	while (sHex.length() < 6){
			sHex = "0" + sHex;
	}
	
	for (int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
			case '0': sReturn.append ("0000"); break;
			case '1': sReturn.append ("0001"); break;
			case '2': sReturn.append ("0010"); break;
			case '3': sReturn.append ("0011"); break;
			case '4': sReturn.append ("0100"); break;
			case '5': sReturn.append ("0101"); break;
			case '6': sReturn.append ("0110"); break;
			case '7': sReturn.append ("0111"); break;
			case '8': sReturn.append ("1000"); break;
			case '9': sReturn.append ("1001"); break;
			case 'A': sReturn.append ("1010"); break;
			case 'B': sReturn.append ("1011"); break;
			case 'C': sReturn.append ("1100"); break;
			case 'D': sReturn.append ("1101"); break;
			case 'E': sReturn.append ("1110"); break;
			case 'F': sReturn.append ("1111"); break;
			default : sReturn.append ("0000"); break;
		}
	}
return sReturn;
}

int* Cache::binToInt(int tag_size, int index_size, int offset_size, string strBin){

	int* addrInt;
	addrInt = new int [3];

	//Asigno los tamanos de tag, index y offset basados en el str binary
	string tag_bin = strBin.substr(0,tag_size);
	string index_bin = strBin.substr(tag_size , index_size);
	string offset_bin = strBin.substr(tag_size + index_size , offset_size);

	int tag_dec = std::stoi(tag_bin, nullptr , 2);
	int index_dec = std::stoi(index_bin, nullptr , 2);
	int offset_dec = std::stoi(offset_bin, nullptr , 2);
	
	addrInt[0] = tag_dec;
	addrInt[1] = index_dec;
	addrInt[2] = offset_dec;
	
return addrInt;
}

