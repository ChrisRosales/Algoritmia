#include <iostream>
#include <cstring>
using namespace std;

typedef struct
{
    int prioridad;
    char* codigoISI;
} Elemento;

typedef struct nodoC
{
    Elemento elem;
    struct nodoC* sig;
} NodoC;

typedef struct
{
    NodoC* frente;
    NodoC* final;
    NodoC* prioridad1;
    NodoC* prioridad2;
    NodoC* prioridad3;
    int longitud;
} Cola;

void construirCola(Cola& pC)
{
    pC.frente = NULL;
    pC.final = NULL;
    pC.prioridad1 = NULL;
    pC.prioridad2 = NULL;
    pC.prioridad3 = NULL;
    pC.longitud = 0;
}

bool esColaVacia(Cola C)
{
    return C.frente == NULL;
}

int obtenerLongitudCola(Cola C)
{
    return C.longitud;
}

NodoC* crearNodoCola(Elemento e)
{
    NodoC* p;
    p = new NodoC;
    p->elem = e;
    p->sig = NULL;
    return p;
}

void encolar(Cola& pC, Elemento e)
{
    NodoC* p, * pU;
    p = crearNodoCola(e);
    if (esColaVacia(pC))
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

void mostrarCola(Cola C)
{
    NodoC* p;
    if (esColaVacia(C))
        cout << "La cola esta vacia" << endl;
    else
    {
        p = C.frente;
        while (p != NULL)
        {
            cout << p->elem.prioridad << " - " << p->elem.codigoISI << endl;
            p = p->sig;
        }
        cout << endl;
    }
}

Elemento desencolar(Cola& pC)
{
    Elemento x;
    NodoC* p;
    p = pC.frente;
    if (p->sig == NULL)
        pC.final = NULL;
    pC.frente = p->sig;
    x = p->elem;
    pC.longitud--;
    delete p;
    return x;
}

void destruirCola(Cola& pC)
{
    int i;
    NodoC* p, * q;
    if (!esColaVacia(pC))
    {
        p = pC.frente;
        for (i = 1; i <= pC.longitud; i++)
        {
            q = p->sig;
            delete[] p->elem.codigoISI;
            delete p;
            p = q;
        }
        pC.frente = NULL;
        pC.final = NULL;
        pC.prioridad1 = NULL;
    	pC.prioridad2 = NULL;
    	pC.prioridad3 = NULL;
        pC.longitud = 0;
    }
}

void encolar_prioridad(Cola& cola, int prioridad, const char* codigoISI)
{
    // Creamos espacio en la memoria
    Elemento elem;
    elem.prioridad = prioridad;
    elem.codigoISI = new char[strlen(codigoISI) + 1];
    strcpy(elem.codigoISI, codigoISI);

    // Creamos el nuevo nodo
    NodoC* nuevoNodo = crearNodoCola(elem);

    if (esColaVacia(cola)) {
        cola.frente = nuevoNodo;
        cola.final = nuevoNodo;
        cola.prioridad1 = NULL;
        cola.prioridad2 = NULL;
        cola.prioridad3 = NULL;
        if (prioridad == 1) cola.prioridad1 = nuevoNodo;
        if (prioridad == 2) cola.prioridad2 = nuevoNodo;
        if (prioridad == 3) cola.prioridad3 = nuevoNodo;
    } else {
        if (prioridad == 1) {
            if (cola.prioridad1 != NULL) { // ya hay nodos de prioridad1
                nuevoNodo->sig = cola.prioridad1->sig;
                cola.prioridad1->sig = nuevoNodo;
                cola.prioridad1 = nuevoNodo;
            } else { // será el primer nodo con prioridad1
                if (cola.prioridad2 != NULL) { // pero ya hay nodos de prioridad2
                    nuevoNodo->sig = cola.frente;
                    cola.frente = nuevoNodo;
                    cola.prioridad1 = nuevoNodo;
                } else if (cola.prioridad3 != NULL) { // pero ya hay nodos de prioridad3
                    nuevoNodo->sig = cola.prioridad3;
                    cola.prioridad3 = nuevoNodo;
                    cola.prioridad1 = nuevoNodo;
                } else {
                    // no hay nodos de prioridad2 ni prioridad3, la cola está vacía
                    cola.frente = nuevoNodo;
                    cola.final = nuevoNodo;
                    cola.prioridad1 = nuevoNodo;
                }
            }
        }
        if (prioridad == 2) {
            if (cola.prioridad2 != NULL) { // ya hay nodos de prioridad2
                nuevoNodo->sig = cola.prioridad2->sig;
                cola.prioridad2->sig = nuevoNodo;
                cola.prioridad2 = nuevoNodo;
            } else { // será el primer nodo con prioridad2
                if (cola.prioridad1 != NULL) { // pero ya hay nodos de prioridad1
                    nuevoNodo->sig = cola.prioridad1->sig;
                    cola.prioridad1->sig = nuevoNodo;
                    cola.prioridad2 = nuevoNodo;
                } else if (cola.prioridad3 != NULL) { // pero ya hay nodos de prioridad3
                    nuevoNodo->sig = cola.prioridad3;
                    cola.prioridad3 = nuevoNodo;
                    cola.prioridad2 = nuevoNodo;
                } else {
                    // no hay nodos de prioridad1 ni prioridad3, la cola está vacía
                    cola.frente = nuevoNodo;
                    cola.final = nuevoNodo;
                    cola.prioridad1 = nuevoNodo;
                    cola.prioridad2 = nuevoNodo;
                }
            }
        }
        if (prioridad == 3) {
            if (cola.prioridad3 != NULL) { // ya hay nodos de prioridad3
                nuevoNodo->sig = cola.prioridad3->sig;
                cola.prioridad3->sig = nuevoNodo;
                cola.prioridad3 = nuevoNodo;
            } else { // será el primer nodo con prioridad3
                if (cola.prioridad2 != NULL) { // pero ya hay nodos de prioridad2
                    nuevoNodo->sig = cola.prioridad2->sig;
                    cola.prioridad2->sig = nuevoNodo;
                    cola.prioridad3 = nuevoNodo;
                } else if (cola.prioridad1 != NULL) { // pero ya hay nodos de prioridad1
                    nuevoNodo->sig = cola.prioridad1->sig;
                    cola.prioridad1->sig = nuevoNodo;
                    cola.prioridad3 = nuevoNodo;
                } else {
                    // no hay nodos de prioridad1 ni prioridad2, la cola está vacía
                    cola.frente = nuevoNodo;
                    cola.final = nuevoNodo;
                    cola.prioridad1 = nuevoNodo;
                    cola.prioridad2 = nuevoNodo;
                    cola.prioridad3 = nuevoNodo;
                }
            }
        }
    }
    // Aumentamos la longitud de la Cola
    cola.longitud++;
    mostrarCola(cola);
}



int main(){
    Cola cola;
    construirCola(cola);

    // Encolamos con prioridad
    encolar_prioridad(cola, 2, "ISI001");
    encolar_prioridad(cola, 1, "ISI002");
    encolar_prioridad(cola, 1, "ISI003");
    encolar_prioridad(cola, 3, "ISI004");
    encolar_prioridad(cola, 2, "ISI005");
    encolar_prioridad(cola, 3, "ISI006");
    encolar_prioridad(cola, 1, "ISI007");

    cout << endl;
    mostrarCola(cola);

    destruirCola(cola);

    return 0;
}

