
/* 
 * File:   main.c
 * Autor: Gabriel Omar Durán Ruiz 
 * Código: 20203371
 * Created on 22 de abril de 2022, 03:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "StructRegion.h"
#define M 7
void leerDatos(FILE *arch,struct Region *regiones,int cantReg,int marcasRobot,
        double matrizRobots[][7]);
void elegirRobots(int i,struct Region *regiones,int cantReg,int marcasRobot,
        double presupuesto,double *pago,double *ahorro);
void hallarAhorrosRegion(struct Region *regiones,int nroReg,int marcasRobot,
        double presupuesto,double *ahorroReg,double *ahorro);
void hallarPagosRobot(struct Region region,int distribucion,int nroRobot,int cantMarcas,
        double *preciosDist,int *cantPrecios,double *ahorros);
int minIndex(int lista[],int inicio,int n);
void fun(int arr[], int start_index, int end_index);
void recorrerArreglo(int *precios,int distribucion,double *precio,
        int limInf,int limtSup,int robotsDisp);
void imprimirCabecera();
char buscarIndice(double valor,int nroReg,int numRobots,int matrizRobots[][M]);
/*
 * 
 */
int main(int argc, char** argv) {
    //Aclarar lectura y  proceso de datos
    FILE *arch;
    int cantReg,marcasRobot;
    double presupuesto,pago=0,ahorro=0;
    arch=fopen("2022-1_L2_P2_data.txt","r");
    if(arch==NULL){
        printf("Error, no se pudo abrir el archivo 2022-1_L2_P2_data.txt");
        exit(1);
    }
    fscanf(arch,"%lf %d %d",&presupuesto,&cantReg,&marcasRobot);
    struct Region solucion[cantReg],regiones[20];
    double matrizRobots[cantReg][marcasRobot];
    leerDatos(arch,regiones,cantReg,marcasRobot,matrizRobots);
    imprimirCabecera();
    //elegimos los robots en cada region después de haber cargado la info
    //de los robots
    elegirRobots(0,regiones,cantReg,marcasRobot,presupuesto,&pago,&ahorro);
    printf("El costo real de distribucion es de USD %.0lf con un ahorro de USD"
            " %.0lf",presupuesto,ahorro);
    fclose(arch);
    return (EXIT_SUCCESS);
}

void imprimirCabecera(){
    printf("Region  Monto destinado  Robots para distribuir     Costo Real"
    "   Ahorro hasta la region\n");
}

void leerDatos(FILE *arch,struct Region *regiones,int cantReg,int marcasRobot,
        double matrizRobots[][7]){
    int j,distribucion,cantRobot;
    double porc,precio;
    char nombre[30];
    int i;
    for( i=0;i<cantReg;i++){
        fscanf(arch,"%d.%s %lf",&j,nombre,&porc);
        for(j=0;j<marcasRobot;j++){
            fscanf(arch,"%lf",&precio);
            regiones[i].precioRobot[j]=precio;
            matrizRobots[i][j]=precio;
        }
        fscanf(arch,"%d %d",&distribucion,&cantRobot);
        regiones[i].porcPresup=porc;
        regiones[i].cantRobot=cantRobot;
        regiones[i].distribucion=distribucion;
        strcpy(regiones[i].nombre,nombre);
    }
}

void elegirRobots(int i,struct Region *regiones,int cantReg,int marcasRobot,
        double presupuesto,double *pago,double *ahorro){
    hallarAhorrosRegion(regiones,i,marcasRobot,presupuesto,pago,ahorro);
    if(i+1==cantReg)return;
    elegirRobots(i+1,regiones,cantReg,marcasRobot,presupuesto,pago,ahorro);
}

void hallarAhorrosRegion(struct Region *regiones,int nroReg,int marcasRobot,
        double presupuesto,double *pago,double *ahorro){
    int numRobots=regiones[nroReg].cantRobot,cantPrecios=0,distribucion;
    double pagoRobots=0,preciosDist[numRobots],precio,esperado;
    int arrRobots[numRobots];
    //fun ordena de menor a mayor
    esperado=regiones[nroReg].porcPresup/100*presupuesto;
    fun(regiones[nroReg].precioRobot,0,marcasRobot);
    distribucion=regiones[nroReg].distribucion;
    recorrerArreglo(regiones[nroReg].precioRobot,distribucion,&precio
            ,0,marcasRobot-1,numRobots);
    printf("%-d.%-15s %5.0lf \t\t\t\t",nroReg+1,regiones[nroReg].nombre,esperado
                );
    if(pago==0)(*ahorro)=esperado-precio;
    else (*ahorro)+=esperado-precio;
    printf("%-5.0lf %20.0lf\n",precio,*ahorro);
    (*pago)+=precio;
    
}

void recorrerArreglo(int *precios,int distribucion,double *precio,
        int limInf,int limtSup,int robotsDisp){
    if(robotsDisp==0)return;
    
    if(distribucion==0){
        (*precio)+=precios[limInf];
        recorrerArreglo(precios,distribucion,precio,limInf+1,limtSup,robotsDisp-1);
    }else{
         (*precio)+=precios[limtSup];
         recorrerArreglo(precios,distribucion,precio,limInf,limtSup-1,robotsDisp-1);
    }
}

int minIndex(int lista[],int inicio,int n)
{   int menor,resto;
    if(inicio==n-1)
        return(inicio);
        
    menor=inicio;
    resto=minIndex(lista,inicio+1,n);
            
    if(lista[menor]<lista[resto])
        return(resto);
    else
        return(menor);
}

void fun(int arr[], int start_index, int end_index)
{
    if(start_index>=end_index)
        return;
    int min_index;
    int temp;
    
    min_index=minIndex(arr,start_index,end_index);
    temp = arr[start_index];
    arr[start_index]=arr[min_index];
    arr[min_index]=temp;
    fun(arr,start_index+1,end_index);
}

char buscarIndice(double valor,int nroReg,int numRobots,int matrizRobots[][M]){
    char c;
    if(fabs(valor-matrizRobots[nroReg][numRobots])<=0.01)return numRobots+'A';
    c=buscarIndice(valor,nroReg,numRobots-1,matrizRobots);
    return c;
    if(numRobots==0)return 0;
}


