/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Colas.h
 * Author: cueva
 *
 * Created on 26 de mayo de 2020, 02:54 PM
 */

#ifndef COLAS_H
#define COLAS_H

typedef int TInfo;

typedef struct NodoCola{
    int elem;
    struct NodoCola* sig;
} TNodoCola;
typedef TNodoCola* TCola;

/*prototipos para trabajar la cola*/
void crea_cola(TCola *ptrCola);
int cola_vacia(TCola ptrCola);
void encolar(TCola *ptrCola, int valor);
void inserta_nodo(TCola *ptrCola, TInfo elem);
TNodoCola* ingresa(TCola *ptrCola);
int desencolar(TCola *ptrCola);
void imprimecola(TCola ptrcola);

#endif /* COLAS_H */
