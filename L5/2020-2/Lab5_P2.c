#include <stdio.h>

int buscaSuma(int menores[4],int n,int presupuesto){
	int pd[n+1][presupuesto+1];
	int i,j, diferencia;
	for (i=0;i<=n;i++){
		pd[i][0] = 0;
	}
	for (j=0;j<=presupuesto;j++){
		pd[0][j] = 0;
	}
	
	for (j=1; j<=presupuesto;j++){
		for (i=1; i<=n; i++){
			if (pd[i-1][j] == 1){
				pd[i][j] = 1;
			}
			else {
				if (menores[i-1]==j){
					pd[i][j] = 1;
				}
				else {
					if (menores[i-1]>j){
						pd[i][j] = 0;
					}
					else {
						diferencia = j -menores[i-1];
						pd[i][j] = pd[i-1][diferencia];
					}
				}
			}
		}
	}

	for (i=1; i<=n;i++){
		for (j=1; j<=presupuesto; j++){
			printf("%d ",pd[i][j]);
		}
		printf("\n");
	}

	for (j=presupuesto; j>=0; j--){
		for (i=0; i<=n; i++){
			if (pd[i][j]==1){
				return j;
			}
		}
	}
	
	return 0;
}

int main(){
	int menores[4] = {2,3,3,5};
	int n = 4;
	int presupuesto = 12; /*quitando al paneton que vale 8*/
	printf("El presupuesto mayor es: %d", 8 + buscaSuma(menores,n,presupuesto));
	return 0;
}
