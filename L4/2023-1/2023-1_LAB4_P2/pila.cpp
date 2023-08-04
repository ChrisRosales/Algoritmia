#include <iostream>
#include "pila.h"

using namespace std;

void construirPila(Pila *pP) {
    // toda pila empieza vacia
    pP->cima = nullptr;
    pP->longitud = 0;
}

bool esPilaVacia(Pila P) {
    return P.cima == nullptr;
    // return P.longitud == 0;
}

int obtenerLongitud(Pila P) {
    return P.longitud;
}

NodoP* crearNodo(ElementoP e, NodoP *s) {
    NodoP *p;
    p = new NodoP;
    p->elem = e;
    p->sig = s;
    return p; // devuelve la direccion del nodo creado
}

void apilar(Pila *pP, ElementoP e) {
    NodoP *p;
    p = crearNodo(e, pP->cima);
    pP->cima = p;
    pP->longitud++;
}

void mostrar(Pila P) {
    NodoP *p;
    int i;
    if (esPilaVacia(P))
        cout << "Pila vacia" << endl << endl;
    else {
        p = P.cima;
        for (i = 1; i <= P.longitud; i++) {
            cout << p->elem << endl;
            p = p->sig;
        }
        cout << endl;
    }
}

// esta funcion solo sera invocada si la pila no es vacia

ElementoP desapilar(Pila *pP) {
    ElementoP x;
    NodoP *p;
    p = pP->cima;
    x = p->elem;
    pP->cima = p->sig;
    pP->longitud--;
    delete p;
    return x;
}

void ordenarPila(Pila *p) {
    if (esPilaVacia(*p)) {
        return;
    }
    ElementoP e = desapilar(p);
    ordenarPila(p);
    ordenarInsertar(p, e);
}

void ordenarInsertar(Pila *p, ElementoP e) {
    if (esPilaVacia(*p) || e >= p->cima->elem) {
        apilar(p, e);
        return;
    }
    ElementoP top = desapilar(p);
    ordenarInsertar(p, e);
    apilar(p, top);
}
