#include <stdio.h>
#include <stdlib.h>
#include "ab.h"
#include "pilas.h"
#include "colas.h"

void construir_arbol_binario(ArbolBinario *tad){
    *tad=NULL;
}

NodoArbol *crear_nuevo_nodo_arbol(ArbolBinario arbol_izq, ElementoArbol elemento, ArbolBinario arbol_der){
    NodoArbol* nuevo_nodo = (NodoArbol*)malloc(sizeof(NodoArbol));
    nuevo_nodo->elemento=elemento;
    nuevo_nodo->hijo_izq=arbol_izq;
    nuevo_nodo->hijo_der=arbol_der;
    return nuevo_nodo;
}

void plantar_arbol_binario(ArbolBinario *tad, ArbolBinario arbol_izq, ElementoArbol elemento, ArbolBinario arbol_der){
    NodoArbol *nuevo_nodo=crear_nuevo_nodo_arbol(arbol_izq, elemento, arbol_der);
    *tad=nuevo_nodo;
}

int es_arbol_vacio(ArbolBinario tad){
    return tad==NULL;
}

ElementoArbol raiz(ArbolBinario tad){
    if (es_arbol_vacio(tad)){
        printf("No se puede obtener la raíz de un árbol vacío.\n");
        exit(41);
    }
    return tad->elemento;
}

ArbolBinario hijo_der(ArbolBinario tad){
    if (es_arbol_vacio(tad)){
        printf("No se puede obtener el hijo derecho de un árbol vacío.\n");
        exit(42);
    }
    return tad->hijo_der;
}

ArbolBinario hijo_izq(ArbolBinario tad){
    if (es_arbol_vacio(tad)){
        printf("No se puede obtener el hijo izquierdo de un árbol vacío.\n");
        exit(43);
    }
    return tad->hijo_izq;
}

void imprime_raiz(ArbolBinario tad){
    printf(" %d-%d ", tad->elemento.stock_number, tad->elemento.status );
}

int maximo(int a, int b){
    return a>=b?a:b;
}

int altura(ArbolBinario tad){
    if (es_arbol_vacio(tad))
        return 0;
    else
        return 1+maximo(altura(tad->hijo_izq), altura(tad->hijo_der));
}

int numero_nodos(ArbolBinario tad){
    if (es_arbol_vacio(tad))
        return 0;
    else
        return 1+numero_nodos(tad->hijo_izq)+numero_nodos(tad->hijo_der);    
}

int numero_hojas(ArbolBinario tad){
    if (es_arbol_vacio(tad))
        return 0;
    else if (es_arbol_vacio(tad->hijo_izq) && es_arbol_vacio(tad->hijo_der))
        return 1;
    else
        return numero_hojas(tad->hijo_izq)+numero_hojas(tad->hijo_der);
}

ArbolBinario especular(ArbolBinario tad){
    ArbolBinario arbol_retorno;
    if (es_arbol_vacio(tad)){
        construir_arbol_binario(&arbol_retorno);       
    }
    else{
        ArbolBinario hijo_izq=especular(tad->hijo_der);
        ArbolBinario hijo_der=especular(tad->hijo_izq);
        plantar_arbol_binario(&arbol_retorno, hijo_izq, tad->elemento, hijo_der);
    }
    return arbol_retorno;
}

ArbolBinario copia_arbol_binario(ArbolBinario tad){
    ArbolBinario arbol_retorno;
    if (es_arbol_vacio(tad)){
        construir_arbol_binario(&arbol_retorno);       
    }
    else{
        ArbolBinario hijo_izq=copia_arbol_binario(tad->hijo_izq);
        ArbolBinario hijo_der=copia_arbol_binario(tad->hijo_der);
        plantar_arbol_binario(&arbol_retorno, hijo_izq, tad->elemento, hijo_der);       
    }
    return arbol_retorno;
}

void destruir_arbol_binario(ArbolBinario *tad){
    if (!es_arbol_vacio(*tad)){
        destruir_arbol_binario(&(*tad)->hijo_izq);
        destruir_arbol_binario(&(*tad)->hijo_der);
        free(*tad);
        *tad=NULL;
    }
}

