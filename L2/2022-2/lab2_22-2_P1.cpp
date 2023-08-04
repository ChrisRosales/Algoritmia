#include <iostream>
#include <cmath>

using namespace std;

void imprimirAnaquel(int anaquel[][6], int f, int c){
    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            cout << anaquel[i][j] << " ";
        }
        cout << endl;
    }
}

void llenarAnaquel(int anaquel[][6], int f,int c,int p,int num){
    //caso base
    if(p<=0) return;
    //caso normal
    if(c%2!=0){
        for(int i=0;i<=(num/2);i++){
            if(anaquel[f][(c/2)+i]==0 && p>0){
                anaquel[f][(c/2)+i]=5;
                p--;
            }
            if(anaquel[f][(c/2)-i]==0 && p>0){
                anaquel[f][(c/2)-i]=5;
                p--;
            }
        }
    }
    else{
        int a=c/2;
        int b=c/2-1;
        for(int i=0;i<=(num/2);i++){
            if(anaquel[f][a+i]==0 && p>0){
                anaquel[f][a+i]=5;
                p--;
            }
            if(anaquel[f][b-i]==0 && p>0){
                anaquel[f][b-i]=5;
                p--;
            }
        }
    }
    llenarAnaquel(anaquel,f+1,c,p,num+2);
}

int main(){
    int f=6,c=6,p=27,inicio;
    int anaquel[][6]={{0,0,0,0,0,0},
                       {0,0,0,0,0,0},
                       {0,0,0,1,0,0},
                       {0,1,0,0,0,0},
                       {0,0,0,0,1,0},
                       {0,0,0,0,0,0}};
    inicio=1;
    llenarAnaquel(anaquel,0,c,p,inicio);
    imprimirAnaquel(anaquel,f,c);
    return 0;
}