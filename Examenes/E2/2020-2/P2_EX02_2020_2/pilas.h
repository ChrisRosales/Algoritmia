/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pilas.h
 * Author: Ricardo
 *
 * Created on 10 de julio de 2023, 02:07 PM
 */

#ifndef PILAS_H
#define PILAS_H

#include "ABB.h"

typedef struct nodoP
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodoP *sig;  // sig es la dirección del siguiente nodo
} NodoP;

typedef struct
{
    NodoP *cima; // cima almacena la direccion del primer nodo de la pila
    int longitud; // cantidad de nodos de la pila
} Pila;

void construir( Pila &pP );
bool esPilaVacia( Pila P );
NodoP* crearNodo( Elemento e, NodoP *s );
void apilar( Pila &pP, Elemento e );
void mostrar( Pila P );
Elemento desapilar( Pila &pP ); // solo se usara esta funcion si la pila tiene datos
void destruir( Pila *pP );
int top(Pila ptrPila);

#endif /* PILAS_H */

