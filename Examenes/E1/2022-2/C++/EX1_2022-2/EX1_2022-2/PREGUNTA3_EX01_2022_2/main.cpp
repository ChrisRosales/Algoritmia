/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: AlienCoders
 *
 * Created on 15 de mayo de 2023, 06:55 PM
 */

#include <iostream>

using namespace std;
#include "listaSimple.h"
#include "cola.h"

void llenarLista(int n, Lista &lista){
    for(Elemento i=2 ; i<=n ; i++){
        insertarFinal(lista, i);
    }    
}

void EliminarMultiplos(Lista &lista, int index){

    Cola cola;
    construir(cola);
    
    Nodo *nodo=lista.cabeza;
    for(int i=0 ; i<index ; i++) nodo = nodo->sig;
     //caso base
    if( nodo==NULL ) return;
    
    //nodo de inicio
    int dato = nodo->elem;//2
    
    nodo = nodo->sig;
    while(nodo!=NULL){
        int datoNodo = nodo->elem; 
        nodo = nodo->sig;
        if(datoNodo % dato == 0){ // multiplos
            encolar(cola, datoNodo);
            
            //eliminar nodo de la lista    
            eliminar(lista, datoNodo);                
        }
    }
    
    //imprime
    cout<<"Numero Procesado: "<<dato<<endl;
    cout<<"Numeros Tachados para el "<<dato<<": ";
    mostrar(cola);
    
    EliminarMultiplos(lista, index+1);
}

int main(int argc, char** argv) {
    
        int n;
    cout<<"Ingrese el valor de n: ";
    cin>>n;
    
    Lista lista;
    construir(lista);
    
    llenarLista(n, lista);
    EliminarMultiplos(lista, 0);
            

    return 0;
}

