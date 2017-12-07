#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef COORDENADAS_H
#define COORDENADAS_H

typedef struct Coordenadas{
	int x;
	int y;
}Coordenadas;

void visualizarCoordenadas(Coordenadas c);
Coordenadas* crearCoordenadas (int x, int y);
Coordenadas* initializarCoordenadas ();
bool existe (Coordenadas c);
//TODO --> poner all funciones

#endif // COORDENADAS_H
