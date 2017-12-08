#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "camino.h"

#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H

typedef struct Iteracion{
    int numero;
    struct Camino* solucionActual;
    struct Camino* vecindario;
}Iteracion;

typedef struct Restart{
    struct Camino* primero;
}Restart;

Restart* crearRestart();
Iteracion* crearIteracion();
void definirSolucionInicial(Camino* camino, Iteracion* iteracion);
void elegirSolucionActual(Camino* camino, Iteracion* iteracion);
void crearVecino(int numeroVecino, Camino* caminoInicial, Camino* vecino);
void sumarVecino(Camino* camino, Iteracion* iteracion);
void sumarCaminoARestart(Restart* restart, Camino* camino);
Camino* mejorMejora(Iteracion* iteracion);
Camino* mejorRestart(Restart* restart);
void visualizarIteracion(Iteracion* it);
void liberarVecindario(Iteracion* it);
void liberarIteracion(Iteracion* it);
void liberarRestart(Restart* r);

#endif // HILL_CLIMBING_H

