#include <stdio.h>

int obtenerMaximasUnidades(int almacen[6][6],int n,int m,int p,int q){
	int solucion[p][q], i, j;
	/*Calculamos la fila inicial en solucion*/	
	solucion[0][0] = almacen[0][0];
	for (j=1; j<q; j++){
		solucion[0][j] = almacen[0][j] + solucion[0][j-1];
	}
	/*Calculamos la columna inicial en solucion*/
	for (i=1;i<p;i++){
		solucion[i][0] = almacen[i][0] + solucion[i-1][0];
	}
	
	/*Calculamos para el resto de la solucion*/
	for (i=1; i<p; i++){
		for (j=1; j<q; j++){
			if (solucion[i-1][j]>solucion[i][j-1]){
				solucion[i][j] = solucion[i-1][j] + almacen[i][j];
			}
			else {
				solucion[i][j] = solucion[i][j-1] + almacen[i][j];
			}
		}
	}
	return solucion[p-1][q-1];
}

int main(){
	int almacen[6][6] = {{1,2,9,1,2,3},
						 {5,1,7,1,2,1},
						 {1,7,1,3,8,1},
						 {2,2,6,1,2,2},
						 {3,6,9,5,1,5},
						 {1,1,4,1,9,1}};
	int p=6, q=6, n=6, m=6;
	int unidadesMaxima = obtenerMaximasUnidades(almacen,n,m,p,q);
	printf("La solucion a esta disposicion es de %d unidades",unidadesMaxima);	
	return 0;
}
