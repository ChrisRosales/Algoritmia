/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   abb.h
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 10 de junio de 2022, 15:23
 */

#ifndef ABB_H
#define ABB_H
#include "ab.h"
typedef ArbolBinario ABB;

void insertar(ABB *, ElementoArbol);
void insertar_iterativo(ABB *, ElementoArbol);
int esta(ABB, ElementoArbol);
int esta_iterativo(ABB, ElementoArbol);
int minimo_valor(ABB);
int maximo_valor(ABB);
int minimo_iterativo(ABB);
int maximo_iterativo(ABB);
void juntar(ABB *,ABB *);
void verificar(ABB *tad,ElementoArbol elemento);
int verificacionInserta(ABB *tad, ElementoArbol elemento);
void actualizar(ABB *tad,ElementoArbol elemento);
int verificacionDeActualizacion(ABB *tad,ElementoArbol elementoActualizar);
void modificar(ABB *tad,ElementoArbol elementoModificar);

#endif /* ABB_H */

