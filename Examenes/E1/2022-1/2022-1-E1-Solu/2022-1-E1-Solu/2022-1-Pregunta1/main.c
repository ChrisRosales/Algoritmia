
/*
 * File:   main.c
 * Author: Piero Franchesco Gonzales Fernandez
 * Codigo: 20201706
 * Created on 13 de octubre de 2022, 11:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FuncionesPilas.h"

void leerDatosContenedor(Pila *contenedor){
    FILE *arch = fopen("contenedor.txt","r");
    if(arch == NULL) {
        printf("lacasasd\n");
        exit(1);
    }
    ElementoPila aux;
    int code,fecha;
    while(1){
        fscanf(arch,"%d",&code);
        if(feof(arch)) break;
        fscanf(arch,"%d",&fecha);
        aux.codigo = code;
        aux.fechaVencimiento = fecha;
        apilar(contenedor,aux);
    }
    fclose(arch);
}

void pasarTodoAlContenedor(Pila *contenedor,Pila *cajas,int capacidad,int p,int n){
    int cantElementos=0,cantContenedor=0,i=0;
    ElementoPila elemento;
    while(1){
        elemento = desapilar(&cajas[i]);
        apilar(contenedor,elemento);
        cantElementos++; 
        cantContenedor++;
        if(cantElementos == capacidad){
            i++;
            cantElementos = 0;
        }
        if(cantContenedor == n-1) break;   
    } 
}

void ordenarEnCajas(Pila *contenedor,Pila *cajas,int capacidad,int p,int n){
    ElementoPila mayor,elemento;
    int j=0,cantElementos=0;
    
    if(n==1) return;
    int i;
    for(i=1;i<=n;i++){
        elemento = desapilar(contenedor);
        if(i == 1){
           mayor = elemento; 
        }
        else{
            if(elemento.fechaVencimiento>mayor.fechaVencimiento){
                apilar(&cajas[j],mayor);
                mayor = elemento;
            }
            else{
                apilar(&cajas[j],elemento);
            }
            cantElementos++;
            if(cantElementos == capacidad){
                j++;
                cantElementos = 0;
            }     
        }  
    }
    
    
    pasarTodoAlContenedor(contenedor,cajas,capacidad,p,n);
    ordenarEnCajas(contenedor,cajas,capacidad,p,n-1);
    apilar(contenedor,mayor);
}

void pasarALasCajas(Pila *contenedor,Pila *cajas,int capacidad,int p){
    ElementoPila aux;
    int cantElementos=0,i=0;
    
    while(!esPilaVacia(*contenedor)){
        aux = desapilar(contenedor);
        apilar(&cajas[i],aux);
        cantElementos++;
        if(cantElementos == capacidad){
            cantElementos = 0;
            i++;               
        }     
    }
}

void imprimirResultados(Pila *cajas,int p){
    int i=0;
    Nodo *pAux;
    while(i<p){
        printf("Caja %d: ",i+1);
        pAux = cajas[i].cima;
        while(pAux != NULL){
            printf("%d",pAux->elemento.codigo);
            if(pAux->sig != NULL) printf(", ");
            pAux = pAux->sig;
            
        }
        i++;
        putchar('\n');
    }
    
    
}
int main(int argc, char** argv) {

    Pila contenedor;
    Pila *cajas;
    int n, capacidad; 
    int p;
	int i;
    printf("Ingrese la cantidad de productos(n): ");
    scanf("%d",&n);
    printf("Ingrese la capacidad de la caja: ");
    scanf("%d",&capacidad);
    
    p = ceil((double)n/capacidad);
    construirPila(&contenedor);
    cajas = (Pila *)malloc(sizeof(Pila)*p);
    for(i=0;i<p;i++)
        construirPila(&cajas[i]);
    
    
    leerDatosContenedor(&contenedor);
    ordenarEnCajas(&contenedor,cajas,capacidad,p,n);
    
    pasarALasCajas(&contenedor,cajas,capacidad,p);

    imprimirResultados(cajas,p);
    
    return (EXIT_SUCCESS);
}

