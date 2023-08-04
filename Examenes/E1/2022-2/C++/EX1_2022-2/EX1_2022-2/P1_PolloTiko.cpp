#include <iostream>

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

void fusionar(Lista  &L1, Lista &L2){
	if(L1.cola->elem < L2.cabeza->elem ){ //L1 contiene solo elementos menores a L2
		L1.cola->sig = L2.cabeza;
		L1.cola = L2.cola;
	}
        else 
            if(L2.cola->elem < L1.cabeza->elem){ //L2 contiene solo elementos menores a L1
		L2.cola->sig = L1.cabeza;
		L1.cabeza = L2.cabeza;
            }
            else{ //Hay que fusionar
		Nodo *F_ini, *F_fin;
		F_ini = NULL; 
                F_fin = NULL; 

		while(!esListaVacia(L1) && !esListaVacia(L2)){
			if(L1.cabeza->elem <= L2.cabeza->elem){ //Pasa L1
				if(F_ini==NULL){
					F_ini = L1.cabeza;
					F_fin = L1.cabeza;
				}else{
					F_fin->sig = L1.cabeza;
					F_fin = L1.cabeza;
				}
				L1.cabeza = L1.cabeza->sig;
			}
                        else 
                            if(L1.cabeza->elem > L2.cabeza->elem){
				if(F_ini==NULL){
                                    F_ini = L2.cabeza;
				F_fin = L2.cabeza;
				}
                                else{
                                    F_fin->sig = L2.cabeza;
                                    F_fin = L2.cabeza;
				}
				L2.cabeza = L2.cabeza->sig;
			}
		}

		//Puede ser que alguna lista aun tenga elementos, repasamos ambas
		while(!esListaVacia(L1)){
			if(F_ini==NULL){
                            F_ini = L1.cabeza;
                            F_fin = L1.cabeza;
			}
                        else{
                            F_fin->sig = L1.cabeza;
                            F_fin = L1.cabeza;
				}
			L1.cabeza = L1.cabeza->sig;
		}

		while(!esListaVacia(L2)){
			if(F_ini==NULL){
                            F_ini = L2.cabeza;
                            F_fin = L2.cabeza;
			}
                        else{
                            F_fin->sig = L2.cabeza;
                            F_fin = L2.cabeza;
			}
			L2.cabeza = L2.cabeza->sig;
		}

		L1.cabeza = F_ini;
		L1.cola = F_fin;
	}
}

int main(){
	Lista lunes,martes,miercoles,jueves,viernes;
	construir(lunes);
	construir(martes);
	construir(miercoles);
	construir(jueves);
	construir(viernes);
	
	int numLunes, numMartes, numMiercoles, numJueves, numViernes;
	
    insertarComienzo(lunes,12);insertarComienzo(lunes,10);insertarComienzo(lunes,8);
    insertarComienzo(martes,11);insertarComienzo(martes,9);
    insertarComienzo(miercoles,10);insertarComienzo(miercoles,9);insertarComienzo(miercoles,8);
    insertarComienzo(jueves,16);insertarComienzo(jueves,15);insertarComienzo(jueves,14);
    insertarComienzo(viernes,19);insertarComienzo(viernes,18);insertarComienzo(viernes,17);

    mostrar(lunes);
    fusionar(lunes, martes);
    fusionar(lunes, miercoles);
    fusionar(lunes, jueves);
    fusionar(lunes, viernes);
    mostrar(lunes);
    return 0;
}
