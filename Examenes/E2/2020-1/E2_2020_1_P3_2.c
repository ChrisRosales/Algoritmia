#include <stdio.h>
#include <stdlib.h>

// preg 3.2

typedef char* TInfo;

typedef struct Nodo {
	TInfo elem;
	int peso; // id de la pregunta/respuesta
	int valor; // 1: verdadero ; 0 : falso
	struct Nodo *izq;
	struct Nodo *der;
} TNodo;

typedef TNodo *TArbol;


void crearArbol(TArbol *Arbol) {
	(*Arbol) = NULL;
}

void insertarRec(TArbol *Arbol, TInfo elem, int peso, int valor) {	
	if ((*Arbol) == NULL) {
		TNodo *ptrNuevo = (TNodo *)malloc(sizeof(TNodo));
		ptrNuevo->elem = elem;
		ptrNuevo->peso = peso;
		ptrNuevo->valor = valor;
		ptrNuevo->izq = ptrNuevo->der = NULL;
		(*Arbol) = ptrNuevo;
	} else {
		if ((*Arbol)->peso > peso) insertarRec(&((*Arbol)->izq),elem,peso,valor);
		else insertarRec(&((*Arbol)->der),elem,peso,valor);
	}
}

void consultar_enfermedad (TArbol arbol) {
	char rpta;
	printf("%s \n",arbol->elem); // preguntamos
	if (arbol->izq == NULL || arbol->der == NULL) return; // si ya no hay mas hijos es rpta
	scanf(" %c",&rpta); // de lo contrario necesitamos saber la rpta a la pregunta
	if (rpta == 'S') consultar_enfermedad(arbol->izq); // si es Si vamos a la izquierda
	else consultar_enfermedad(arbol->der); // si es NO vamos a la derecha
}

int main () {
	TArbol arbol;
	crearArbol(&arbol);
	// insertamos de forma fija y arbitraria, el criterio se evaluara en la funcion consultar_enfermedad
	insertarRec(&arbol,"Tiene tos seca?",50,2);
	insertarRec(&arbol,"Tiene fiebre?",30,1);
	insertarRec(&arbol,"Tiene tos con flema?",70,0);
	insertarRec(&arbol,"Le duele la garganta?",40,0);
	insertarRec(&arbol,"Le falta aire?",20,1);
	insertarRec(&arbol,"Riesgo de Covid",10,1);
	insertarRec(&arbol,"Debe estar en observacion",25,0);
	insertarRec(&arbol,"Tiene gripe, cuidese",60,1);
	insertarRec(&arbol,"No tiene nada, cuidese",80,0);
	insertarRec(&arbol,"Debe estar en observacion",35,1);
	insertarRec(&arbol,"No hay riesgo",45,0);
	consultar_enfermedad(arbol);
	return 0;
}
