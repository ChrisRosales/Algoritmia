/* 
 * File:   funcionesAuxiliares.cpp
 * Author: Jordan Martel Alcantara
 *
 * Created on May 27, 2023, 4:19 PM
 */

#include <iostream>
#include <iomanip>     
#include <fstream>
using namespace std;
#include "listaSimple.h"
#include "funcionesAuxiliares.h"

void leerDatos(Lista &listaA, Lista &listaB, Lista &listaC, Lista &listaD, Lista &listaE){
    ifstream archDatos("datos.txt",ios::in);
    if(not archDatos.is_open()){
        cout<<"ERROR:No se pudo abrir el archivo datos.txt"<<endl;
        exit(1);
    }
    leerDatosCategoria(listaA,archDatos);
    mostrar(listaA);
    leerDatosCategoria(listaB,archDatos);
    mostrar(listaB);
    leerDatosCategoria(listaC,archDatos);
    mostrar(listaC);
    leerDatosCategoria(listaD,archDatos);
    mostrar(listaD);
    leerDatosCategoria(listaE,archDatos);
    mostrar(listaE);
    
}
void leerDatosCategoria(Lista &lista,ifstream &archDatos){
    int nivel;
    char categoria,c;
    while(true){
        archDatos>>categoria>>c>>nivel;
        //Creamos el nodo
        Elemento elem;
        elem.categoria=categoria;
        elem.impacto=nivel;
        insertarFinal(lista,elem);
        if(archDatos.get()=='\n')break;
    }
}
void fusionarListas(Lista &listaA, Lista &listaB, Lista &listaC, Lista &listaD, Lista &listaE){
    fusionar2Listas(listaA,listaB);
    mostrar(listaA);
    fusionar2Listas(listaA,listaC);
    mostrar(listaA);
    fusionar2Listas(listaA,listaD);
    mostrar(listaA);
    fusionar2Listas(listaA,listaE);
    mostrar(listaA);
}
void fusionar2Listas(Lista &principal,Lista &secundaria){
    //Creamos los nodos que usaremos
    Nodo *nodoPrincipal, *nodoSecundario, *nodoAnterior;
    //Ambos nodos apuntan a la cabeza de ambas listas
    nodoPrincipal=principal.cabeza;
    nodoSecundario=secundaria.cabeza;
    nodoAnterior=NULL;
    //Recorremos la lista secundaria
    while(nodoSecundario!=NULL){
        if(nodoPrincipal!=NULL){
            //Comparo los niveles de impacto, cuando no coinciden 
            if(nodoSecundario->elem.impacto > nodoPrincipal->elem.impacto){
                Nodo *aux;
                aux=crearNodo(nodoSecundario->elem,NULL);
                
                //Lo agregamos a la lista principal
                if(nodoAnterior!=NULL){
                    nodoAnterior->sig=aux;
                }
                else{
                    principal.cabeza=aux;
                }
                aux->sig=nodoPrincipal;
                nodoAnterior=aux;
                nodoSecundario=nodoSecundario->sig;
                principal.longitud++;
            }
            else{
                nodoAnterior=nodoPrincipal;
                nodoPrincipal=nodoPrincipal->sig;
            }
        }
        else{
            //El elemento que se quiere agregar debe ir al final
            insertarFinal(principal,nodoSecundario->elem);
            nodoSecundario=nodoSecundario->sig;
        }
    }
}
