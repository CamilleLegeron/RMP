#include "camino.h"

LV_Nodo* crearListaVinculadaNodo(Nodo* nodo){
    LV_Nodo *n;
    n = malloc(sizeof (LV_Nodo));
    n->nodo = nodo;
    n->siguiente = NULL;
    return n;
}

Camino* crearCamino(){
    Camino *c;
    c = malloc(sizeof (Camino));
    c->largo = 0;
    c->primero = NULL;
    c->siguiente = NULL;
    return c;
}

int sumarNodo(Nodo* nodo, Camino *camino){
    LV_Nodo* n = camino->primero;
    LV_Nodo *nuevo_nodo = crearListaVinculadaNodo(nodo);
    LV_Nodo* n2 = NULL;
    int cantidadRemovida = 0;

    if(n==NULL){
        camino->primero = nuevo_nodo;
    } else {
        int salida = 0;
        while(salida==0){
            if(n->nodo->x == nodo->x && n->nodo->y == nodo->y){
                printf("\nEl robot acaba de hacer un ciclo, paso dos veces por el mismo punto");
                n2 = n;
                n=n->siguiente;
                n2->siguiente = NULL;
                while(n!=NULL){
                    n2 = n;
                    n=n->siguiente;
                    free(n2);
                    cantidadRemovida++;
                }
                camino->largo = camino->largo - cantidadRemovida;
                return 1;
            }
            if(n->siguiente!=NULL){
                n = n->siguiente;
            } else {
                n->siguiente = nuevo_nodo;
                salida = 1;
            }
        }
    }
    camino->largo++;
    return 0;
}

void cortarCamino(Camino* camino, Nodo* nodo){
    LV_Nodo *n = camino->primero;
    LV_Nodo *n2 = NULL;
    int cantidadRemovida = 0;
    bool encontrado = false;
    while(!encontrado || n!=NULL){
        if(n->nodo->x == nodo->x && n->nodo->y == nodo->y){
            visualizarNodo(nodo);
            visualizarNodo(n->nodo);
            n2 = n;
            n=n->siguiente;
            n2->siguiente = NULL;
            while(n!=NULL){
                n2 = n;
                n=n->siguiente;
                free(n2);
                cantidadRemovida++;
            }
            camino->largo = camino->largo - cantidadRemovida;
            encontrado = true;
        } else {
            n=n->siguiente;
        }

    }
}


void visualizarCamino(Camino* camino){
    printf("\nLargo del camino : %d \n", camino->largo);
    LV_Nodo* n = camino->primero;
    printf("[ ");
    while(n!=NULL){
        printf("(%d,%d) ",n->nodo->x, n->nodo->y);
        n = n->siguiente;
    }
    printf("]\n");
}

void liberarCamino(Camino*camino){
    LV_Nodo* n = camino->primero;
    LV_Nodo* n2;
    while(n!=NULL){
        n2=n;
        n=n->siguiente;
        //No liberamos el node de n2 porque es un puntero sobre un nodo de la matriz
        free(n2);
    }
    free(camino);
    camino = NULL;
}
