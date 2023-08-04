#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"

void insertar(ArbolBinarioBusqueda *tad, ElementoArbol elemento, StockArbol stock){
	if (es_arbol_vacio(*tad))
		plantar_arbol_binario(tad, NULL, elemento, stock, NULL);
	else{
		if ((*tad)->elemento>elemento)
			insertar(&(*tad)->hijo_izq, elemento, stock);
		else
			insertar(&(*tad)->hijo_der, elemento, stock);
	}
}

// void insertar_iterativo(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
// 	if (es_arbol_vacio(*tad))
// 		plantar_arbol_binario(tad, NULL, elemento, NULL);
// 	else{
// 		//parte 1. Se busca el padre de la hoja que se va a colocar
// 		ArbolBinarioBusqueda recorrido=*tad, padre=NULL;
// 		while(!es_arbol_vacio(recorrido)){
// 			padre=recorrido;
// 			if (recorrido->elemento>elemento)
// 				recorrido=recorrido->hijo_izq;
// 			else
// 				recorrido=recorrido->hijo_der;
// 		}

// 		//parte 2. Se planta la hoja en el árbol
// 		if (padre->elemento>elemento)
// 			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
// 		else
// 			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);
// 	}
// }

int esta(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento==llave)
			return 1;
		else if(tad->elemento>llave)
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
			if (tad->elemento==llave)
				return 1;
			if(tad->elemento>llave)
				tad=tad->hijo_izq;
			else
				tad=tad->hijo_der;
		}
	}
	return 0;
}

int minimo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor pues el árbol está vacío.\n");
		exit(51);
	}
	if (es_arbol_vacio(tad->hijo_izq))
		return tad->elemento;
	else
		return minimo_valor(tad->hijo_izq);
}

int maximo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor pues el árbol está vacío.\n");
		exit(52);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento;
	else
		return maximo_valor(tad->hijo_der);
}

int minimo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor pues el árbol está vacío.\n");
		exit(53);
	}
	while(!es_arbol_vacio(tad->hijo_izq))
		tad=tad->hijo_izq;
	return tad->elemento;
}

int maximo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor pues el árbol está vacío.\n");
		exit(54);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento;
}