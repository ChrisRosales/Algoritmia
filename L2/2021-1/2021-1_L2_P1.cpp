/* 
 * File:   main.cpp
 * Author: Omar
 *
 * Created on April 26, 2023, 10:10 AM
 */

#include <cstdlib>
#include <iostream>
#define MAXF 20
#define MAXC 20


void imprimirCodigos(int x,int cantidadInicial,int cantidadMaxima,
        int cantidadMinima, int matriz[MAXF][MAXC], int filas,int columnas,
        int flag, int *contador);
int EncuentraMayor(int i,int matriz[MAXF][MAXC],int longitud_arreglo);
int BuscaNumero(int i,int matriz[MAXF][MAXC], int longitud_arreglo, int numero);
void corePrograma(int i, int cantidadInicial, int x,int matriz[MAXF][MAXC],int columnas);

using namespace std;
 
int main(int argc, char** argv) {
    int cantidadInicial = 6, cantidadMaxima = 8, cantidadMinima = 4;
    int filas,columnas;
    cout << "Ingrese los dias y cuantos productos se tienen que analizar: "<<endl;
    cin >> filas >> columnas;
    
    int matriz[MAXF][MAXC];
    
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            cin >> matriz[i][j];
        }
    }
    /*Impresion para verficar entrada de datos*/
//    for(int i=0;i<filas;i++){
//        for(int j=0;j<columnas;j++){
//            cout << matriz[i][j]<<" ";
//        }
//        cout <<endl;
//    }
    
    int contador = 0;
    cout <<endl;
    imprimirCodigos(0,cantidadInicial,cantidadMaxima,cantidadMinima,matriz,filas,columnas, 0,&contador);
    cout << "El rodillo durara : "<<contador<< " dias";
    
    return 0;
}

void imprimirCodigos(int x,int cantidadInicial,int cantidadMaxima,int cantidadMinima, int matriz[MAXF][MAXC], int filas,int columnas,
        int flag, int *contador){
    
    if(cantidadInicial>=cantidadMinima){
        (*contador)++;
        corePrograma(0,cantidadInicial,x,matriz,columnas);
        cout<<endl;
        if(cantidadInicial<cantidadMaxima && flag == 0){
            imprimirCodigos(x+1,cantidadInicial+1,cantidadMaxima,cantidadMinima,matriz,filas,columnas,0,contador);
        }else if(cantidadInicial == cantidadMaxima && flag == 0){
            imprimirCodigos(x+1,cantidadInicial,cantidadMaxima,cantidadMinima,matriz,filas,columnas,1,contador);
        }else if(cantidadInicial == cantidadMaxima && flag == 1){
             imprimirCodigos(x+1,cantidadInicial-1,cantidadMaxima,cantidadMinima,matriz,filas,columnas,1,contador);
        }else{
            imprimirCodigos(x+1,cantidadInicial-1,cantidadMaxima,cantidadMinima,matriz,filas,columnas,1,contador);
        }
    }
}
void corePrograma(int i, int cantidadInicial, int x,int matriz[MAXF][MAXC],int columnas){
    int maximo,posicionY;
    if(i<cantidadInicial){
        maximo = EncuentraMayor(x,matriz,columnas);
        posicionY = BuscaNumero(x,matriz,columnas,maximo);
        matriz[x][posicionY] = -1;
        cout << maximo << " ";
        corePrograma(i+1,cantidadInicial,x,matriz,columnas);
    }
}
int EncuentraMayor(int i,int matriz[MAXF][MAXC],int longitud_arreglo){
    int opcion1, opcion2;
    if (longitud_arreglo == 1) {
	    return matriz[i][longitud_arreglo-1];
    }
    opcion1=matriz[i][longitud_arreglo-1];
    opcion2=EncuentraMayor(i,matriz,longitud_arreglo-1);
    if (opcion1<opcion2){
    	return opcion2;
    }else{
    	return opcion1;
    }
}
int BuscaNumero(int i,int matriz[MAXF][MAXC], int longitud_arreglo, int numero) {
    if (longitud_arreglo == 0) {
	    return -1; 
    }
    if(matriz[i][longitud_arreglo-1]==numero){
        return longitud_arreglo-1;
    }else{
	return BuscaNumero(i,matriz, longitud_arreglo-1, numero);
    }
}


