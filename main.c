#include "robot.h"
#include <math.h>

// TODO : remplacer les c->string = string par strcpy(livre->titre, titre);

int main(int argc, char* argv[])
{
    //--Initializacion del random--
    srand(time(NULL));

    //-------------------INITIALIZACIONES---------------
    FILE* archivoMatriz = NULL;
    FILE* archivoPuntos = NULL;
    archivoMatriz = fopen("Instancias/7.-10x10.inv", "r");
    archivoPuntos = fopen("Instancias/7.-10x10.points", "r");
    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;
    int** matrizInitialization = NULL;
    Ambiente *ambiente = NULL;
    Coordenadas** intentos = malloc(3*sizeof(int*)); //coordenadas de los puntos de origin y de destino de los tres intentos
    for (i=0; i<3; i++){
        intentos[i] = malloc(2*sizeof(int));
    }

    //----------------------DEFINE LA MATRIZ---------------------
    if(archivoMatriz != NULL){
        printf("\n\nPossible de leer en el texto");
        fscanf(archivoMatriz, "%d %d", &n, &m);
        printf("\nLes dimensions sont : %d, %d", n, m);

        matrizInitialization = malloc(n*sizeof(int*));
        for (i=0; i<n; i++){
            matrizInitialization[i]=malloc(m*sizeof(int));
        }

        for (i=0; i<n; i++){
            for(j=0; j<m; j++){
                if(!fscanf(archivoMatriz, "%d", &matrizInitialization[i][j])){
                    break;
                }if(j == 0){
                    printf("\n");
                }
                printf("%d ", matrizInitialization[i][j]);
            }
        }
        fclose(archivoMatriz);
    } else {
        printf("\nImpossible de abrir\n");
    }

    //------------------DEFINE LOS TRES INTENTOS----------------
    if (archivoPuntos != NULL){
        printf("\n\nEl archivo se lee");
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
        printf("\nTEST\n");
        //fclose(archivoPuntos);
        printf("\nTEST2\n");
    } else {
        printf("\n\nImpossible de abrir\n");
    }

    //--------------------Crear el ambiente---------------
    printf("\n\n---------- Construir el ambiente ");
    ambiente = crearAmbiente(n, m, matrizInitialization, &intentos[0][0], &intentos[0][1]);
    visualizarAmbiente(ambiente);


    //--------------------Crear el camino : solucion initial----------------
    printf("\n\n ---------Construir la solucion initial");
    Iteracion* it = crearIteracion();
    Camino* caminoInicial = crearCamino();
    Nodo* nodoInicial = &ambiente->matriz[intentos[0][0].x][intentos[0][0].y];
    Nodo* nodoObjetivo = &ambiente->matriz[intentos[0][1].x][intentos[0][1].y];
    int r = 0;
    crearSolucionInitial(ambiente, NULL, nodoInicial, nodoObjetivo, caminoInicial, r);
    free(r);
    printf("\n\n\nDespues del la incializacion");
    visualizarCamino(caminoInicial);



//----------------------FONCTION DE SUPPRESSION---------
    // Clean up when you're done.
    free(ambiente);
    free(it); //TODO : faire la fonction de libération de l'espace !!!!!!!!!!!!!
    free(intentos);
    free(matrizInitialization);

    return 0;
}
