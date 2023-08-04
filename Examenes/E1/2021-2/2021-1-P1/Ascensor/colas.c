#include <stdio.h>
#include <stdlib.h>
#include "colas.h"

void construir_cola(Cola *tad){
	construir_lista(&tad->contenido);
}

void destruir_cola(Cola *tad){
	destruir_lista(&tad->contenido);	
}

int es_cola_vacia(Cola tad){
	return es_lista_vacia(tad.contenido);
}

void pide_vez(Cola *tad, ElementoCola elemento){
	insertar_al_final(&tad->contenido, elemento);
}

ElementoCola avanzar(Cola *tad){
	if (es_cola_vacia(*tad)){
		printf("La cola está vacía, no se puede avanzar en ella.\n");
		exit(11);
	}	
    ElementoCola elemento = retorna_cabeza(tad->contenido);	
    elimina_cabeza(&tad->contenido);
    return elemento;
}

/*
void enqueue_with_priority(Cola *tad, ElementoCola elemento) {
	if (elemento.type == 2)
		insertar_al_inicio(&tad->contenido, elemento);
	else {
		if (es_lista_vacia(tad->contenido))
			insertar_al_inicio(&tad->contenido, elemento);	
		else {
			NodoLista* prevListNode = tad->contenido.cabeza; 
			NodoLista* listNode = tad->contenido.cabeza;
			
			while (listNode != NULL && listNode->elemento.type != 1){
				prevListNode = listNode;
				listNode = listNode->sig;
			}
			
			NodoLista* nuevo_nodo = (NodoLista*)malloc(sizeof(NodoLista));
			nuevo_nodo->elemento.type = elemento.type;
			nuevo_nodo->elemento.value = elemento.value;
			nuevo_nodo->sig = listNode;
			prevListNode->sig = nuevo_nodo;
			
		}
	}
}
*/
void enqueue_with_priority2(Cola *tad, ElementoCola elemento){
	if (es_lista_vacia(tad->contenido))
		pide_vez(tad, elemento);
	else {	
		if (retorna_cabeza(tad->contenido).is_ascending) {
			int continue_rotation=1;
			if (elemento.is_ascending){
				int head_level = retorna_cabeza(tad->contenido).level;
				int head_is_ascending = retorna_cabeza(tad->contenido).is_ascending;
				if (elemento.level < head_level)
					head_level = elemento.level;
				while (retorna_cabeza(tad->contenido).level < elemento.level &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = head_level != retorna_cabeza(tad->contenido).level;
				}
				if (retorna_cabeza(tad->contenido).level != elemento.level || 
					(retorna_cabeza(tad->contenido).level == elemento.level &&
					retorna_cabeza(tad->contenido).is_ascending != elemento.is_ascending)){
					pide_vez(tad, elemento);
				}
				while (retorna_cabeza(tad->contenido).level != head_level/* &&
					   retorna_cabeza(tad->contenido).is_ascending != head_is_ascending*/) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
				}		
			} else {
				int head_level = retorna_cabeza(tad->contenido).level;
				int head_is_ascending = retorna_cabeza(tad->contenido).is_ascending;
				while (retorna_cabeza(tad->contenido).is_ascending &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = head_level != retorna_cabeza(tad->contenido).level;
				}
				continue_rotation=retorna_cabeza(tad->contenido).level > elemento.level;
				while (retorna_cabeza(tad->contenido).is_ascending==0 &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = retorna_cabeza(tad->contenido).level > elemento.level;
				}				
				if (retorna_cabeza(tad->contenido).level != elemento.level || 
					( retorna_cabeza(tad->contenido).level == elemento.level &&
					retorna_cabeza(tad->contenido).is_ascending != elemento.is_ascending)){
					pide_vez(tad, elemento);
				}
				while (retorna_cabeza(tad->contenido).level != head_level ||
					   ( retorna_cabeza(tad->contenido).level == elemento.level &&
					retorna_cabeza(tad->contenido).is_ascending != elemento.is_ascending)) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
				}					
			}
		}
		else {
			int continue_rotation=1;
			if (!elemento.is_ascending){
				int head_level = retorna_cabeza(tad->contenido).level;
				int head_is_ascending = retorna_cabeza(tad->contenido).is_ascending;
				if (elemento.level > head_level)
					head_level = elemento.level;
				while (retorna_cabeza(tad->contenido).level > elemento.level &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = head_level != retorna_cabeza(tad->contenido).level;
				}
				if (retorna_cabeza(tad->contenido).level != elemento.level || 
					(retorna_cabeza(tad->contenido).level == elemento.level &&
					retorna_cabeza(tad->contenido).is_ascending != elemento.is_ascending)){
					pide_vez(tad, elemento);
				}
				while (retorna_cabeza(tad->contenido).level != head_level/* &&
					   retorna_cabeza(tad->contenido).is_ascending != head_is_ascending*/) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
				}		
			} else {
				//Corregir esta parte
				int head_level = retorna_cabeza(tad->contenido).level;
				int head_is_ascending = retorna_cabeza(tad->contenido).is_ascending;
				while (!retorna_cabeza(tad->contenido).is_ascending &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = head_level != retorna_cabeza(tad->contenido).level;
				}
				continue_rotation=retorna_cabeza(tad->contenido).level > elemento.level;
				while (retorna_cabeza(tad->contenido).is_ascending==0 &&
						continue_rotation) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
					continue_rotation = retorna_cabeza(tad->contenido).level > elemento.level;
				}				
				if (retorna_cabeza(tad->contenido).level != elemento.level || 
					( retorna_cabeza(tad->contenido).level == elemento.level &&
					retorna_cabeza(tad->contenido).is_ascending != elemento.is_ascending)){
					pide_vez(tad, elemento);
				}
				while (retorna_cabeza(tad->contenido).level != head_level &&
					   retorna_cabeza(tad->contenido).is_ascending != head_is_ascending) {
					ElementoCola queueNode = avanzar(tad);
					pide_vez(tad, queueNode);
				}					
			}
		}			
	}
}

void show_queue(Cola tad){
	imprime_examen(tad.contenido);	
}