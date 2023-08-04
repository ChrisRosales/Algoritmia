/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tabla.c
 * Author: cueva.r
 * 
 * Created on 27 de septiembre de 2022, 08:24 AM
 */

#include "Ab.h"
#include "Abb.h"
#include "Tabla.h"
#include "lse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void construir_tabla(Tabla *tad){
    construir_ab(tad);
}
void destruir_tabla(Tabla *tad){
    destruir_ab(tad);
}

void registrar_entrada(Tabla *tad,ElementoArbol dato){
    ArbolBB aux;
    
    aux = buscaarbol(*tad,dato);
    if(es_arbol_vacio(aux))
        insertar_abb(tad,dato);
    else
        printf("Llave ya existe no se puede registrar\n");
}

void elimina_entrada(Tabla *tad,int llave){
    ElementoTabla temp;
    temp.codigo = llave;
    temp.peso = 0;
    *tad=borranodo(*tad,temp);
}

void actualiza_entrada(Tabla *tad,int llave,double nvalor){
    ElementoTabla temp;
    ArbolBB aux;
    
    temp.codigo = llave;
    temp.peso = nvalor;
    
    aux=buscaarbol(*tad,temp);
    
    if(es_arbol_vacio(aux))
        printf("No se puede actualizar\n");
    else
        asigna(&(aux->elemento),temp);
    
}
