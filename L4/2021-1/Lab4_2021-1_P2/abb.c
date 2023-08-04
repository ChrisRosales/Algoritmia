#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"

void insertar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad)){
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	}
	else{
		if ((*tad)->elemento.amount > elemento.amount)
			insertar(&(*tad)->hijo_izq, elemento);
		else
			insertar(&(*tad)->hijo_der, elemento);
	}
}

void insertar_iterativo(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad)){
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	}
	else{
		ArbolBinarioBusqueda recorrido=*tad, padre=NULL;
		while(!es_arbol_vacio(recorrido)){
			padre=recorrido;
			if (recorrido->elemento.amount > elemento.amount)
				recorrido=recorrido->hijo_izq;
			else
				recorrido=recorrido->hijo_der;
		}
		if (padre->elemento.amount > elemento.amount)
			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
		else
			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);		
	}
}

int esta(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento.stock_number == llave.stock_number)
			return 1;
		else if (tad->elemento.amount >llave.amount)
			return esta(tad->hijo_izq, llave);
		else
			return esta(tad->hijo_der, llave);	
	}
}

int esta_iterativo(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		while(!es_arbol_vacio(tad)){
			if (tad->elemento.stock_number == llave.stock_number)
				return 1;
			if (tad->elemento.amount >llave.amount)
				tad=tad->hijo_izq;
			else
				tad=tad->hijo_der;	
		}
	}
	return 0;
}

int minimo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor valor pues el árbol está vacío.\n");
		exit(51);
	}
	if (es_arbol_vacio(tad->hijo_izq))
		return tad->elemento.stock_number;
	else
		return minimo_valor(tad->hijo_izq);
}

int maximo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(52);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento.stock_number;
	else
		return maximo_valor(tad->hijo_der);
}

int minimo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor valor pues el árbol está vacío.\n");
		exit(53);
	}
	while(!es_arbol_vacio(tad->hijo_izq))
		tad=tad->hijo_izq;
	return tad->elemento.stock_number;
}

int maximo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(54);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento.stock_number;
}

void eliminar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (!es_arbol_vacio(*tad)){
		//CD: se ha encontrado el nodo que se desea eliminar
		if ((*tad)->elemento.stock_number==elemento.stock_number){
			ArbolBinarioBusqueda nodo_a_eliminar;
			if (es_arbol_vacio((*tad)->hijo_der)){
				nodo_a_eliminar=*tad;
				*tad=(*tad)->hijo_izq;
				free(nodo_a_eliminar);
			}
			else if (es_arbol_vacio((*tad)->hijo_izq)){
				nodo_a_eliminar=*tad;
				*tad=(*tad)->hijo_der;
				free(nodo_a_eliminar);
			}
			else			
				eliminar_auxiliar(tad, &(*tad)->hijo_der);
		}
		//CR1: el nodo que se quiere eliminar es menor que la raíz del árbol pasado como parámetro
		else if ((*tad)->elemento.amount >elemento.amount)
			eliminar(&(*tad)->hijo_izq, elemento);
		//CR2: el nodo que se quiere eliminar es mayor que la raíz del árbol pasado como parámetro
		else
			eliminar(&(*tad)->hijo_der, elemento);
	}	
}

//elimina el nodo que está más a la izquierda del arbol_derecha.
//y copia el valor del elemento a la raíz del árbol tad.
void eliminar_auxiliar(ArbolBinarioBusqueda *tad, ArbolBinarioBusqueda *arbol_derecha){
	if (!es_arbol_vacio((*arbol_derecha)->hijo_izq))
		eliminar_auxiliar(tad, &(*arbol_derecha)->hijo_izq);
	else{
		(*tad)->elemento=(*arbol_derecha)->elemento;
		ArbolBinarioBusqueda nodo_a_eliminar=*arbol_derecha;
		*arbol_derecha=(*arbol_derecha)->hijo_der;
		free(nodo_a_eliminar);
	}
}

int are_first_chars_the_same(char* dt1, char *dt2, int size){
	for (int i=0; i<size; i++){
		if (dt1[i] != dt2[i])
			return 0;
	}
	return 1;
}

int is_present(NodoArbol *tree_ptr, ElementoArbol data){
	int result = 0;
	if (tree_ptr == NULL)
		return result;
	if (tree_ptr != NULL && 
		are_first_chars_the_same(tree_ptr->elemento.doc_number, data.doc_number, 8))
		return 1;

	if (data.amount < tree_ptr->elemento.amount)
		result = is_present(tree_ptr->hijo_izq, data);
	else
		result = is_present(tree_ptr->hijo_der, data);

	return result;	
}

int is_possible_insert(ArbolBinarioBusqueda * tree_ptr, ElementoArbol data, char* ref_date){
	if (are_first_chars_the_same(data.datetime, ref_date, 8)){
		if (is_present(*tree_ptr, data))
			return 0;
		else
			return 1;
	} else
		return 0;
}

void consolidate(ArbolBinarioBusqueda tree){
	if (tree != NULL) {
		tree->elemento.status = 'P';
		consolidate(tree->hijo_izq);
		consolidate(tree->hijo_der);
	}
}

void show_report(ArbolBinarioBusqueda tree){
	if (tree != NULL){
		show_report(tree->hijo_der);
		printf("DNI: %s - Monto: %.2lf - Núm. acciones: %d - Estado: %c\n",
			tree->elemento.doc_number, tree->elemento.amount, 
			tree->elemento.stock_number, tree->elemento.status);
		show_report(tree->hijo_izq);
	}
}