#include <stdio.h>
#define MAX 100

int llena(int n, int m, int max, int min, int pal, int fil, int campo[MAX][MAX], int *flag) {
	int i, cont = 0;
	if (max < min || max > n) {
		(*flag) = 0;
		return 0;
	}
	for (i = 0; i < max; i++) { 
		if (campo[fil][i] == 0) {
			campo[fil][i] = 5;
			cont++;
		}
	}
	cont += llena(n,m,max-1,min,pal,fil+1,campo,flag);
	for (i = 0; i < max; i++) {
		if (campo[m-(fil+1)][i] == 0) {
			campo[m-(fil+1)][i] = 5;
			cont++;
		}
		if (pal <= cont) (*flag) = 1;
		else (*flag) = 0;
	}
	return cont;
}

int main () {
	int i, j, flag, pal;
	int max, min, m, n, cont;
	int campo[MAX][MAX];
	printf("Ingrese las dimensiones del almacen: ");
	scanf("%d %d",&m,&n);
	printf("Ingrese la cantidad maxima y minima de ubicaciones a considerar: ");
	scanf("%d %d",&max,&min);
	printf("Ingrese la cantidad de palets: ");
	scanf("%d",&pal);
	for (i = 0; i < m; i++) { 
		for (j = 0; j < n; j++) {
			scanf("%d",&campo[i][j]);
		}
	}
	cont = llena(n,m,max,min,pal,0,campo,&flag);
	for (i = 0; i < m; i++) { 
		for (j = 0; j < n; j++) {
			printf(" %d",campo[i][j]);
		}
		printf("\n");
	}
	printf("Ubicaciones: %d   Se pueden ubicar los productos: %d",cont,flag);
	return 0;
}
