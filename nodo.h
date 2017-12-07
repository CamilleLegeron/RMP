#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef NODO_H
#define NODO_H

typedef struct Nodo{
	int x;
	int y;
	bool libre;
	int costo;
}Nodo;

Nodo* crearNodo (int x, int y, bool libre);

#endif // NODO_H
