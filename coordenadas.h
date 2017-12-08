#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef COORDENADAS_H
#define COORDENADAS_H

typedef struct Coordenadas{
	int x;
	int y;
}Coordenadas;

Coordenadas* crearCoordenadas (int x, int y);
Coordenadas* initializarCoordenadas ();

#endif // COORDENADAS_H
