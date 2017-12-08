#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "nodo.h"

#ifndef CAMINO_H
#define CAMINO_H


typedef enum Direccion Direccion;
enum Direccion
{
    N = 0, NE = 1, E = 2, SE = 3, S = 4, SO = 5, O = 6, NO = 7
};

//Orientacion que tiene el robot para ir de una casilla a la siguiente
//la lista de referencia corresponde a las direcciones no intentadas desde una casilla
typedef struct Orientacion{
    Direccion direccion;
    Direccion direccionIdeal;
    //i y j permiten avenzar en la buena direccion
    int i;
    int j;
    Direccion* listaReferencia;
    int tamanoListReferencia;
}Orientacion;

//Lista vinculada
typedef struct LV_Nodo{
    Nodo *nodo;
    Orientacion* orientacion;
    struct LV_Nodo *siguiente;
}LV_Nodo;

//Lista vinculada
typedef struct Camino{
	LV_Nodo *primero;
	int largo;
	struct Camino *siguiente;
}Camino;


LV_Nodo* crearListaVinculadaNodo(Nodo* nodo);
Camino* crearCamino();
int sumarNodo(Nodo* nodo, Camino *camino);
void cortarCamino(Camino* camino, Nodo* nodo);
void visualizarCamino(Camino* camino);
void liberarCamino(Camino*camino);



#endif // CAMINO_H
