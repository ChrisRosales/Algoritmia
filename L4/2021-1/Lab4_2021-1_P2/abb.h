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

//Nuevas funciones para resolver el laboratorio 4 - Pregunta 2 del 2021-1
int is_possible_insert(ArbolBinarioBusqueda *, ElementoArbol, char*);
void consolidate(ArbolBinarioBusqueda);
void show_report(ArbolBinarioBusqueda);
#endif