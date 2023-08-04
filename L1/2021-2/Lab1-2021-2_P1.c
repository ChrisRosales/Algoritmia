#include <stdio.h>
#include <math.h>
#define MAX 16

void carga_bin(int n,int num,int cromo[MAX]){
	int i, j, residuo;
	for (j=0; j<MAX; j++){
		cromo[j] = 0;
	}
	i = 0;
	while (num>0){
		residuo = num % 2;
		num = num/2;
		cromo[i] = residuo;
		i++;
	}
}

int main(){
	int congelador[] = {7,9,8,18,17,12,6,7,14,11,10,15,19,8,12,11};
	int n=16, pedido=23, i, j;
	int combinaciones = (int)pow(2,n);
	int cromo[n];
	int solucion[n];
	int nSolucion=0, pesoParcial;
	
	for (i=0; i<combinaciones; i++){
		carga_bin(n,i,cromo);
		/*Recorremos el cromo*/
		pesoParcial = 0;
		for (j=0; j<n; j++){
			if (cromo[j]==1){
				pesoParcial += congelador[j];
			}
		}
		if (pesoParcial==pedido){
			/*Impresion*/
			nSolucion++;
			printf("Resultado %d: ",nSolucion);
			carga_bin(n,i,solucion);
			for (j=0;j<n;j++){
				if (solucion[j]==1){
					printf("%d ",congelador[j]);
				}			
			}
			printf("Ubicaciones: ");
			for (j=0;j<n;j++){
				if (solucion[j]==1){
					if (j%4<2){
						printf("I");
					}
					else {
						printf("D");
					}
					if (j%2==0){
						printf("A");	
					}
					else{
						printf("B");
					}
					printf("%d ",(j/4)+1);
				}			
			}
			printf("\n");
		}
	}
	return 0;
}
