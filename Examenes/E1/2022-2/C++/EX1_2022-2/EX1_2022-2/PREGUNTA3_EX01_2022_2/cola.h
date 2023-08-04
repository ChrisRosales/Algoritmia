#ifndef COLA_H
#define COLA_H

#include <iostream>

using namespace std;

typedef int Elemento;

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
int desencolar( Cola &pC );
void destruir( Cola &pC );

#endif /* COLA_H */