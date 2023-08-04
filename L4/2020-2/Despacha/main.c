/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: cueva.r
 *
 * Created on 28 de septiembre de 2022, 09:27 AM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Abb.h"

void despacha(ArbolBB* ptrarbol,int cant){
    ArbolBB aux;
    int falta;
    if(es_arbol_vacio(*ptrarbol) ||cant==0)
        return;
    aux = minimoarbol(*ptrarbol);
    if(aux->elemento.cantidad<=cant){
        falta = cant- aux->elemento.cantidad;
        *ptrarbol=borranodo(*ptrarbol,aux->elemento);
        despacha(ptrarbol,falta);
    }
    else
        aux->elemento.cantidad=aux->elemento.cantidad-cant;
    
}


int main(int argc, char** argv) {
    ArbolBB arboldespacha;
    ElementoArbol temp;
    
    construir_ab(&arboldespacha);
    temp.cantidad=20;
    temp.lote= 20170620;
    insertar_abb(&arboldespacha,temp);
    temp.cantidad=20;
    temp.lote= 20170810;
    insertar_abb(&arboldespacha,temp);    
    temp.cantidad=20;
    temp.lote= 20180211;
    insertar_abb(&arboldespacha,temp);
    temp.cantidad=10;
    temp.lote= 20180409;
    insertar_abb(&arboldespacha,temp);
    
    en_orden(arboldespacha);
    despacha(&arboldespacha,35);
    printf("\n");
    en_orden(arboldespacha);   

    return 0;
}


