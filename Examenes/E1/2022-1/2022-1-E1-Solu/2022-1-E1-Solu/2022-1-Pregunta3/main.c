/* 
 * File:   main.c
 * Autor:  Joham Manuel Elias Ruiz
 * Codigo: 20191626
 *
 * Created on 21 de mayo de 2022, 11:40 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "lse.h"
#include "lse.c"
#include "funciones.h"

/*
 * 
 */
int main(int argc, char** argv) {
    Lista procesos;
    construir_lista(&procesos);
    
    int numProcesos,T,tiempo;
    
    printf("# procesos iniciales = ");
    scanf("%d",&numProcesos);
    printf("T= ");
    scanf("%d",&T);
    
    printf("Duraciones iniciales de procesos(en minutos, respectivamente) = ");
    int i;
    for(i=0;i<numProcesos;i++){
        scanf("%d",&tiempo);
        ElementoLista proc=crearProceso(tiempo,i+1);
        insertar_al_final(&procesos,proc);
    }
    int confirmacion;
    NodoLista *procesoActual=procesos.cabeza;
    while(!es_lista_vacia(procesos) && procesoActual!=NULL){
        printf("Se ejecuto proceso #%d\n",procesoActual->elemento.num);
        volverEnlistar(&(procesoActual)->elemento,&procesos,T);
        procesoActual=procesoActual->sig;
        elimina_cabeza(&procesos);
        printf("Desea insertar un nuevo proceso? ");
        scanf("%d",&confirmacion);
        if(confirmacion){
            printf("Indicar duracion de proceso #%d: ",i+1);
            scanf("%d",&tiempo);
            ElementoLista proc=crearProceso(tiempo,i+1);
            insertar_al_inicio(&procesos,proc);
            procesoActual=procesos.cabeza;
            i++;
        }
        
        
    }
    
    destruir_lista(&procesos);
    
    
    printf("\nSe termino el programa satisfactoriamente.\n");
    
    
    return (EXIT_SUCCESS);
}

