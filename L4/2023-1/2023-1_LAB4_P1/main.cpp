/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 10 de junio de 2023, 16:20
 */

#include <iostream>
#include <cmath>
#include "ab.h"
#include "colas.h"

using namespace std;

/* NOTA: Se esta haciendo uso de las librerias y funciones del
 * proyecto subido en PAIDEIA, Semana 11, carpeta 0582
 * Proyecto: ArbolCalidad-Amplitud
 * Dicho proyecto fue resuelto en C, se hicieron algunas modificaciones para 
 * que pueda ser usado en C++
 */
bool recorridoPorNivel(NodoArbol *pR,ElementoArbol Skd);

int main(int argc, char** argv) {
    ArbolBinario SkyNerd;
    construir_arbol_binario(&SkyNerd);
    ElementoArbol e;
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////INSERSION DE LOS DATOS//////////////////////////
    ////////////////////////////////////////////////////////////////////////
    e.servidor = 'Z'; // raiz
    e.velocidad = 100;
    e.nivel = 1;
    plantar_arbol_binario(&SkyNerd,nullptr,e,nullptr);
    e.servidor = 'Z'; // izquierda
    e.velocidad = 50;
    e.nivel = 2;
    plantar_arbol_binario(&SkyNerd->hijo_izq,nullptr,e,nullptr);
    e.servidor = 'E'; // derecha
    e.velocidad = 200;
    e.nivel = 2;
    plantar_arbol_binario(&SkyNerd->hijo_der,nullptr,e,nullptr);
    
    // Nodos del hijo derecho de la raiz
    e.servidor = 'S';
    e.velocidad = 200;
    e.nivel = 3;
    plantar_arbol_binario(&SkyNerd->hijo_der->hijo_izq,nullptr,e,nullptr);
    e.servidor = 'S';
    e.velocidad = 150;
    e.nivel = 3;
    plantar_arbol_binario(&SkyNerd->hijo_der->hijo_der,nullptr,e,nullptr);
    // Nodos del hijo izquierdo del hijo derecho de la raiz
    e.servidor = 'S';
    e.velocidad = 100;
    e.nivel = 4;
    plantar_arbol_binario(&SkyNerd->hijo_der->hijo_izq->hijo_izq,nullptr,e,nullptr);
    e.servidor = 'E';
    e.velocidad = 200;
    e.nivel = 4;
    plantar_arbol_binario(&SkyNerd->hijo_der->hijo_izq->hijo_der,nullptr,e,nullptr);
    // Nodos del hijo izquierdo de la raiz
    e.servidor = 'E';
    e.velocidad = 100;
    e.nivel = 3;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_izq,nullptr,e,nullptr);
    e.servidor = 'S';
    e.velocidad = 50;
    e.nivel = 3;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_der,nullptr,e,nullptr);
    // Nodos del hijo del hijo izquierdo de la raiz
    e.servidor = 'S';
    e.velocidad = 50;
    e.nivel = 4;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_izq->hijo_izq,nullptr,e,nullptr);
    e.servidor = 'Z';
    e.velocidad = 200;
    e.nivel = 4;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_izq->hijo_der,nullptr,e,nullptr);
    // Nodos del hijos del hijo izquierdo del hijo izquierdo de la raiz
    e.servidor = 'E';
    e.velocidad = 50;
    e.nivel = 5;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_izq->hijo_izq->hijo_izq,nullptr,e,nullptr);
    // Nodos del hijos del hijo izquierdo del hijo izquierdo de la raiz
    e.servidor = 'E';
    e.velocidad = 100;
    e.nivel = 5;
    plantar_arbol_binario(&SkyNerd->hijo_izq->hijo_izq->hijo_der->hijo_izq,nullptr,e,nullptr);
    ////////////////////////////////////////////////////////////////////////
    ////////////////////////Busqueda por Amplitud//////////////////////////
    ////////////////////////////////////////////////////////////////////////1
    ElementoArbol skd; // aqui guardamos el nodo donde va a estar skynerd
    skd.servidor = 'S';
    skd.velocidad = 200;
    bool existeSkynerd = recorridoPorNivel(SkyNerd,skd);
    
    if(!existeSkynerd){
        cout << "Skynerd no se encuentra en el sistema\n";
    }
    return 0;
}


bool recorridoPorNivel(NodoArbol *pR,ElementoArbol Skd) {
    if (pR == nullptr)
        return false;
    Cola cola;
    construir_cola(&cola);
    pide_vez(&cola, pR);
    NodoArbol *aux;
    while (!es_cola_vacia(cola)) {
        aux = avanzar(&cola);
        if(aux->elemento.velocidad == 200){ //Padre de Skyned
            if(aux->hijo_izq != nullptr){
                NodoArbol *auxIzq = aux->hijo_izq;
                if(auxIzq->elemento.servidor == Skd.servidor && auxIzq->elemento.velocidad == Skd.velocidad){
                    cout << "SkyNerd se encuentra en el nivel: " << auxIzq->elemento.nivel;
                    destruir_cola(&cola);                
                    return true;
                }
            }
            if(aux->hijo_der != nullptr){
                NodoArbol *auxDer = aux->hijo_der;
                if(auxDer->elemento.servidor == Skd.servidor && auxDer->elemento.velocidad == Skd.velocidad){
                    cout << "SkyNerd se encuentra en el nivel: " << auxDer->elemento.nivel;
                    destruir_cola(&cola);                
                    return true;
                }
            }
        }
        if (aux->hijo_izq != nullptr)
            pide_vez(&cola, aux->hijo_izq);
        if (aux->hijo_der != nullptr)
            pide_vez(&cola, aux->hijo_der);
    }
    destruir_cola(&cola);
    return false;
}