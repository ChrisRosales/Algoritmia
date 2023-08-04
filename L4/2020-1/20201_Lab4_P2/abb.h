/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   abb.h
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 5 de noviembre de 2022, 16:58
 */

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

#endif /* ABB_H */

