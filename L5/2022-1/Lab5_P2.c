#include <stdio.h>
#define MAX 20
#define MAX_MOV 8

int movimientos[8][2];
int contador = 0;

void generarMovimientos(){
	/*Arriba, abajo, izquierda, derecha, no precisamente en ese orden*/
	movimientos[0][0] = 1; movimientos[0][1] = 0;
	movimientos[1][0] = 0; movimientos[1][1] = -1;
	movimientos[2][0] = 0; movimientos[2][1] = 1;
	movimientos[3][0] = -1; movimientos[3][1] = 0;
	
	/*Ahora las diagonales*/
	movimientos[4][0] = 1; movimientos[4][1] = 1;
	movimientos[5][0] = -1; movimientos[5][1] = -1;
	movimientos[6][0] = 1; movimientos[6][1] = -1;
	movimientos[7][0] = -1; movimientos[7][1] = 1;
}

void imprime(char tablero[MAX][MAX],int n,int m){
	int i, j;
	for (i=0;i<n;i++){
		for (j=0; j<m; j++){
			if (tablero[i][j]=='0'){
				printf("  ");
			}
			else {
				printf("%c ", tablero[i][j]);				
			}
		}
		printf("\n");
	}		
}

void inicializarTablero(char tablero[MAX][MAX]){
	int i, j;
	for (i=0;i<MAX;i++){
		for (j=0; j<MAX; j++){
			tablero[i][j] = '0';
		}
	}
}

int validarMovimiento(char tablero[MAX][MAX],int x,int y,int n,int m, char solucion[MAX][MAX]){
	if (x<n && y<m && x>=0 && y>=0 && tablero[x][y] != '*' && solucion[x][y]=='0'){
		return 1;
	}
	else {
		if (tablero[x][y]=='*')
			solucion[x][y] = '*';
		return 0;
	}
}

void colocarMinas(char tablero[MAX][MAX]){
	tablero[0][4] = '*';
	tablero[2][2] = '*';
	tablero[4][1] = '*';
	tablero[4][2] = '*';
	tablero[4][4] = '*';
	tablero[5][1] = '*';
	tablero[5][2] = '*';
	tablero[5][4] = '*';
	tablero[6][1] = '*';
	tablero[6][3] = '*';
	tablero[7][0] = '*';
	tablero[7][1] = '*';
	tablero[7][2] = '*';
	tablero[7][3] = '*';
}

int encontrarCaminos(char tablero[MAX][MAX],int n,int m,int x,int y,int xFinal,int yFinal,char solucion[MAX][MAX],char paso){
	int i, nuevoX, nuevoY;
	if (x==xFinal && y==yFinal){
		contador++;
		imprime(solucion,n,m);
		printf("\n");
		if (contador==20){
			return 1;	
		}
		else {
			return 0;
		}
	}
	for (i=0; i<MAX_MOV; i++){
		nuevoX = x + movimientos[i][0];
		nuevoY = y + movimientos[i][1];
		if (validarMovimiento(tablero,nuevoX,nuevoY,n,m,solucion)){
			solucion[nuevoX][nuevoY] = paso + 1;
		//	imprime(solucion,n,m);
			if (encontrarCaminos(tablero,n,m,nuevoX,nuevoY,xFinal,yFinal,solucion,paso+1))
				return 1;
			solucion[nuevoX][nuevoY] = '0';
		}
	}
	return 0;
}

int main(){
	char tablero[MAX][MAX];
	char solucion[MAX][MAX];
	int n=9, m=5, xFinal= 8, yFinal = 4;
	char paso = 'A';
	generarMovimientos();
	inicializarTablero(tablero);
	colocarMinas(tablero);
	inicializarTablero(solucion);
	imprime(tablero,n,m);
	solucion[0][0] = 'A';
	encontrarCaminos(tablero,n,m,0,0,xFinal,yFinal,solucion,paso);
	return 0;
}
