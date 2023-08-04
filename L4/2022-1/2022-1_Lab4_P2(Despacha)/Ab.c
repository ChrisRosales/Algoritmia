/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ab.c
 * Author: cueva.r
 * 
 * Created on 13 de septiembre de 2022, 08:43 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ab.h"
#include "Colas.h"

void construir_ab(ArbolB *tad){
    *tad = NULL;
}

int es_arbol_vacio(ArbolB tad){
    return tad==NULL;
    
}

NodoArbol* crear_nodoab(ElementoArbol dato,ArbolB arbol_izq,ArbolB arbol_der){
    NodoArbol* nuevo = (NodoArbol*) malloc(sizeof(NodoArbol));
    
    nuevo->elemento.cantidad=dato.cantidad;
    nuevo->elemento.lote=dato.lote;
    nuevo->hijo_izq = arbol_izq;
    nuevo->hijo_der = arbol_der;
    return nuevo;
}

void insertar_ab(ArbolB* tad,ElementoArbol dato,ArbolB arbol_izq,ArbolB arbol_der){
   NodoArbol* nuevo = crear_nodoab(dato,arbol_izq,arbol_der);
   *tad=nuevo; 
}
void imprimirelemento(ElementoArbol dato){
    printf("[%d %d]",dato.lote,dato.cantidad);    
}

int cuenta_nodos(ArbolB tad){
    if(es_arbol_vacio(tad))    
        return 0;
    return (1+cuenta_nodos(tad->hijo_der)+cuenta_nodos(tad->hijo_izq));
}

int cuenta_hojas(ArbolB tad){
    if(es_arbol_vacio(tad))    
        return 0;
    else
        if(es_arbol_vacio(tad->hijo_der) 
                && es_arbol_vacio(tad->hijo_izq))
            return 1;
        else    
            return cuenta_hojas(tad->hijo_der)+cuenta_hojas(tad->hijo_izq);
}

int maximo(int a,int b){
    if(a>b) return a;
    return b;
}

int altura(ArbolB tad){
  if(es_arbol_vacio(tad))    
        return 0;
  return 1 + maximo(altura(tad->hijo_der),altura(tad->hijo_izq));
}



void en_orden(ArbolB tad){
    if(!es_arbol_vacio(tad)){
        en_orden(tad->hijo_izq);
        imprimirelemento(tad->elemento);
        en_orden(tad->hijo_der);
    }   
}

void pre_orden(ArbolB tad){
    if(!es_arbol_vacio(tad)){
        imprimirelemento(tad->elemento);
        pre_orden(tad->hijo_izq);
        pre_orden(tad->hijo_der);
    }    
}

void destruir_ab(ArbolB *tad){
    if(!es_arbol_vacio(*tad)){
        destruir_ab(&(*tad)->hijo_izq);
        destruir_ab(&(*tad)->hijo_der);
        free(*tad);
        *tad = NULL;
    }
}


