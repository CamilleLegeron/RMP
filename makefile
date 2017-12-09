all : main.o hill_climbing.o solucion_inicial.o ambiente.o camino.o nodo.o coordenadas.o
	gcc main.o hill_climbing.o solucion_inicial.o ambiente.o camino.o nodo.o coordenadas.o -o rmp

main.o : main.c hill_climbing.c solucion_inicial.c ambiente.c camino.c nodo.c coordenadas.c
	gcc -c main.c -o main.o

hill_climbing.o : hill_climbing.c camino.c nodo.c
	gcc -c hill_climbing.c -o hill_climbing.o

solucion_inicial.o : solucion_inicial.c ambiente.c camino.c nodo.c coordenadas.c
	gcc -c solucion_inicial.c -o solucion_inicial.o

ambiente.o : ambiente.c camino.c nodo.c coordenadas.c
	gcc -c ambiente.c -o ambiente.o

camino.o : camino.c nodo.c
	gcc -c camino.c -o camino.o

nodo.o : nodo.c
	gcc -c nodo.c -o nodo.o

coordenadas.o : coordenadas.c
	gcc -c coordenadas.c -o coordenadas.o

#supresion de los archivos temporales
clean :
	rm -rf *.o

#supresion de todos los archivos sino los fuentes para una reconstruccion completa
mrproper :
	rm -rf rmp
