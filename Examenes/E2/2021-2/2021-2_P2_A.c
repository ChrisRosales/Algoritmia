#include <stdio.h>

int calcularMinimo(int a,int b,int c){
	int menor;
	if (a<=b && a<=c){
		menor = a;
	}
	else {
		if (b<=a && b<=c){
			menor = b;
		}
		else {
			menor = c;
		}
	}
	return menor;
}

int evaluarMenorDistancia(int almacen[4][4],int n,int m){
	int solucion[n+1][m+1], i, j;
	/*Inicializamos en 0 la fila y columna que hemos agregado*/
	for (i=0;i<n+1;i++){
		solucion[i][0] = 0;
	}
	for (j=0;j<m+1;j++){
		solucion[0][j] = 0;
	}
	
	/*Partiendo del 0,0 vamos a analizar el camino de la misma fila*/
	solucion[1][1] = 0;
	for (j=2;j<m+1;j++){
		solucion[1][j] = abs(almacen[0][j-1] - almacen[0][j-2]) + solucion[1][j-1];
	}
	
	/*Partiendo del 0,0 vamos a analizar el camino de la misma columna*/
	for (i=2; i<n+1; i++){
		solucion[i][1] = abs(almacen[i-1][0] - almacen[i-2][0]) + solucion[i-1][1];
	}
	
	/*Ahora si viene la accion*/
	for (i=2;i<n+1;i++){
		for (j=2; j<m+1; j++){
			int distArriba = abs(almacen[i-1][j-1] - almacen[i-2][j-1]) + solucion[i-1][j];
			int distIzquierda = abs(almacen[i-1][j-1] - almacen[i-1][j-2]) + solucion[i][j-1];
			int distDiagonal = abs(almacen[i-1][j-1] - almacen[i-2][j-2]) + solucion[i-1][j-1];
			int minimo = calcularMinimo(distArriba,distIzquierda,distDiagonal);
			solucion[i][j] = minimo;
		}
	}
	
	for (i=1;i<n+1;i++){
		for (j=1; j<m+1; j++){
			printf("%d ",solucion[i][j]);
		}
		printf("\n");
	}
	
	return solucion[n][m];
}

int main(){
	int almacen[4][4] = {{4,2,2,4},
						 {1,4,6,8},
						 {2,5,9,1},
						 {1,3,11,12}};
	int n=4, m=4, menorDistancia;
	menorDistancia = evaluarMenorDistancia(almacen,n,m);
	printf("La menor distancia es %d\n",menorDistancia);
	return 0;
}
