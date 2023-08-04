#include "pila.h"

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
            cout << p->elem << endl;
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
{   NodoP *ptrrec;
    
    ptrrec = ptrPila.cima;
    if(esPilaVacia(ptrPila))
        return 0;
    else
        return ptrrec->elem;

}
void unirPilas(Pila &Kupa1,Pila &Kupa2){
    int elem;
    while(Kupa2.longitud!=0){
        elem=desapilar(Kupa2);
        apilar(Kupa1,elem);
    }
}
void ordenarPilar(Pila &Kupa1){
    //Nos permiten utilizar una pila auxiliar por lo que creamos una
    Pila pilaAux;
    construir(pilaAux);
    int mayor;
    while(Kupa1.longitud!=0){
        //Desapilamos un elemento del Kupa1
        mayor=desapilar(Kupa1);
        //Verificamos si es el elemento de la pilaAux es mayor al elemento de Kupa1
        while(pilaAux.longitud!=0 and pilaAux.cima->elem>mayor){
            apilar(Kupa1,desapilar(pilaAux));
        }
        //Lo apilamos en la pilaAux
        apilar(pilaAux,mayor);
    }
    while(pilaAux.longitud!=0){
        apilar(Kupa1,desapilar(pilaAux));
    }
}
void pasarKupaAChampinon(Pila &origen,Pila &destino){
    Elemento nivel;
    //CASO BASE
    if(origen.longitud==0){
        return;
    }
    nivel=desapilar(origen);
    pasarKupaAChampinon(origen,destino);
    apilar(destino,nivel);
}
