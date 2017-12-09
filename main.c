#include <time.h>
#include <string.h>

#include "solucion_inicial.h"
#include "hill_climbing.h"

#define RESTRART 1
#define NUM_MAX_IT 9
#define NUMERO_DE_VECINO 4

/// TODO : remplacer les c->string = string par strcpy(livre->titre, titre);

int main(int argc, char* argv[])
{
    ///--Initializacion del random--
    srand(time(NULL));

    ///-------------------INITIALIZACIONES---------------
    FILE* archivoMatriz = NULL;
    FILE* archivoPuntos = NULL;

    char nameMatriz[50] = "Instancias/", namePuntos[50] = "Instancias/";
    strcat(nameMatriz, argv[1]);
    strcat(namePuntos, argv[2]);
    archivoMatriz = fopen(nameMatriz, "r");
    archivoPuntos = fopen(namePuntos, "r");

    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;
    int** matrizInitialization = NULL;
    Coordenadas** intentos = malloc(3*sizeof(int*)); ///coordenadas de los puntos de origin y de destino de los tres intentos
    for (i=0; i<3; i++){
        intentos[i] = malloc(2*sizeof(int));
    }

    bool terminado = false;
    Ambiente* ambiente = NULL;
    Nodo *nodoInicial = NULL;
    Nodo *nodoObjetivo = NULL;
    Restart* guardaRestarts = NULL;
    Iteracion* it = NULL;
    Camino* caminoInicial = NULL;
    Camino* caminoElegido = NULL;

    clock_t start, end;
    double cpu_time_used;

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
                }
            }
        }
        fclose(archivoMatriz);
    } else {
        printf("\nImpossible de abrir\n");
        return 1;
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
                }
            }
        }
        //fclose(archivoPuntos);
    } else {
        printf("\n\nImpossible de abrir\n");
        return 1;
    }

    ///-----------------------------------------------------------------------------------------------------------
    ///-------------------------------------------------HILL CLIMBING + MEJOR MEJORA -----------------------------
    ///-----------------------------------------------------------------------------------------------------------

    printf("\n\n------------------------- PRINCIPIO DE HILL CLIMBING --------------------");

    for(i=0; i<3; i++){
        printf("\n\n\n---------------------------------------------------\n");
        printf("%d) Pareja de puntos : Inicio=(%d,%d), Objetivo=(%d,%d) ",i+1, intentos[i][0].x, intentos[i][0].y, intentos[i][1].x, intentos[i][1].y );
        printf("\n---------------------------------------------------");

        if(matrizInitialization[intentos[i][0].x][intentos[i][0].y] == 1){
            printf("\n No se puede buscar un camino, la casilla de inicio es un obstaculo");
        } else if(matrizInitialization[intentos[i][1].x][intentos[i][1].y] == 1){
            printf("\n No se puede buscar un camino, la casilla objetivo es un obstaculo");
        } else if(intentos[i][1].x > n || intentos[i][1].y > m){
            printf("\n No se puede buscar un camino, la casilla de inicio no esta en la matriz");
        } else if(intentos[i][1].x > n || intentos[i][1].y > m){
            printf("\n No se puede buscar un camino, la casilla objetivo no esta en la matriz");
        }else {
            ///--------------------Crear el ambiente---------------

            start = clock();

            printf("\n\n\n       a) Construir el ambiente ");
            ambiente = crearAmbiente(n, m, matrizInitialization, &intentos[i][0], &intentos[i][1]);
            if(n==10 && m==10){
                ///visualizamos el ambiente solamente si la matriz es chica.
                visualizarAmbiente(ambiente);
            }
            nodoInicial = &ambiente->matriz[intentos[i][0].x][intentos[i][0].y];
            nodoObjetivo = &ambiente->matriz[intentos[i][1].x][intentos[i][1].y];

            guardaRestarts = crearRestart();
            for(j=0;j<RESTRART;j++){
                if(j>0) {
                    printf("\n\n\n -------------------- RE-START !!! -------------------");
                }
                ///--------------------Crear la solucion initial----------------
                printf("\n\n\n       b) Construir la solucion initial");

                it = crearIteracion(1);
                caminoInicial = crearCamino();
                int r = 0;
                crearSolucionInitial(ambiente, nodoInicial, nodoObjetivo, caminoInicial, r);
                definirSolucionInicial(caminoInicial, it);
                demarcarNodos(ambiente);
                printf("\n Solucion Initial : ");
                //visualizarCamino(caminoInicial);
                printf("largo = %d", caminoInicial->largo);
                printf("\n El costo optimizado :  %d", nodoInicial->costo);

                ///---------------------Iteraciones de Hill Climbing------------------------
                terminado = false;
                while(!terminado){
                    //visualizarIteracion(it);
                    printf("\n\n\n       c) Construir el vecindario");
                    if(it->numero == NUM_MAX_IT){
                        printf("\nUltima iteracion");
                        terminado = true;
                    }
                    int k;
                    for(k=1;k<= NUMERO_DE_VECINO; k++){
                        Camino* nuevoVecino = crearCamino();
                        crearVecino(k, it->solucionActual, nuevoVecino);
                        sumarVecino(nuevoVecino, it);
                    }
                    visualizarIteracion(it);

                    printf("\n\n\n       d) Elegir el vecino : mejor mejora");
                    caminoElegido = mejorMejora(it);
                    if(caminoElegido != NULL){
                        elegirSolucionActual(caminoElegido, it);
                        printf("\n Nueva solucion : ");
                        printf("largo = %d", it->solucionActual->largo);
                        //visualizarCamino(it->solucionActual);
                    } else {
                        printf("\n No hay vecino mejor que la solucion actual ! ");
                        terminado = true;
                    }
                }
                printf("\n\n Solucion de este restart en %d iteraciones", it->numero-1);
                //printf("\n Solucion de este restart : ");
                //visualizarCamino(it->solucionActual);
                sumarCaminoARestart(guardaRestarts, it->solucionActual);
            }

            printf("\n\n\n       e) SOLUCION FINAL : ");
            if(mejorRestart(guardaRestarts)->largo > 100){
                printf("largo = %d", mejorRestart(guardaRestarts)->largo);
            } else {
                visualizarCamino(mejorRestart(guardaRestarts));
            }


            printf("\nLiberar ambiente");
            liberarAmbiente(ambiente);
            ambiente = NULL;

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nEl calculo tomo %f segundos", cpu_time_used);
        }
    }

    ///----------------------LIBERACION DEL ESPACIO------------------
    printf("\n\n\n Liberacion del espacio");
    free(nodoInicial);
    free(nodoObjetivo);
    liberarRestart(guardaRestarts);
    liberarIteracion(it);
    liberarCamino(caminoInicial);
    free(caminoElegido);
    free(intentos);
    free(matrizInitialization);
    return 0;
}
