#include <stdio.h>
#include <assert.h>
#include "abb.h"
#include "batch.h"

int main(){
    ArbolBinarioBusqueda arbol;
    construir_arbol_binario(&arbol);
    /*
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
    */
    
    char opt;
    char ini_date[9];
    int count = 0;
    do {
        ElementoArbol stock_purchase;
        printf("Fecha [YYYYMMDDhhmmss]: ");
        scanf("%s", stock_purchase.datetime);
        printf("DNI: ");
        scanf("%s", stock_purchase.doc_number);

        if (count == 0){
            for (int i=0; i<8; i++)
                ini_date[i] = stock_purchase.datetime[i];
        }
        if (is_possible_insert(&arbol, stock_purchase, ini_date)){
            printf("Ingrese el número de acciones: ");
            scanf("%d", &stock_purchase.stock_number);
            printf("Monto de compra: ");
            scanf("%lf", &stock_purchase.amount);
            stock_purchase.status = 'R';
            insertar(&arbol, stock_purchase);
            count++;
        } else {
            printf("No es posible insertar los datos de la compra de acciones.\n");
        }

        printf("¿Desea ingresar más compras de acciones? [S,N]: ");
        scanf(" %c", &opt);
    } while (opt == 'S' || opt =='s');    
    
    //Consolidación de las operaciones
    consolidate(arbol);
    //Reporte de las operaciones de compra de acciones presentadas ordenadas de mayor a menor.
    show_report(arbol);

    destruir_arbol_binario(&arbol);
    
    printf("Todas las pruebas se han ejecutado con éxito\n");
    return 0;
}