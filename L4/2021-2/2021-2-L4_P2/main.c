#include <stdio.h>
#include <assert.h>
#include "abb.h"

int main(){
    ArbolBinarioBusqueda arbol, origin_arbol, parent_arbol;
    construir_arbol_binario(&arbol);
    
    ElementoArbol product1;
    product1.name = 'A';
    product1.price = 190;
    insertar(&arbol, product1);

    ElementoArbol product2;
    product2.name = 'C';
    product2.price = 180;
    insertar(&arbol, product2);

    ElementoArbol product3;
    product3.name = 'G';
    product3.price = 150;
    insertar(&arbol, product3);

    ElementoArbol product4;
    product4.name = 'B';
    product4.price = 210;
    insertar(&arbol, product4);

    ElementoArbol product5;
    product5.name = 'M';
    product5.price = 100;
    insertar(&arbol, product5);

    ElementoArbol product6;
    product6.name = 'P';
    product6.price = 140;
    insertar(&arbol, product6);

    ElementoArbol product7;
    product7.name = 'Q';
    product7.price = 20;
    insertar(&arbol, product7);

    pre_orden(arbol);
    printf("\n");
    
    arbol = balance(arbol);
    pre_orden(arbol);
    printf("\nLos productos filtrados son:\n");
    show_products(arbol, 160);
    destruir_arbol_binario(&arbol);
    
    printf("Todas las pruebas se han ejecutado con éxito\n");
    return 0;
}