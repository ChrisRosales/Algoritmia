/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ALEJANDRO
 *
 * Created on 8 de abril de 2022, 03:01 PM
 * Se utiliza la estrategia de Fuerza bruta
 */

#include <stdio.h>
#include <stdlib.h>

//Estructura de un canal
struct canal{
    int id;
    char nombre[20];
    double roas;
    int nivelRecordacion;
    double montoInversion;
};

void convertirBinario(int *, int, int);

int main(int argc, char** argv) {
    
    //Variables P y N
    int presupuesto, cantCanales;
    //Archivo de datos
    FILE *archDatos;
    archDatos = fopen("2022-1_L1_P1_data.txt", "r");
    if(archDatos==NULL){
        printf("Error en el archivo 2022-1_L1_P1_data.txt");
        exit(1);
    }
    //Lectura del presupuesto y la cantidad de canales
    fscanf(archDatos, "%d %d", &presupuesto, &cantCanales);
    //Creando un arreglo de tipo struct canal
    struct canal canales[cantCanales];
    //Asignando los datos de los canales a mi arreglo de canales
    for(int i=0;i<cantCanales;i++){
        fscanf(archDatos, "%d %s %lf %lf %d", &canales[i].id, &canales[i].nombre, 
     &canales[i].montoInversion, &canales[i].roas, &canales[i].nivelRecordacion);
/*
        printf("%d %s %d %.2lf %d\n", canales[i].id, canales[i].nombre, 
     canales[i].montoInversion, canales[i].roas, canales[i].nivelRecordacion);
*/
    }
    //Cantidad de combinaciones
    int combinaciones = 1 << cantCanales;
    double maxIngreso = 0.0, ingreso, maxInversion, inversion;
    double maxIngresoR = 0.0, maxInversionR;
    int maxRecordacion=0, recordacion, mejorComb, mejorRComb; 
    int cromo[cantCanales];
    //Rellenar mi cromosoma de 0s
    for(int i=0;i<cantCanales;i++)cromo[i]=0;
    
    for(int i=0;i<combinaciones;i++){
        //Convierte la combinacion actual en bianrio
        convertirBinario(cromo, cantCanales, i);
        //Inicializar datos
        ingreso=recordacion=inversion=0;
        for(int j=0;j<cantCanales;j++){
            ingreso += (canales[j].roas*canales[j].montoInversion)*cromo[j];
            inversion += canales[j].montoInversion*cromo[j];
            recordacion += canales[j].nivelRecordacion*cromo[j];
        }
        /*Verificar que no sobrepase el presupuesto
         *Calcular el mayor ingreso*/
        if(ingreso>maxIngreso && presupuesto>=inversion){
            maxIngreso = ingreso;
            maxInversion = inversion;
            mejorComb = i;
        }
        /*Verificar que no sobrepase el presupuesto
         *Calcular la mayor recordacion*/
        if(recordacion>maxRecordacion && presupuesto>=inversion){
            maxIngresoR = ingreso;
            maxInversionR = inversion;
            mejorRComb = i;
            maxRecordacion = recordacion;
        }
    }
    
    //Resultado 1
    FILE *archReporte1;
    archReporte1 = fopen("Reporte1.txt", "w");
    
    fprintf(archReporte1, "El máximo ingreso por ventas es de %.2lf dolares"
            " con una inversion total en publicidad de %.2lf dolares.\n\n"
            , maxIngreso, maxInversion);
    
    fprintf(archReporte1,"Los canales de publicidad que se deben de "
            "elegir para obtener el máximo ingreso total son:\n");
    
    convertirBinario(cromo, cantCanales, mejorComb);
    
    for(int i=0;i<cantCanales;i++){
        if(cromo[i]){
            fprintf(archReporte1,"- Canal %d - %s, ingreso = %.2lf dolares con"
                    " una inversion publicitaria de %.2lf dolares.\n",
                    canales[i].id, canales[i].nombre, 
                    canales[i].roas*canales[i].montoInversion, 
                    canales[i].montoInversion);
        }
    }
    
    fclose(archReporte1);
    //Resultado 2
    FILE *archReporte2;
    archReporte2 = fopen("Reporte2.txt", "w");
    
    fprintf(archReporte2, "El nivel máximo de recordación de marca es de %d"
            " con una inversion total en publicidad de %.2lf dólares y un "
            "ingreso de %.2lf dólares.\n\n", maxRecordacion, 
            maxInversionR, maxIngresoR);
    
    fprintf(archReporte2, "Los canales de publicidad que se deben de elegir "
            "para obtener el máximo nivel de recordación de marca son: \n");
    
    convertirBinario(cromo, cantCanales, mejorRComb);
    
    for(int i=0;i<cantCanales;i++){
        if(cromo[i]){
            fprintf(archReporte2, "- Canal %d - %s, ingreso = %.2lf dolares con"
                    " una inversion publicitaria de %.2lf dolares.\n",
                    canales[i].id, canales[i].nombre, 
                    canales[i].roas*canales[i].montoInversion, 
                    canales[i].montoInversion);
        }
    }
    
    fclose(archReporte2);
    fclose(archDatos);
    
    return (EXIT_SUCCESS);
}

void convertirBinario(int *cromo, int cantCromo, int numero) {
    int resto;
    for (int i = 0; i < cantCromo; i++) {
        resto = numero % 2;
        numero = numero / 2;
        cromo[i] = resto;
    }
}