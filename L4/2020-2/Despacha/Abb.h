/* 
 * File:   Abb.h
 * Author: cueva.r
 *
 * Created on 14 de septiembre de 2022, 09:29 AM
 */

#ifndef ABB_H
#define ABB_H
#include "Ab.h"

typedef ArbolB ArbolBB;

void insertar_abb(ArbolBB *,ElementoArbol );
ElementoArbol minimoabb(ArbolBB );
ElementoArbol maximoabb(ArbolBB );
ArbolBB minimoarbol(ArbolBB tad);
ArbolBB  borranodo(ArbolBB,ElementoArbol );
int comparaabb(ElementoArbol , ElementoArbol ); 
ArbolBB buscaarbol(ArbolBB ,ElementoArbol );
void asigna(ElementoArbol *a, ElementoArbol b);
#endif /* ABB_H */
