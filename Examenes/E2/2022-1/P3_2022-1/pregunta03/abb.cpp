#include <iostream>
#include "abb.h"
using namespace std;

void construir(ABB *pA) {
    pA->raiz = nullptr; // todo arbol empieza vacio
}

NodoABB* crearNodo(Elemento e) {
    // todo nodo que sea crea es siempre una hoja
    NodoABB *p;
    p = new NodoABB; // se crea el nodo en memoria
    p->hizq = nullptr;
    p->elem = e;
    p->hder = nullptr;
    return p; // se retorna la direccion del nodo creado
}

void insertar(ABB *pA, Elemento e) {
    NodoABB *p, *q, *pq;

    p = crearNodo(e);
    if (pA->raiz == nullptr) // arbol vacio
        pA->raiz = p;
    else {
        q = pA->raiz;
        pq = nullptr;
        while (q != nullptr) {
            pq = q;
            if (e.id < q->elem.id)
                q = q->hizq;
            else
                q = q->hder;
        }
        if (e.id < pq->elem.id)
            pq->hizq = p;
        else
            pq->hder = p;
    }
}

NodoABB* obtenerRaiz(ABB A) {
    return A.raiz;
}

void mostrarEnOrden(NodoABB *pR) {
    NodoABB *pAI, *pAD;
    if (pR != nullptr) {
        pAI = pR->hizq;
        pAD = pR->hder;
        mostrarEnOrden(pAI);
        cout << pR->elem.id << "-" << pR->elem.letra << "->";
        mostrarEnOrden(pAD);
    }
}

void mostrarEnPreOrden(NodoABB *pR) {
    NodoABB *pAI, *pAD;
    if (pR != nullptr) {
        pAI = pR->hizq;
        pAD = pR->hder;
        cout << pR->elem.id << "-" << pR->elem.letra << "->";
        mostrarEnPreOrden(pAI);
        mostrarEnPreOrden(pAD);
    }
}

void mostrarEnPostOrden(NodoABB *pR) {
    NodoABB *pAI, *pAD;
    if (pR != nullptr) {
        pAI = pR->hizq;
        pAD = pR->hder;
        mostrarEnPostOrden(pAI);
        mostrarEnPostOrden(pAD);
        cout << pR->elem.id << "-" << pR->elem.letra << "->";
    }
}

int buscar(NodoABB *pR, Elemento e) {
    if (pR != nullptr) {
        if(pR->elem.letra == e.letra) return 1;
        if(pR->hizq == nullptr) return 0;
        int izq = buscar(pR->hizq,e);
        if(pR->hder == nullptr) return 0;
        int der = buscar(pR->hder,e);
        return izq + der;
    }
    return 0;
}

Elemento menor(NodoABB *pR) {
    NodoABB *p;
    p = pR;
    while (p->hizq != nullptr)
        p = p->hizq;
    return p->elem;
}

Elemento mayor(NodoABB *pR) {
    NodoABB *p;
    p = pR;
    while (p->hder != nullptr)
        p = p->hder;
    return p->elem;
}

