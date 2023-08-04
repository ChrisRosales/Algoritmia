/* 
 * File:   main.c
 * Author: cueva
 *
 * Created on 9 de mayo de 2022, 09:28 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "lse.h"
#include "funcion.h"
#include "pilas.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    int n=7;
    
    int arr1[]={1,1,1,0,0,0,0};
    int prod1[]={2,1,3,2,3,1,1};
    
    int arr2[]={1,1,1,1,1,1,0};
    int prod2[]={1,2,3,3,3,2,1};
            
    int arr3[]={1,1,1,1,1,0,0};
    int prod3[]={1,2,1,1,3,1,2};
           
    int arr4[]={0,0,1,1,1,1,1};
    int prod4[]={3,1,3,2,3,3,1};
    
    Lista list1,list2,list3,list4;
    
    cargalista(arr1,prod1,n,&list1);
    cargalista(arr2,prod2,n,&list2);
    cargalista(arr3,prod3,n,&list3);
    cargalista(arr4,prod4,n,&list4);
    
    imprime(list1);imprime(list2);
    imprime(list3);imprime(list4);
    
    unifica(&list1,&list2);
    unifica(&list1,&list3);
    unifica(&list1,&list4);
    
    imprime(list1);

    Pila pil1,pil2,pil3;
    construir_pila(&pil1);
    construir_pila(&pil2);        
    construir_pila(&pil3);
    
    clasifica(&list1,&pil1,&pil2,&pil3);
    imprime(pil1.contenido);
    imprime(pil2.contenido);
    imprime(pil3.contenido);
    
    return (EXIT_SUCCESS);
}

