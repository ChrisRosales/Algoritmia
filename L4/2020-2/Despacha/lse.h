/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lse.h
 * Author: cueva.r
 *
 * Created on 24 de agosto de 2022, 09:00 AM
 */

#ifndef LSE_H
#define LSE_H

typedef int Elemento;

typedef struct nodo{
    Elemento elemento;    
    struct nodo *sig;
} Nodo;

typedef struct{
    Nodo *cabeza;
    int longitud;
}Lista;

void construir(Lista *);
void insertar_inicio(Lista *,Elemento );
void imprimir(Lista );
void insertar_orden(Lista *,Elemento );
void insertar_final(Lista *,Elemento );
Nodo *crear_nodo(Elemento );
Nodo *busca_nodo(Lista tad,Elemento dato);
void destruir(Lista *);
void Elimina_nodo(Lista *,Elemento );
int es_lista_vacia(Lista );
Elemento retorna_cabeza(Lista );
void elimina_cabeza(Lista *);

#endif /* LSE_H */
