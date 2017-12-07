#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "nodo.h"

#ifndef CAMINO_H
#define CAMINO_H


//Lista vinculada
typedef struct LV_Nodo{
    Nodo *nodo;
    struct LV_Nodo *siguiente;
}LV_Nodo;

//Lista vinculada
typedef struct Camino{
	LV_Nodo *primero;
	int largo;
	struct Camino *siguiente;
}Camino;

typedef struct Iteracion{
    int numero;
    struct Camino* solucionActual;
    struct Camino* vecindario;
}Iteracion;


LV_Nodo* crearListaVinculadaNodo(Nodo* nodo);
Camino* crearCamino();
Iteracion* crearIteracion();
int sumarNodo(Nodo* nodo, Camino *camino);
void definirSolucionActual(Camino* camino, Iteracion* iteracion);
void sumarVecino(Camino* camino, Iteracion* iteracion);
Camino* mejorVecino(Iteracion* iteracion);
void visualizarCamino(Camino* camino);



#endif // CAMINO_H
