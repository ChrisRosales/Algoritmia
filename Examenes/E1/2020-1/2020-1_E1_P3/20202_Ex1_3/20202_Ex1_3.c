#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lse.h"

void mergeLists(Lista* target,Lista* source);
void readData(Lista* lista,int day,char dayName);

int main() {
    Lista lunes;
    construir_lista(&lunes);
    readData(&lunes,1,'L');

    Lista martes;
    construir_lista(&martes);
    readData(&martes,2,'M');

    Lista miercoles;
    construir_lista(&miercoles);
    readData(&miercoles,3,'I');

    Lista jueves;
    construir_lista(&jueves);
    readData(&jueves,4,'J');

    Lista viernes;
    construir_lista(&viernes);
    readData(&viernes,5,'V');

    printf("Al incio del dia sabado, los pedidos son:\n");
    printf("Lunes: ");
    imprime(lunes);
    printf("Martes: ");
    imprime(martes);
    printf("Miercoles: ");
    imprime(miercoles);
    printf("Jueves: ");
    imprime(jueves);
    printf("Viernes: ");
    imprime(viernes);

    mergeLists(&lunes,&martes);
    mergeLists(&lunes,&miercoles);
    mergeLists(&lunes,&jueves);
    mergeLists(&lunes,&viernes);
    printf("Los pedidos en orden para el dia sabado son:\n");
    imprime(lunes);

    return 0;
}

void mergeLists(Lista* target,Lista* source) {
    if (source->cabeza==NULL) {
        return;
    }

    Nodo* lastNodeT = obtener_ultimo_nodo(*target);
    if (lastNodeT==NULL) {
        target->cabeza = source->cabeza;
        target->longitud = source->longitud;
        source->cabeza = NULL;
        source->longitud = 0;
    } else if (lastNodeT->elemento<source->cabeza->elemento) {
        lastNodeT->sig = source->cabeza;
        target->longitud += source->longitud;
        source->cabeza = NULL;
        source->longitud = 0;
    } else {
        Nodo* currentNode = target->cabeza;
        while (source->longitud!=0) {
            if (currentNode->sig!=NULL) {
                if (currentNode->sig->elemento>source->cabeza->elemento) {
                    Nodo* tempNode = currentNode->sig;
                    currentNode->sig = source->cabeza;
                    source->cabeza = source->cabeza->sig;
                    currentNode->sig->sig = tempNode;
                    source->longitud--;
                    target->longitud++;
                }
                currentNode = currentNode->sig;
            } else {
                currentNode->sig = source->cabeza;
                target->longitud += source->longitud;
                source->cabeza = NULL;
                source->longitud = 0;
            }
        }
    }
    assert(es_lista_vacia(*source));
}

void readData(Lista* lista,int day,char dayName) {
    printf("Ingresar datos del dia %d: ",day);
    int tempData = 0;
    while (1) {
        scanf("%d",&tempData);
        if (tempData==-1) {
            return;
        } else {
            insertar_en_orden(lista,tempData,dayName);
        }
    }
}