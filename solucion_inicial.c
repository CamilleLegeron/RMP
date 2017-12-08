#include "solucion_inicial.h"

//function recursiva
bool crearSolucionInitial(Ambiente* ambiente, Nodo* actual, Nodo* objetivo, Camino* camino, int random){
    //printf("\n");
    marcarComoVisitado(&ambiente->matriz[actual->x][actual->y]);
    if(actual->x == objetivo->x && actual->y == objetivo->y){
        sumarNodo(actual, camino);
        //printf("\nTerminado");
        return true;
    }
    Orientacion* orientacionRobot = crearOrientacion();
    construirListaReferencia(ambiente, orientacionRobot, actual);
    definirOrientacion(orientacionRobot, actual, objetivo);

    Nodo* siguiente;
    if(sumarNodo(actual, camino) == 1){
        //elegirNuevaDireccion(orientacionRobot);
        siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
    } else {
        siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
    }
    /*printf("\nTest 2: ");
    int k;
    for(k=0;k<orientacionRobot->tamanoListReferencia;k++){
        printf(" %d ", orientacionRobot->listaReferencia[k]);
    }*/
    //visualizarCamino(camino);
    //printf("\n--- Largo del nuevo camino : %d", camino->largo);
    //Nodo* siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
    bool terminado = false;
    bool validado = false;
    //Seguimos si no encontremos el final y que hay que hacer otros intentos
    while (!terminado){
        //Seguimos si el nodo siguiente todavia no esta validado
        //printf("\n Buscamos el siguiente del nodo actual (%d,%d)",actual->x, actual->y);
        while(!validado){
            //Estas dos lineas permiten borrar de la lista de referencia la direccion del siguiente, para no volver a probarlo si es que este caso no funciona
            removerEnListaReferencia(orientacionRobot, orientacionRobot->direccion);
            //printf("\n Intenta direccion %d ", orientacionRobot->direccion);
            if(siguiente->libre){
                //printf("\nLibre");
                if(siguiente->visitado){
                    //printf("\nNodo ya visitado ... ");
                    visualizarNodo(siguiente);
                    //Redefinicion del siguiente
                    /*if(orientacionRobot->tamanoListReferencia == 0) {
                        //printf("\nNo queda siguiente possible");
                        return false;
                    }*/
                    /*random = rand() %orientacionRobot->tamanoListReferencia;
                    redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);*/
                    /*elegirNuevaDireccion(orientacionRobot);
                    siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];*/
                    siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
                    if (siguiente == NULL){
                        return false;
                    }
                } else {
                    validado = true;
                }
            } else {
                //printf("\nObstaculo");
                //Redefinicion del siguiente
                /*if(orientacionRobot->tamanoListReferencia == 0) {
                    //printf("\nNo queda siguiente possible");
                    return false;
                }*/
                /*random = rand() %orientacionRobot->tamanoListReferencia;
                redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);*/
                /*elegirNuevaDireccion(orientacionRobot);
                siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];*/
                siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
                if (siguiente == NULL){
                    return false;
                }
            }
        }
        //free(orientacionRobot);
        //return crearSolucionInitial(ambiente, siguiente, objetivo, camino, random);
        if(crearSolucionInitial(ambiente, siguiente, objetivo, camino, random)){
            terminado = true;
        } else {
            printf("-->REGRESO");
            validado = false;
            cortarCamino(camino, actual);
            //visualizarCamino(camino);
            //Redefinicion del siguiente
            /*random = rand() %orientacionRobot->tamanoListReferencia;
            redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);*/
            /*
            elegirNuevaDireccion(orientacionRobot);
            siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];*/
            siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
            if(siguiente == NULL){
                return false;
            }
        }
    }
    return true;
}

void demarcarNodos (Ambiente* ambiente){
    int i;
    int j;
    for(i=0;i<ambiente->n;i++){
        for(j=0;j<ambiente->m;j++){
            marcarComoNoVistitado(&ambiente->matriz[i][j]);
        }
    }
}

