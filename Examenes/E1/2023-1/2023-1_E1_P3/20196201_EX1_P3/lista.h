#ifndef LISTA_H
#define LISTA_H

using namespace std;

typedef int Elemento;

typedef struct nodo{
    Elemento elem;
    struct nodo *sig;
} Nodo;

typedef struct{
    Nodo *cabeza;
    Nodo *cola;
    int longitud;
    // nombre de la lista
    string ejercicito;
    int numEjercitio;
} Lista;

// Funciones de la Cola
void construir( Lista *pL );
bool esListaVacia( Lista L);
int obtenerLongitud( Lista L );
Nodo* crearNodo( Elemento e, Nodo *s );
void insertarComienzo( Lista *pL, Elemento e);
void mostrar( Lista L );
Nodo* ubicarUltimo( Lista L );
void insertarFinal( Lista *pL, Elemento e);
Nodo* ubicar( Lista L, Elemento e);
Nodo* ubicarAnterior( Lista L, Elemento e);
void eliminar( Lista *pL, Elemento e);
void destruir( Lista *pL );
#endif // !LISTA_H
