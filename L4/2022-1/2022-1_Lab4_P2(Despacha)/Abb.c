/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Abb.c
 * Author: cueva.r
 * 
 * Created on 14 de septiembre de 2022, 09:29 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ab.h"
#include "Abb.h"
#include "Colas.h"

//se especifica segun su problema
int comparaabb(ElementoArbol a, ElementoArbol b){
    return (a.lote-b.lote);
}

void asigna(ElementoArbol *a, ElementoArbol b){
    a->lote = b.lote;
    a->cantidad = b.cantidad;
    
}

void insertar_abb(ArbolBB *tad,ElementoArbol dato){
    if(es_arbol_vacio(*tad))    
        insertar_ab(tad,dato,NULL,NULL);
    else{
        if(!comparaabb((*tad)->elemento,dato)){
            printf("No se puede insertar repetido");
            return;
        }
        if(comparaabb((*tad)->elemento, dato)>0)
            insertar_abb(&(*tad)->hijo_izq,dato);
        else
            insertar_abb(&(*tad)->hijo_der,dato);     
    }
}

ElementoArbol minimoabb(ArbolBB tad){
    if(es_arbol_vacio(tad)){
        printf("El arbol esta vacio");
        exit(2);
    } 
    if(es_arbol_vacio(tad->hijo_izq))
        return tad->elemento;
    minimoabb(tad->hijo_izq);
}

ArbolBB minimoarbol(ArbolBB tad){
    if(es_arbol_vacio(tad)){
        return tad;
    } 
    if(es_arbol_vacio(tad->hijo_izq))
        return tad;
    minimoarbol(tad->hijo_izq);
}

ArbolBB buscaarbol(ArbolBB tad,ElementoArbol dato){
    if(es_arbol_vacio(tad)){
        return tad;
    } 
    if(comparaabb(tad->elemento,dato)==0)
        return tad;
    if(comparaabb(tad->elemento,dato)>0)
        return buscaarbol(tad->hijo_izq,dato);
    else
        if(comparaabb(tad->elemento,dato)<0) 
            return buscaarbol(tad->hijo_der,dato);
}

ElementoArbol maximoabb(ArbolBB tad){
    if(es_arbol_vacio(tad)){
        printf("El arbol esta vacio");
        exit(2);
    } 
    if(es_arbol_vacio(tad->hijo_der))
        return tad->elemento;
    maximoabb(tad->hijo_der);
}

ArbolBB  borranodo(ArbolBB tad,ElementoArbol dato){
    if(es_arbol_vacio(tad))
        return tad;
    if(comparaabb(tad->elemento,dato)>0)
        tad->hijo_izq=borranodo(tad->hijo_izq,dato);
    else
        if(comparaabb(tad->elemento,dato)<0)
            tad->hijo_der=borranodo(tad->hijo_der,dato);
        else{
            if(es_arbol_vacio(tad->hijo_izq)){
                ArbolBB temp = tad->hijo_der;
                free(tad);
                return temp;  
            }
            else
                if(es_arbol_vacio(tad->hijo_der)){
                    ArbolBB temp = tad->hijo_izq;
                    free(tad);
                    return temp;  
                }
                else{
                    ArbolBB temp = minimoarbol(tad->hijo_der);
                    //Debemos armar una funcion de asignacion
                    //tad->elemento = temp->elemento;
                    asigna(&(tad->elemento),temp->elemento);
                    tad->hijo_der=borranodo(tad->hijo_der,temp->elemento);
                }
            //Tenia razon funciona igual
            return tad;
        }    
    
}


