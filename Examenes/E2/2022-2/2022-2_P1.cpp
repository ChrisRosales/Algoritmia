/* 
 * File:   main.cpp
 * Author: Omar
 *
 * Created on July 11, 2023, 6:08 PM
 */

#include <cstdlib>
#include <climits>
#include <iostream>
#define MAX 9

int solTribuna[MAX] = {0};
int solPreferencial[MAX] = {0};
int solVip[MAX] = {0};
int t = 0;
int p = 0;
int v = 0;
int capacidadSector = 3;
int cantidadSectores = 3;

double mejorPromTrib = INT_MAX;
double mejorPromPref = INT_MAX;
double mejorPromVip = INT_MAX;

int mejorSolT[MAX] = {0};
int mejorSolP[MAX] = {0};
int mejorSolV[MAX] = {0};


using namespace std;
int asignacionCorrecta(int edades[], int n, int iterador, int sillasT, int sillasP, int sillasV, int espacios);
int asignacionCorrectaParteb(int edades[], int n, int iterador, int sillasT, int sillasP, int sillasV, int espacios);
int valida(int edades[], int posicionEdad, int posicionSector,int sillasT, int sillasP, int sillasV);

int main(int argc, char** argv){
    int edades[MAX] = {25,50,35,28,45,23,24,18,48};
    int n = 9;
    int sillasTribuna = 2;
    int sillasPreferencial = 1;
    int sillasVip = 0;
    asignacionCorrecta(edades,n,0,sillasTribuna,sillasPreferencial,sillasVip,3);
    t = 0;
    p = 0;
    v = 0;
    asignacionCorrectaParteb(edades,n,0,sillasTribuna,sillasPreferencial,sillasVip,3);
    cout << "Mejor tribuna" << endl;
    for(int i = 0;i<3;i++){
        cout << mejorSolT[i]<<" ";
    }
    cout << mejorPromTrib;
    cout << endl;
    cout << "Mejor preferencial" << endl;
    for(int i = 0;i<3;i++){
        cout << mejorSolP[i]<<" ";
    }
    cout << mejorPromPref;
    cout << endl;
    cout<< "Mejor vip" << endl;
    for(int i = 0;i<3;i++){
        cout << mejorSolV[i] << " ";
    }
    cout << mejorPromVip;
    cout << endl;
    
    return 0;
}

int asignacionCorrecta(int edades[], int n, int iterador, int sillasT, int sillasP, int sillasV, int espacios){
    if(iterador == n){
        cout << "Inciso a: "<<endl;
        cout << "Tribuna" << endl;
        for(int i = 0;i<espacios;i++){
            cout << solTribuna[i] << " ";
        }
        cout << endl << "Preferencial" << endl;
        for(int i = 0;i<espacios;i++){
            cout << solPreferencial[i] << " ";
        }
        cout <<endl<< "VIP"<<endl;
        for(int i = 0;i<espacios;i++){
            cout << solVip[i] << " ";
        }
        cout << endl<<endl;
        return 0;
    }
    
    for(int posicionSector = 0;posicionSector<cantidadSectores;posicionSector++){
        if(valida(edades,iterador,posicionSector,sillasT,sillasP,sillasV)){
            if(posicionSector == 0){
                solTribuna[t] = edades[iterador];
                if(edades[iterador] >= 45) sillasT--;
                t++;
            }else if(posicionSector == 1){
                solPreferencial[p] = edades[iterador];
                if(edades[iterador] >=45) sillasP--;
                p++;
            }else if(posicionSector == 2){
                solVip[v] = edades[iterador];
                if(edades[iterador] >=45) sillasV--;
                v++;
            }
            if(asignacionCorrecta(edades,n,iterador+1,sillasT,sillasP,sillasV,espacios)){
                return 1;
            }
            if(posicionSector == 0){
                solTribuna[t] = 0;
                if(edades[iterador] >=45) sillasT++;
                t--;
            }else if(posicionSector == 1){
                solPreferencial[p] = 0;
                if(edades[iterador] >=45) sillasP++;
                p--;
            }else if(posicionSector == 2){
                solVip[v] = 0;
                if(edades[iterador] >=45) sillasV++;
                v--;
            }
        }   
    }
    
    return 0;
    
}

int asignacionCorrectaParteb(int edades[], int n, int iterador, int sillasT, int sillasP, int sillasV, int espacios){
    if(iterador == n){
        double promTrib = 0, promPref = 0, promVip = 0;
        int sumatoriaTrib = 0, sumatoriaPref = 0, sumatoriaVip = 0;
        for(int i = 0;i<espacios;i++){
            sumatoriaTrib += solTribuna[i];
            sumatoriaPref += solPreferencial[i];
            sumatoriaVip  += solVip[i];
        }
        promTrib = (double)sumatoriaTrib/espacios;
        promPref = (double)sumatoriaPref/espacios;
        promVip = (double)sumatoriaVip/espacios;
        
        if(promTrib <= mejorPromTrib && promPref <= mejorPromPref && promVip <=mejorPromVip){
            mejorPromTrib = promTrib,mejorPromPref = promPref,mejorPromVip = promVip;
            for(int i = 0;i<espacios;i++){
                mejorSolT[i] = solTribuna[i];
                mejorSolP[i] = solPreferencial[i];
                mejorSolV[i] = solVip[i];
            }
        }
        
        
        return 0;
    }
    
    for(int posicionSector = 0;posicionSector<cantidadSectores;posicionSector++){
        if(valida(edades,iterador,posicionSector,sillasT,sillasP,sillasV)){
            if(posicionSector == 0){
                solTribuna[t] = edades[iterador];
                if(edades[iterador] >= 45) sillasT--;
                t++;
            }else if(posicionSector == 1){
                solPreferencial[p] = edades[iterador];
                if(edades[iterador] >=45) sillasP--;
                p++;
            }else if(posicionSector == 2){
                solVip[v] = edades[iterador];
                if(edades[iterador] >=45) sillasV--;
                v++;
            }
            if(asignacionCorrectaParteb(edades,n,iterador+1,sillasT,sillasP,sillasV,espacios)){
                return 1;
            }
            if(posicionSector == 0){
                solTribuna[t] = 0;
                if(edades[iterador] >=45) sillasT++;
                t--;
            }else if(posicionSector == 1){
                solPreferencial[p] = 0;
                if(edades[iterador] >=45) sillasP++;
                p--;
            }else if(posicionSector == 2){
                solVip[v] = 0;
                if(edades[iterador] >=45) sillasV++;
                v--;
            }
        }   
    }
    return 0;
    
}

int valida(int edades[], int posicionEdad, int posicionSector,int sillasT, int sillasP, int sillasV){            
    if(edades[posicionEdad]>=45){
        if(posicionSector == 0){
            if(sillasT!=0 && t<3){
                return 1;
            }
            return 0;
        }else if(posicionSector == 1){
            if(sillasP!=0 && p<3){
                return 1;
            }
            return 0;
        }else if(posicionSector == 2){
            if(sillasV!=0 && v<3){
                return 1;
            }
            return 0;
        }
    }else{
        if(posicionSector == 0){
            if(capacidadSector - t == 1 && sillasT == 1){
                return 0;
            }
            if(t<3){
                return 1;
            }
            return 0;
            
        }else if(posicionSector == 1){
            if(capacidadSector - p == 1 && sillasP == 1){
                return 0;
            }
            if(p<3){
                return 1;
            }
            return 0;
            
        }else if(posicionSector == 2){
            if(capacidadSector - v == 1 && sillasV == 1){
                return 0;
            }
            if(v<3){
                return 1;
            }
            return 0;
        }
    }
}




