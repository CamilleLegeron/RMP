#include "robot.h"

//function recursiva
bool crearSolucionInitial(Ambiente* ambiente, Nodo* anterior, Nodo* actual, Nodo* objetivo, Camino* camino, int random){
    sumarNodo(actual, camino);
    visualizarCamino(camino);
    if(actual->x == objetivo->x && actual->y == objetivo->y){
        printf("Terminado");
        return true;
    }
    Orientacion* orientacionRobot = crearOrientacion();
    construirListaReferencia(ambiente, orientacionRobot, actual);
    definirOrientacion(orientacionRobot, actual, objetivo);
    Nodo* siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
    bool terminado = false;
    bool validado = false;
    int i;
    //Seguimos si no encontremos el final y que hay que hacer otros intentos
    while (!terminado){
        //Seguimos si el nodo siguiente todavia no esta validado
        printf("\n Buscamos el siguiente del nodo actual (%d,%d)",actual->x, actual->y);
        while(!validado){
            //Estas dos lineas permiten borrar de la lista de referencia la direccion del siguiente, para no volver a probarlo si es que este caso no funciona
            removerEnListaReferencia(orientacionRobot, orientacionRobot->direccion);
            printf("\n Intenta direccion %d ", orientacionRobot->direccion);
            if(siguiente->libre){
                printf("\nLibre");
                if(siguiente == anterior){
                    printf("\nMala suerte, el siguiente eligido es el mismo que el anterior ... ");
                    //Redefinicion del siguiente
                    if(orientacionRobot->tamanoListReferencia == 0) {
                        printf("\nNo queda siguiente possible");
                        return false;
                    }
                    random = rand() %orientacionRobot->tamanoListReferencia;
                    redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);
                    siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
                } else {
                    validado = true;
                }
            } else {
                printf("\nObstaculo");
                //Redefinicion del siguiente
                if(orientacionRobot->tamanoListReferencia == 0) {
                    printf("\nNo queda siguiente possible");
                    return false;
                }
                random = rand() %orientacionRobot->tamanoListReferencia;
                redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);
                siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
            }
        }
        //free(orientacionRobot);
        //return crearSolucionInitial(ambiente, actual, siguiente, objetivo, camino, random);
        if(crearSolucionInitial(ambiente, actual, siguiente, objetivo, camino, random)){
            terminado = true;
        } else {
            printf("-->RETRESO");
            validado = false;
            //Redefinicion del siguiente
            random = rand() %orientacionRobot->tamanoListReferencia;
            redefinirOrientacion(orientacionRobot, orientacionRobot->listaReferencia[random]);
            siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
        }
    }
    return true;
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
