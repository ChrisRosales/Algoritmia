/* 
 * File:   listaSimple.h
 * Author: PC
 *
 * Created on 27 de mayo de 2023, 03:35 PM
 */

#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "ABB.h"

typedef struct nodoL
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodoL *sig;  // sig es la direcciÃ³n del siguiente nodo
} NodoL;

typedef struct
{
    NodoL *cabeza; // cabeza almacena la direccion del primer nodo de la lista
    NodoL *cola;
    int longitud; // cantidad de nodos de la lista
} Lista;

void construir( Lista &pL );
bool esListaVacia( Lista L );
NodoL* crearNodo( Elemento e, NodoL *s );
int obtenerLongitud( Lista L );
void insertarComienzo( Lista &pL, Elemento e );
void mostrar( Lista L );
NodoL* ubicarUltimo( Lista L );
void insertarFinal( Lista &pL, Elemento e );
NodoL* ubicarElemento( Lista L, Elemento e );
NodoL* ubicarAnterior( Lista L, Elemento e );
void eliminar( Lista *pL, Elemento e );
void destruir( Lista *pL );

#endif /* LISTASIMPLE_H */

