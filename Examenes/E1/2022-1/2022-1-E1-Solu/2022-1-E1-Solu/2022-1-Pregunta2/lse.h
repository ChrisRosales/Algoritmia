/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lse.h
 * Author: cueva.r
 *
 * Created on 24 de agosto de 2022, 09:00 AM
 */

#ifndef LSE_H
#define LSE_H

typedef struct{
    char prioridad;
    int codigo;
}Elemento;

typedef struct nodo{
    Elemento elemento;    
    struct nodo *sig;
} Nodo;

typedef struct{
    Nodo *cabeza;
    Nodo *vip;
    Nodo *cliente;
    Nodo *cola;
    int longitud;
}Lista;

void construir(Lista *);
void imprimir(Lista );
Nodo *crear_nodo(Elemento );
void destruir(Lista *);
int es_lista_vacia(Lista );
Elemento retorna_cabeza(Lista );
void elimina_cabeza(Lista *);
void imprime_elemento(Elemento );
void insertar_prioridad(Lista *tad,Elemento );

#endif /* LSE_H */
