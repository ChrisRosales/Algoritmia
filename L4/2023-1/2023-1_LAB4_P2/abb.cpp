#include <iostream>
#include "abb.h"

using namespace std;

void construir(ABB *pA) {
    pA->raiz = nullptr;
}

NodoABB* crearNodo(Elemento e) {
    NodoABB *p;
    p = new NodoABB;
    p->hizq = nullptr;
    p->elem = e;
    p->hder = nullptr;
    return p;
}

void insertar(ABB *pA, Elemento e) {
    NodoABB *p, *q, *pq;

    p = crearNodo(e);
    if (pA->raiz == nullptr)
        pA->raiz = p;
    else {
        q = pA->raiz;
        pq = nullptr;
        while (q != nullptr) {
            pq = q;
            if (e.nivel < q->elem.nivel)
                q = q->hizq;
            else
                q = q->hder;
        }
        if (e.nivel < pq->elem.nivel)
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
        cout << "(" << pR->elem.nivel << " - " << pR->elem.cnt_guerreros << ") ";
        mostrarEnOrden(pAD);
    }
}

void mostrarEnPreOrden(NodoABB *pR) {
    NodoABB *pAI, *pAD;
    if (pR != nullptr) {
        pAI = pR->hizq;
        pAD = pR->hder;
        cout << "(" << pR->elem.nivel << " - " << pR->elem.cnt_guerreros << ") ";
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
        cout << "(" << pR->elem.nivel << " - " << pR->elem.cnt_guerreros << ") ";
    }
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

