#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>

#include "camino.h"
#include "coordenadas.h"

#ifndef AMBIENTE_H
#define AMBIENTE_H

typedef struct Ambiente{
	Nodo** matriz;
    int n;
    int m;
    Nodo* inicio;
    Nodo* objetivo;
}Ambiente;


Ambiente* crearAmbiente (int n, int m, int** matrizInitial, Coordenadas* c_inicio, Coordenadas* c_objetivo);
void construirMatriz (Nodo** matriz, int n, int m, Nodo* actual, int largo, int i, int j);
bool dentroAmbiente(Ambiente* ambiente, int x, int y);
void visualizarAmbiente(Ambiente* ambiente);
void liberarAmbiente(Ambiente* ambiente);


#endif // AMBIENTE_H
