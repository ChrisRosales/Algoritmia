/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   colas.h
 * Author: Ricardo
 *
 * Created on 10 de julio de 2023, 02:07 PM
 */

#ifndef COLAS_H
#define COLAS_H

#include "ABB.h"

typedef struct nodoC
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodoC *sig;  // sig es la dirección del siguiente nodo
} NodoC;

typedef struct
{
    NodoC *frente; // frente almacena la direccion del primer nodo de la cola
    NodoC *final; // final almacena la direccion del ultimo nodo de la colaa
    int longitud; // cantidad de nodos de la cola
} Cola;

void construir( Cola &pC );
bool esColaVacia( Cola C );
int obtenerLongitud( Cola C );
NodoC* crearNodo( Elemento e, NodoC *s );
void encolar( Cola &pC, Elemento e );
void mostrar( Cola C );
Elemento desencolar( Cola &pC );
void destruir( Cola &pC );

#endif /* COLAS_H */

