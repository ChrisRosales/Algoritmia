#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"

void insertar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad)){
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	}
	else{
		if ((*tad)->elemento.price > elemento.price)
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
			if (recorrido->elemento.price > elemento.price)
				recorrido=recorrido->hijo_izq;
			else
				recorrido=recorrido->hijo_der;
		}
		if (padre->elemento.price > elemento.price)
			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
		else
			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);		
	}
}

int esta(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento.name == llave.name)
			return 1;
		else if (tad->elemento.price >llave.price)
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
			if (tad->elemento.name == llave.name)
				return 1;
			if (tad->elemento.price >llave.price)
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
		return tad->elemento.price;
	else
		return minimo_valor(tad->hijo_izq);
}

int maximo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(52);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento.price;
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
	return tad->elemento.price;
}

int maximo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor valor pues el árbol está vacío.\n");
		exit(54);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento.price;
}

void eliminar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (!es_arbol_vacio(*tad)){
		//CD: se ha encontrado el nodo que se desea eliminar
		if ((*tad)->elemento.name==elemento.name){
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
		else if ((*tad)->elemento.price >elemento.price)
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


int get_balance(ArbolBinarioBusqueda tad){
	return altura(tad->hijo_izq) - altura(tad->hijo_der);
}

ArbolBinarioBusqueda right_rotate(ArbolBinarioBusqueda tad) {
	ArbolBinarioBusqueda tad_left = tad->hijo_izq;
	tad->hijo_izq = tad_left->hijo_der;
	tad_left->hijo_der = tad;
	return tad_left;
}

ArbolBinarioBusqueda left_rotate(ArbolBinarioBusqueda tad) {
	ArbolBinarioBusqueda tad_right = tad->hijo_der;
	tad->hijo_der = tad_right->hijo_izq;
	tad_right->hijo_izq = tad;
	return tad_right;
}

ArbolBinarioBusqueda balance(ArbolBinarioBusqueda arbol) {
    ArbolBinarioBusqueda origin_arbol, parent_arbol;
    int is_balanced = 0, is_in_down_level = 0;
    origin_arbol = arbol;
    
    while (!is_balanced){
        if (get_balance(arbol) > 1 ||
            get_balance(arbol) == 1 && numero_nodos(arbol->hijo_izq) > numero_nodos(arbol->hijo_der)){
                arbol = right_rotate(arbol);
                if (!is_in_down_level)
                    origin_arbol = arbol;
                else
                    parent_arbol->hijo_izq = arbol;
                if (get_balance(origin_arbol) == 0)
                    is_balanced = 1;
        } else if (get_balance(arbol) < -1 ||
            get_balance(arbol) == -1 && numero_nodos(arbol->hijo_der) > numero_nodos(arbol->hijo_izq)) {
                arbol = left_rotate(arbol);
                if (!is_in_down_level)
                    origin_arbol = arbol;
                else
                    parent_arbol->hijo_der = arbol;
                if (get_balance(origin_arbol) == 0)
                    is_balanced = 1;                
        } else if (get_balance(arbol) == 1 && 
                    numero_nodos(arbol->hijo_izq) == numero_nodos(arbol->hijo_der)){
            parent_arbol = arbol;
            arbol = arbol->hijo_izq;
            is_in_down_level = 1;
        } else if (get_balance(arbol) == -1 && 
                    numero_nodos(arbol->hijo_izq) == numero_nodos(arbol->hijo_der)) {
            parent_arbol = arbol;
            arbol = arbol->hijo_der;
            is_in_down_level = 1;
        }
    }
    arbol = origin_arbol;
    return arbol;
}

void show_products(ArbolBinarioBusqueda tad, int price) {
    if (!es_arbol_vacio(tad)){
    	if (tad->elemento.price <= price) {
        	printf(" %c-%d ", tad->elemento.name, tad->elemento.price );
    	}
        show_products(tad->hijo_izq, price);
        show_products(tad->hijo_der, price);
    }
}