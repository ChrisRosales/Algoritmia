/* 
 * File:   pilas.c
 * Author: cueva
 * 
 * Created on 25 de mayo de 2020, 09:55 AM
 */

#include "pilas.h"
#include <stdio.h>
#include <stdlib.h>


/* al inicio la pila se inicializa con nulo, lo que indica que estaÂ¡ vacia*/
void crear(Tpila *ptrpila) {
    *ptrpila=NULL;
}

/*Se implementaraÂ¡ usando una lista simplemente enlazada. push insertaraÂ¡ siempre
 un nodo al inicio.*/
void push(Tpila *Pila, int valor) {
    TNodoPila *ptrNuevo;
    
    ptrNuevo = (TNodoPila *) malloc(sizeof (TNodoPila));
    ptrNuevo->valor = valor;
    ptrNuevo->ptrSig = *Pila;
    *Pila = ptrNuevo;
    
}

int pila_vacia(Tpila *ptrPila){
    return *ptrPila==NULL;
}

int top(Tpila *ptrPila)
{   TNodoPila *ptrrec;
    
    ptrrec=*ptrPila;
    if(pila_vacia(ptrPila))
        return 0;
    else
        return ptrrec->valor;

}

/*Dado que se ha realizado una insercion al inicio, para que la estructura se
 comporte como pila, se debe sacar los dados a partir del inicio de la lista.*/

int pop(Tpila *Pila) {    
    TNodoPila *ptrEliminar;
    int valor;
    
    if (!pila_vacia(Pila)) { 
        ptrEliminar=*Pila;
        valor = ptrEliminar->valor; 
        *Pila = ptrEliminar->ptrSig; 
        free(ptrEliminar);
    }
    return valor;
}

/*Libera toda la memoria reservada para la lista utilizada en la pila.*/
void finalizar(Tpila ptrPila){
    TNodoPila *ptrEliminar;
    
    ptrEliminar = ptrPila;
    
    while (ptrEliminar != NULL){
        
        ptrPila = ptrEliminar->ptrSig;
        free(ptrEliminar);
        ptrEliminar = ptrPila;
    }
}

void cambia(Tpila ptrPila,int n)
{
    ptrPila->valor=n;

}
/*Solo para ver resultados*/
void imprimepila(Tpila ptrpila)
{
	while(ptrpila!=NULL){
		printf("%d ",ptrpila->valor);
		ptrpila=ptrpila->ptrSig;
	}
    printf("\n");    
}

/*A veces no se permite ojo*/
int tamanopila(Tpila ptrPila)
{	Tpila  ptraux;
    
    if(ptrPila==NULL)
    	return 0;
    	
	ptraux=ptrPila;
	ptrPila=ptrPila->ptrSig;
	return(tamanopila(ptrPila)+1);
	

}

