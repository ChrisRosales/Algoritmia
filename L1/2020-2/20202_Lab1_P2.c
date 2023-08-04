#include <stdio.h>
#include <math.h>
#define MAX 8

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
	int maquinas[8][4] = {{1,40,150,1},
						 {2,20,80,1},
						 {3,100,300,2},
						 {4,100,150,2},
						 {5,50,80,2},
						 {6,10,50,3},
						 {7,50,120,3},
						 {8,50,150,3},						 						 						 						 						 
						};
	int cromo[8], n=8;
	int resultado[8];
	int combinaciones = pow(2,n);
	int presupuesto = 250, i, j, solucion;
	int gananciaMaxima = 0, gananciaParcial, costoParcial, cantTipo1, cantTipo2, cantTipo3;
	for (i=0;i<combinaciones;i++){
		carga_bin(n,i,cromo);
		costoParcial = 0;
		gananciaParcial = 0;
		cantTipo1 = cantTipo2 = cantTipo3 = 0;
		for (j=0; j<n; j++){
			if (cromo[j]==1){
				costoParcial = costoParcial + maquinas[j][1];
				gananciaParcial = gananciaParcial + maquinas[j][2];
				if (maquinas[j][3]==1)
					cantTipo1++;
				else {
					if (maquinas[j][3]==2)
						cantTipo2++;
					else
						cantTipo3++;
				}
			}
		}
		if (costoParcial<=presupuesto && gananciaParcial>gananciaMaxima && cantTipo1 && cantTipo2 && cantTipo3){
			gananciaMaxima = gananciaParcial;
			solucion = i;
		}
	}
	carga_bin(n,solucion,resultado);
	printf("Maquinas: ");
	costoParcial = 0;
	gananciaParcial = 0;
	for (j=0; j<n; j++){		
		if (resultado[j]==1){
			printf("%d, ",maquinas[j][0]);
			costoParcial = costoParcial + maquinas[j][1];
			gananciaParcial = gananciaParcial + maquinas[j][2];
		}
	}
	printf("Costo de Maquinas %d y una ganancia de %d",costoParcial,gananciaParcial);
	return 0;	
}
