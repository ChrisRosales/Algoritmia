/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 10 de junio de 2023, 15:04
 */

#include <iostream>

#include "abb.h"
#include "pila.h"

using namespace std;

void fusionar(NodoABB* pR1, NodoABB* pR2);
NodoABB* buscarNodo(NodoABB* pR, int lote);
NodoABB* insertarRecursivo(NodoABB* pR, int lote, int cantidad);

void preOrdenIterativo(NodoABB *raiz);

int main(int argc, char** argv) {
    // Creacion de los arboles
    ABB Peach, Donkey;
    construir(&Peach);
    construir(&Donkey);

    int cntPeach, cntDonkey;

    cout << "Inserte la cantida de niveles de nivel que tiene el ejercicio de Peach" << endl;
    cin >> cntPeach;
    cout << "Ingrese el nivel y la cantidad de guerreros de dicho nivel:\n";
    Elemento aux;
    for (int i = 0; i < cntPeach; i++) {
        cin >> aux.nivel >> aux.cnt_guerreros;
        insertar(&Peach, aux);
    }

    cout << "Inserte la cantida de niveles de nivel que tiene el ejercicio de Donkey" << endl;
    cin >> cntDonkey;
    cout << "Ingrese el nivel y la cantidad de guerreros de dicho nivel:\n";
    for (int i = 0; i < cntDonkey; i++) {
        cin >> aux.nivel >> aux.cnt_guerreros;
        insertar(&Donkey, aux);
    }

    NodoABB *peachRaiz = obtenerRaiz(Peach);
    NodoABB *donkeyRaiz = obtenerRaiz(Donkey);


    cout << "\nAntes de la fusion"
            << "Ejercicitos en Orden";
    cout << "\nEjercicito de Peach: " << endl;
    mostrarEnOrden(peachRaiz);
    cout << "\nEjercicito de Donkey: " << endl;
    mostrarEnOrden(donkeyRaiz);
    cout << "\nFusion de los arboles en Orden\n" << endl;
    fusionar(peachRaiz, donkeyRaiz);
    mostrarEnOrden(peachRaiz);
    cout << "\nFusion de los arboles en PreOrdenIterativo\n";
    preOrdenIterativo(peachRaiz);
    /*Ejemplo de ejecucion del programa
     5
     52 2
     40 1
     25 3
     42 2
     60 1
     
     6
     65 1
     25 1
     12 2
     34 1
     75 2
     70 1
     */
    return 0;
}

// Funcion que imprime el arbol en forma de preorden Iterativo
/*
 Para este poder realizar el preOrdenIterativo, lo que se realizo
 fue que el ElementoP es un NodoABB *
 para que asi podamos apilar y desapilar cada nodo del Arbol a imprimir
 Apilamos la raiz, ya que este es el primer valor que tenemos que almacenar
 Posteriormente imprimos segundo el formato pedido
 Apilamos el hijoDerecho y hijoIzquierdo en caso estos no sean nullptr
    Primero se apilo el hijo derecho, ya que en la impresion preOrden, primero se imprime el hijoIzquierdo y posteriormente el hijoDerecho
 En el siguiente bucle desapilamos el nodo hijoIzquierdo, imprimos su valor y apilamos sus repestivos hijos
 y asi sucesivamente hasta que la pila este completamente vacia, y acabe nuestra funcion
 */
void preOrdenIterativo(NodoABB *raiz) {
    if (raiz == nullptr) return ;
    Pila pila;
    construirPila(&pila);
    apilar(&pila, raiz);
    while (!esPilaVacia(pila)) {
        NodoABB *arbol = desapilar(&pila);
        cout << "(" << arbol->elem.nivel << " - " << arbol->elem.cnt_guerreros << ") ";
        if (arbol->hder != nullptr)
            apilar(&pila, arbol->hder);
        if (arbol->hizq != nullptr)
            apilar(&pila, arbol->hizq);
    }
}

/*Funciones que se uso del Profesor Huaman
 Semana 11, pregunta 2020_1-L4-P2*/
void fusionar(NodoABB* pR1, NodoABB* pR2) {
    int nivel, guerreros;
    NodoABB* pAux;
    pAux = pR2;
    // Si el nodo auxiliar es válido (no es nulo), se realiza la fusión
    if (pAux) {
        // Se fusiona el subárbol izquierdo del nodo auxiliar con el árbol pR1
        fusionar(pR1, pAux->hizq);
        // Se fusiona el subárbol derecho del nodo auxiliar con el árbol pR1
        fusionar(pR1, pAux->hder);
        // Se obtiene el lote y la cantidad del nodo auxiliar
        nivel = pAux->elem.nivel;
        guerreros = pAux->elem.cnt_guerreros;
        // Se elimina el nodo auxiliar
        delete pAux;
        // Se busca si ya existe un nodo con el mismo lote en el árbol pR1
        NodoABB* nodoExistente = buscarNodo(pR1, nivel);
        // Si se encuentra un nodo existente con el mismo lote, se suma la cantidad
        if (nodoExistente) {
            nodoExistente->elem.cnt_guerreros += guerreros;
        } else { // Si no se encuentra un nodo existente con el mismo lote, se inserta un nuevo nodo en el árbol pR1
            pR1 = insertarRecursivo(pR1, nivel, guerreros); // Se asume que existe una función llamada "insertarRecursivo"
        }
        // Se asigna nulo al árbol pR2, ya que se ha fusionado con pR1
        pR2 = nullptr;
    }
}

// Función para buscar un nodo en un árbol binario de búsqueda (ABB) por su nivel

NodoABB* buscarNodo(NodoABB* pR, int nivel) {
    // Si la raíz es nula o el nivel del nodo es igual al nivel buscado, se ha encontrado el nodo
    if (pR == nullptr || pR->elem.nivel == nivel) {
        return pR;
    }

    // Si el nivel buscado es menor que el nivel del nodo raíz, se busca en el subárbol izquierdo
    if (nivel < pR->elem.nivel) {
        return buscarNodo(pR->hizq, nivel);
    } else { // Si no, se busca en el subárbol derecho
        return buscarNodo(pR->hder, nivel);
    }
}

NodoABB* insertarRecursivo(NodoABB* pR, int nivel, int cantidad) {
    if (pR == nullptr) {
        // Creamos un nuevo nodo y lo retornamos como resultado de la inserción
        Elemento e;
        e.nivel = nivel;
        e.cnt_guerreros = cantidad;
        return crearNodo(e);
    } else if (nivel < pR->elem.nivel) {
        // Insertamos en el subárbol izquierdo y actualizamos el puntero al hijo izquierdo
        pR->hizq = insertarRecursivo(pR->hizq, nivel, cantidad);
    } else {
        // Insertamos en el subárbol derecho y actualizamos el puntero al hijo derecho
        pR->hder = insertarRecursivo(pR->hder, nivel, cantidad);
    }

    // Retornamos el puntero al nodo raíz después de realizar la inserción
    return pR;
}
