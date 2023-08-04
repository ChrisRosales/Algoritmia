/* 
 * File:   funcionesAuxiliares.h
 * Author: Jordan Martel Alcantara
 *
 * Created on May 27, 2023, 4:19 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H
#include "listaSimple.h"

void leerDatos(Lista &listaA, Lista &listaB, Lista &listaC, Lista &listaD, Lista &listaE);
void leerDatosCategoria(Lista &lista,ifstream &archDatos);
void fusionarListas(Lista &listaA, Lista &listaB, Lista &listaC, Lista &listaD, Lista &listaE);
void fusionar2Listas(Lista  &L1, Lista &L2);

#endif /* FUNCIONESAUXILIARES_H */

