/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   colas.h
 * Author: Martin
 *
 * Created on May 19, 2023, 4:35 PM
 */

#ifndef COLAS_H
#define COLAS_H

typedef struct {
    int codProd;
    int cant;
    double precio;
}Elemento;

typedef struct nodoC
{
    Elemento elem;
    struct nodoC *sig;
} NodoC;

typedef struct
{
    NodoC* frente;
    NodoC* final;
    int longitud;
} Cola;

void construir( Cola *pC );
bool esColaVacia( Cola C );
int obtenerLongitud( Cola C );
NodoC* crearNodo( Elemento e, NodoC *s );
void mostrar( Cola C );
void encolar( Cola *pC, Elemento e );
Elemento desencolar( Cola *pC );
void destruir( Cola *pC );

#endif /* COLAS_H */
