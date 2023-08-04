
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
    tad->longitud = 0;
}

int es_lista_vacia(Lista tad){
    if(tad.cabeza==NULL) return 1;
    return 0;
}

Nodo *crear_nodo(Elemento dato){
    Nodo *nuevo;
    
    nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->elemento = dato;
    nuevo->sig = NULL;    
    
    return nuevo;
}

void insertar_inicio(Lista *tad,Elemento dato){
    Nodo *nuevo;
    nuevo = crear_nodo(dato);
    
    if(tad->longitud==0)
        tad->cabeza = nuevo;
    else{
        nuevo->sig = tad->cabeza;
        tad->cabeza = nuevo;
    }   
    tad->longitud++;
}

void insertar_orden(Lista *tad,Elemento dato){
    Nodo *nuevo,*ptr,*aux=NULL;
    
    nuevo = crear_nodo(dato);
    
    ptr = tad->cabeza;
    
    while(1){
        if(ptr==NULL || dato < ptr->elemento  ){
            break;
        }
        aux = ptr;
        ptr = ptr->sig;
    }
    if(aux==NULL){
        nuevo->sig = tad->cabeza;
        tad->cabeza = nuevo;
    }
    else{
        aux->sig = nuevo;
        nuevo->sig = ptr;
    }
    tad->longitud ++;
    
}

void insertar_final(Lista *tad,Elemento dato){
    Nodo *nuevo,*ptr,*aux=NULL;
    
    nuevo = crear_nodo(dato);
    
    ptr = tad->cabeza;
    
    while(ptr!=NULL){
        aux = ptr;
        ptr = ptr->sig;       
    }
    if(aux==NULL){
        tad->cabeza = nuevo;
    }
    else{
        aux->sig = nuevo;
    }
    tad->longitud++;

}


void imprime_elemento(Elemento dato){
    printf("%d ",dato);
    
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

int compara(Elemento dato1, Elemento dato2){
    
    return dato1==dato2;
}

Nodo *busca_nodo(Lista tad,Elemento dato){
    Nodo *ptr;
    ptr = tad.cabeza;
    while(ptr!=NULL && !compara(ptr->elemento,dato) ){
        ptr = ptr->sig;
    }
    return ptr;
}

void Elimina_nodo(Lista *tad,Elemento dato){
    Nodo *ptr,*aux=NULL;
    
    ptr = tad->cabeza;
    while(ptr!=NULL && !compara(ptr->elemento,dato) ){
        aux = ptr;
        ptr = ptr->sig;
    }
    if(ptr!=NULL){
        if(aux==NULL){
            tad->cabeza = ptr->sig;
        }
        else{
            aux->sig = ptr->sig;
        }
        free(ptr);
        tad->longitud--;
    }
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


