#include <stdio.h>
#include <stdlib.h>

typedef struct NodoPila{
    int valor;
    struct NodoPila *ptrSig; /*estructura auto-referenciada*/
}TNodoPila;

typedef TNodoPila* Tpila ;

/* al inicio la pila se inicializa con nulo, lo que indica que esta¡ vacia*/
void crear(Tpila *ptrpila) {
    *ptrpila=NULL;
}

/*Se implementara¡ usando una lista simplemente enlazada. push insertara¡ siempre
 un nodo al inicio.*/
void push(Tpila *Pila, int valor) {
    TNodoPila *ptrNuevo;
    
    ptrNuevo = (TNodoPila *) malloc(sizeof (TNodoPila));
    ptrNuevo->valor = valor;
    ptrNuevo->ptrSig = *Pila;
    *Pila = ptrNuevo;
    
}

int pila_vacia(Tpila *ptrPila){
    return *ptrPila==NULL;
}

void top(Tpila *ptrPila)
{   TNodoPila *ptrrec;
    
    ptrrec=*ptrPila;
    if(pila_vacia(ptrPila))
        printf("Pila vacia\n");
    else
        printf("%d\n",ptrrec->valor);

}

/*Dado que se ha realizado una insercion al inicio, para que la estructura se
 comporte como pila, se debe sacar los dados a partir del inicio de la lista.*/

int pop(Tpila *Pila) {    
    TNodoPila *ptrEliminar;
    int valor;
    
    if (!pila_vacia(Pila)) { 
        ptrEliminar=*Pila;
        valor = ptrEliminar->valor; 
        *Pila = ptrEliminar->ptrSig; 
        free(ptrEliminar);
    }
    return valor;
}

/*Libera toda la memoria reservada para la lista utilizada en la pila.*/
void finalizar(Tpila ptrPila){
    TNodoPila *ptrEliminar;
    
    ptrEliminar = ptrPila;
    
    while (ptrEliminar != NULL){
        
        ptrPila = ptrEliminar->ptrSig;
        free(ptrEliminar);
        ptrEliminar = ptrPila;
    }
}

void cambia(Tpila ptrPila,int n)
{
    ptrPila->valor=n;

}

void imprimepila(Tpila ptrPila)
{	Tpila  ptraux;
    
    if(ptrPila==NULL)
    	return;
    	
	ptraux=ptrPila;
	ptrPila=ptrPila->ptrSig;
	
	printf("%d\n",ptraux->valor);
	imprimepila(ptrPila);

}

//Une 2 pilas empleando una pila auxiliar, complejidad O(n)
void fusiona(Tpila *Pila1,Tpila *Pila2) 
{   int valor1,valor2,aux,flag1=1,flag2=1;
    Tpila paux;
    
    crear(&paux);
    while (1) { 
    	if(pila_vacia(Pila1) && pila_vacia(Pila2))
    		break;
		if(pila_vacia(Pila1) && flag1) 
    		valor1=9999999;
    	if(pila_vacia(Pila2) && flag2)
			valor2=9999999;
    	
   		if(!pila_vacia(Pila1) && flag1)
		   valor1=pop(Pila1);	
		if(!pila_vacia(Pila2) && flag2)
		   valor2=pop(Pila2);	
		
		if(valor1<valor2)
		{	aux = valor1;
			flag2 = 0;
			flag1 = 1;
		}
		else
		{	aux = valor2;
			flag1 = 0;
			flag2 = 1;
		}
		push(&paux,aux);
    }
	while(!pila_vacia(&paux)){
		aux = pop(&paux);
		push(Pila1,aux);
	}
}

int main() {
    Tpila ptrPila,ptrPila2;

    crear(&ptrPila);
    push(&ptrPila, 6);
    push(&ptrPila, 5);
    push(&ptrPila, 2);
 	printf("Pila1:\n");
    
  	imprimepila(ptrPila);

  	crear(&ptrPila2);
    push(&ptrPila2, 5);
    push(&ptrPila2, 4);
    push(&ptrPila2, 3);
    push(&ptrPila2, 1);
  	printf("Pila2:\n");
	imprimepila(ptrPila2);
 

  	fusiona(&ptrPila,&ptrPila2);
  	printf("\nPila1:\n");
	imprimepila(ptrPila);
    finalizar(ptrPila);
    
    return (0);
}
