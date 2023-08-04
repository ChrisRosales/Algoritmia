#include <iostream>
#include <cmath>

using namespace std;

//movimientos posibles
int movimientos[8][2]={{-1,-1},
                       {-1,0},
                       {-1,1},
                       {0,-1},
                       {0,1},
                       {1,-1},
                       {1,0},
                       {1,1}};

int cuentaMinPasos(int campo[][5],int x,int y,int xFin,int yFin){
    //caso base
    if((x==xFin && y==yFin) || x<0 || x>8 || y<0 || y>4){
        return 0;
    }
    //caso normal
    int minPasos=1000000;
    for(int i=0;i<8;i++){
        int xSig=x+movimientos[i][0];
        int ySig=y+movimientos[i][1];
        if(xSig>=0 && xSig<9 && ySig>=0 && ySig<5 && campo[xSig][ySig]==0){
            campo[xSig][ySig]=1;
            int pasos=cuentaMinPasos(campo,xSig,ySig,xFin,yFin);
            if(pasos<minPasos){
                minPasos=pasos;
            }
            campo[xSig][ySig]=0;
        }
    }
    return minPasos+1;
}

int main(){
    int campo[9][5]={{0,0,0,0,1},
                     {0,0,0,0,0},
                     {0,0,1,0,0},
                     {0,0,0,0,0},
                     {0,1,1,0,1},
                     {0,1,1,0,1},
                     {1,1,0,1,0},
                     {1,1,1,1,0},
                     {1,0,0,0,0}};
    //cout<<"El campo es: "<<endl;
    /*for(int i=0;i<9;i++){
        for(int j=0<;j<5;j++){
            cout<<campo[i][j]<<" ";
        }
        cout<<endl;
    }*/
    cout<<"La cantidad minima de pasos para llegar a la meta es: "
    <<cuentaMinPasos(campo,0,0,8,4)<<endl;
    
    return 0;
}