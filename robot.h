#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "ambiente.h"

#ifndef ROBOT_H
#define ROBOT_H

typedef enum Direccion Direccion;
enum Direccion
{
    N = 0, NE = 1, E = 2, SE = 3, S = 4, SO = 5, O = 6, NO = 7
};

typedef struct Orientacion{
    Direccion direccion;
    //i y j permiten avenzar en la buena direccion
    int i;
    int j;
    Direccion* listaReferencia;
    int tamanoListReferencia;
}Orientacion;

typedef struct Robot {
    Orientacion orientacion;
    Camino* mejorCamino;
}Robot;

bool crearSolucionInitial(Ambiente* ambiente, Nodo* anterior, Nodo* actual, Nodo* objetivo, Camino* camino, int random);
Orientacion* crearOrientacion();
void definirOrientacion(Orientacion* orientacion, Nodo* inicio, Nodo* objetivo);
void redefinirOrientacion(Orientacion* o, Direccion d);

#endif // ROBOT_H
