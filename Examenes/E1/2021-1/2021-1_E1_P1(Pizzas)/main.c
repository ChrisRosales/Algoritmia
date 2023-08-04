
/* 
 * File:   main.c
 * Autor: Gabriel Omar Durán Ruiz 
 * Código: 20203371
 * Created on 20 de mayo de 2022, 12:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "colas.h"
#include "pilas.h"

void imprime_pilas_colas(Cola cola,Pila pila1,Pila pila2);
void reordenamiento(Cola *cola,Pila *pila1,Pila *pila2);
void procesa_Pizzas(FILE *arch,Cola *cola);
void ordenacola(Cola *ptrcola);
/*
 * 
 */
int main(int argc, char** argv) {
    FILE *arch;
    Cola cola;
    ElementoCola elemento;
    int numero;
    char tipo;
    construir_cola(&cola);
    arch=fopen("datos.txt","r");
    if(arch==NULL){
        printf("Error, no se pudo abrir el archivo .txt");
        exit(1);
    }
    while(1){
        fscanf(arch," %c%d",&tipo,&numero);
        elemento.numero=numero;
        elemento.tipo=tipo;
        pide_vez(&cola,elemento);
        if(fgetc(arch)=='\n')break;
    }
    procesa_Pizzas(arch,&cola);
    return (EXIT_SUCCESS);
}

void procesa_Pizzas(FILE *arch,Cola *cola){
    ElementoCola elemento,aux;
    Pila pila1,pila2;
    construir_pila(&pila1);
    construir_pila(&pila2);
    int numero;
    char tipo;
    while(1){
        fscanf(arch," %c%d",&tipo,&numero);
        if(feof(arch))break;
        elemento.numero=numero;
        elemento.tipo=tipo;
        aux=avanzar(cola);
        if(aux.tipo=='A'){
            apilar(&pila1,aux);
        }else apilar(&pila2,aux);
        pide_vez(cola,elemento);
    }
    imprime_pilas_colas(*cola,pila1,pila2);
    reordenamiento(cola,&pila1,&pila2);
    imprime_pilas_colas(*cola,pila1,pila2);
}

void imprime_pilas_colas(Cola cola,Pila pila1,Pila pila2){
    printf("Cola: ");
    imprime(cola.contenido);
    printf("Pila1: ");
    imprime(pila1.contenido);
    printf("Pila2: ");
    imprime(pila2.contenido);
}

void reordenamiento(Cola *cola,Pila *pila1,Pila *pila2){
    int n=pila1->contenido.longitud+pila2->contenido.longitud;
    Pila aux;
    ElementoCola elemento1;
    ElementoPila elemento2,elemento;
    construir_pila(&aux);
    while(!es_cola_vacia(*cola)){
        elemento1=avanzar(cola);
        apilar(&aux,elemento1);
    }
    while(!es_pila_vacia(*pila1)){
        elemento2=desapilar(pila1);
        pide_vez(cola,elemento2);
    }
    
    while(!es_pila_vacia(*pila2)){
        elemento2=desapilar(pila2);
        pide_vez(cola,elemento2);
    }
    for(int i=0;i<n;i++){
        elemento=desapilar(&aux);
        if(elemento.tipo=='A'){
            apilar(pila1,elemento);
        }else apilar(pila2,elemento);
    }
    while(!es_pila_vacia(aux)){
        elemento=desapilar(&aux);
        pide_vez(cola,elemento);
    }
    ordenacola(cola);
}

void ordenacola(Cola *ptrcola){
    int i,j,n;
    ElementoCola menor,valor;
    n=ptrcola->contenido.longitud;
    j=n;
    while(j>0){
        menor = avanzar(ptrcola);
        i=1;
        while(i<j){
            valor = avanzar(ptrcola);
            if(valor.numero>menor.numero){
                pide_vez(ptrcola,menor);
                menor=valor;
            }
            else
                pide_vez(ptrcola,valor);
            i++;
        }
        /*Para posicionar los ordenados*/
        for(i=j;i<n;i++){
            valor = avanzar(ptrcola);
            pide_vez(ptrcola,valor);
        }
        pide_vez(ptrcola,menor);
        j--;
    }
}




