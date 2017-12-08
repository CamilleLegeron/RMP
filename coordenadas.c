#include "coordenadas.h"

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

