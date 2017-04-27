//*********************************************************************************
//                           Universidad de Costa Rica
//                   Estructuras de Computadores Digitales II
//                          Tarea 1: Simulador de Cache
//                                  I Ciclo 2017
//
//                                  mesi.cpp
//
// Prof: Francisco Rivera
// Authors: Pablo Avila B30724
//          Guido Armas B30647
//*********************************************************************************

#include <iostream>
#include <string>
#include "Mesi.h"
using namespace std;

Mesi::Mesi(int estado, bool copies, bool ubicacion, string evento){

//Inicializar estado en invalido
	estado = 0;

//Definicion de variables
	copies = false;
	ubicacion = false;

//La variable evento esta compuesta de la manera n-OP
//n: indica de cual CPU viene la instruccion
//O: indica la operacion solicitada, L o S
	evento = "00";
}

//Descripcion:
//Esta funcion se encarga de implementar dos FSM, dependiendo
//de si el request de read/write es local o remoto.

//Variables usadas:
//ubicacion: false/request local, true/request remoto. Usado para decidir cual
//flujo de FSM usar
//copies: false/no hay copias en otros caches, true/hay copias en otros caches.
//Usado para indicar si hay copias del dato presente en el cache
//estado: variable entera, indica el estado de la linea de cache, de la forma:
//0/Invalido, 1/Exclusivo, 2/Modificado, 3/Scompartido
//evento: caracter, L/lectura, S/escritura
//contadorRead/Write: constantes utilizadas para calcular el hit/miss rate

//Eventos:
//read: se quiere leer una linea del cache
//write: se quiere escribir a una linea del cache

//Salidas:
//La funcion retorna la variable estado, con el estado de la linea de cache


int contadorRead, contadorWrite;

contadorRead = 0;
contadorWrite = 0;

int estadoMESI (char evento) {

	if (estado = 0){
		copies = 0;
	}
	else {
		copies = 1;
	}

	int cpu_counter = 0;

//ALternar el uso de los cpus, cpu1 x3, cpu2 x1, cpu1 x3, cpu2 x1 ...
	if (cpu_counter = 4) {
		cpu_counter = 0;
	}
	else {
		if (cpu_counter == 3) {
			procesador = 2;
			cpu_counter = cpu_counter + 1;
		}
		else {
			procesador = 1;
			cpu_counter = cpu_counter + 1;
		}
	}

	int cacheL1_1 = 1;
	int cacheL1_2 = 2;

	if (procesador = cacheL1_1)
		ubicacion = false; 	//request local
	else
		ubicacion = true;

	if (ubicacion){
		//Request remoto
		//Analizo el estado presente para hallar el proximo estado
		//El proximo estado depende de estado y de eventos (L/S)
		switch (estado) {
			case 0:
				if (evento.at(1) = 'L'){
					contadorRead = contadorRead + 1;
					estado = 0;
				}
				else {
					contadorWrite = contadorWrite + 1;
					estado = 0;
				}
			break;
			case 1:
				if (evento.at(1) == 'L'){
					estado = 3;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 0;
					contadorWrite = contadorWrite + 1;
				}
			break;
			case 2:
				if (evento.at(1) == 'L') {
					estado = 3;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 0;
					contadorWrite = contadorWrite + 1;
				}
			break;
			case 3:
				if (evento.at(1) == 'L') {
					estado == 3;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 0;
					contadorWrite = contadorWrite + 1;
				}
			break;
			default:
				estado = 0;
			break;
		}
	}

	else {
		//Request local
		switch (estado) {
			case 0:
				if (evento.at(1) == 'L'){
					if (copies) {
					//Lectura y ya hay copias del dato en otro cache
						estado = 3;
						contadorRead = contadorRead + 1;
					}
					//Exclusivo, no habian copias del dato en caches
					else {
						estado = 1;
						contadorWrite = contadorWrite + 1;
					}
				}
				estado = 2;
			break;
			case 1:
				if (evento.at(1) == 'L'){
					estado = 1;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 2;
					contadorWrite = contadorWrite + 1;
				}
			break;
			case 2:
				if (evento.at(1) == 'L'){
					estado = 2;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 2;
					contadorWrite = contadorWrite + 1;
				}
			break;
			case 3:
				if (evento.at(1) == 'L'){
					estado == 3;
					contadorRead = contadorRead + 1;
				}
				else {
					estado = 2;
					contadorWrite = contadorWrite + 1;
				}
			break;
			default:
				estado = 0;
			break;
		}
	}

  //trslacion de estados mesi a bits de valid y dirty
 switch (estado) {
   case 0:
      valid = 0;
    break;

    case 1:
        valid = 1;
        dirty = 0;
    break;

    case 2:
        dirty = 1;
    break;

    case 3:
        valid = 1;
        dirty = 0;
    break;
 }

	return estado;
}

//Destructor
Mesi::~Mesi(){
	delete estado;
}
