/* 
 * File:   main.cpp
 * Author: Omar
 *
 * Created on April 27, 2023, 5:12 PM
 */

#include <cstdlib>
#include <iostream>
#define COLUMNAS 6 
#define FILAS 6
#define TAMARR 3

int sumarTotal(int i,int limite,int constante, int total, int x,int y, int *arr);
int obtenerMaximo(int x,int y, int total, int maximo);
//int buscarNumero(int x,int y, int numero,int pos);
int buscar(int numero, int *arr, int i);

int arrBuscaNumeros[TAMARR] = {1,2,9};

int matriz[FILAS][COLUMNAS] = {
    {1, 2, 9, 1, 2, 3},
    {5, 1, 7, 0, 2, 1},
    {0, 7, 0, 3, 8, 1},
    {1, 2, 6, 1, 2, 2},
    {0, 6, 9, 5, 0, 5},
    {0, 0, 4, 0, 9, 0}

};

using namespace std;

int main(int argc, char** argv) {
    cout << obtenerMaximo(0,COLUMNAS-1,0,0);
    
    int encontrado = 0;
    int flag = 0;
    

    return 0;
}
int obtenerMaximo(int x,int y, int total, int maximo){
    if(x == FILAS -1){
        return maximo;
    }
    
    int arr[TAMARR] = {0,0,0};
    int flag = 0;
    
    total = sumarTotal(0,y,x,total,x,y,arr);
    total  = sumarTotal(x,FILAS,y,total,x,y,arr);
    for(int i=0;i<TAMARR;i++){
        if(arr[i] == 0 ){
            flag = 1;
        }
    }
    
    if(flag == 0){
        cout<<"Se encontro los paquetes"<<endl;
    }
    
    if(total > maximo){
       maximo = total;
   }  
    return obtenerMaximo(x+1,y-1,0,maximo);
}
int sumarTotal(int i,int limite,int constante, int total, int x,int y, int *arr){
    if(i == limite){
        return total;
    }
    if(i<limite){
        if(constante == x){
            total += matriz[constante][i];
            buscar(matriz[constante][i],arr,0);
            
        }else{
            total +=matriz[i][constante];
            buscar(matriz[i][constante],arr,0);
        }
        
        return sumarTotal(i+1,limite,constante,total,x,y,arr);
    }
}

int buscar(int numero, int *arr, int i){
    if( i >TAMARR){
        return -1;
    }
    //voy a buscar el numero recibido como parametro en el arrBuscaNumeros
    if(arrBuscaNumeros[i] == numero){
        //Si lo encontre, entonces coloco un uno en mi arreglo auxiliar;
        arr[i] = 1;
        buscar(numero,arr,i+1);
    }else{
        buscar(numero,arr,i+1);
    }
    
    
}

