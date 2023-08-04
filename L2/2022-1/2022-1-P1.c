
/* 
 * File:   main.c
 * Autor: Gabriel Omar Durán Ruiz 
 * Código: 20203371
 * Created on 22 de abril de 2022, 03:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
void imprimirLinea(char c,int cantidad);
void imprimirBahias(int M,int N,int A,int crecimiento,int cantidad);
void imprimirLineaBahia(char c,int cantidad);
/*
 * 
 */
int main(int argc, char** argv) {
    int M,N,A;
    printf("Ingrese el largo mínimo, largo máximo y el ancho del terreno:\n");
    scanf("%d %d %d",&N,&M,&A);
    imprimirLinea('=',20);
    imprimirBahias(M,N,A,-1,M);
    imprimirLinea('=',20);
    return (EXIT_SUCCESS);
}

void imprimirLinea(char c,int cantidad){
    for(int i=0;i<cantidad;i++){
        putchar(c);
    }
    putchar('\n');
}

void imprimirBahias(int M,int N,int A,int crecimiento,int cantidad){
    //Llevar contador de ancho y controlar largos
    //Además se analiza cómo se irán imprimiendo las bahías, es decir si su
    //cantidad disminuye o aumenta para poder compararlo con el largo máximo
    if(A==0||(cantidad>M&&A==0))return;
    printf("Entrada\n");
    if(A==1||cantidad>M)return;
    if(A>=2){
        imprimirLineaBahia('*',cantidad);
        if(A>2){
            if(A!=3){
                imprimirLineaBahia('*',cantidad);
                A=A-3;
            }else return;
        }else A=0;
    }
    if(cantidad==N)crecimiento=1;
    if(crecimiento==1)cantidad++;
    else cantidad--;
    imprimirBahias(M,N,A,crecimiento,cantidad);
}

void imprimirLineaBahia(char c,int cantidad){
    for(int i=0;i<cantidad;i++){
        printf("%c ",c);
    }
    putchar('\n');
}

