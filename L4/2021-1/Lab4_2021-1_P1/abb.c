#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"

void insertar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad)){
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	}
	else{
		if ((*tad)->elemento.id > elemento.id)
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
			if (recorrido->elemento.id > elemento.id)
				recorrido=recorrido->hijo_izq;
			else
				recorrido=recorrido->hijo_der;
		}
		if (padre->elemento.id > elemento.id)
			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
		else
			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);		
	}
}

int esta(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento.id == llave.id)
			return 1;
		else if (tad->elemento.id >llave.id)
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
			if (tad->elemento.id == llave.id)
				return 1;
			if (tad->elemento.id >llave.id)
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
		return tad->elemento.id;
	else
		return minimo_valor(tad->hijo_izq);
}

int maximo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(52);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento.id;
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
	return tad->elemento.id;
}

int maximo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(54);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento.id;
}

void eliminar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (!es_arbol_vacio(*tad)){
		//CD: se ha encontrado el nodo que se desea eliminar
		if ((*tad)->elemento.id==elemento.id){
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
		else if ((*tad)->elemento.id >elemento.id)
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


NodoArbol * get_minor_node_w_o_children(ArbolBinarioBusqueda tree){
	while (tree != NULL && (tree->hijo_izq != NULL || tree->hijo_der != NULL)){
		if (tree->hijo_izq != NULL)
			tree = tree->hijo_izq;
		else
			tree = tree->hijo_der;
	}
	return tree;
}

void dispatch(ArbolBinarioBusqueda * tree_ptr, int num_to_dispatch, Pila *stack){
	//Despacho iterativo de los nodos hoja que a su vez, son menores.
	int i=0;
	while (i < num_to_dispatch ){
		NodoArbol * minor_node_w_o_children = get_minor_node_w_o_children(*tree_ptr);
		
		/* Se crea un puntero nuevo para guardar los datos en la pila del nodo menor sin hijos del árbol*/		
		NodoArbol* new_minor_node_w_o_children = (NodoArbol*)malloc(sizeof(NodoArbol));;
		new_minor_node_w_o_children->elemento.id = minor_node_w_o_children->elemento.id;
		new_minor_node_w_o_children->elemento.quantity = minor_node_w_o_children->elemento.quantity;

		apilar(stack, new_minor_node_w_o_children);
		eliminar(tree_ptr, minor_node_w_o_children->elemento);
		i++;
	}
}

void return_batches(Pila *stack_ptr, ArbolBinarioBusqueda* tree_ptr) {
	while (!es_pila_vacia(*stack_ptr)) {
		insertar(tree_ptr, desapilar(stack_ptr)->elemento);
	}
}