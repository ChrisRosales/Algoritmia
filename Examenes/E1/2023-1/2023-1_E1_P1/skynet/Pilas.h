/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Pilas.h
 * Author: piero
 *
 * Created on 22 de mayo de 2023, 16:44
 */

#ifndef PILAS_H
#define PILAS_H

typedef struct nodo{
    
    int valor;
    nodo *sig;
    
} Nodo;

typedef struct{
    
    Nodo *cabeza;
    int longitud;
    
} Pila;

void construir(Pila &p)
{
    p.cabeza = nullptr;
    p.longitud = 0;
}

Nodo* crearNodo(int valor, Nodo *s)
{
    Nodo *p;
    p = new Nodo;
    p->sig = s;
    p->valor = valor;
    return p;
}

void apilar(Pila &pila, int valor)
{
    Nodo *p;
    p = crearNodo(valor, pila.cabeza);
    pila.cabeza = p;
    pila.longitud++;
}

int desapilar(Pila &pila)
{
    Nodo *p;
    int x;
    p = pila.cabeza;
    x = p->valor;
    pila.cabeza = p->sig;
    delete p;
    pila.longitud--;
    return x;
}

void mostrar(Pila pila)
{
    Nodo *p;
    p = pila.cabeza;
    for(int i=1; i <= pila.longitud; i++)
    {
        cout << p->valor << " ";
        p = p->sig;
    }
    cout << endl;
}

#endif /* PILAS_H */

