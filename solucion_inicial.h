#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "ambiente.h"

#ifndef SOLUCION_INICIAL_H
#define SOLUCION_INICIAL_H

bool crearSolucionInitial(Ambiente* ambiente, Nodo* actual, Nodo* objetivo, Camino* camino, int random);
void demarcarNodos (Ambiente* ambiente);
Orientacion* crearOrientacion();
void definirOrientacion(Orientacion* orientacion, Nodo* inicio, Nodo* objetivo);
void redefinirOrientacion(Orientacion* o, Direccion d);
void construirListaReferencia(Ambiente* a, Orientacion* o, Nodo* n);
void removerEnListaReferencia(Orientacion* o, int aRemover);
Nodo* elegirNuevoSiguiente(Nodo* actual, Ambiente* ambiente, Orientacion* orientacion, int random);

#endif // SOLUCION_INICIAL_H

