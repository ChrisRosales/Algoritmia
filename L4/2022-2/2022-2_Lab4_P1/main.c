/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 5 de noviembre de 2022, 15:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ab.h"
#include "abb.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int arreglo[]={10,50};
    int cantidad=sizeof(arreglo)/sizeof(int);
    
    ArbolBinarioBusqueda abb;
    
    //Pregunta 1a
    construir_arbol_binario(&abb);
    llenarArbol(&abb,arreglo,cantidad);
    en_orden(abb);
    printf("\n\n");
    //Pregunta 1b
    int numeroSolicitado;
    ArbolBinarioBusqueda abb2;
    construir_arbol_binario(&abb2);
    int arregloPropuesto[]={10,50,20,30,40};
    int cantidadPropuesto=sizeof(arregloPropuesto)/sizeof(int);
    llenarArbol(&abb2,arregloPropuesto,cantidadPropuesto);
    printf("Ingrese un numero para buscar:");
    scanf("%d",&numeroSolicitado);

    int combinaciones;
    combinaciones=buscarCombinacionesV2(abb2,numeroSolicitado);
    printf("\nLa cantidad de combinaciones es: %d",combinaciones+1);
    return (EXIT_SUCCESS);
}



int buscarCombinacionesV2(ArbolBinarioBusqueda abb,int numeroSolicitado){
    //Sumar nodos que juntos den el numero solicitado y que tengan de cromosoma al 1
    int combinaciones=0;
    if(!es_arbol_vacio(abb)){
        if(raiz(abb).numeroArr==numeroSolicitado){
            if(raiz(abb).cromo==1){
                combinaciones++;
            }
        }
        combinaciones+=buscarCombinacionesV2(hijo_izq(abb),numeroSolicitado-raiz(abb).numeroArr);
        combinaciones+=buscarCombinacionesV2(hijo_der(abb),numeroSolicitado-raiz(abb).numeroArr);
    }
}
/*void llenarArbolBinarioBusqueda(ArbolBinarioBusqueda *abb,int arreglo[],int cantidad){
    ElementoArbol elementoInicial;
    elementoInicial.cromo=0;
    elementoInicial.numeroArr=0;
    plantar_arbol_binario(abb,NULL,elementoInicial,NULL);
    for(int i=0;i<cantidad;i++){
        ElementoArbol elemento;
        elemento.cromo=0;
        elemento.numeroArr=arreglo[i];
        insertar(abb,elemento);
        elemento.cromo=1;
        insertar(abb,elemento);
    }
}*/

void llenarArbol(ArbolBinarioBusqueda *abb,int arreglo[],int cantidad){
    ElementoArbol element;
    int fin;
    element.cromo=0;
    element.numeroArr=0;
    plantar_arbol_binario(abb,NULL,element,NULL);
    for(int i=0;i<cantidad;i++){
        element.cromo=0;
        element.numeroArr=arreglo[i];
        fin=pow(2,i);
        int j=0;
        while(j<fin){
            insertar(abb,element);
            j++;
        }
        element.cromo=1;
        j=0;
        while(j<fin){
            insertar(abb,element);
            j++;
        }
    }
}