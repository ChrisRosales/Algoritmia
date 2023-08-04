/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 15 de julio de 2023, 8:05
 */

#include <iostream>
#include <codecvt>
#include "abb.h"
using namespace std;

// variables globales
NodoABB* nodoRaiz; // nodoRaiz para poder buscar cual es el mayor del arbol
// funciones
NodoABB* inserta_nodo(NodoABB* pR, Elemento token);
int calcularAltura(NodoABB* nodo);
NodoABB* rotacionDerecha(NodoABB* nodo);
NodoABB* rotacionIzquierda(NodoABB* nodo);
NodoABB* rotacionDobleDerecha(NodoABB* nodo);
NodoABB* rotacionDobleIzquierda(NodoABB* nodo);
NodoABB* balancearNodo(NodoABB* nodo);
NodoABB* balancearArbol(NodoABB* raiz);
bool suma_arboles(NodoABB*, NodoABB*);
NodoABB* suma_arboles_nodos(NodoABB *raizToken, NodoABB *raizSistema);
bool verificarABB(NodoABB *pR);

int main(int argc, char** argv) {
    int tokens[] = {2, 5, 2, 1, 5, 6, 3, 4}; // datos que se va a ingresar
        int tokensSistema[] = {3, 1, 2, 5, 4, 6, 7}; // token que genera el sistema, CASO FALSO
//    int tokensSistema[] = {4, 1, 2, 3, 6, 5, 7}; // token que genera el sistema, CASO VERDADERO
    // tamano de los datos
    int cntTokens = sizeof (tokens) / sizeof (tokens[0]);
    int cntTokensSistema = sizeof (tokensSistema) / sizeof (tokensSistema[0]);
    // Arboles
    ABB arbolToken;
    construir(&arbolToken);
    NodoABB* raizToken = obtenerRaiz(arbolToken);
    for (int i = 0; i < cntTokens; i++) {
        if (raizToken == nullptr) {
            raizToken = crearNodo(tokens[i]);
            nodoRaiz = raizToken;
        } else {
            inserta_nodo(raizToken, tokens[i]);
        }
    }


    ABB arbolSistema;
    construir(&arbolSistema);
    NodoABB* raizSistema = obtenerRaiz(arbolSistema);
    for (int i = 0; i < cntTokensSistema; i++) {
        if (raizSistema == nullptr) {
            raizSistema = crearNodo(tokensSistema[i]);
            nodoRaiz = raizSistema;
        } else {
            inserta_nodo(raizSistema, tokensSistema[i]);
        }
    }
    /***************************************************************************
     * BALANCEO
     **************************************************************************/
    raizToken = balancearArbol(raizToken);
    /***************************************************************************
     * SUMAR ARBOLES
     **************************************************************************/
    cout << "Despues de la suma el arbol sigue siendo ABB: " << (suma_arboles(raizToken, raizSistema) ? "TRUE" : "FALSE") << endl;

    return 0;
}

NodoABB* inserta_nodo(NodoABB* pR, Elemento token) {
    if (pR == nullptr) {
        return crearNodo(token);
    } else if (token == pR->elem) {
        Elemento e = mayor(nodoRaiz);
        token = token + e;
        if (token < pR->elem) {
            pR->hizq = inserta_nodo(pR->hizq, token);
        } else {
            pR->hder = inserta_nodo(pR->hder, token);
        }
    } else if (token < pR->elem) {
        pR->hizq = inserta_nodo(pR->hizq, token);
    } else {
        pR->hder = inserta_nodo(pR->hder, token);
    }
    return pR;
}

/***************************************************************************
 * BALANCEO
 **************************************************************************/
int calcularAltura(NodoABB* nodo) {
    if (nodo == NULL)
        return 0;
    else {
        int alturaIzq = calcularAltura(nodo->hizq);
        int alturaDer = calcularAltura(nodo->hder);
        return max(alturaIzq, alturaDer) + 1;
    }
}

NodoABB* rotacionDerecha(NodoABB* nodo) {
    NodoABB* nodoIzq = nodo->hizq;
    nodo->hizq = nodoIzq->hder;
    nodoIzq->hder = nodo;
    return nodoIzq;
}

NodoABB* rotacionIzquierda(NodoABB* nodo) {
    NodoABB* nodoDer = nodo->hder;
    nodo->hder = nodoDer->hizq;
    nodoDer->hizq = nodo;
    return nodoDer;
}

NodoABB* rotacionDobleDerecha(NodoABB* nodo) {
    nodo->hizq = rotacionIzquierda(nodo->hizq);
    return rotacionDerecha(nodo);
}

NodoABB* rotacionDobleIzquierda(NodoABB* nodo) {
    nodo->hder = rotacionDerecha(nodo->hder);
    return rotacionIzquierda(nodo);
}

NodoABB* balancearNodo(NodoABB* nodo) {
    int alturaIzq = calcularAltura(nodo->hizq);
    int alturaDer = calcularAltura(nodo->hder);
    int diferencia = alturaIzq - alturaDer;

    if (diferencia > 1) {
        if (calcularAltura(nodo->hizq->hizq) >= calcularAltura(nodo->hizq->hder))
            nodo = rotacionDerecha(nodo);
        else
            nodo = rotacionDobleDerecha(nodo);
    } else if (diferencia < -1) {
        if (calcularAltura(nodo->hder->hder) >= calcularAltura(nodo->hder->hizq))
            nodo = rotacionIzquierda(nodo);
        else
            nodo = rotacionDobleIzquierda(nodo);
    }

    return nodo;
}

NodoABB* balancearArbol(NodoABB* raiz) {
    if (raiz == NULL)
        return NULL;

    raiz->hizq = balancearArbol(raiz->hizq);
    raiz->hder = balancearArbol(raiz->hder);

    raiz = balancearNodo(raiz);

    return raiz;
}

/* Los nodos del arbol Sistema son los que se van a pasar al arbolToken*/
bool suma_arboles(NodoABB *raizToken, NodoABB *raizSistema) {
    raizToken = suma_arboles_nodos(raizToken, raizSistema);
    return verificarABB(raizToken);
}

bool verificarABB(NodoABB *pR) {
    if (pR == nullptr or (pR->hizq == nullptr and pR->hder == nullptr)) { // llegamos a una raiz
        return true;
    }
    // NO cumple con las condiciones de ser ABB
    if (pR->hizq == nullptr and pR->hder->elem < pR->elem){
        return false;
    }else if (pR->hder == nullptr and pR->hizq->elem > pR->elem){
        return false;
    }else if ((pR->hizq != nullptr and pR->elem < pR->hizq->elem) or ( pR->hder != nullptr  and pR->elem > pR->hder->elem))
        return false;
    return verificarABB(pR->hizq) and verificarABB(pR->hder);
}

NodoABB* suma_arboles_nodos(NodoABB *raizToken, NodoABB *raizSistema) {
    if (raizSistema == nullptr) { // no podemos seguir sumando
        return raizToken;
    }

    if (raizToken == nullptr and raizSistema != nullptr) {
        Elemento e = raizSistema->elem;
        return crearNodo(e);
    }
    // Procedemos con la suma
    raizToken->elem = raizToken->elem + raizSistema->elem;
    raizToken->hizq = suma_arboles_nodos(raizToken->hizq, raizSistema->hizq);
    raizToken->hder = suma_arboles_nodos(raizToken->hder, raizSistema->hder);
    return raizToken;
}










