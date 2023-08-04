/* 
 * File:   main.cpp
 * Author: Martin
 *
 * Created on May 19, 2023, 4:25 PM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "colas.h"
#define DIGIT 32
using namespace std;

int potencia(int n1,int n2){
    int res=1;
    for(int i=1;i<n2;i++) res*=n1;
    return res;
}

void llenarPedidos(int trama[][DIGIT],int cant,Cola*colita){
    int codigo=0,stoMin=0,stock=0,encargo=0;
    double preVen=0,n;
    Elemento aux;
    
    for(int i=0;i<cant;i++){
        n=5;
        codigo=0;
        for(int j=7;j<12;j++){
            int a=trama[i][j];
            cout<<a<<endl;
            codigo+=trama[i][j]*potencia(10,n);
            n--;
        }
        n=5;
        preVen=0;
        for(int j=13;j<20;j++){
            if(n<=0){
                preVen+=trama[i][j]*pow(10,n-1);
                n--;
                continue;
            }
            preVen+=trama[i][j]*potencia(10,n);
            n--;
        }
        n=5;
        stock=0;
        for(int j=20;j<25;j++){
            stock+=trama[i][j]*potencia(10,n);
            n--;
        }
        n=4;
        stoMin=0;
        for(int j=25;j<29;j++){
            stoMin+=trama[i][j]*potencia(10,n);
            n--;
        }
        cout<<codigo<<" "<<preVen<<" "<<stoMin<<" "<<stock<<endl;
        aux.codProd=codigo;
        aux.precio=preVen/1.2;
        if(stock<stoMin){
            if(codigo<20000) encargo=20*stoMin;
            else{
                encargo=3*stoMin;
            }
            aux.cant=encargo;
            encolar(colita,aux);
        }
    }
    
}

//void imprimir(int trama[][DIGIT]){
//    for(int i=0;i<DIGIT;i++) cout<<trama[1][i]<<" ";
//}

double desencolarPrioridad(Cola*pedido,double presupuesto){
    double presuParcial=presupuesto,total;
    int prioTop=20000,prioBot=10000,i=0;
    Elemento datos;
    while(presuParcial>0 && !esColaVacia(*pedido)){
        if(i>pedido->longitud){
            prioTop+=10000;
            prioBot+=10000;
        }
        //cout<<"llegue"<<endl;
        datos=desencolar(pedido);
        if(datos.codProd<prioTop && datos.codProd>=prioBot){
            total=datos.cant*datos.precio;
            cout<<datos.codProd<<endl;
            if(total<presuParcial || presuParcial-total<0){
                if(presuParcial-total<0){
                    double resto=presuParcial/datos.precio;
                    presuParcial=0;
                    datos.cant-=(int)resto;
                    encolar(pedido,datos);
                    cout<<"gaga es gay"<<endl;
                }
                else{
                    presuParcial-=total;
                }
            }
            i=0;
        }
        else{
            encolar(pedido,datos);
        }
        i++;
    }
    return presuParcial;
}

int main(int argc, char** argv) {
    int trama[][DIGIT]={{7,7,5,1,2,3,4,4,6,7,8,9,2,0,1,9,9,9,9,0,0,0,0,0,2,0,0,0,3,0,0,0},
                          {7,7,5,1,2,3,4,2,2,3,4,5,6,0,0,0,9,6,9,0,0,0,0,0,7,0,0,0,8,0,0,0},
                          {7,7,5,1,2,3,4,3,3,7,6,5,4,0,0,1,9,9,9,0,0,0,0,1,0,0,0,0,5,0,0,0},
                          {7,7,5,1,2,3,4,1,9,6,9,6,9,0,0,0,1,9,9,0,0,0,0,0,9,0,0,1,0,0,0,0},
                          {7,7,5,1,2,3,4,3,6,6,9,9,9,0,0,2,4,9,9,0,0,0,0,0,2,0,0,0,3,0,0,0},
                          {7,7,5,1,2,3,4,1,6,9,6,9,6,0,0,0,0,9,9,0,0,0,0,0,3,0,0,1,0,0,0,0},
                          {7,7,5,1,2,3,4,2,6,7,8,9,2,0,0,0,3,9,9,0,0,0,0,0,4,0,0,0,5,0,0,0},
                          {7,7,5,1,2,3,4,2,8,7,6,5,4,0,0,0,2,9,9,0,0,0,0,0,6,0,0,0,5,0,0,0},
                          {7,7,5,1,2,3,4,3,9,6,9,6,9,0,0,3,1,9,9,0,0,0,0,0,2,0,0,0,3,0,0,0},
                          {7,7,5,1,2,3,4,2,6,6,9,9,9,0,0,0,2,9,9,0,0,0,0,0,5,0,0,0,8,0,0,0}};
    int n=10;
    Cola pedido;
    construir(&pedido);
    llenarPedidos(trama,n,&pedido);
    mostrar(pedido);
    //hasta aqui funciono
    double presu=11000;
    presu=desencolarPrioridad(&pedido,presu);
    cout<<presu<<endl;
    mostrar(pedido);
    return 0;
}

