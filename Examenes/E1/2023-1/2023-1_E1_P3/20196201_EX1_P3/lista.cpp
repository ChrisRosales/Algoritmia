#include <iostream>
#include <cstring>
#include "lista.h"

using namespace std;

void construir(Lista *pL) {
    // toda lista empieza vacia
    pL->cabeza = nullptr;
    pL->cola = nullptr;
    pL->longitud = 0;
    pL->ejercicito = "";
    pL->numEjercitio = 0;
}

bool esListaVacia(Lista L) {
    return L.cabeza == nullptr;
    // return L.longitud == 0;
}

int obtenerLongitud(Lista L) {
    return L.longitud;
}

Nodo* crearNodo(Elemento e, Nodo *s) {
    Nodo *p;
    p = new Nodo;
    p->elem = e;
    p->sig = s;
    return p; // devuelve la direccion del nodo creado
}

void insertarComienzo(Lista *pL, Elemento e) {
    Nodo *p;
    p = crearNodo(e, pL->cabeza);
    pL->cabeza = p;
    pL->longitud++;
}

void mostrar(Lista L) {
    Nodo *p;
    int i;
    if (esListaVacia(L))
        cout << "Lista vacia" << endl;
    else {
        p = L.cabeza;
        cout << L.ejercicito << ":";
        while (p != nullptr) {
            cout << p->elem;
            if (p->sig != nullptr) cout << "->";
            p = p->sig;
        }
        //        for (i = 1; i <= L.longitud; i++) {
        //            cout << p->elem;
        //            if(i + 1 != L.longitud) cout << "->";
        //            p = p->sig;
        //        }
        cout << endl;
    }
}

Nodo* ubicarUltimo(Lista L) {
    Nodo *pU;
    int i;
    if (esListaVacia(L))
        return nullptr; //  no hay ultimo al ser la lista vacia
    else {
        pU = L.cabeza;
        for (i = 1; i <= L.longitud - 1; i++)
            pU = pU->sig;
        return pU; // devuelve la direccion del ultimo nodo    
    }
}

void insertarFinal(Lista *pL, Elemento e) {
    Nodo *p, *pU;

    p = crearNodo(e, nullptr);

    if (esListaVacia(*pL))
        pL->cabeza = p;
    else {
        pU = ubicarUltimo(*pL);
        pU->sig = p;
        pL->cola = p;
    }
    pL->longitud++;
}

Nodo* ubicar(Lista L, Elemento e) {
    Nodo *p;
    int i;
    if (esListaVacia(L))
        return nullptr;
    else {
        p = L.cabeza;
        for (i = 1; i <= L.longitud; i++) {
            if (p->elem == e)
                return p; // devuelve la direc del nodo donde encontro el dato el e
            p = p->sig;
        }
        return nullptr; // el dato no fue hallado en la lista
    }
}

Nodo* ubicarAnterior(Lista L, Elemento e) {
    Nodo *p, *pA;
    pA = nullptr;
    p = L.cabeza;
    while (p != nullptr) {
        if (p->elem == e) {
            return pA;
        }
        pA = p;
        p = p->sig;
    }
    // no se encontro el anterior
    return nullptr;
}

void eliminar(Lista *pL, Elemento e) {
    Nodo *p, *pA;

    p = ubicar(*pL, e);
    if (p == nullptr) // el dato e no esta en la Lista
        cout << "No se puede eliminar un dato inexistente" << endl;
    else // el dato si está en la Lista
    {
        pA = ubicarAnterior(*pL, e);
        if (pA == nullptr) // el nodo a eliminar es el primero
            pL->cabeza = p->sig;
        else // el nodo a eliminar no es el primero 
            pA->sig = p->sig;
        pL->longitud--;
        delete p; // se elimina el nodo
    }
}

void destruir(Lista *pL) {
    Nodo *p, *q;
    int i;
    if (!esListaVacia(*pL)) {
        p = pL->cabeza;
        for (i = 1; i <= pL->longitud; i++) {
            q = p->sig;
            delete p;
            p = q;
        }
        pL->cabeza = nullptr;
        pL->longitud = 0;
        cout << "Todos los nodos han sido eliminados" << endl;
    }
}
