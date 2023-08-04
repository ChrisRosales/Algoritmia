#include <stdio.h>
#include <stdlib.h>

// preg 3.1

typedef int TInfo;

typedef struct Nodo {
	TInfo elem;
	struct Nodo *izq;
	struct Nodo *der;
} TNodo;

typedef TNodo *TArbol;


void crearArbol(TArbol *Arbol) {
	(*Arbol) = NULL;
}

void insertarRec(TArbol *Arbol, TInfo elem) {	
	if ((*Arbol) == NULL) {
		TNodo *ptrNuevo = (TNodo *)malloc(sizeof(TNodo));
		ptrNuevo->elem = elem;
		ptrNuevo->izq = ptrNuevo->der = NULL;
		(*Arbol) = ptrNuevo;
	} else {
		if ((*Arbol)->elem > elem) insertarRec(&((*Arbol)->izq),elem);
		else insertarRec(&((*Arbol)->der),elem);
	}
}

int altura(TArbol arbol, int *t) {
	if (arbol == NULL) return 0;
	int alt_izq = altura(arbol->izq,t);
	int alt_der = altura(arbol->der,t);
	(*t)++;
	if (alt_izq > alt_der) return alt_izq + 1;
	else return alt_der + 1;
}

int main () {
	TArbol arbol;
	int a;
	double d;
	crearArbol(&arbol);
	// insertamos valores arbitrarios
	insertarRec(&arbol,80);
	insertarRec(&arbol,40);
	insertarRec(&arbol,100);
	insertarRec(&arbol,30);
	insertarRec(&arbol,60);
	insertarRec(&arbol,120);
	insertarRec(&arbol,55);
	insertarRec(&arbol,50);
	insertarRec(&arbol,70);
	insertarRec(&arbol,110);
	insertarRec(&arbol,130);
	int t = 0; // almacenamos el numero de nodos aca
	a = altura(arbol,&t); // calculamos la altura y el numero de nodos a la vez en un solo recorrido
	d = (double)t/a; // densidad
	printf("La densidad es %lf",d);
	return 0;
}
