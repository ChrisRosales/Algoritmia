/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ALEJANDRO
 *
 * Created on 8 de julio de 2022, 10:29 AM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Canal{
    int id;
    char nombre[20];
    int montoInvPub;
    double roas;
    int nivelRecMar;
}Canal;

int backtracking(Canal *, int, int, int, double*, double*, double*, double*, 
        int*, int*);

int main(int argc, char** argv) {
    
    //P, N
    int presupuesto, cantCanales;
    FILE *arch;
    
    arch = fopen("datos.txt", "r");
    if(arch==NULL){
        printf("Error en el archivo datos.txt");
        exit(1);
    }
    
    fscanf(arch, "%d %d", &presupuesto, &cantCanales);
    Canal *canales = (Canal*)malloc(cantCanales*sizeof(Canal));
    for(int i=0;i<cantCanales;i++){
        fscanf(arch, "%d", &canales[i].id);
        fscanf(arch, "%s", &canales[i].nombre);
        fscanf(arch, "%d", &canales[i].montoInvPub);
        fscanf(arch, "%lf", &canales[i].roas);
        fscanf(arch, "%d", &canales[i].nivelRecMar); 
    }
/*
    for(int i=0; i<cantCanales; i++){
        printf("%d %s %d %.2lf %d\n", canales[i].id, canales[i].nombre, 
                canales[i].montoInvPub, canales[i].roas, canales[i].nivelRecMar);
    }
*/
    double maxIngreso=0, ingreso=0, montoTotal=0, monto=0;
    int cromo[cantCanales], cromoMostrar[cantCanales];
    for(int i=0;i< cantCanales;i++){
        cromo[i]=0;
        cromoMostrar[i]=0;
    }
    backtracking(canales, presupuesto, cantCanales, cantCanales, &maxIngreso, 
            &ingreso, &monto, &montoTotal, cromo, cromoMostrar);
    printf("El maximo ingreso por ventas es de %.2lf dolares con una inversion "
            "total en publicidad de %.2lf dolares\n", maxIngreso, montoTotal);
    printf("\nLos canales de publicidad que se deben de elegir para obtener el "
            "máximo ingreso total son:\n");
    for(int i=0;i<cantCanales;i++){
        if(cromoMostrar[i]){
            double mostrarIng = canales[i].roas*canales[i].montoInvPub;
            double mostrarMon = canales[i].montoInvPub;
            printf("- Canal %d - %s, ingreso = %.2lf dolares con una inversion "
                    "publicitaria de %.2lf dolares.\n", canales[i].id, 
                    canales[i].nombre, mostrarIng, mostrarMon);
        }
    }    
    
    free(canales);    
    fclose(arch);
    return (EXIT_SUCCESS);
}

int backtracking(Canal *canales, int presupuesto, int n, int cantCanales, 
        double *maxIngreso, double *ingresoActual, double *monto, 
        double *montoTotal, int *cromo, int *mejorCromo){
    if(cantCanales==0 && presupuesto>=0){
        if(*maxIngreso<*ingresoActual){
            *maxIngreso=*ingresoActual;
            *montoTotal = *monto;
            for(int i=0;i<n;i++){
                mejorCromo[i]=cromo[i];
                //printf("%d-%d ", i+1, cromo[i]);
            }
            //printf("\n");
        }
        return 0;
    }
    if(presupuesto<0) return 0;
    *ingresoActual += canales[cantCanales-1].roas*canales[cantCanales-1].montoInvPub;
    *monto += canales[cantCanales-1].montoInvPub;
    cromo[cantCanales-1]=1;
    backtracking(canales, presupuesto-canales[cantCanales-1].montoInvPub, n,
            cantCanales-1, maxIngreso, ingresoActual, monto, montoTotal, cromo,
            mejorCromo);
    *ingresoActual -= canales[cantCanales-1].roas*canales[cantCanales-1].montoInvPub;
    *monto -= canales[cantCanales-1].montoInvPub;
    cromo[cantCanales-1]=0;
    backtracking(canales, presupuesto, n, cantCanales-1, maxIngreso, ingresoActual,
            monto, montoTotal, cromo, mejorCromo);
}