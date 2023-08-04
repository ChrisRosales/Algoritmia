/* 
 * File:   main.cpp
 * Author: Omar
 *
 * Created on April 27, 2023, 9:28 AM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

int EncuentraMayor(int arreglo[], int longitud_arreglo);
int BuscaNumero(int arreglo[], int longitud_arreglo, int numero);

struct trabajador{
    int id;
    int arrMaquinas[20];
};

int main(int argc, char** argv){
    int numeroTrabajadores = 3;
    int numeroMaquinas = 3;
    
    struct trabajador trabajadores[numeroTrabajadores];
    
    cout << "Ingrese las informacion de las maquinas por trabajador: "<<endl;
 
    
    for(int i=0;i<numeroTrabajadores;i++){
        trabajadores[i].id = i+1;
        for(int j=0;j<numeroMaquinas;j++){
            cin >> trabajadores[i].arrMaquinas[j]; 
        }
    }
    int sumatoria = 0;
    int mayor = 0;
    int posicion = 0;
    
    for(int i=0;i<numeroTrabajadores;i++){
        mayor = EncuentraMayor(trabajadores[i].arrMaquinas,numeroMaquinas);
        posicion = BuscaNumero(trabajadores[i].arrMaquinas,numeroMaquinas,mayor);
        cout << trabajadores[i].id << " "<<trabajadores[i].arrMaquinas[posicion]<<endl;
        sumatoria+=mayor;
    }
    cout << sumatoria;
    
//    for(int i=0;i<numeroTrabajadores;i++){
//        cout << trabajadores[i].id << " ";
//        for(int j=0;j<numeroMaquinas;j++){
//           cout <<trabajadores[i].arrMaquinas[j]; 
//        }
//        cout <<endl;
//    }

    return 0;
}

int EncuentraMayor(int arreglo[], int longitud_arreglo){
    int opcion1, opcion2;
    
    if (longitud_arreglo == 1) {
        return arreglo[longitud_arreglo-1];
    }
    
    opcion1=arreglo[longitud_arreglo-1];
    opcion2=EncuentraMayor(arreglo,longitud_arreglo-1);    
    
    if (opcion1<opcion2){
    	return opcion2;
    }
    else{
    	return opcion1;
    }    
}

int BuscaNumero(int arreglo[], int longitud_arreglo, int numero) {
    if (longitud_arreglo == 0) {
	    return -1; 
    }
    
    if(arreglo[longitud_arreglo-1]==numero){
    	return longitud_arreglo-1;
    }
    else{
	return BuscaNumero(arreglo, longitud_arreglo-1, numero);
    }
}


