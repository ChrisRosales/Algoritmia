/* 
 * File:   main.cpp
 * Author: Jordan Martel Alcantara
 *
 * Created on May 27, 2023, 3:01 PM
 */

#include <cstdlib>

#include <iostream>
#include <iomanip>
#include <fstream>
#include "pila.h"        
using namespace std;

int main(int argc, char** argv) {
    Pila Kupa1,Kupa2;
    construir(Kupa1);
    construir(Kupa2);
    ifstream archDatosKupa1("datosKupa1.txt",ios::in);
    if(not archDatosKupa1.is_open()){
        cout<<"ERROR:No se pudo abrir el archivo datosKupa1.txt"<<endl;
        exit(1);
    }
    ifstream archDatosKupa2("datosKupa2.txt",ios::in);
    if(not archDatosKupa2.is_open()){
        cout<<"ERROR:No se pudo abrir el archivo datosKupa2.txt"<<endl;
        exit(1);
    }
    //Leemos los datos del primer ejercito Kupa
    int nivel;
    while(true){
        archDatosKupa1>>nivel;
        if(archDatosKupa1.eof())break;
        apilar(Kupa1,nivel);
    }
    cout<<"ROBOT KUPA 1: "<<endl;
    mostrar(Kupa1);
    while(true){
        archDatosKupa2>>nivel;
        if(archDatosKupa2.eof())break;
        apilar(Kupa2,nivel);
    }
    cout<<"ROBOT KUPA 2: "<<endl;
    mostrar(Kupa2);
    //Para unir las dos pilas en una pila unica, desapilo los datos de una pila y lo apilo en otra
    cout<<"ROBOT KUPAS UNIDOS: "<<endl;
    unirPilas(Kupa1,Kupa2);
    mostrar(Kupa1);
    
    //Pasamos ahora a ordenar la pila unica(Kupa1) de mayor a menor nivel
    cout<<"PILA UNICA ORDENADA"<<endl;
    ordenarPilar(Kupa1);
    mostrar(Kupa1);
    
    //Pasamos ahora la pila unica del mundo Browser a la pila unica del mundo champinon 
    Pila champinon;
    construir(champinon);
    //Se crea otra pila sin embargo solo es para darle el nombre de champinon, en la indicacion dice que no se debe 
    // hacer uso de una pila extra sin embargo, no la estoy usando, solo es para el nombre.
    // La funcion funcionaria igual si se pasa del ejercito KUPA1 al ejercito KUPA2(el que representaria al mundo champinon)
    cout<<"PILA EN EL MUNDO CHAMPINON"<<endl;
    pasarKupaAChampinon(Kupa1,champinon);
    mostrar(champinon);
    return 0;
}

