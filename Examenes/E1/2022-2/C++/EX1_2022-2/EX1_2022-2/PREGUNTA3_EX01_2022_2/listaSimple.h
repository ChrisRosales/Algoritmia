#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include<iostream>

using namespace std;

typedef int Elemento;

typedef struct nodo
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodo *sig;  // sig es la dirección del siguiente nodo
} Nodo;

typedef struct
{
    Nodo *cabeza; // cabeza almacena la direccion del primer nodo de la lista
    int longitud; // cantidad de nodos de la lista
} Lista;

void construir( Lista &pL );
bool esListaVacia( Lista L );
Nodo* crearNodo( Elemento e, Nodo *s );
int obtenerLongitud( Lista L );
void insertarComienzo( Lista &pL, Elemento e );
void mostrar( Lista L );
Nodo* ubicarUltimo( Lista L );
void insertarFinal( Lista &pL, Elemento e );
Nodo* ubicarElemento( Lista L, Elemento e );
Nodo* ubicarAnterior( Lista L, Elemento e );
void eliminar( Lista &pL, Elemento e );
void destruir( Lista &pL );

#endif /* LISTASIMPLE_H */