Nodo* elegirNuevoSiguiente(Nodo* actual, Ambiente* ambiente, Orientacion* orientacion, int random){
    if(orientacion->tamanoListReferencia == 0) {
        //printf("\nNo queda siguiente possible");
        return NULL;
    }
    Direccion nuevaDireccion = orientacion->listaReferencia[0];
    //redefinirOrientacion(orientacion, orientacion->listaReferencia[0]);
    //int min = ambiente->matriz[actual->x+orientacion->i][actual->y+orientacion->j].costo;
    int min = fabs(orientacion->listaReferencia[0] - orientacion->direccionIdeal);
    //la distancia maxima entre dos direcciones es 4.
    if(min>4){min = 8-min;}

    int i;
    int tab;
    for(i=1;i<orientacion->tamanoListReferencia;i++){
        /*redefinirOrientacion(orientacion, orientacion->listaReferencia[i]);
        tab = ambiente->matriz[actual->x+orientacion->i][actual->y+orientacion->j].costo;
        if(tab<min && tab >= 0 ){
                min = tab; nuevaDireccion = orientacion->listaReferencia[i];
        } else if (tab==min){
            random = rand() %2;
            if(random = 1){
                nuevaDireccion = orientacion->listaReferencia[i];
            }
        }*/
        tab = fabs(orientacion->listaReferencia[i] - orientacion->direccionIdeal);
        if(tab>4){tab = 8-tab;}
        if(tab<min){min = tab; nuevaDireccion = orientacion->listaReferencia[i];}
        else if (tab==min){
            random = rand() %2;
            if(random = 1){
                nuevaDireccion = orientacion->listaReferencia[i];
            }
        }
    }
    redefinirOrientacion(orientacion, nuevaDireccion);
    return &ambiente->matriz[actual->x+orientacion->i][actual->y+orientacion->j];
}


Orientacion* crearOrientacion(){
    Orientacion* o;
    o = malloc(sizeof (Orientacion));
    o->listaReferencia = malloc(8*sizeof(Direccion));
    int i;
    for(i=N;i<=NO;i++){
        o->listaReferencia[i] = i;
    }
    o->tamanoListReferencia = 8;
    return o;
}

void construirListaReferencia(Ambiente* a, Orientacion* o, Nodo* n){
    int d;
    int largoLista = 0;
    for(d=N;d<=NO;d++){
        redefinirOrientacion(o, d);
        if(dentroAmbiente(a, n->x+o->i, n->y+o->j)){
            o->listaReferencia[largoLista] = o->direccion;
            largoLista++;
        }
    }
    o->tamanoListReferencia = largoLista;
}

void removerEnListaReferencia(Orientacion* o, int aRemover){
    int i;
    int j = 0;
    for(i=0;i<o->tamanoListReferencia;i++){
        if(o->listaReferencia[i]!=aRemover){
            o->listaReferencia[j]=o->listaReferencia[i];
            j++;
        }
    }
    o->tamanoListReferencia --;
}

void definirOrientacion(Orientacion* orientacion, Nodo* inicio, Nodo* objetivo){
    Direccion d;
    if(inicio->x > objetivo->x && inicio->y > objetivo->y){d = NO; orientacion->i = -1; orientacion->j = -1;}
    else if(inicio->x > objetivo->x && inicio->y < objetivo->y){d = NE; orientacion->i = -1; orientacion->j = 1;}
    else if (inicio->x > objetivo->x && inicio->y == objetivo->y){d = N; orientacion->i = -1; orientacion->j = 0;}
    else if (inicio->x < objetivo->x && inicio->y > objetivo->y){d = SO; orientacion->i = 1; orientacion->j = -1;}
    else if (inicio->x < objetivo->x && inicio->y < objetivo->y){d = SE; orientacion->i = 1; orientacion->j = 1;}
    else if (inicio->x < objetivo->x && inicio->y == objetivo->y){d = S; orientacion->i = 1; orientacion->j = 0;}
    else if (inicio->x == objetivo->x && inicio->y > objetivo->y){d = O; orientacion->i = 0; orientacion->j = -1;}
    else if (inicio->x == objetivo->x && inicio->y < objetivo->y){d = E; orientacion->i = 0; orientacion->j = 1;}
    orientacion->direccion = d;
    orientacion->direccionIdeal= d;
}

void redefinirOrientacion(Orientacion* o, Direccion d){
    o->direccion = d;
    switch(d){
    case N:
        o->i = -1;
        o->j = 0;
        break;
    case NE:
        o->i = -1;
        o->j = 1;
        break;
    case E:
        o->i = 0;
        o->j = 1;
        break;
    case SE:
        o->i = 1;
        o->j = 1;
        break;
    case S:
        o->i = 1;
        o->j = 0;
        break;
    case SO:
        o->i = 1;
        o->j = -1;
        break;
    case O:
        o->i = 0;
        o->j = -1;
        break;
    case NO:
        o->i = -1;
        o->j = -1;
        break;
    }
}

