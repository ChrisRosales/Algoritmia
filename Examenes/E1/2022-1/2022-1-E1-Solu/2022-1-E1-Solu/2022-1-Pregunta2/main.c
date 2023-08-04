/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: cueva.r
 *
 * Created on 3 de octubre de 2022, 11:50 AM
 */
#include "Colas.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    Cola banco;
    ElementoCola dato;
    
    construir_cola(&banco);
    
    dato.codigo = 1;
    dato.prioridad = 'N';
    encola(&banco,dato);

    dato.codigo = 1;
    dato.prioridad = 'V';
    encola(&banco,dato);

    
    dato.codigo = 2;
    dato.prioridad = 'N';
    encola(&banco,dato);
    
    dato.codigo = 2;
    dato.prioridad = 'V';
    encola(&banco,dato);    

    dato.codigo = 1;
    dato.prioridad = 'C';
    encola(&banco,dato);

    dato.codigo = 2;
    dato.prioridad = 'C';
    encola(&banco,dato);

    dato.codigo = 3;
    dato.prioridad = 'C';
    encola(&banco,dato);   

    dato.codigo = 3;
    dato.prioridad = 'N';
    encola(&banco,dato);

    dato.codigo = 3;
    dato.prioridad = 'V';
    encola(&banco,dato);    
    
    imprimecola(banco);
    
    
    
    return 0;
}

