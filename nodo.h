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
	bool visitado;
}Nodo;

Nodo* crearNodo (int x, int y, bool libre);
void marcarComoVisitado (Nodo* nodo);
void marcarComoNoVistitado (Nodo* nodo);
void visualizarNodo(Nodo* nodo);

#endif // NODO_H
