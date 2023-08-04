#include <iostream>
#define N 11

using namespace std;

typedef int Elemento;

typedef struct nodo
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodo *sig;  // sig es la dirección del siguiente nodo
} Nodo;

typedef struct
{
    Nodo *cabeza; // cabeza almacena la direccion del primer nodo de la lista
    Nodo *cola;
    int longitud; // cantidad de nodos de la lista
} Lista;

typedef struct nodoP
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodoP *sig;  // sig es la dirección del siguiente nodo
} NodoP;

typedef struct
{
    NodoP *cima; // cima almacena la direccion del primer nodo de la pila
    int longitud; // cantidad de nodos de la pila
} Pila;

void construir( Lista &pL )
{
    // se crea la lista vacia
    pL.cabeza = NULL;
    pL.cola = NULL;
    pL.longitud = 0;
}

bool esListaVacia( Lista L )
{
    return L.cabeza == NULL;
    // return L.longitud == 0;
}

Nodo* crearNodo( Elemento e, Nodo *s )
{
    Nodo *p;
    p = new Nodo; // se crea un nodo y su direccion se almacena en p
    p->elem = e;
    p->sig = s;
    return p;
}

int obtenerLongitud( Lista L )
{
    return L.longitud;
}

void insertarComienzo( Lista &pL, Elemento e )
{
    Nodo *nuevo;
    nuevo = crearNodo(e,NULL);
    
    if(pL.longitud==0){
        pL.cabeza = nuevo;
        pL.cola = nuevo;
    }
    else{
        nuevo->sig = pL.cabeza;
        pL.cabeza = nuevo;
    }   
    pL.longitud++;
    
}

void mostrar( Lista L )
{
    Nodo *p;
    if ( esListaVacia(L) )
        cout << "La lista esta vacia" << endl;
    else
    {
        p = L.cabeza;
        while ( p!= NULL )
        {
            cout << p->elem << " ";
            p = p->sig;
        }
        cout << endl;
    }
}

Nodo* ubicarUltimo( Lista L )
{
    Nodo *pU;
    int i;
    if ( esListaVacia(L) )
        return NULL;
    else
    {
        pU = L.cabeza;
        for(i=1; i<=L.longitud-1; i++ )
            pU = pU->sig;
        return pU;
    }
}

void insertarFinal( Lista &pL, Elemento e )
{
    Nodo *p, *pU;
    p = crearNodo( e, NULL);
    if ( esListaVacia(pL) )
        pL.cabeza = p;
    else
    {
        pU = ubicarUltimo( pL );
        pU->sig = p;
    }
    pL.longitud++;
}

Nodo* ubicarElemento( Lista L, Elemento e)
{
    Nodo *p;
    if ( esListaVacia(L) )
        return NULL;
    else
    {
        p = L.cabeza;
        while ( p != NULL )
        {
            if ( p->elem == e )
                return p;
            p = p->sig;    
        }
        return NULL;
    }
}

Nodo* ubicarAnterior( Lista L, Elemento e)
{
    Nodo *p, *pA;
    pA = NULL;
    p = L.cabeza;
    while ( p!=NULL )
    {
        if ( p->elem == e )
            return pA;
        pA = p;
        p = p->sig;
    }
}

void eliminar( Lista *pL, Elemento e )
{
    Nodo *p, *pA;
    p = ubicarElemento( *pL, e);
    if ( p == NULL )
        cout << "No es posible eliminar un dato inexistente" << endl;
    else
    {
        pA = ubicarAnterior( *pL, e);
        if ( pA == NULL )
            pL->cabeza = p->sig;
        else
            pA->sig = p->sig;
        pL->longitud--;
        delete p;
    }
}

void destruir( Lista *pL )
{
    Nodo *p, *pAux;
    if ( ! esListaVacia( *pL) )
    {
        p = pL->cabeza;
        while ( p != NULL )
        {
            pAux = p->sig;
            delete p;
            p = pAux;
        }
        pL->cabeza = NULL;
        pL->longitud = 0;
    }
}

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

int calcularFrecMaxima(int frecuencias[N], int size, int *duracion, double *area){
	int i = 0, frecMax, frec, indiceFrecMax, duracionActual;
	double areaActual, areaMax=0;
	Pila ptrPila;
	construir(ptrPila);
	while (i<size){
		if (esPilaVacia(ptrPila) || frecuencias[top(ptrPila)]<=frecuencias[i]){
			apilar(ptrPila,i);
			i++;
		}
		else {
			indiceFrecMax = desapilar(ptrPila);
			frec = frecuencias[indiceFrecMax];
			if (esPilaVacia(ptrPila)){
				areaActual = frec*i;
				duracionActual = i;
			}
			else {
				areaActual = frec*(i-indiceFrecMax);
				duracionActual = i-indiceFrecMax;
			}
			if (areaMax<areaActual){
				areaMax = areaActual;
				frecMax = frec;
				*duracion = duracionActual;
				*area = areaMax;
			}
		}
	}
	
	while (!esPilaVacia(ptrPila)){
		indiceFrecMax = desapilar(ptrPila);
		frec = frecuencias[indiceFrecMax];
		if (esPilaVacia(ptrPila)){
			areaActual = frec*i;
			duracionActual = i;
		}
		else {
			areaActual = frec*(i-indiceFrecMax);
			duracionActual = i-indiceFrecMax;
		}
		if (areaMax<areaActual){
			areaMax = areaActual;
			frecMax = frec;
			*duracion = duracionActual;
			*area = areaMax;
		}
	}	
	return frecMax;
}

int main(){
	int frecuencias[N] = {1,2,1,4,5,6,4,5,2,2,1};
	int duracion = 0;
	double area;
	cout << "La frecuencia maxima es: " << calcularFrecMaxima(frecuencias,N,&duracion,&area) << endl;
	cout << "La duracion es: " << duracion << endl;
	cout << "El area es: " << area;
	return 0;
}
