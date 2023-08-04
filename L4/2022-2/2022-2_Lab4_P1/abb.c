/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

/*
 *Proyecto: $(project.name)
 *Archivo: $(NAME).$(EXTENSION)
 * Autor: Christian Carrillo Aburto
            20202692
 * Created on $(DATE),$(TIME) 
 */


#include<stdio.h>
#include<stdlib.h>
#include "ab.h"
#include "abb.h"

void insertar(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad))
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	else{
		if ((*tad)->elemento.cromo>elemento.cromo)
			insertar(&(*tad)->hijo_izq, elemento);
		else
			insertar(&(*tad)->hijo_der, elemento);
	}
}

/*void insertar_iterativo(ArbolBinarioBusqueda *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad))
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	else{
		//parte 1. Se busca el padre de la hoja que se va a colocar
		ArbolBinarioBusqueda recorrido=*tad, padre=NULL;
		while(!es_arbol_vacio(recorrido)){
			padre=recorrido;
			if (recorrido->elemento>elemento)
				recorrido=recorrido->hijo_izq;
			else
				recorrido=recorrido->hijo_der;
		}

		//parte 2. Se planta la hoja en el Ã¡rbol
		if (padre->elemento>elemento)
			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
		else
			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);
	}
}*/

int esta(ArbolBinarioBusqueda tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento.numeroArr==llave.numeroArr)
			return 1;
		else if(tad->elemento.numeroArr>llave.numeroArr)
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
			if (tad->elemento.numeroArr==llave.numeroArr)
				return 1;
			if(tad->elemento.numeroArr>llave.numeroArr)
				tad=tad->hijo_izq;
			else
				tad=tad->hijo_der;
		}
	}
	return 0;
}

/*int minimo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor pues el Ã¡rbol estÃ¡ vacÃ­o.\n");
		exit(51);
	}
	if (es_arbol_vacio(tad->hijo_izq))
		return tad->elemento;
	else
		return minimo_valor(tad->hijo_izq);
}
*/
/*int maximo_valor(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor pues el Ã¡rbol estÃ¡ vacÃ­o.\n");
		exit(52);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento;
	else
		return maximo_valor(tad->hijo_der);
}*/

/*int minimo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el menor pues el Ã¡rbol estÃ¡ vacÃ­o.\n");
		exit(53);
	}
	while(!es_arbol_vacio(tad->hijo_izq))
		tad=tad->hijo_izq;
	return tad->elemento;
}

int maximo_iterativo(ArbolBinarioBusqueda tad){
	if (es_arbol_vacio(tad)){
		printf("No se puede obtener el mayor pues el Ã¡rbol estÃ¡ vacÃ­o.\n");
		exit(54);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento;
}*/