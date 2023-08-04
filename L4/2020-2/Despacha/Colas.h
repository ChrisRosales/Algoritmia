/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Colas.h
 * Author: cueva.r
 *
 * Created on 7 de septiembre de 2022, 08:51 AM
 */

#ifndef COLAS_H
#define COLAS_H
#include "lse.h"

typedef Elemento ElementoCola; 

typedef struct{
    Lista contenido;    
}Cola;

int es_cola_vacia(Cola );
void construir_cola(Cola *);
void encola(Cola *,ElementoCola );
ElementoCola desencola(Cola *);



#endif /* COLAS_H */
