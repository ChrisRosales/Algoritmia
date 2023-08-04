#ifndef ABB_H
#define ABB_H

typedef struct{
    int id;
    char letra;
}Elemento;

typedef struct nodo {
    struct nodo *hizq;
    Elemento elem;
    struct nodo *hder;
} NodoABB;

typedef struct {
    NodoABB *raiz;
} ABB;

void construir(ABB *pA);
NodoABB* crearNodo(Elemento e);
void insertar(ABB *pA, Elemento e);
NodoABB* obtenerRaiz(ABB A);
void mostrarEnOrden(NodoABB *pR);
void mostrarEnPreOrden(NodoABB *pR);
void mostrarEnPostOrden(NodoABB *pR);
int buscar(NodoABB *pR, Elemento e);
Elemento menor(NodoABB *pR);
Elemento mayor(NodoABB *pR);
#endif /* ABB_H */

