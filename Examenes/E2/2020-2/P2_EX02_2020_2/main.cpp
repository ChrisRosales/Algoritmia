/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Ricardo
 *
 * Created on 10 de julio de 2023, 02:06 PM
 */

#include <cstdlib>
#include <iostream>

#include "ABB.h"

using namespace std;

void insertarDatos(int arrTablaProd[4][5], ABB &arbolDatos, int semana){
    Elemento e;
    for(int i=0; i<5; i++){
        e.id_producto = i+1;
        e.cantProducir = arrTablaProd[semana-1][i];
        e.semana = semana;
        insertar(arbolDatos, e);
    }
}

NodoABB *buscarCabezaSemana(NodoABB *pR, int semana){
    NodoABB *p;
    p = pR;
    while ( p != NULL )
    {
        if ( semana == p->elem.semana )  // si lo encuentra retorna true
            return p;
        else
            if ( semana < p->elem.semana )
                p = p->hizq;   // continua la búsqueda en el subárbol izquierdo
            else
                p = p->hder;   // continua la búsqueda en el subárbol derecho
    }
    return NULL;
}

NodoABB* buscarMayor(NodoABB* pR, int semana){
    NodoABB *p;
    p = pR;
    while ( p->hder != NULL and p->hder->elem.semana == semana)
        p = p->hder;
    return p;
}

NodoABB* borraNodo(NodoABB* pA, Elemento e) {
    NodoABB *pR;
    pR = pA;
    // Vamos a utilizar recursividad para encontrar el nodo con el valor a eliminar
    if (pR == NULL)
        return pR; // El nodo actual es nulo, no hay nodos para borrar. (Caso base)
    if (e.semana < pR->elem.semana)
        pR->hizq = borraNodo(pR->hizq, e); // Buscamos el nodo a eliminar en el subárbol izquierdo
    else if (e.semana > pR->elem.semana)
        pR->hder = borraNodo(pR->hder, e); // Buscamos el nodo a eliminar en el subárbol derecho
    else if (e.cantProducir < pR->elem.cantProducir)
        pR->hizq = borraNodo(pR->hizq, e);
    else if (e.cantProducir > pR->elem.cantProducir)
        pR->hder = borraNodo(pR->hder, e);
    else if (e.id_producto < pR->elem.id_producto)
        pR->hizq = borraNodo(pR->hizq, e);
    else if (e.id_producto > pR->elem.id_producto)
        pR->hizq = borraNodo(pR->hizq, e);
    else {
        // Encontramos el nodo a eliminar
        if (pR->hizq == NULL) {
            // El nodo tiene al menos un hijo en el subárbol derecho
            NodoABB* temp = pR->hder; // Nos quedamos con el hijo derecho
            delete pR; // Eliminamos la raíz
            return temp; // Devolvemos el hijo derecho como nueva raíz
        }
        else if (pR->hder == NULL) {
            // El nodo tiene al menos un hijo en el subárbol izquierdo
            NodoABB* temp = pR->hizq; // Nos quedamos con el hijo izquierdo
            delete pR; // Eliminamos la raíz
            return temp; // Devolvemos el hijo izquierdo como nueva raíz
        }
        else {
            // El nodo tiene ambos hijos
            // Entonces vamos a hallar el menor elemento de ese subárbol derecho
            NodoABB* temp = menor(pR->hder); // Buscamos el nodo con el valor mínimo
            pR->elem.semana = temp->elem.semana; // Reemplazamos el valor del nodo actual con el valor mínimo
            pR->elem.cantProducir = temp->elem.cantProducir;
            pR->elem.id_producto = temp->elem.id_producto;
            pR->hder = borraNodo(pR->hder, temp->elem); // Eliminamos el nodo mínimo del subárbol derecho
        }
    }
}

void atenderOrdenes(ABB &arbolDatos, int capacidad){
    NodoABB *cabeza, *orden;
    Elemento ordenActualizada;
    int cantidadAtender, ordenesRevisadas = 5;
    //atendemos por semana
    for(int semana=1; semana<=4; semana++){
        int capacidadSemana = capacidad;
        while(capacidadSemana > 0 and ordenesRevisadas >= 0){      
            //buscamos la cabeza con la semana actual
            cabeza = buscarCabezaSemana(arbolDatos, semana);
            //buscamos el nodo con mayor cantidad pedida
            orden = buscarMayor(cabeza, semana);
            //guardamos el elemento del nodo
            ordenActualizada = orden->elem;
            //actualizamos la orden
            if(orden->elem.cantProducir<capacidadSemana){
                cantidadAtender = orden->elem.cantProducir;
                capacidadSemana -=cantidadAtender;
                ordenActualizada.cantProducir = 0;
            }else{
                cantidadAtender = capacidadSemana;
                capacidadSemana = 0;
                ordenActualizada.cantProducir -=cantidadAtender;
            }
            //imprimimos la orden que vamos a atender
            if(cantidadAtender != 0){
                cout << "Semana: " << orden->elem.semana << "   ";
                cout << "Producto: " << orden->elem.id_producto << "   ";
                cout << "Cant. Atendida: " << cantidadAtender << endl;
                //eliminamos el nodo del arbol
                borraNodo(arbolDatos, orden->elem);
                //insertamos el nodo actualizado en el arbol
                insertar(arbolDatos, ordenActualizada);
            } 
            ordenesRevisadas--;
        }
        //mostrarEnPreOrden(arbolDatos);
        ordenesRevisadas = 5;
        //retirarNoAtendido(arbolDatos);
    }
}

int main(int argc, char** argv) {
    int p = 40, n = 5, capacidad = p/4;
    int arrTablaProd[4][5] =   {{4,2,8,0,2},
                                {0,0,0,3,2},
                                {2,3,4,0,0},
                                {0,3,2,0,0}};
    ABB arbolDatos;
    construir(arbolDatos);
    
    insertarDatos(arrTablaProd, arbolDatos, 3);
    insertarDatos(arrTablaProd, arbolDatos, 4);
    insertarDatos(arrTablaProd, arbolDatos, 1);
    insertarDatos(arrTablaProd, arbolDatos, 2);
    
    //mostrarEnOrden(arbolDatos);
    //mostrarEnPreOrden(arbolDatos);
    
    atenderOrdenes(arbolDatos, capacidad);
    //mostrarEnPreOrden(arbolDatos);
    cout << endl << endl;
    mostrarEnOrden(arbolDatos);
    
    return 0;
}

