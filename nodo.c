#include "nodo.h"


Nodo* crearNodo (int x, int y, bool libre){
    Nodo* n = (Nodo*) malloc (sizeof (Nodo));
    n->x = x;
    n->y = y;
    n->costo = -1;
    n->libre = libre;
    n->visitado = false;

    return n;
}

void marcarComoVisitado (Nodo* nodo){
    nodo->visitado = true;
}

void marcarComoNoVistitado (Nodo* nodo){
    nodo->visitado = false;
}

void visualizarNodo(Nodo* nodo){
    printf("\n(%d,%d), costo : %d", nodo->x, nodo->y, nodo->costo);
}


