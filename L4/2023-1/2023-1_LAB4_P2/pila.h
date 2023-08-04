#ifndef PILA_H
#define PILA_H

#include "abb.h"


typedef NodoABB * ElementoP;

typedef struct nodoP {
    ElementoP elem;
    struct nodoP *sig;
} NodoP;

typedef struct {
    NodoP *cima;
    int longitud;
} Pila;
void construirPila(Pila *pP);
bool esPilaVacia(Pila P);
int obtenerLongitud(Pila P);
NodoP* crearNodo(ElementoP e, NodoP *s);
void apilar(Pila *pP, ElementoP e);
void mostrar(Pila P);
ElementoP desapilar(Pila *pP);
void ordenarPila(Pila *p);
void ordenarInsertar(Pila *p, ElementoP e);
#endif // !PILA_H

