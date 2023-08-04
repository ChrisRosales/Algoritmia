/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Colas.c
 * Author: cueva.r
 * 
 * Created on 7 de septiembre de 2022, 08:51 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include "Colas.h"

void construir_cola(Cola *tad){
    construir(&tad->contenido);    
}

int es_cola_vacia(Cola tad){
    return es_lista_vacia(tad.contenido);    
}

void encola(Cola *tad,ElementoCola dato){
    insertar_prioridad(&(tad->contenido),dato);
}

ElementoCola desencola(Cola *tad){
    ElementoCola aux;
    if(es_cola_vacia(*tad)){
        printf("La cola esta vacia\n");
        exit(2);    
    }    
    else{
        aux=retorna_cabeza(tad->contenido); 
        elimina_cabeza(&tad->contenido);
        return aux;
    }
}

void imprime_elecola(ElementoCola dato){
    imprime_elemento(dato);
    
}

//Recorre la cola solo para imprimir
void imprimecola(Cola tad){
   imprimir(tad.contenido);
    
}

void destruir_cola(Cola *tad){
    ElementoCola aux;
    while(!es_cola_vacia(*tad)){
        aux = desencola(tad);
    }
    
}
