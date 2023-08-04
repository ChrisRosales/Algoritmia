/* 
 * File:   main.cpp
 * Author: Jordan Martel Alcantara
 *
 * Created on May 27, 2023, 3:51 PM
 */

#include <cstdlib>

#include <iostream>
#include <iomanip> 
#include <fstream>
using namespace std;
#include "funcionesAuxiliares.h"

#include "listaSimple.h"

int main(int argc, char** argv) {
    Lista listaA, listaB, listaC, listaD, listaE;
    construir(listaA);
    construir(listaB);
    construir(listaC);
    construir(listaD);
    construir(listaE);
    //El ingreso de datos se hara por archivo 
    leerDatos(listaA, listaB, listaC, listaD, listaE);
    //Una vez que contemos con las 5 listas llenas, procedemos a unir todas en una sola
    fusionarListas(listaA, listaB, listaC, listaD, listaE);
    cout<<"LISTA FINAL RESULTADO DE LA REORGANIZACION: "<<endl;
    mostrar(listaA);
    return 0;
}

