
/* 
 * File:   FuncionesPilas.h
 * Author: Piero Franchesco Gonzales Fernandez
 * Codigo: 20201706
 * Created on 15 de septiembre de 2022, 09:36 AM
 */

#ifndef FUNCIONESPILAS_H
#define FUNCIONESPILAS_H

typedef struct{
    
    int codigo;
    int fechaVencimiento;
    
    
    
}ElementoPila;

typedef struct nodo{
    ElementoPila elemento;
    struct nodo *sig;
    
}Nodo;


typedef struct{
    Nodo *cima;
    int longitud;
}Pila;





void construirPila(Pila *pP);
int esPilaVacia(Pila P);
Nodo *crearNuevoNodo(ElementoPila elemento, Nodo *sig);
void apilar(Pila *pP,ElementoPila elemento);
void mostrar(Pila P);
int obtenerLongitud (Pila P);
ElementoPila desapilar(Pila *pP);
#endif /* FUNCIONESPILAS_H */

