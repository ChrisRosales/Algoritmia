#include <iostream>

using namespace std;

// ===========================
// ====== INICIO COLAS =======
// ===========================
typedef int Elemento;

typedef struct nodoC
{
    Elemento elem;  // el dato que almacena el nodo
    struct nodoC *sig;  // sig es la dirección del siguiente nodo
} NodoC;

typedef struct
{
    NodoC *frente; // frente almacena la direccion del primer nodo de la cola
    NodoC *final; // final almacena la direccion del ultimo nodo de la colaa
    int longitud; // cantidad de nodos de la cola
} Cola;
void construirCola( Cola &pC )
{
    // se crea la cola vacia
    pC.frente= NULL;
    pC.final = NULL;
    pC.longitud = 0;
}

bool esColaVacia( Cola C )
{
    return C.frente == NULL;
    // return C.final == NULL;
    // return C.longitud == 0;
}

int obtenerLongitudCola( Cola C )
{
    return C.longitud;
}

NodoC* crearNodoCola( Elemento e, NodoC *s )
{
    NodoC *p;
    p = new NodoC; // se crea un nodo y su direccion se almacena en p
    p->elem = e;
    p->sig = s;
    return p;  // retorna la dirección del nodo creado
}

void encolar( Cola &pC, Elemento e )
{
    NodoC *p, *pU;
    p = crearNodoCola( e, NULL);
    if ( esColaVacia(pC) )
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

void mostrarCola( Cola C )
{
    NodoC *p;
    if ( esColaVacia(C) )
        cout << "La cola esta vacia" << endl;
    else
    {
        p = C.frente;
        while ( p!= NULL )
        {
            cout << p->elem << " ";
            p = p->sig;
        }
        cout << endl;
    }
}

// esta funcion solo sera invocada previa verificacion de que la cola no esta vacia
Elemento desencolar( Cola &pC )
{
    Elemento x;
    NodoC *p;
    p = pC.frente;
    if ( p->sig == NULL ) // hay un solo nodo en la Cola
        pC.final = NULL;
    pC.frente = p->sig;
    x = p->elem;
    pC.longitud--;
    delete p;
    return x;
}

void destruirCola( Cola &pC )
{
    int i;
    NodoC *p, *q;
    if ( !esColaVacia(pC) )
    {
        p = pC.frente;
        for(i=1; i<=pC.longitud; i++)
        {
            q = p->sig;
            delete p;
            p = q;
        }
        pC.frente = NULL;
        pC.final = NULL;
        pC.longitud = 0;
    }
}
// ===========================
// ======== FIN COLAS ========
// ===========================

// ===========================
// ======= INICIO PILAS ======
// ===========================
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
void construirPila( Pila &pP )
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

NodoP* crearNodoPila( Elemento e, NodoP *s )
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
    p = crearNodoPila( e, pP.cima );
    pP.cima = p;
    pP.longitud++;
}

void mostrarPila( Pila P )
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
            cout << p->elem << " ";
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

void destruirPila( Pila *pP )
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
// ===========================
// ======== FIN PILAS ========
// ===========================

