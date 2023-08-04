#ifndef ABB_H
#define ABB_H
#include "ab.h"

typedef ArbolBinario ArbolBinarioBusqueda;

void insertar(ArbolBinarioBusqueda *, ElementoArbol, StockArbol);
// void insertar_iterativo(ArbolBinarioBusqueda *, ElementoArbol);
int esta(ArbolBinarioBusqueda, ElementoArbol);
int esta_iterativo(ArbolBinarioBusqueda, ElementoArbol);
int minimo_valor(ArbolBinarioBusqueda);
int maximo_valor(ArbolBinarioBusqueda);
int minimo_iterativo(ArbolBinarioBusqueda);
int maximo_iterativo(ArbolBinarioBusqueda);

#endif