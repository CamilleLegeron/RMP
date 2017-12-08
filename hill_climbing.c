#include "hill_climbing.h"

Restart* crearRestart(){
    Restart* r;
    r = malloc(sizeof (Restart));
    r->primero = NULL;
    return r;
}

Iteracion* crearIteracion(){
    Iteracion *it;
    it = malloc(sizeof (Iteracion));
    it->numero=1;
    it->solucionActual=NULL;
    it->vecindario=NULL;
    return it;
}

void definirSolucionInicial(Camino* camino, Iteracion* iteracion){
    if(iteracion!=NULL){
        iteracion->solucionActual = camino;
    } else {
        printf("La iteracion es NULL");
    }
}


void elegirSolucionActual(Camino* camino, Iteracion* iteracion){
    if(iteracion!=NULL){
        //Camino* c = iteracion->solucionActual;
        iteracion->solucionActual = camino;
        //liberarCamino(c);
        iteracion->numero++;
        //liberarVecindario(iteracion);
        iteracion->vecindario = NULL;
    } else {
        printf("La iteracion es NULL");
    }
}

void crearVecino(int numeroVecino, Camino* caminoInicial, Camino* vecino){
    //printf("\n En vecino %d", numeroVecino);
    //printf("\n EL CAMINO INICIAL ES ::: ");
    //visualizarCamino(caminoInicial);
    //Camino* vecino = crearCamino();
    LV_Nodo* n = caminoInicial->primero;
    LV_Nodo* n2 = n;
    LV_Nodo* n_tamp = NULL;
    int k = 0;
    while(k<=numeroVecino && n!=NULL){
        n=n->siguiente;
        k++;
    }
    while(n!=NULL){
        sumarNodo(n2->nodo, vecino);
        if(fabs(n->nodo->x - n2->nodo->x)<2 && fabs(n->nodo->y - n2->nodo->y)<2){
            printf("\nLos dos nodos n=(%d,%d) y n2=(%d,%d) son vecinos, el camino puede ser mas corto", n->nodo->x, n->nodo->y, n2->nodo->x,  n2->nodo->y);
            n_tamp = n;
            while(n2!=n_tamp){
                n=n->siguiente;
                n2=n2->siguiente;
            }
        } else {
            n=n->siguiente;
            n2=n2->siguiente;
        }
    }
    while(n2!=NULL){
        sumarNodo(n2->nodo, vecino);
        n2=n2->siguiente;
    }
}


void sumarVecino(Camino* vecino, Iteracion* iteracion){
    vecino->siguiente = NULL;
    Camino* v = iteracion->vecindario;
    if(v==NULL){
        iteracion->vecindario = vecino;
    } else {
        int salida = 0;
        while(salida == 0){
            if(v->siguiente != NULL){
                v = v->siguiente;
            } else {
                v->siguiente = vecino;
                salida = 1;
            }
        }
    }
}

void sumarCaminoARestart(Restart* restart, Camino* camino){
    Camino* c = restart->primero;
    if(c==NULL){
        restart->primero = camino;
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

Camino* mejorMejora(Iteracion* iteracion){
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
    if(evaluacion<iteracion->solucionActual->largo){
        return mejorCamino;
    }
    return NULL;
}

Camino* mejorRestart(Restart* r){
    Camino* mejorCamino = NULL;
    Camino* caminoAProbar = r->primero;
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

void visualizarIteracion(Iteracion* it){
    printf("\n\nIteracion %d \n", it->numero);
    printf("\nSolucion actual : ");
    visualizarCamino(it->solucionActual);
    printf("\nVecindario : ");
    Camino* c = it->vecindario;
    if(c!=NULL){
        int i = 1;
        while(c!=NULL){
            printf("\n-Vecino %d", i);
            visualizarCamino(c);
            c = c->siguiente;
            i++;
        }
    } else {
        printf("No hay vecinos ! ");
    }

}

void liberarVecindario(Iteracion* it){
    Camino* c = it->vecindario;
    it->vecindario=NULL;
    Camino* c2;
    while(c!=NULL){
        c2=c;
        c=c->siguiente;
        liberarCamino(c2);
    }
}

void liberarIteracion(Iteracion* it){
    liberarVecindario(it);
    liberarCamino(it->solucionActual);
    free(it);
    it = NULL;
}


void liberarRestart(Restart* r){
    Camino* c = r->primero;
    Camino* c2;
    while(c!=NULL){
        c2=c;
        c=c->siguiente;
        liberarCamino(c2);
    }
    free(r);
    r = NULL;
}

