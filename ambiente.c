#include "ambiente.h"

Ambiente* crearAmbiente (int n, int m, int** matrizInitial, Coordenadas* c_inicio, Coordenadas* c_objetivo){
    printf("\nEn la funccion CrearAmbiente");
    int i;
    int j;
    Ambiente* a = (Ambiente*) malloc (sizeof (Ambiente));
    a->m = m;
    a->n = n;
    a->matriz = malloc(n*sizeof(Nodo*));
    for (i=0; i<n; i++){
        a->matriz[i]=malloc(m*sizeof(Nodo));
    }
    for (i=0; i<n ; i++){
        for(j=0; j<m ; j++){
            if(matrizInitial[i][j] == 0){
                a->matriz[i][j] = *crearNodo(i, j, true);
            } else {
                a->matriz[i][j] = *crearNodo(i, j, false);
            }
        }
    }
    a->inicio = &a->matriz[c_inicio->x][c_inicio->y];
    a->objetivo = &a->matriz[c_objetivo->x][c_objetivo->y];
    a->matriz[a->objetivo->x][a->objetivo->y].costo = 1;
    if(n<=100 && m <= 100){
        ///Para las matrizes mas grandes esta funccion es demasiado compleja
        printf("\n Llamada de la funccion recursiva construirMatriz");
        construirMatriz(a->matriz, n , m , a->objetivo, 2, i, j);
    }
    return a;
}

void construirMatriz (Nodo** matriz, int n, int m, Nodo* actual, int largo, int i, int j){
    for(i = -1; i<=1; i++){
        if(actual->x+i >= 0 && actual->x+i < n){
            for(j=-1; j<=1 ; j++){
                if(actual->y+j >= 0 &&
                   actual->y+j < m &&
                   !(j==0 && i==0) &&
                   matriz[actual->x+i][actual->y+j].libre
                   ){
                       if(matriz[actual->x+i][actual->y+j].costo == -1 || matriz[actual->x+i][actual->y+j].costo > largo){
                            matriz[actual->x+i][actual->y+j].costo = largo;
                            construirMatriz(matriz, n, m, &matriz[actual->x+i][actual->y+j], largo+1, i, j);
                       }
                }
            }
        }
    }
}

bool dentroAmbiente(Ambiente* ambiente, int x, int y){
    if(x >= ambiente->n || x < 0 || y >= ambiente->m || y < 0){
        return false;
    }
    return true;
}

void visualizarAmbiente(Ambiente* ambiente){
    printf("\n----------- Visializacion del ambiente ---------- \n");
    printf("%d lineas, %d columnas \n\n", ambiente->n, ambiente->m);
    int i;
    int j;
    for (i=0; i<ambiente->n; i++){
        for(j=0; j<ambiente->m; j++){
            if(j==0){
                printf("\n");
            }
            if(ambiente->matriz[i][j].libre){
                if(ambiente->inicio == &ambiente->matriz[i][j]){
                    SetColor(14);
                    printf("%3d ", ambiente->matriz[i][j].costo);
                    SetColor(15);
                } else if(ambiente->objetivo == &ambiente->matriz[i][j]){
                    SetColor(2);
                    printf("%3d ", ambiente->matriz[i][j].costo);
                    SetColor(15);
                } else {
                    printf("%3d ", ambiente->matriz[i][j].costo);
                }
            } else {
                printf("  - ");
            }
        }
    }
}

///Funccion que permite cambiar el color del output
void SetColor(int ForgC){
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
    //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void liberarAmbiente(Ambiente* ambiente){
    int i;
    for(i=0;i<ambiente->n;i++){
        free(ambiente->matriz[i]);
    }
    free(ambiente->matriz);
    free(ambiente);
    ambiente = NULL;
}
