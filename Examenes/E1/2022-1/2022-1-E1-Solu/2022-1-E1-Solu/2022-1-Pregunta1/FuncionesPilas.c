/* 
 * File:   FuncionesPilas.c
 * Author: Piero Franchesco Gonzales Fernandez
 * Codigo: 20201706
 * Created on 15 de septiembre de 2022, 09:36 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncionesPilas.h"

void construirPila(Pila *pP){
    pP->cima = NULL;
    pP->longitud =0;
}


int esPilaVacia(Pila P){
    return P.cima == NULL;
}    

Nodo *crearNuevoNodo(ElementoPila elemento, Nodo *sig){
    Nodo *pNuevoNodo;
    pNuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    pNuevoNodo->elemento = elemento;
    pNuevoNodo->sig = sig;
    return pNuevoNodo;
}


void apilar(Pila *pP,ElementoPila elemento){
    Nodo *pNuevoNodo;
    pNuevoNodo = crearNuevoNodo(elemento,pP->cima);
    pP->cima = pNuevoNodo;
    pP->longitud++;
    
    //SOLO SE AGREGA UNO AL COMIENZO, Y SE VUELVE A CONECTAR
}

void mostrar(Pila P){
    Nodo *pNodo;
    if(esPilaVacia(P))
        printf("LA PILA ESTA VACIA\n");
    else{
        pNodo = P.cima;
        while(pNodo != NULL){
            printf("%d\n",pNodo->elemento.fechaVencimiento);
            pNodo = pNodo->sig;
        }
        putchar('\n');
        putchar('\n');
    }
    
    
    
    
}

int obtenerLongitud (Pila P){
    return P.longitud;
}

ElementoPila desapilar(Pila *pP){
    Nodo *pNodo;
    ElementoPila elemento;
    pNodo = pP->cima;
    
    elemento = pNodo->elemento;
    pP->cima = pNodo->sig;
    
    free(pNodo);
    pP->longitud--;
    return elemento;
}

ElementoPila cima (Pila p){
    return p.cima->elemento;
}