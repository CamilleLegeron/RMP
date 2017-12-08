#include "solucion_inicial.h"
#include "hill_climbing.h"

#define RESTRART 2
#define NUM_MAX_IT 5
#define NUMERO_DE_VECINO 3

/// TODO : remplacer les c->string = string par strcpy(livre->titre, titre);

int main(int argc, char* argv[])
{
    ///--Initializacion del random--
    srand(time(NULL));

    ///-------------------INITIALIZACIONES---------------
    FILE* archivoMatriz = NULL;
    FILE* archivoPuntos = NULL;
    archivoMatriz = fopen("Instancias/7.-10x10.inv", "r");
    archivoPuntos = fopen("Instancias/7.-10x10.points", "r");
    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;
    int** matrizInitialization = NULL;
    Coordenadas** intentos = malloc(3*sizeof(int*)); ///coordenadas de los puntos de origin y de destino de los tres intentos
    for (i=0; i<3; i++){
        intentos[i] = malloc(2*sizeof(int));
    }

    ///----------------------DEFINE LA MATRIZ---------------------
    if(archivoMatriz != NULL){
        fscanf(archivoMatriz, "%d %d", &n, &m);
        printf("\nLas dimensiones son : %d, %d", n, m);

        matrizInitialization = malloc(n*sizeof(int*));
        for (i=0; i<n; i++){
            matrizInitialization[i]=malloc(m*sizeof(int));
        }

        for (i=0; i<n; i++){
            for(j=0; j<m; j++){
                if(!fscanf(archivoMatriz, "%d", &matrizInitialization[i][j])){
                    break;
                }/*if(j == 0){
                    printf("\n");
                }
                printf("%d ", matrizInitialization[i][j]);*/
            }
        }
        fclose(archivoMatriz);
    } else {
        printf("\nImpossible de abrir\n");
    }

    ///------------------DEFINE LOS TRES INTENTOS----------------
    if (archivoPuntos != NULL){
        int x = 0;
        int y = 0;
        Coordenadas* c = NULL;
        for (i=0; i<3; i++){
            for(j=0; j<2; j++){
                if(fscanf(archivoPuntos, "%d %d", &x, &y)){
                    c = crearCoordenadas(x, y);
                    intentos[i][j] = *c;
                } else {
                    break;
                }if(j == 0){
                    printf("\n");
                }
                visualizarCoordenadas(intentos[i][j]);
            }
        }
        //fclose(archivoPuntos);
    } else {
        printf("\n\nImpossible de abrir\n");
    }

    ///-----------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------HILL CLIMBING + MEJOR MEJORA -----------------------------
    ///-----------------------------------------------------------------------------------------------------------

    printf("\n\n------------------------- PRINCIPIO DE HILL CLIMBING --------------------");

    bool terminado = false;
    Ambiente* ambiente = NULL;
    Nodo *nodoInicial = NULL;
    Nodo *nodoObjetivo = NULL;
    Restart* guardaRestarts = NULL;
    Iteracion* it = NULL;
    Camino* caminoInicial = NULL;
    Camino* caminoElegido = NULL;

    for(i=0; i<3; i++){
        printf("\n\n\n%d) Pareja de puntos : Inicio=(%d,%d), Objetivo=(%d,%d) ",i+1, intentos[i][0].x, intentos[i][0].y, intentos[i][1].x, intentos[i][1].y );

        if(matrizInitialization[intentos[i][0].x][intentos[i][0].y] == 1){
            printf("\n No se puede buscar un camino, la casilla de inicio es un obstaculo");
            free(intentos);
            free(matrizInitialization);
            break;
        }
        if(matrizInitialization[intentos[i][1].x][intentos[i][1].y] == 1){
            printf("\n No se puede buscar un camino, la casilla objetivo es un obstaculo");
            free(intentos);
            free(matrizInitialization);
            break;
        }

        ///--------------------Crear el ambiente---------------
        printf("\n\n\n       a) Construir el ambiente ");
        ambiente = crearAmbiente(n, m, matrizInitialization, &intentos[i][0], &intentos[i][1]);
        visualizarAmbiente(ambiente);
        nodoInicial = &ambiente->matriz[intentos[i][0].x][intentos[i][0].y];
        nodoObjetivo = &ambiente->matriz[intentos[i][1].x][intentos[i][1].y];
        printf("\n El costo optimizado :  %d", nodoInicial->costo);

        guardaRestarts = crearRestart();
        for(j=0;j<RESTRART;j++){
            if(j>0) {
                printf("\n\n\n RE-START !!! ");
            }
            ///--------------------Crear la solucion initial----------------
            printf("\n\n\n       b) Construir la solucion initial");
            if (nodoInicial->costo == -1){
                printf("\n No hay solucion possible ! ");
                break;
            }

            it = crearIteracion(1);
            caminoInicial = crearCamino();
            int r = 0;
            crearSolucionInitial(ambiente, nodoInicial, nodoObjetivo, caminoInicial, r);
            definirSolucionInicial(caminoInicial, it);
            demarcarNodos(ambiente);
            printf("\n Solucion Initial : ");
            visualizarCamino(caminoInicial);
            printf("\n El costo optimizado :  %d", nodoInicial->costo);

            ///---------------------Iteraciones de Hill Climbing------------------------
            terminado = false;
            while(!terminado){
                visualizarIteracion(it);
                printf("\n\n\n       c) Construir el vecindario");
                if(it->numero == NUM_MAX_IT){
                    printf("\nUltimo restart");
                    terminado = true;
                }
                int k;
                for(k=1;k<= NUMERO_DE_VECINO; k++){
                    Camino* nuevoVecino = crearCamino();
                    crearVecino(k, it->solucionActual, nuevoVecino);
                    sumarVecino(nuevoVecino, it);
                }

                //construirVecindario(it, NUMERO_DE_VECINO);
                visualizarIteracion(it);

                printf("\n\n\n       d) Elegir el vecino : mejor mejora");
                caminoElegido = mejorMejora(it);
                if(caminoElegido != NULL){
                    elegirSolucionActual(caminoElegido, it);
                    printf("\n ---- Nueva solucion : ");
                    visualizarCamino(it->solucionActual);
                } else {
                    printf("\n No hay vecino mejor que la solucion actual ! ");
                    terminado = true;
                }
                //liberarCamino(caminoElegido);
                //caminoElegido=NULL;
            }
            printf("\n Solucion de este restart : ");
            visualizarCamino(it->solucionActual);
            sumarCaminoARestart(guardaRestarts, it->solucionActual);
            //printf("\n\nLiberar iteracion");
            //liberarIteracion(it);
            //liberarCamino(caminoInicial);
            //caminoInicial = NULL;
        }

        printf("\n\n    e) SOLUCION FINAL : ");
        visualizarCamino(mejorRestart(guardaRestarts));

        printf("\nLiberar ambiente");
        //liberarAmbiente(ambiente);
        ambiente = NULL;
    }

    free(intentos);
    free(matrizInitialization);
    return 0;
}
