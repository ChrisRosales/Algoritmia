#ifndef AB_H
#define AB_H
#include "product.h"

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

#endif
