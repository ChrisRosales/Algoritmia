/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "pilas.h"

using namespace std;

void construir( Pila &pP )
{
    // se crea la pila vacia
    pP.cima = NULL;
    pP.longitud = 0;
}

bool esPilaVacia( Pila P )
{
    return P.cima == NULL;
    // return P.longitud == 0;
}

NodoP* crearNodo( Elemento e, NodoP *s )
{
    NodoP *p;
    p = new NodoP; // se crea un nodo y su direccion se almacena en p
    p->elem = e;
    p->sig = s;
    return p;  // devuelve la direccion del nodo creado
}

void apilar( Pila &pP, Elemento e )
{
    NodoP *p;
    p = crearNodo( e, pP.cima );
    pP.cima = p;
    pP.longitud++;
}

void mostrar( Pila P )
{
    NodoP *p;
    int i;
    if ( esPilaVacia(P) )
        cout << "Pila vacia" << endl << endl;
    else
    {
        p = P.cima;
        for(i=1; i<=P.longitud; i++)
        {
            cout << p->elem.id_producto<<"  "<< endl;
            p = p->sig;
        }
        cout << endl;
    }
}

// solo se usara esta funcion si la pila tiene datos
Elemento desapilar( Pila &pP )
{
    NodoP *p;
    Elemento e;
    p = pP.cima;
    e = p->elem;
    pP.cima = p->sig;
    pP.longitud--;
    delete p;
    return e;
}

void destruir( Pila *pP )
{
    int i;
    NodoP *p, *q;
    if ( !esPilaVacia(*pP) )
    {
        p = pP->cima;
        for(i=1; i<=pP->longitud; i++)
        {
            q = p->sig;
            delete p;
            p = q;
        }
        pP->cima = NULL;
        pP->longitud = 0;
    }
}

int top(Pila ptrPila)
{   Pila ptrrec;
    
    ptrrec = ptrPila;
    if(esPilaVacia(ptrPila))
        cout << "Pila vacia"<<endl;
    else
       return ptrrec.cima->elem.id_producto;

}

