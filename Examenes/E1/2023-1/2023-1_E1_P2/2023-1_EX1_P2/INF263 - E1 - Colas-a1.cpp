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
    int longitud;
} Cola;

void construirCola(Cola& pC)
{
    pC.frente = NULL;
    pC.final = NULL;
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
        pC.longitud = 0;
    }
}

void encolar_prioridad(Cola& cola, int prioridad, const char* codigoISI)
{
	//Creamos espacio en la memoria
    Elemento elem;
    elem.prioridad = prioridad;
    elem.codigoISI = new char[strlen(codigoISI) + 1];
    strcpy(elem.codigoISI, codigoISI);

    //Creamos el nuevo nodo
	NodoC* nuevoNodo = crearNodoCola(elem);
    
	//El nodo va al frente de la Cola (cola vacía o tiene mejor prioridad)
    if (esColaVacia(cola) || prioridad < cola.frente->elem.prioridad){
        //Ponemos el nuevo nodo como el frente de la Cola
        nuevoNodo->sig = cola.frente;
        cola.frente = nuevoNodo;

        if (esColaVacia(cola)){//Si la cola está vacía, también es final de la Cola
            cola.final = nuevoNodo;
        }
		//Aumentamos la longitud de la Cola
        cola.longitud++;
        return;
    }

	//Buscamos el sitio del nuevo nodo según su prioridad
    NodoC* ptraux = cola.frente;
    while (ptraux->sig != NULL && ptraux->sig->elem.prioridad <= prioridad){
        //Avanzamos en la cola para encontrar la posición para el nuevo nodo
        ptraux = ptraux->sig;
    }

    // Insertar el nuevo nodo después de ptraux
    nuevoNodo->sig = ptraux->sig;
    ptraux->sig = nuevoNodo;

    if (nuevoNodo->sig == NULL){//Nos encontramos al final de la Cola
        //Como el nuevo nodo va al final de la Cola, se actualiza el puntero
        cola.final = nuevoNodo;
    }
	//Aumentamos la longitud de la Cola
    cola.longitud++;
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

