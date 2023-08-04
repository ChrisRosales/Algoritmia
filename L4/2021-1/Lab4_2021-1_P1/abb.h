#ifndef ABB_H
#define ABB_H
#include "ab.h"
#include "pilas.h"

typedef ArbolBinario ArbolBinarioBusqueda;

void insertar(ArbolBinarioBusqueda *, ElementoArbol);
void insertar_iterativo(ArbolBinarioBusqueda *, ElementoArbol);
int esta(ArbolBinarioBusqueda, ElementoArbol);
int esta_iterativo(ArbolBinarioBusqueda, ElementoArbol);
int minimo_valor(ArbolBinarioBusqueda);
int maximo_valor(ArbolBinarioBusqueda);
int minimo_iterativo(ArbolBinarioBusqueda);
int maximo_iterativo(ArbolBinarioBusqueda);
void eliminar(ArbolBinarioBusqueda *, ElementoArbol);
void eliminar_auxiliar(ArbolBinarioBusqueda *, ArbolBinarioBusqueda *);

//Nuevas funciones para resolver el laboratorio 4 del 2021-1
void dispatch(ArbolBinarioBusqueda * my_tree, int num_to_dispatch, Pila *stack);
void return_batches(Pila *, ArbolBinarioBusqueda*);

#endif