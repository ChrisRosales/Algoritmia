#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "abb.h"

void customInsert(ArbolBinarioBusqueda *tree,NodoArbol *node);
void mergeTrees(ArbolBinarioBusqueda *sourceTree, ArbolBinarioBusqueda *destinationTree);
void readData(int treeNumber,ArbolBinarioBusqueda* tree);

int main() {
    ArbolBinarioBusqueda tree1, tree2;
    construir_arbol_binario(&tree1);
    readData(1,&tree1);
    construir_arbol_binario(&tree2);
    readData(2,&tree2);

    printf("Los elementos del arbol 1 en orden:\n");
    en_orden(tree1);
    printf("\nLos elementos del arbol 2 en orden:\n");
    en_orden(tree2);

    if(numero_nodos(tree1)>numero_nodos(tree2)) {
        printf("\nEl arbol 1 sera el destino\n");
        mergeTrees(&tree2,&tree1);
        printf("El arbol final en orden:\n");
        en_orden(tree1);
    } else {
        printf("\nEl arbol 2 sera el destino\n");
        mergeTrees(&tree1,&tree2);
        printf("El arbol final en orden:\n");
        en_orden(tree2);
    }

    return 0;
}

void customInsert(ArbolBinarioBusqueda *tree,NodoArbol *node) {
    if (es_arbol_vacio(*tree)) {
		*tree = node;
        return;
    }

    if ((*tree)->elemento==node->elemento) {
        (*tree)->stock += node->stock;
    } else if ((*tree)->elemento>node->elemento) {
        customInsert(&(*tree)->hijo_izq,node);
    } else {
        customInsert(&(*tree)->hijo_der,node);
    }        
}

void mergeTrees(ArbolBinarioBusqueda *sourceTree, ArbolBinarioBusqueda *destinationTree) {
    if (es_arbol_vacio(*sourceTree)) {
        return;
    }

    if(!es_arbol_vacio((*sourceTree)->hijo_izq)) {
        mergeTrees(&(*sourceTree)->hijo_izq,destinationTree);
    }

    if(!es_arbol_vacio((*sourceTree)->hijo_der)) {
        mergeTrees(&(*sourceTree)->hijo_der,destinationTree);
    }

    customInsert(destinationTree,*sourceTree);
    *sourceTree = NULL;
}

void readData(int treeNumber,ArbolBinarioBusqueda* tree) {
    int lote;
    int stock;
    int i = 0;
    while(1) {
        i++;
        printf("Insertar lote y stock del producto %d para el arbol %d. Ingresar -1 para terminar.",i,treeNumber);
        scanf("%d %d",&lote,&stock);
        if ((lote==-1)||(stock==-1)) {
            break;
        }
        insertar(tree,lote,stock);
    }
}