int es_equilibrado(ArbolBinario tad){
    if (es_arbol_vacio(tad))
        return 1;
    else{
        int altura_hijo_izq=altura(tad->hijo_izq);
        int altura_hijo_der=altura(tad->hijo_der);
        int diferencia=abs(altura_hijo_izq-altura_hijo_der);
        return diferencia<=1 && es_equilibrado(tad->hijo_izq) && es_equilibrado(tad->hijo_der);
    }        
}


int es_hoja(ArbolBinario tad){
    if (es_arbol_vacio(tad))
        return 0;
    else
        return es_arbol_vacio(tad->hijo_izq) && es_arbol_vacio(tad->hijo_der);
}

void es_zurdo(ArbolBinario tad, int *es_zurdo_arbol, int *numero_descendientes){
    if (es_arbol_vacio(tad)){
        *es_zurdo_arbol=1;
        *numero_descendientes=0;
    }   
    else if (es_hoja(tad)){
        *es_zurdo_arbol=1;
        *numero_descendientes=1;
    }     
    else{
        int es_zurdo_hijo_izq, numero_descendientes_izq;
        int es_zurdo_hijo_der, numero_descendientes_der;
        es_zurdo(tad->hijo_izq, &es_zurdo_hijo_izq, &numero_descendientes_izq);
        es_zurdo(tad->hijo_der, &es_zurdo_hijo_der, &numero_descendientes_der);
        *es_zurdo_arbol=es_zurdo_hijo_izq && es_zurdo_hijo_der && numero_descendientes_izq>numero_descendientes_der;
        *numero_descendientes=1+numero_descendientes_izq+numero_descendientes_der;
    }        
}

void pre_orden(ArbolBinario tad){
    if (!es_arbol_vacio(tad)){
        printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
        pre_orden(tad->hijo_izq);
        pre_orden(tad->hijo_der);
    }
}

void en_orden(ArbolBinario tad){
    if (!es_arbol_vacio(tad)){
        en_orden(tad->hijo_izq);
        printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
        en_orden(tad->hijo_der);
    }
}

void post_orden(ArbolBinario tad){
    if (!es_arbol_vacio(tad)){        
        post_orden(tad->hijo_izq);
        post_orden(tad->hijo_der);
        printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
    }
}

void pre_orden_iterativo(ArbolBinario tad){
    Pila pila;
    construir_pila(&pila);
    if (!es_arbol_vacio(tad)){        
        apilar(&pila, tad);
        while(!es_pila_vacia(pila)){
            ArbolBinario arbol = desapilar(&pila);
            printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
            if (!es_arbol_vacio(arbol->hijo_der))
                apilar(&pila, arbol->hijo_der);           
            if (!es_arbol_vacio(arbol->hijo_izq))
                apilar(&pila, arbol->hijo_izq);           
        }
    }
    destruir_pila(&pila);    
}

void en_orden_iterativo(ArbolBinario tad){
    Pila pila;
    construir_pila(&pila);
    int fin=0;
    do{
        while (!es_arbol_vacio(tad)){
            apilar(&pila, tad);
            tad=tad->hijo_izq;
        }
        if (es_pila_vacia(pila))
            fin=1;
        else{
            tad = desapilar(&pila);
            printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
            tad=tad->hijo_der;
        }
    } while(fin==0);
    destruir_pila(&pila);
}

void recorrido_por_nivel(ArbolBinario tad){
    Cola cola;
    construir_cola(&cola);
    if (!es_arbol_vacio(tad)){
        pide_vez(&cola, tad);
        while(!es_cola_vacia(cola)){
            ArbolBinario tad=avanzar(&cola);
            printf(" %s-%d ", tad->elemento.doc_number, tad->elemento.stock_number );
            if (!es_arbol_vacio(tad->hijo_izq))
                pide_vez(&cola, tad->hijo_izq);
            if (!es_arbol_vacio(tad->hijo_der))
                pide_vez(&cola, tad->hijo_der);
        }
    }
    destruir_cola(&cola);   
}