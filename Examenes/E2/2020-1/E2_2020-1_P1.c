#include <stdio.h>
#include <stdlib.h>
#define max 50

void iniciar_tabla (int arr[max][max], int N, int M) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			arr[i][j] = 0;
		}
	}
}

void imprimir(int tabla[max][max], int N, int M) {
	int i, j;
	printf("\n");
	for (i = 0; i < N; i ++) {
		for (j = 0; j < M; j++) {
			printf("%d ",tabla[i][j]);
		}
		printf("\n");
	}
}

int m[8][2];

void generar_movimientos() { // limites del robotin
	m[0][0] =  0;	m[0][1] =  1;
	m[1][0] =  1;	m[1][1] =  0;
	m[2][0] =  0;	m[2][1] = -1;
	m[3][0] = -1;	m[3][1] =  0;
	m[4][0] =  1;	m[4][1] =  1;
	m[5][0] = -1;	m[5][1] = -1;
	m[6][0] =  1;	m[6][1] = -1;
	m[7][0] = -1;	m[7][1] =  1;
}

int es_valido (int tabla[max][max], int N, int M, int x, int y) {
	if (tabla[x][y] == 3) return 0; // al inicio no se puede colocar un palet
	if (tabla[x][y] != 0) return 0; // no se puede colocar un palet si ya hay otro
	int i, j;
	int p, q;
	for (i = 0; i < 8; i++) {
		p = x+m[i][0];
		q = y+m[i][1];
		if (p < N && p >= 0 && q < M && q >= 0) { // verificamos que el palet este dentro del tablero
			if (tabla[p][q] != 0 && tabla[p][q] != 3) return 0; // si hay otro palet alrededor no es una pos valida
		}
		
	}
	return 1;
}

int tablero[max][max];
int k = -1; // inicio max
int cont; // contador de palets

void guardar_max(int tabla[max][max], int N, int M) {
	int i, j;
	for (i = 0; i < N; i++) { // limpiamos el tablero
		for (j = 0; j < M ;j++) {
			tablero[i][j] = 0;
		}
	}
	for (i = 0; i < N; i++) { // guardamos una solucion que contenga el max en un tablero aux
		for (j = 0; j < M ;j++) {
			tablero[i][j] = tabla[i][j];
		}
	}
}

int robotin (int tabla[max][max], int N, int M, int x, int y) {
	if (y > M-1) { 
		//imprimir(tabla,N,M);
		if (cont > k) {
			k = cont; // actualizamos max
			guardar_max(tabla,N,M);
		}
		return 0; // generemos todas las posibles distribuciones	
	}
	int i;
	if (x < N) {
		for (i = x; i < N; i++) {
			if (es_valido(tabla,N,M,i,y)) {				
				tabla[i][y] = 1; 
				cont++;				
				if (robotin(tabla,N,M,i+1,y)) return 1;
				cont--;
				tabla[i][y] = 0; 
			}
		}
	}
	if (robotin(tabla,N,M,0,y+1)) return 1;	
	return 0;
}

int main () {
	int N, M;
	int tabla[max][max];
	printf("Ingresar las dimensiones del almacen: ");
	scanf("%d %d",&N,&M);
	iniciar_tabla(tabla,N,M);
	generar_movimientos();
	tabla[0][0] = 3; // colocamos el inicio como entrada
	robotin(tabla,N,M,0,0);
	printf("\nCantidad maxima de palets: %d\n",k);
	imprimir(tablero,N,M);
	return 0;
}
