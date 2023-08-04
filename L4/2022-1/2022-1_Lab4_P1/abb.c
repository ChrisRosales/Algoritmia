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

void insertar(ABB *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad))
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	else {
		//Los campos 1 y 2 son los primary key 
		if ((*tad)->elemento.campo1 >elemento.campo1 && (*tad)->elemento.campo2 <elemento.campo2)
			insertar(&(*tad)->hijo_izq, elemento);
		else
			insertar(&(*tad)->hijo_der, elemento);
	}
}

//Crear una funcion que permita verificar si se puede insertar un elemento en el arbol binario
//Si es que los campos 1 y 2 son iguales, no se puede insertar

void verificar(ABB *tad,ElementoArbol elemento){
	int validacion=verificacionInserta(tad,elemento);
	if(validacion==1){
		printf("Ok");
	}
	else{
		printf("Cannot insert duplicate key\n");
	}
}

void actualizar(ABB *tad,ElementoArbol elemento){
	int validacion=verificacionActualiza(tad,elemento);
	if(validacion==1){
		printf("Ok");
	}
	else{
		printf("Violation of Primary Key constraint on update\n");
	}
}

int verificacionInserta(ABB *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad))
		return 1;
	else {
		//Los campos 1 y 2 son los primary key 
		if ((*tad)->elemento.campo1 ==elemento.campo1 && (*tad)->elemento.campo2 ==elemento.campo2)
			return 0;
		else if ((*tad)->elemento.campo1 >elemento.campo1 && (*tad)->elemento.campo2 <elemento.campo2)
			return verificacionInserta(&(*tad)->hijo_izq, elemento);
		else
			return verificacionInserta(&(*tad)->hijo_der, elemento);
	}
}

int verificacionDeActualizacion(ABB *tad,ElementoArbol elementoActualizar){
	if(es_arbol_vacio(*tad)){
		return 0;
	}else{
		if(esta(tad,elementoActualizar)){
			//Si es que no se encuentra el elemento, no se puede actualizar
			return 0;
		}else{
			//Si es que no se encuentra el elemento, si se puede actualizar dicho elemento
			return 1;
		}
	}
}

void modificar(ABB *tad,ElementoArbol elementoModificar){
	if(verificacionDeActualizacion(tad,elementoModificar)){
		if((*tad)->elemento.campo1==elementoModificar.campo1 && (*tad)->elemento.campo2==elementoModificar.campo2){
			(*tad)->elemento=elementoModificar;
		}else{
			if((*tad)->elemento.campo1>elementoModificar.campo1 && (*tad)->elemento.campo2<elementoModificar.campo2){
				modificar(&(*tad)->hijo_izq,elementoModificar);
			}else{
				modificar(&(*tad)->hijo_der,elementoModificar);
			}
		}
	}
}

void rotarNodos(ABB *arbolCambiante){
	if(es_arbol_vacio(*arbolCambiante)){
		return;
	}else{
		
	}
}

/*void insertar_iterativo(ABB *tad, ElementoArbol elemento){
	if (es_arbol_vacio(*tad))
		plantar_arbol_binario(tad, NULL, elemento, NULL);
	else {
		ABB recorrido=*tad, padre=NULL;
		while(!es_arbol_vacio(recorrido)){
			padre=recorrido;
			if (recorrido->elemento>elemento)
				recorrido=recorrido->hijo_izq;
			else
				recorrido=recorrido->hijo_der;
		}
		if (padre->elemento>elemento)
			plantar_arbol_binario(&padre->hijo_izq, NULL, elemento, NULL);
		else
			plantar_arbol_binario(&padre->hijo_der, NULL, elemento, NULL);
	}
}*/

int esta(ABB tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		if (tad->elemento.campo1==llave.campo1 && tad->elemento.campo2==llave.campo2)
			return 1;
		else if (tad->elemento.campo1 >llave.campo1)
			return esta(tad->hijo_izq, llave);
		else
			return esta(tad->hijo_der, llave);

	}
}

/*int esta_iterativo(ABB tad, ElementoArbol llave){
	if (es_arbol_vacio(tad))
		return 0;
	else{
		while(!es_arbol_vacio(tad)){
			if (tad->elemento==llave)
				return 1;
			if (tad->elemento>llave)
				tad=tad->hijo_izq;
			else
				tad=tad->hijo_der;
		}
		return 0;
	}
}*/

