//En el archivo lse.c se implementarán las operaciones de la lista simplemente enlazada
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"

void construir_lista(Lista *tad){
	tad->cabeza=NULL;
	tad->longitud=0;
}

int es_lista_vacia(Lista tad){
	return tad.cabeza==NULL;
}

Nodo *crear_nuevo_nodo(ElementoLista elemento, DiaLista dia, Nodo* sig){
	Nodo *nuevo_nodo=(Nodo*)malloc(sizeof(Nodo));
	nuevo_nodo->elemento=elemento;
	nuevo_nodo->dia=dia;
	nuevo_nodo->sig=sig;
	return nuevo_nodo;
}

void insertar_al_inicio(Lista *tad, ElementoLista elemento, DiaLista dia){
	Nodo *nuevo_nodo=crear_nuevo_nodo(elemento, dia, tad->cabeza);
	tad->cabeza=nuevo_nodo;
	tad->longitud++;
}

//para la operación imprime y para muchas otras operaciones, se recorre la lista de forma
//secuencial.
void imprime(Lista tad){
	Nodo *recorrido = tad.cabeza;
	int esta_imprimiendo_la_cabeza=1;
	printf("[");
	while (recorrido != NULL){
		if (!esta_imprimiendo_la_cabeza)
			printf(", ");
		else
			esta_imprimiendo_la_cabeza=0;
		printf("%c%d", recorrido->dia, recorrido->elemento);
		recorrido=recorrido->sig;
	}
	printf("]\n");
}

void insertar_al_final(Lista *tad, ElementoLista elemento, DiaLista dia){
	Nodo *nuevo_nodo=crear_nuevo_nodo(elemento, dia, NULL);
	Nodo *ultimo_nodo=obtener_ultimo_nodo(*tad);
	//Si no existe último nodo, es decir, la cabeza no apunta a nada, es porque la
	//lista está vacia
	if (ultimo_nodo==NULL)
		tad->cabeza=nuevo_nodo;
	else
		ultimo_nodo->sig=nuevo_nodo;
	tad->longitud++;
}

Nodo *obtener_ultimo_nodo(Lista tad){
	Nodo *ultimo=NULL;
	Nodo *recorrido=tad.cabeza;
	while(recorrido != NULL){
		ultimo=recorrido;
		recorrido=recorrido->sig;
	}
	return ultimo;
}

void insertar_en_orden(Lista *tad, ElementoLista elemento, DiaLista dia){
	Nodo *nuevo_nodo=crear_nuevo_nodo(elemento, dia, NULL);
	Nodo *nodo_anterior=obtener_nodo_anterior(*tad, elemento);
	//Si el nodo anterior es igual a null, pueden pasar dos cosas:
	//  1. La lista se encuentre vacía.
	//  2. Se tiene que insertar al inicio. 
	if (nodo_anterior==NULL){
		nuevo_nodo->sig=tad->cabeza;
		tad->cabeza=nuevo_nodo;
	}
	else{
		nuevo_nodo->sig=nodo_anterior->sig;
		nodo_anterior->sig=nuevo_nodo;
	}
	tad->longitud++;
}

Nodo *obtener_nodo_anterior(Lista tad, ElementoLista elemento){
	Nodo *anterior=NULL;
	Nodo *recorrido=tad.cabeza;
	while (recorrido!=NULL && recorrido->elemento<elemento){
		anterior=recorrido;
		recorrido=recorrido->sig;
	}
	return anterior;
}

void destruir_lista(Lista *tad){
	Nodo *recorrido=tad->cabeza;
	while (recorrido != NULL){
		Nodo *nodo_a_eliminar=recorrido;
		recorrido=recorrido->sig;
		free(nodo_a_eliminar);
	}
	tad->cabeza=NULL;
	tad->longitud=0;
}

int longitud(Lista tad){
	return tad.longitud;
}

void reverse(Lista *tad){
    int i,j;
    Nodo * runner_ptr;
    Nodo * previous_ptr;
    Nodo * ini_ptr;

    int n = longitud(*tad);
    
    for (i=1; i<n; i++){
        runner_ptr = tad->cabeza;    
        for (j=i; j<n; j++){
            previous_ptr = runner_ptr;
            runner_ptr = runner_ptr->sig;
        }
        if (i == 1)
            ini_ptr = runner_ptr;
        runner_ptr->sig = previous_ptr;
    }
    previous_ptr->sig = NULL;
    tad->cabeza = ini_ptr;
}

