/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: Christian Carrillo Aburto
 *          20202692
 *
 * Created on 10 de junio de 2022, 15:23
 */

#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "ab.h"
/*
 * 
 */
int main(int argc, char** argv) {
    ABB arbolCampos;
    //Con esto creamos el arbol que sera el que guardemos los campos
    construir_arbol_binario(&arbolCampos);
    //Ingreso de datos
    ElementoArbol nodo1;
    nodo1.campo1=10;
    nodo1.campo2=8;
    nodo1.campo3=5;
    insertar(&arbolCampos, nodo1);

    ElementoArbol nodo2;
    nodo2.campo1=8;
    nodo2.campo2=20;
    nodo2.campo3=6;
    insertar(&arbolCampos, nodo2);

    ElementoArbol nodo3;
    nodo3.campo1=15;
    nodo3.campo2=10;
    nodo3.campo3=3;
    insertar(&arbolCampos, nodo3);

    ElementoArbol nodo4;
    nodo4.campo1=5;
    nodo4.campo2=10;
    nodo4.campo3=3;
    insertar(&arbolCampos, nodo4);

    ElementoArbol nodo5;
    nodo5.campo1=10;
    nodo5.campo2=1;
    nodo5.campo3=7;
    insertar(&arbolCampos, nodo5);

    ElementoArbol nodo6;
    nodo6.campo1=16;
    nodo6.campo2=8;
    nodo6.campo3=7;
    insertar(&arbolCampos, nodo6);

    printf("Recorrido pre-orden:\n");
    pre_orden(arbolCampos);

    //Con este nodo se verificara la funcion de verificar si se puede insertar un elemento en el arbol binario
    ElementoArbol nodoVerificador;
    nodoVerificador.campo1=5;
    nodoVerificador.campo2=10;
    nodoVerificador.campo3=6;
    printf("\n");
    verificar(&arbolCampos, nodoVerificador);

    //Se crea un nodo para verificar la actualizacion del arbol
    ElementoArbol nodoActualizar;
    nodoActualizar.campo1=5;
    nodoActualizar.campo2=10;
    nodoActualizar.campo3=3;
    printf("\n");
    actualizar(&arbolCampos, nodoActualizar);

    //Modificar el arbol en el caso que si se pueda actualizar dicho nodo
    ElementoArbol nodoActualizar2;
    nodoActualizar2.campo1=5;
    nodoActualizar2.campo2=10;
    nodoActualizar2.campo3=100;
    printf("\n");
    modificar(&arbolCampos, nodoActualizar2);

    
    //Inciso d
    ABB arbolCambiante;
    construir_arbol_binario(&arbolCambiante);
    ElementoArbol nodoCambiante;
    nodoCambiante.campo1=10;
    nodoCambiante.campo2=8;
    nodoCambiante.campo3=5;
    insertar(&arbolCambiante, nodoCambiante);

    ElementoArbol nodoCambiante2;
    nodoCambiante2.campo1=8;
    nodoCambiante2.campo2=20;
    nodoCambiante2.campo3=6;
    insertar(&arbolCambiante, nodoCambiante2);

    ElementoArbol nodoCambiante3;
    nodoCambiante3.campo1=5;
    nodoCambiante3.campo2=10;
    nodoCambiante3.campo3=3;
    insertar(&arbolCambiante, nodoCambiante3);

    ElementoArbol nodoCambiante4;
    nodoCambiante4.campo1=10;
    nodoCambiante4.campo2=1;
    nodoCambiante4.campo3=7;
    insertar(&arbolCambiante, nodoCambiante4);

    ElementoArbol nodoCambiante5;
    nodoCambiante5.campo1=15;
    nodoCambiante5.campo2=11;
    nodoCambiante5.campo3=3;
    insertar(&arbolCambiante, nodoCambiante5);

    ElementoArbol nodoCambiante6;
    nodoCambiante6.campo1=16;
    nodoCambiante6.campo2=8;
    nodoCambiante6.campo3=7;
    insertar(&arbolCambiante, nodoCambiante6);

    //Funcion que verifique si es posible cambiar los campos de un nodo, campos 1 y 2 
    //por los campos 3 y 2
    rotarNodos(&arbolCambiante);


    

    return (EXIT_SUCCESS);
}

