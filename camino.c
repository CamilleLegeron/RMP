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

Iteracion* crearIteracion(){
    Iteracion *it;
    it = malloc(sizeof (Iteracion));
    it->numero=0;
    it->solucionActual=NULL;
    it->vecindario=NULL;
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


void definirSolucionActual(Camino* camino, Iteracion* iteracion){
    if(iteracion!=NULL){
        iteracion->solucionActual = camino;
    }
}

void sumarVecino(Camino* camino, Iteracion* iteracion){
    Camino* c = iteracion->vecindario;
    if(c==NULL){
        iteracion->vecindario = camino;
    } else {
        int salida = 0;
        while(salida == 0){
            if(c->siguiente != NULL){
                c = c->siguiente;
            } else {
                c->siguiente = camino;
                salida = 1;
            }
        }
    }
}

Camino* mejorVecino(Iteracion* iteracion){
    Camino* mejorCamino = NULL;
    Camino* caminoAProbar = iteracion->vecindario;
    if(caminoAProbar == NULL){
        return mejorCamino;
    }
    int evaluacion = caminoAProbar->largo;
    mejorCamino = caminoAProbar;
    bool terminado = false;
    while(!terminado){
        if(caminoAProbar->largo <= evaluacion ){
            evaluacion = caminoAProbar->largo;
            mejorCamino = caminoAProbar;
        }
        if(caminoAProbar->siguiente == NULL){
            terminado = true;
        } else {
            caminoAProbar = caminoAProbar->siguiente;
        }
    }
    return mejorCamino;
}

void visualizarCamino(Camino* camino){
    printf("\n----------- Visializacion de un camino ---------- \n");
    printf("Largo del camino : %d \n", camino->largo);
    LV_Nodo* n = camino->primero;
    printf("[ ");
    while(n!=NULL){
        printf("(%d,%d) ",n->nodo->x, n->nodo->y);
        n = n->siguiente;
    }
    printf("]\n");
}

