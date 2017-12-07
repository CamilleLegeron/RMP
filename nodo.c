#include "nodo.h"

Nodo* crearNodo (int x, int y, bool libre){
    Nodo* n = (Nodo*) malloc (sizeof (Nodo));
    n->x = x;
    n->y = y;
    n->costo = -1;
    n->libre = libre;

    return n;
}

void visualizarNodo(Nodo* nodo){
    printf("\n----- Visualizacion de un nodo ------ \n");
    printf("(%d,%d), costo : %d", nodo->x, nodo->y, nodo->costo);
}


