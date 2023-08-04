/* 
 * File:   colas.cpp
 * Author: Martin
 * 
 * Created on May 19, 2023, 4:35 PM
 */

#include <cstdlib>
#include <iostream>
#include "colas.h"

using namespace std;

void construir( Cola *pC )
{
    pC->frente = NULL;
    pC->final = NULL;
    pC->longitud = 0;
    // la cola empieza vacia
}

bool esColaVacia( Cola C )
{
    return C.frente == NULL;
    // return C.final == NULL;
    // return C.longitud == 0;
}

int obtenerLongitud( Cola C )
{
    return C.longitud;
}

NodoC* crearNodo( Elemento e, NodoC *s )
{
    NodoC *p;
    p = new NodoC; // se crea el nuevo nodo
    p->elem = e;
    p->sig = s;
    return p; // retorna la direccion del nodo creado
} 

void mostrar( Cola C )
{
    NodoC *p;
    int i;
    if ( esColaVacia(C) )
        cout << "Cola vacia" <<endl;
    else
    {
        p = C.frente;
        for(i=1; i<=C.longitud; i++)
        {
            cout <<"Codigo:"<< p->elem.codProd << "  Precio:"<<p->elem.precio<<" Cantidad:"<<p->elem.cant<<endl;
            p = p->sig;
        }
        cout << endl;
    }
}

void encolar( Cola *pC, Elemento e )
{
    NodoC *p, *pU;
    p = crearNodo( e, NULL);
    if( esColaVacia(*pC) )
    {
        pC->frente = p;
    }
    else
    {
        pU = pC->final;
        pU->sig = p;
    }
    pC->final = p;
    pC->longitud++;
}

// esta funcion solo sera invocada si la cola no esta vacia
Elemento desencolar( Cola *pC )
{
    NodoC *p;
    Elemento x;
    p = pC->frente;
    x = p->elem;
    pC->frente = p->sig;
    if ( pC->frente == NULL )
        pC->final = NULL;
    pC->longitud--;
    delete p; // elimina el Nodo
    return x;
}

void destruir( Cola *pC )
{
    NodoC *p, *q;
    int i;
    if ( !esColaVacia(*pC) )
    {
        p = pC->frente;
        for(i=1; i<=pC->longitud; i++)
        {
            q = p->sig;
            delete p;
            p = q;
        }
        pC->frente = NULL;
        pC->final = NULL;
        pC->longitud = 0;
    }
}