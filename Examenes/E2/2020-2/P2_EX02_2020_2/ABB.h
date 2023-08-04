/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ABB.h
 * Author: Ricardo
 *
 * Created on 10 de julio de 2023, 02:07 PM
 */

#ifndef ABB_H
#define ABB_H

using namespace std;

typedef struct elem{
    int id_producto;
    int semana;
    int cantProducir;
}Elemento;

typedef struct nodo{
    Elemento elem;      // dato
    struct nodo *hizq;  // puntero al hijo izquierdo
    struct nodo *hder;  // puntero al hijo derecho
} NodoABB;

typedef NodoABB * ABB;

void construir( ABB &pA );
NodoABB* crearNodo( Elemento e );
void insertar( ABB &pA, Elemento e );
NodoABB* obtenerRaiz( ABB A );
int es_arbol_vacio(ABB );
void mostrarEnOrden( ABB );
void mostrarEnPreOrden( ABB );
void mostrarEnPostOrden( ABB );
bool buscar( ABB, Elemento e );
NodoABB* menor( NodoABB *pR );
NodoABB* mayor( NodoABB *pR );
int contarNodos( NodoABB *pR );
int sumarNodos( NodoABB *pR );

#endif /* ABB_H */

