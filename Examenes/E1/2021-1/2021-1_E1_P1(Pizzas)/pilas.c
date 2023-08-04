#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"

void construir_pila(Pila *tad){
	//El parámetro de esta función es Pila *tad
	//El tipo de tipo de dato Pila se ha definido como:
	//	typedef struct {
	//		Lista contenido;    
	//	} Pila;
	//La operación que queremos invocar es:
	//	void construir_lista(Lista *tad)
	//¿Cómo a partir de Pila *tad, se llega a la lista?
	//	 tad->contenido
	//	 tad->contenido es del tipo Lista
	//Para invocar a la operación construir_lista se requiere el tipo
	//de dato Lista *
	//	&tad->contenido
	construir_lista(&tad->contenido);
}

void destruir_pila(Pila *tad){
	destruir_lista(&tad->contenido);
}

int es_pila_vacia(Pila tad){
	return es_lista_vacia(tad.contenido);
}

void apilar(Pila *tad, ElementoPila elemento){
	insertar_al_inicio(&tad->contenido, elemento);
}

ElementoPila desapilar(Pila *tad){	
	if (es_pila_vacia(*tad)){
		printf("La pila está vacía, por lo tanto no se puede desapilar.\n");
		exit(12);
	}	
    ElementoPila elemento=cima(*tad);
    elimina_cabeza(&tad->contenido);
    return elemento;
}

ElementoPila cima(Pila tad){
	if (es_pila_vacia(tad)){
		printf("La pila está vacía, por lo tanto no posee cima.\n");
		exit(11);
	}		
    //return tad.contenido.cabeza->elemento; //NO SE DEBE HACER	
    return retorna_cabeza(tad.contenido);
}