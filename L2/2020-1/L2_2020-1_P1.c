#include <stdio.h>
#define max 100

void carga(int x, int y, int N, int M, int matriz[max][max]) { 
	int i;
	if (x >= N || x >= M) return;
	if (x == M-1 && y == N-1) printf("%d ",matriz[y][x]);
	for (i = x; i < M-1; i++) printf("%d ",matriz[y][i]);
	for (i = y; i < N-1; i++) printf("%d ",matriz[i][M-1]);
	for (i = M-1; i > x; i--) printf("%d ",matriz[N-1][i]);
	for (i = N-1; i > y; i--) printf("%d ",matriz[i][x]);
	carga(x+1,y+1,N-1,M-1,matriz);
}

int main () {
	int i, j, N, M;
	int alm[max][max];
	printf("Ingrese las dimensiones del almacen: ");
	scanf("%d %d",&N,&M);
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			scanf("%d",&alm[i][j]);
		}
	}
	carga(0,0,N,M,alm);
	return 0;
}
