//En el archivo lse.c se implementarán las operaciones de la lista simplemente enlazada
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"

void construir_lista(Lista *tad){
	tad->cabeza=NULL;
        tad->cola=NULL;
	tad->longitud=0;
}

int es_lista_vacia(Lista tad){
	return tad.cabeza==NULL;
}

Nodo *crear_nuevo_nodo(ElementoLista elemento, Nodo* sig){
	Nodo *nuevo_nodo=(Nodo*)malloc(sizeof(Nodo));
	nuevo_nodo->elemento=elemento;
	nuevo_nodo->sig=sig;
	return nuevo_nodo;
}

void insertar_al_inicio(Lista *tad, ElementoLista elemento){
	Nodo *nuevo_nodo=crear_nuevo_nodo(elemento, tad->cabeza);
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
		printf("%d", recorrido->elemento);
		recorrido=recorrido->sig;
	}
	printf("]\n");
}

void insertar_al_final(Lista *tad, ElementoLista elemento){
	Nodo *nuevo_nodo=crear_nuevo_nodo(elemento, NULL);

        if(es_lista_vacia(*tad)){
            tad->cabeza=nuevo_nodo;
            tad->cola=nuevo_nodo;
        }
        else{
            tad->cola->sig = nuevo_nodo;
            tad->cola = nuevo_nodo; //No olvidarse
        }
        tad->longitud++;
}


int longitud(Lista tad){
	return tad.longitud;
}

ElementoLista retorna_cabeza(Lista tad){
    if (es_lista_vacia(tad)){
        printf("No existe la cabeza por que la lista estÃ¡ vacÃ­a.\n");
        exit(4);
    }
    return tad.cabeza->elemento;
}

void elimina_cabeza(Lista *tad){
    if (es_lista_vacia(*tad)){
        printf("No se puede eliminar la cabeza pues la lista estÃ¡ vacÃ­a.\n");
        exit(2);
    }
    Nodo *nodo_a_eliminar=tad->cabeza;    
    tad->cabeza=tad->cabeza->sig;
    free(nodo_a_eliminar); 
    tad->longitud--;          
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