void atencionSemanalGPSI(Cola *cola) {
    int i, valor;
    Pila paux;
    construirPila(paux);

    //PROBAMOS: 
	cout<<"INICIO"<<endl;
	cout<<"Cola: ";
	mostrarCola(*cola);
	cout<<"Pila: ";
	mostrarPila(paux);
	cout<<endl;

    //Apilo los PSI detectados por Sistemas
    for (i = 0; i < 5; i++) {
        valor = desencolar(*cola);
        apilar(paux, valor);
    }
    //PROBAMOS:
	cout<<"SE APILA LOS PSI detectados por Sistemas"<<endl; 
	cout<<"Cola: ";
	mostrarCola(*cola);
	cout<<"Pila: ";
	mostrarPila(paux);
	cout<<endl;

    //Encolamos los PSI detectados por Sistemas desde la Pila, es decir colocamos en la Cola los PSI detectados por Sistemas al final pero al reves
    while (!esPilaVacia(paux)) {
        encolar(*cola, desapilar(paux));
    }
	//PROBAMOS: 
	cout<<"SE ENCOLAN LOS PSI detectados por Sistemas"<<endl; 
	cout<<"Cola: ";
	mostrarCola(*cola);
	cout<<"Pila: ";
	mostrarPila(paux);
	cout<<endl;

    // Ahora encolamos los PSI detectados por los Trabajadores
    for (i = 0; i < 5; i++) {
        encolar(*cola, desencolar(*cola));
    }
    //PROBAMOS: 
	cout<<"SE ENCOLAN LOS PSI detectados por Trabajadores"<<endl; 
	cout<<"Cola: ";
	mostrarCola(*cola);
	cout<<"Pila: ";
	mostrarPila(paux);
	cout<<endl;

    //Apilamos los PSI detectados por Sistemas
    for (i = 0; i < 5; i++) {
        apilar(paux, desencolar(*cola));
    }
    //PROBAMOS: 
	cout<<"SE APILA LOS PSI detectados por Sistemas"<<endl; 
	cout<<"Cola: ";
	mostrarCola(*cola);
	cout<<"Pila: ";
	mostrarPila(paux);
	cout<<endl;
	
	//Hasta aquí tenemos los PSI detectados por Sistemas para desapilar en forma ordenada 1 -> 2 -> 3 -> 4 -> 5 -> NULL
	//y a los PSI detectados por los Trabajadores para desencolar en forma ordenada 5 -> 4 -> 3 -> 2 -> 1 -> NULL

    //Colocamos en la cola tomando uno de la pila (los PSI detectados por Sistemas) y uno de la cola (los PSI detectados por Trabajadores)
    cout<<"SE ENCOLAN 1 a 1"<<endl; 
	while (!esPilaVacia(paux)) {
        encolar(*cola, desapilar(paux));
        encolar(*cola, desencolar(*cola));
        //PROBAMOS: 
		cout<<"Cola: ";
		mostrarCola(*cola);
		cout<<"Pila: ";
		mostrarPila(paux);
		cout<<endl;
    }
}

int main() {
    Cola cola;

    construirCola(cola);
    encolar(cola, 01); //PSI001, con código "interno" 01, 0 de PSI detectado por Sistemas, 1 de correlativo
    encolar(cola, 02); //PSI002, con código "interno" 02, 0 de PSI detectado por Sistemas, 2 de correlativo
    encolar(cola, 03); //PSI003, con código "interno" 03, 0 de PSI detectado por Sistemas, 3 de correlativo
    encolar(cola, 04); //PSI004, con código "interno" 04, 0 de PSI detectado por Sistemas, 4 de correlativo
    encolar(cola, 05); //PSI005, con código "interno" 05, 0 de PSI detectado por Sistemas, 5 de correlativo
    encolar(cola, 11); //PSI006, con código "interno" 11, 1 de PSI detectado por Trabajador, 1 de correlativo
    encolar(cola, 12); //PSI007, con código "interno" 12, 1 de PSI detectado por Trabajador, 2 de correlativo
    encolar(cola, 13); //PSI008, con código "interno" 13, 1 de PSI detectado por Trabajador, 3 de correlativo
    encolar(cola, 14); //PSI009, con código "interno" 14, 1 de PSI detectado por Trabajador, 4 de correlativo
    encolar(cola, 15); //PSI010, con código "interno" 15, 1 de PSI detectado por Trabajador, 5 de correlativo

    mostrarCola(cola);
    cout << endl;

	//Se reorganizarán los nodos de la Cola para la atención Semanal de Gestión de Problemas de Seg. Inf.
    atencionSemanalGPSI(&cola);
    cout << endl;
    
	cout<<"PSI reorganizados según dinámica del enunciado:"<<endl; 
    mostrarCola(cola);

    return 0;
}

