/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 5 de noviembre de 2022, 16:54
 */

#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"
/*
 * 
 */
int main(int argc, char** argv) {
    //OBS: EN MIS PRUEBAS, ALGUNAS VECES NO ME LEÍA EL ARCHIVO
    //PERO EN LAS ULTIMAS COMPILADAS SI MOSTRO RESULTADOS 
    //POR FAVOR INSISTA CON EL ARCHIVO :((((((((((
    FILE *arch;
    arch=fopen("Datos.txt","r");
    ArbolBinarioBusqueda abb1,abb2;
    construir_arbol_binario(&abb1);
    leerArbol(&abb1,arch);
    construir_arbol_binario(&abb2);
    leerArbol(&abb2,arch);

    printf("Por ejemplo, si el arbol destino cuenta con los siguientes nodos (inorden):\n");
    en_orden(abb1);
    printf("\n\n");
    printf("\nY el arbol emisor tiene los siguientes nodos:\n");
    en_orden(abb2);
    printf("\n\n");
    if(numero_nodos(abb1)>numero_nodos(abb2)){
        printf("\n\nSOLUCION:\n\nEl arbol 1 sera el destino:\n\n");
        fusionarArboles(&abb2,&abb1);
        en_orden(abb1);
        printf("\n\n");
    }else{
        printf("\n\nSOLUCION:\n\nEl arbol 2 sera el destino:\n\n");
        fusionarArboles(&abb1,&abb2);
        en_orden(abb2);
        printf("\n\n");
    }
    fclose(arch);
    return (EXIT_SUCCESS);
}

void fusionarArboles(ArbolBinarioBusqueda *arbolInicio,ArbolBinarioBusqueda *arbolDestino){
    if(es_arbol_vacio(*arbolInicio)){
        return;
    }
    if(!es_arbol_vacio((*arbolInicio)->hijo_izq)){
        fusionarArboles(&(*arbolInicio)->hijo_izq,arbolDestino);
    }
    if(!es_arbol_vacio((*arbolInicio)->hijo_der)){
        fusionarArboles(&(*arbolInicio)->hijo_der,arbolDestino);
    }
    
    ingreso(arbolDestino,*arbolInicio);
    *arbolInicio=NULL;
}

void ingreso(ArbolBinarioBusqueda *arbol,NodoArbol *nodo){
    if(es_arbol_vacio(*arbol)){
        *arbol=nodo;
        return;
    }
    if((*arbol)->elemento==nodo->elemento){
        (*arbol)->stock+=nodo->stock;
    }else if((*arbol)->elemento>nodo->elemento){
        ingreso(&(*arbol)->hijo_izq,nodo);
    }else{
        ingreso(&(*arbol)->hijo_der,nodo);
    }
}

void leerArbol(ArbolBinarioBusqueda *abb,FILE *arch){
    int codigo,stock;
    int i=0;
    while(1){
        i++;
        fscanf(arch,"%d %d",&codigo,&stock);
        if(codigo==0 && stock==0){
            break;
        }
        insertar(abb,codigo,stock);
    }
}


