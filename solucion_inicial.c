#include "solucion_inicial.h"

///function recursiva que permite crear la solucion inicial
bool crearSolucionInitial(Ambiente* ambiente, Nodo* actual, Nodo* objetivo, Camino* camino, int random){
    marcarComoVisitado(&ambiente->matriz[actual->x][actual->y]);
    if(actual->x == objetivo->x && actual->y == objetivo->y){
        sumarNodo(actual, camino);
        return true;
    }
    Orientacion* orientacionRobot = crearOrientacion();
    construirListaReferencia(ambiente, orientacionRobot, actual);
    definirOrientacion(orientacionRobot, actual, objetivo);

    Nodo* siguiente;
    if(sumarNodo(actual, camino) == 1){
        siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
    } else {
        siguiente = &ambiente->matriz[actual->x+orientacionRobot->i][actual->y+orientacionRobot->j];
    }
    bool terminado = false;
    bool validado = false;
    ///Seguimos en el caso que no encontramos el final y que hay que hacer otros intentos
    while (!terminado){
        ///Seguimos si el nodo siguiente todavia no esta validado
        while(!validado){
            removerEnListaReferencia(orientacionRobot, orientacionRobot->direccion);
            if(siguiente->libre){
                if(siguiente->visitado){
                    ///Redefinicion del siguiente
                    siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
                    if (siguiente == NULL){
                        return false;
                    }
                } else {
                    validado = true;
                }
            } else {
                ///Redefinicion del siguiente
                siguiente = elegirNuevoSiguiente(actual, ambiente, orientacionRobot, random);
                if (siguiente == NULL){
                    return false;
                }
            }
        }
        if(crearSolucionInitial(ambiente, siguiente, objetivo, camino, random)){
            terminado = true;
        } else {
            ///la funcion retorno un false, el camino se encontro atrapado
            validado = false;
            ///borramos, del camino, la parte despues de este punto, vamos a buscar otro posibilidad
            cortarCamino(camino, actual);
            ///Redefinicion del siguiente
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
        return NULL;
    }
    Direccion nuevaDireccion = orientacion->listaReferencia[0];
    int min = fabs(orientacion->listaReferencia[0] - orientacion->direccionIdeal);
    ///la distancia maxima entre dos direcciones es 4.
    if(min>4){min = 8-min;}

    int i;
    int tab;
    for(i=1;i<orientacion->tamanoListReferencia;i++){
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

