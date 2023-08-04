/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   ab.h
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 10 de junio de 2022, 15:23
 */

#ifndef AB_H
#define AB_H

typedef struct nodoCampos{
    //Los campos 1 y 2 seran los primary key de mi tabla
    int campo1;
    int campo2;
    int campo3;
}NodoCampos;

typedef NodoCampos ElementoArbol;


typedef struct nodoArbol {
    ElementoArbol elemento;    
    struct nodoArbol *hijo_izq;
    struct nodoArbol *hijo_der;
} NodoArbol;

typedef NodoArbol* ArbolBinario;

void construir_arbol_binario(ArbolBinario *);
void plantar_arbol_binario(ArbolBinario *, ArbolBinario, ElementoArbol, ArbolBinario);
NodoArbol *crear_nuevo_nodo_arbol(ArbolBinario, ElementoArbol, ArbolBinario);
int es_arbol_vacio(ArbolBinario);
ElementoArbol raiz(ArbolBinario);
ArbolBinario hijo_der(ArbolBinario);
ArbolBinario hijo_izq(ArbolBinario);
void imprime_raiz(ArbolBinario);
int altura(ArbolBinario);
int maximo(int, int);
int numero_nodos(ArbolBinario);
int numero_hojas(ArbolBinario);
ArbolBinario especular(ArbolBinario);
ArbolBinario copia_arbol_binario(ArbolBinario);
void destruir_arbol_binario(ArbolBinario *);
int es_equilibrado(ArbolBinario);
int es_hoja(ArbolBinario);
void es_zurdo(ArbolBinario, int *, int *);
void pre_orden(ArbolBinario);
void en_orden(ArbolBinario);
void post_orden(ArbolBinario);
void pre_orden_iterativo(ArbolBinario);
void en_orden_iterativo(ArbolBinario);
void recorrido_por_nivel(ArbolBinario);


#endif /* AB_H */

