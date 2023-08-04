#include <stdio.h>
#include <stdlib.h>


#define MAX_MOV 4
#define MAX_INI 8
#define N 100
#define M 100
//Como soy alumno que esta llevando el curso por 2da vez (esta es mi bika )
//Revisando mi paideia encontre un problema similar
//el cual es robot cortador de listones
//por tal motivo se procedio a realizarlo de manera similar
//Paideia 2022-1 semana 14

int map[MAX_MOV][2];
int mov[MAX_INI][2];
int cant_rectangulos=0;
//movimientos:
void generar_movimientos(int largo){
    largo--;
    map[0][0] =  largo; map[0][1] =  0;
    map[1][0] =  0; map[1][1] = -1*largo;
    map[2][0] =  0; map[2][1] =  largo;
    map[3][0] = -1*largo; map[3][1] =  0;
}
//posiciones, basado en los problemas resuelto del profesor allasi :
void generar_posiciones(){
    mov[0][0] =  1; mov[0][1] =  0;
    mov[1][0] =  0; mov[1][1] = -1;
    mov[2][0] =  0; mov[2][1] =  1;
    mov[3][0] = -1; mov[3][1] =  0;
    
    mov[4][0] =  1; mov[4][1] =  1;
    mov[5][0] = -1; mov[5][1] = -1;
    mov[6][0] =  1; mov[6][1] = -1;
    mov[7][0] = -1; mov[7][1] =  1;
}
//inicializamos el campo de futbol en 0:
void generar_campo_futbol(int a[N][M], int n,int m) {
    int i, j;
    for ( i = 0; i < n; i++ )
        for ( j = 0; j < m; j++ )
            a[i][j] = 0;
}
//mostramos el campo de futbol:
void mostrar_campo(int a[N][M], int n,int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }
}

int is_valid(int a[N][M], int x, int y, int n,int m) {
    if ( x < n && y < m && x >= 0 && y >= 0 && a[x][y] == 0)  
	//Se realiza una validacion para que no se salga del tablero
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
//basandonos en el problema del profesor cueva realizado el ciclo pasado
//nos guiamos
int robot_podadora(int a[N][M], int n, int m, int x, int y,
	int nMov,int solu[N][M]) 
{
    int i,j,new_x,new_y,mov_x,mov_y;
	int p,q; 	

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
                //validamos:
                if(valida_recorrido(a,new_x,new_y,mov_x,mov_y,n,m)){
                    marca(a,new_x,new_y,mov_x,mov_y,n,m,nMov);
                    if(nMov>cant_rectangulos){
                        cant_rectangulos = nMov;
                        generar_campo_futbol(solu,n,m);
                        for ( p = 0; p < n; p++ )
                                for ( q = 0; q < m; q++ )
                                    solu[p][q] =a[p][q] ;
                    }
                    if(robot_podadora(a,n,m,mov_x,mov_y,nMov+1,solu))
                        return 1;
                    marca(a,new_x,new_y,mov_x,mov_y,n,m,0);
                }
            } 
        }

      }
    return 0;
}
int main() {
    int n,m,x,y,c;
    printf("Ingrese el valor de n m y c: ");
    scanf("%d %d %d",&n,&m,&c);
    x = -1;
    y = 0;
    int campo_futbol[N][M];
    int solu[N][M];
    generar_movimientos(c); 
    generar_posiciones();
    generar_campo_futbol(campo_futbol, n, m);    
    robot_podadora(campo_futbol, n, m,  x, y, 1,solu);
    printf("Para los datos: n=%d m=%d y c=%d \n",n,m,c);
    printf("Tabla inicial: \n");
    mostrar_campo(campo_futbol ,n, m);
    printf("Tabla solucion: \n");
	mostrar_campo(solu ,n, m);
	printf("\nEl total de rectangulos es: %d\n",cant_rectangulos);
    return (EXIT_SUCCESS);
}
