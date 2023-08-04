#include "cola.h"

void construir( Cola &pC )
{
    // se crea la cola vacia
    pC.frente= NULL;
    pC.final = NULL;
    pC.longitud = 0;
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
    p = new NodoC; // se crea un nodo y su direccion se almacena en p
    p->elem = e;
    p->sig = s;
    return p;  // retorna la dirección del nodo creado
}

void encolar( Cola &pC, Elemento e )
{
    NodoC *p, *pU;
    p = crearNodo( e, NULL);
    if ( esColaVacia(pC) )
    {
        pC.frente = p;
    }
    else
    {
        pU = pC.final;
        pU->sig = p;
    }
    pC.final = p;
    pC.longitud++;
}

void mostrar( Cola C )
{
    NodoC *p;
    if ( esColaVacia(C) )
        cout << "La cola esta vacia" << endl;
    else
    {
        p = C.frente;
        while ( p!= NULL )
        {
            cout << p->elem << " ";
            p = p->sig;
        }
        cout << endl;
    }
}

// esta funcion solo sera invocada previa verificacion de que la cola no esta vacia
Elemento desencolar( Cola &pC )
{
    Elemento x;
    NodoC *p;
    p = pC.frente;
    if ( p->sig == NULL ) // hay un solo nodo en la Cola
        pC.final = NULL;
    pC.frente = p->sig;
    x = p->elem;
    pC.longitud--;
    delete p;
    return x;
}

void destruir( Cola &pC )
{
    int i;
    NodoC *p, *q;
    if ( !esColaVacia(pC) )
    {
        p = pC.frente;
        for(i=1; i<=pC.longitud; i++)
        {
            q = p->sig;
            delete p;
            p = q;
        }
        pC.frente = NULL;
        pC.final = NULL;
        pC.longitud = 0;
    }
}