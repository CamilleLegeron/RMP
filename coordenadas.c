#include "coordenadas.h"

void visualizarCoordenadas(Coordenadas c){
    printf("(%d,%d)",c.x, c.y);
}

Coordenadas* crearCoordenadas (int x, int y){
    Coordenadas* coordenadas = (Coordenadas*) malloc (sizeof (Coordenadas));
    coordenadas->x = x;
    coordenadas->y = y;

    return coordenadas;
}

Coordenadas* initializarCoordenadas () {
    Coordenadas* coordenadas = (Coordenadas*) malloc (sizeof (Coordenadas));
    coordenadas->x = -1;
    coordenadas->y = -1;
    return coordenadas;
}

