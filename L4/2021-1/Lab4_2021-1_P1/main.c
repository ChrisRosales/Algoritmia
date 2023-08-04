#include <stdio.h>
#include <assert.h>
#include "abb.h"
#include "batch.h"

int main(){
    ArbolBinarioBusqueda arbol;
    construir_arbol_binario(&arbol);
    
    ElementoArbol batch;
    batch.id = 10;
    batch.quantity = 8;
    insertar(&arbol, batch);

    ElementoArbol batch2;
    batch2.id = 9;
    batch2.quantity = 10;
    insertar(&arbol, batch2);

    ElementoArbol batch3;
    batch3.id = 6;
    batch3.quantity = 20;
    insertar(&arbol, batch3);

    ElementoArbol batch4;
    batch4.id = 5;
    batch4.quantity = 20;
    insertar(&arbol, batch4);

    ElementoArbol batch5;
    batch5.id = 8;
    batch5.quantity = 20;
    insertar(&arbol, batch5);

    ElementoArbol batch6;
    batch6.id = 15;
    batch6.quantity = 20;
    insertar(&arbol, batch6);    

    ElementoArbol batch7;
    batch7.id = 12;
    batch7.quantity = 10;
    insertar(&arbol, batch7);
    
    ElementoArbol batch8;
    batch8.id = 18;
    batch8.quantity = 10;
    insertar(&arbol, batch8);
    /*
    char opt;
    do {
        ElementoArbol batch;
        printf("Ingrese el número de lote y la cantidad: ");
        scanf("%d %d", &batch.id, &batch.quantity);

        if (batch.quantity >= 5 && batch.quantity <=20){
            insertar(&arbol, batch);
        } else{
            printf("La cantidad de productos ingresada para el lote no está en el rango.\n");
        }
        printf("¿Desea ingresar más lotes? [S,N]: ");
        scanf(" %c", &opt);
    } while (opt == 'S' || opt =='s');    
    */
    printf("Los datos del árbol en preorden:\n");
    pre_orden(arbol); putchar('\n');

    int num_to_dispatch;
    Pila stack;
    construir_pila(&stack);
    printf("Cuántos lotes desea despachar? ");
    scanf("%d", &num_to_dispatch);

    dispatch(&arbol, num_to_dispatch, &stack);

    printf("\nLos datos del árbol en preorden luego de despachar %d lotes:\n", num_to_dispatch);
    pre_orden(arbol); putchar('\n');

    printf("\nLos datos de la pila de lotes:\n");
    imprime(stack.contenido);

    return_batches(&stack, &arbol);
    printf("\nLos datos del árbol en preorden luego de regresar los lotes de la pila:\n");
    pre_orden(arbol); putchar('\n');

    destruir_arbol_binario(&arbol);
    
    printf("Todas las pruebas se han ejecutado con éxito\n");
    return 0;
}