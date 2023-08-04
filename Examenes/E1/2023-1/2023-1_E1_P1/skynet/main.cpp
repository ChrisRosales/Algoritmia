/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: piero
 *
 * Created on 22 de mayo de 2023, 16:35
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX 7

using namespace std;

#include "Pilas.h"

void atraparSkynet(int mapa[][MAX]);
int buscarPosible(int mapa[][MAX], Pila &pila);

int main(int argc, char** argv) {
    
    int mapa[MAX][MAX]={
    
        {  0,  0,  0,  0,  0,   0,  0},
        { 10,  0, 20, 30,  0,  20, 40},
        {  0,  0,  0,  0,  0, 100,  0},
        {  0,  0,  0,  0,  0,  80,  0},
        { 50, 10,  5, 10,  0, 100,  4},
        {100,  0,  0,  0,  0,   0,  0},
        {  0,  0,  0,  0,  0,   0,  0},
    
    };
    
    atraparSkynet(mapa);

    return 0;
}

void atraparSkynet(int mapa[][MAX])
{
    Pila pila; int posible, x, y, max=0; bool flag=true;
    construir(pila);
    //Apila solo los que no se envian paquetes a sí mismos para no revisar todo
    for(int i=0; i < MAX; i++) if(mapa[i][i] == 0) apilar(pila, i+1);
    //Buscará el posible skynet
    posible = buscarPosible(mapa, pila);
    //Revisa en cruz
    for(int i=0; i < MAX; i++)
    {
        x = mapa[posible-1][i];
        y = mapa[i][posible-1];
        if(x >= max) max = x;
        if(x == 0 and i != posible-1) flag = false;
        if(y != 0) flag = false;
    }
    if(flag) cout << "Skynet es: " << posible << endl << "Maximo de paquetes enviados por Skynet: " << max;
    else cout << "Skynet no está en la red.";
}

int buscarPosible(int mapa[][MAX], Pila &pila)
{
    if(pila.longitud == 1) return pila.cabeza->valor;
    int valor=desapilar(pila), aux;
    if(mapa[valor-1][pila.cabeza->valor-1] == 0) return buscarPosible(mapa, pila);
    else
    {
        aux = desapilar(pila);
        if(mapa[aux-1][valor-1] != 0) apilar(pila, aux);
        else apilar(pila, valor);
        return buscarPosible(mapa, pila);
    }
}