int minimo_valor(ABB tad){
	if (es_arbol_vacio(tad)){
		printf("El árbol está vacío por lo tanto no tiene valor mínimo.\n");
		exit(100);
	}
	if (es_arbol_vacio(tad->hijo_izq))
		return tad->elemento.campo1;
	else
		return minimo_valor(tad->hijo_izq);
}

int maximo_valor(ABB tad){
	if (es_arbol_vacio(tad)){
		printf("El árbol está vacío por lo tanto no tiene valor máximo.\n");
		exit(101);
	}
	if (es_arbol_vacio(tad->hijo_der))
		return tad->elemento.campo1;
	else
		return maximo_valor(tad->hijo_der);
}

int minimo_iterativo(ABB tad){
	if (es_arbol_vacio(tad)){
		printf("El árbol está vacío por lo tanto no tiene valor mínimo.\n");
		exit(102);
	}
	while(!es_arbol_vacio(tad->hijo_izq))
		tad=tad->hijo_izq;
	return tad->elemento.campo1;
}

int maximo_iterativo(ABB tad){
	if (es_arbol_vacio(tad)){
		printf("El árbol está vacío por lo tanto no tiene valor máximo.\n");
		exit(103);
	}
	while(!es_arbol_vacio(tad->hijo_der))
		tad=tad->hijo_der;
	return tad->elemento.campo1;
}

/*void juntar(ABB *parbol1,ABB *parbol2){
    if (es_arbol_vacio(*parbol1)){
		*parbol1=*parbol2;
		*parbol2=NULL;
    }
    else if (es_arbol_vacio(*parbol2)){
		*parbol2=*parbol1;
		*parbol1=NULL;
    }
    else{
		ABB recorrido=*parbol1;
		ABB padre=NULL;
		while(!es_arbol_vacio(recorrido)){
        	padre=recorrido;
        	if (recorrido->elemento>(*parbol2)->elemento)
				recorrido=recorrido->hijo_izq;
        	else
				recorrido=recorrido->hijo_der;
		}
		if (padre->elemento>(*parbol2)->elemento)
        	plantar_arbol_binario(&padre->hijo_izq, NULL, (*parbol2)->elemento, NULL);
		else
        	plantar_arbol_binario(&padre->hijo_der, NULL, (*parbol2)->elemento, NULL);
        	*parbol2=NULL;
	}
}

void juntarRecursivo(ABB *parbol1,ABB *parbol2){
	ElementoArbol valor;
	ABB paux;
	paux=*parbol2;
	if(paux){
		juntarRecursivo(parbol1,&paux->hijo_izq);
		juntarRecursivo(parbol1,&paux->hijo_der);
		valor=paux->elemento;
		free(paux);
		insertar(parbol1,valor);
		*parbol2=NULL;
	}

}*/

/*ABB borrarNodo(ABB parbol,ElementoArbol valor){
	if(parbol==NULL){
		return parbol;
	}
	if(valor<parbol->elemento){
		parbol->hijo_izq=borrarNodo(parbol->hijo_izq,valor);
	}
	else{
		if(valor>parbol->elemento){
			parbol->hijo_der=borrarNodo(parbol->hijo_der,valor);
		}else{
			if(parbol->hijo_izq=NULL){
				ABB aux=parbol->hijo_der;
				free(parbol);
				return aux;
			}
			else{
				if(parbol->hijo_der=NULL){
					ABB aux=parbol->hijo_izq;
					free(parbol);
					return aux;
				}
				else{
					ABB aux=parbol->hijo_izq;
					while(aux->hijo_der!=NULL){
						aux=aux->hijo_der;
					}
					parbol->elemento=aux->elemento;
					parbol->hijo_der=borrarNodo(parbol->hijo_der,aux->elemento);
				}
			}
		}
	}
}*/

/*ABB buscaM(ABB parbol){
	if(parbol==NULL){
		return NULL;
	}else{
		if(parbol->hijo_izq==NULL){
			return parbol;
		}else{
			return buscaM(parbol->hijo_izq);
		}
	}
}*/