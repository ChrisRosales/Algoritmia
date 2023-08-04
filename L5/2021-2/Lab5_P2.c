/* 
 * File:   main.c
 * Author: cueva
 *
 * Created on 24 de noviembre de 2021, 04:55 PM
 */

#include <stdio.h>
#include <stdlib.h>


#define MAX_MOV 4
#define MAX_INI 8
#define N 100
#define M 100
/*Base*/

int map[MAX_MOV][2];
int mov[MAX_INI][2];
int maximo=0;

void generateMoves(int largo){
    largo--;
    map[0][0] =  largo; map[0][1] =  0;
    map[1][0] =  0; map[1][1] = -1*largo;
    map[2][0] =  0; map[2][1] =  largo;
    map[3][0] = -1*largo; map[3][1] =  0;
}

void generatepos(){
    mov[0][0] =  1; mov[0][1] =  0;
    mov[1][0] =  0; mov[1][1] = -1;
    mov[2][0] =  0; mov[2][1] =  1;
    mov[3][0] = -1; mov[3][1] =  0;
    
    mov[4][0] =  1; mov[4][1] =  1;
    mov[5][0] = -1; mov[5][1] = -1;
    mov[6][0] =  1; mov[6][1] = -1;
    mov[7][0] = -1; mov[7][1] =  1;
}

void generateTable(int a[N][M], int n,int m) {
    int i, j;
    for ( i = 0; i < n; i++ )
        for ( j = 0; j < m; j++ )
            a[i][j] = 0;
}

void print(int a[N][M], int n,int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }
}

int is_valid(int a[N][M], int x, int y, int n,int m) {

    if ( x < n && y < m && x >= 0 && y >= 0 && a[x][y] == 0)  
	//valida que no se salga del tablero y que este libre
        return 1;
    return 0;
}
int valida_recorrido(int a[N][M],int x1,int y1,int x2,int y2,int n,int m){
    int j,k;
    if(is_valid(a,x2,y2,n,m)){
        if(x1<x2)
            for(j=x1;j<=x2;j++){
                if(a[j][y1]!=0) return 0;
            }    
        else
            for(j=x1;j>=x2;j--)
                if(a[j][y1]!=0) return 0;
        if(y1<y2)
            for(k=y1;k<=y2;k++){
                if(a[x1][k]!=0) return 0;
            }    
        else
            for(k=y1;k>=y2;k--)
                if(a[x1][k]!=0) return 0;    
        return 1;
    }
    return 0;
}
void marca(int a[N][M],int x1,int y1,int x2,int y2,int n,
	int m,int nMov){
    int j,k;
    
    if(x1<x2)
        for(j=x1;j<=x2;j++)
            a[j][y1] = nMov;
    else
	for(j=x1;j>=x2;j--)
            a[j][y1] = nMov;
    if(y1<y2)
        for(k=y1;k<=y2;k++)
            a[x1][k] = nMov;
    else
        for(k=y1;k>=y2;k--)
            a[x1][k] = nMov;
}

int solve_robot(int a[N][M], int n, int m, int x, int y,
	int nMov,int solu[N][M]) 
{
    int i,j,new_x,new_y,mov_x,mov_y;
	 int p,q; 	
   //  printf("Movimiento : %d\n", nMov);
    if(nMov == n*m)
        return 1;
    for ( i = 0; i < MAX_INI; i++ ) 
    { 
        new_x = x + mov[i][0];
        new_y = y + mov[i][1];
        
        if(is_valid(a,new_x,new_y,n,m)){
            for ( j = 0; j < MAX_MOV; j++ ){
                mov_x = new_x + map[j][0];
                mov_y = new_y + map[j][1];
                if(valida_recorrido(a,new_x,new_y,mov_x,mov_y,n,m)){
                    marca(a,new_x,new_y,mov_x,mov_y,n,m,nMov);
                    if(nMov>maximo){
                        maximo = nMov;
                        generateTable(solu,n,m);
                        for ( p = 0; p < n; p++ )
                                for ( q = 0; q < m; q++ )
                                    solu[p][q] =a[p][q] ;
                    }
                    if(solve_robot(a,n,m,mov_x,mov_y,nMov+1,solu))
                        return 1;
                    marca(a,new_x,new_y,mov_x,mov_y,n,m,0);
                }
            } 
        }

      }
    return 0;
}
int main() {
    
    int n,m,x,y,largo;
    n = 4;
    m = 5;
    x = -1;
    y = 0;
    largo=3;
    int table[N][M];
    int solu[N][M];
    generateMoves(largo); 
    generatepos();
    generateTable(table, n, m);    
    solve_robot(table, n, m,  x, y, 1,solu);
    print(table ,n, m);
    printf("\nEl maximo es:%d\n",maximo);
	print(solu ,n, m);
    return (EXIT_SUCCESS);
}

