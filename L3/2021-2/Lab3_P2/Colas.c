/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Colas.c
 * Author: cueva
 * 
 * Created on 26 de mayo de 2020, 02:54 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "Colas.h"

/*Solo para impresion esta permitido trabajar como lista*/
void imprimecola(TCola ptrcola)
{
	while(ptrcola!=NULL){
		printf("%d ",ptrcola->elem);
		ptrcola=ptrcola->sig;
	}
	
	printf("\n");
}

/*implementacion de las funciones para la cola*/
void crea_cola(TCola *ptrCola){
    *ptrCola = NULL;
}

int cola_vacia(TCola ptrCola){
    return ptrCola==NULL;
}

/*encolar, se inserta un elemento al final de la cola. Se representa como una 
 insercion al inicio.*/
void encolar(TCola *ptrCola, int valor){
    TNodoCola *ptrNuevo = (TNodoCola*)malloc(sizeof(TNodoCola));
    ptrNuevo->elem=valor;
    ptrNuevo->sig=*ptrCola;
    *ptrCola=ptrNuevo; 
}

/*Solo para el desencolar esta permitido trabajar como lista*/
int desencolar(TCola *ptrCola)
{   TNodoCola *ptrRecorrido, *ptrUltimo;
    int valor;    
    if (!cola_vacia(*ptrCola))
    {
        ptrUltimo = NULL;
        ptrRecorrido = *ptrCola;
        while (ptrRecorrido->sig)
        {
            ptrUltimo = ptrRecorrido;
            ptrRecorrido = ptrRecorrido->sig;
        }
        if (ptrUltimo == NULL)
            *ptrCola=NULL;
        else
            ptrUltimo->sig=NULL; 
            
        valor=ptrRecorrido->elem;
        free(ptrRecorrido);
        return(valor);
    }
    
}


