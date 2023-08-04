/* 
 * Archivo:   funciones.c
 * Autor: Joham Manuel Elias Ruiz
 * Código: 20191626
 *
 * Created on 21 de mayo de 2022, 12:00 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "lse.h"


ElementoLista crearProceso(int tiempo,int numero){
    ElementoLista retornar;
    retornar.tiempo=tiempo;
    retornar.num=numero;
    return retornar;
}

void volverEnlistar(ElementoLista *procesoActual,Lista *procesos,int T){
    int estado=procesoActual->tiempo-T;
    if(estado>0){
       procesoActual->tiempo=estado;
       insertar_al_final(procesos,*procesoActual);
    }else{
        printf("Se completo proceso #%d\n",procesoActual->num);
    }
}



