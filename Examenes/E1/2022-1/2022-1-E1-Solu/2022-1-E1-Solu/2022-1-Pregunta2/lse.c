
/* 
 * File:   lse.c
 * Author: cueva.r
 * 
 * Created on 24 de agosto de 2022, 09:00 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"


void construir(Lista *tad){
    tad->cabeza = NULL;
    tad->vip = NULL;
    tad->cliente = NULL;
    tad->cola = NULL;
    tad->longitud = 0;
}

int es_lista_vacia(Lista tad){
    if(tad.cabeza==NULL) return 1;
    return 0;
}

Nodo *crear_nodo(Elemento dato){
    Nodo *nuevo;
    
    nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->elemento.codigo = dato.codigo;
    nuevo->elemento.prioridad = dato.prioridad;
    nuevo->sig = NULL;    
    
    return nuevo;
}

void insertar_prioridad(Lista *tad,Elemento elemento){
    Nodo *nuevo = crear_nodo(elemento);
    
    if(es_lista_vacia(*tad)){
        tad->cabeza = nuevo;
        tad->cola = nuevo;
        if(nuevo->elemento.prioridad=='V')
            tad->vip = nuevo;
        if(nuevo->elemento.prioridad=='C')
            tad->cliente =nuevo;
    }else{
        if(nuevo->elemento.prioridad=='V'){
            if(tad->vip==NULL){
                nuevo->sig = tad->cabeza;
                tad->cabeza = nuevo;
                tad->vip = nuevo;  
            }
            else{
                if(tad->vip->sig==NULL)
                    tad->cola = nuevo;
                else
                    nuevo->sig = tad->vip->sig;
                tad->vip->sig = nuevo;
                tad->vip = nuevo;
            }
        }
        if(nuevo->elemento.prioridad=='C'){
            if(tad->cliente==NULL){
                if(tad->cola->elemento.prioridad=='V'){
                    tad->cola->sig = nuevo;
                    tad->cola = nuevo;
                    tad->cliente = nuevo;
                }
                if(tad->cola->elemento.prioridad=='N'){
                    if(tad->vip==NULL){
                        nuevo->sig = tad->cabeza;
                        tad->cliente = nuevo;
                        tad->cabeza = nuevo;
                    }else{
                        nuevo->sig = tad->vip->sig;
                        tad->vip->sig = nuevo;
                        tad->cliente = nuevo; 
                    }
                }
            }
            else{
                if(tad->cliente==tad->cola){
                    tad->cliente->sig=nuevo;
                    tad->cola = nuevo;
                    tad->cliente = nuevo;                    
                }
                else{
                    nuevo->sig = tad->cliente->sig;
                    tad->cliente->sig = nuevo;
                    tad->cliente = nuevo;                    
                }
            }
        }
        if(nuevo->elemento.prioridad=='N'){
            tad->cola->sig = nuevo;
            tad->cola = nuevo;
        } 
        
        
    }
    
    
    tad->longitud++;
}

void imprime_elemento(Elemento dato){
    printf("(%c - %d)",dato.prioridad,dato.codigo);
    
}
void imprimir(Lista tad){
    Nodo *rec;
    rec = tad.cabeza;
    if(es_lista_vacia(tad)){
        printf("La lista esta vacia\n");
        return;
    }
    while(rec!=NULL){
        imprime_elemento(rec->elemento);
        rec = rec->sig;
    }
    printf("\n");
}

void destruir(Lista *tad){
    Nodo *ptr,*aux=NULL; 

    ptr = tad->cabeza;
    
    while(ptr!=NULL){
        aux = ptr;
        ptr = ptr->sig;
        free(aux);
    }
    tad->cabeza = NULL;
    tad->longitud = 0;
    
}

Elemento retorna_cabeza(Lista tad){
    if(es_lista_vacia(tad)){
        printf("No hay cabeza\n");
        exit(2);
    }
    return tad.cabeza->elemento;
}
void elimina_cabeza(Lista *tad){
    Nodo *aux;
    
    if(es_lista_vacia(*tad)){
        printf("No hay cabeza que eliminar\n");
        exit(2);
    } 
    aux = tad->cabeza;
    tad->cabeza = tad->cabeza->sig;
    free(aux);
    tad->longitud --;
}


