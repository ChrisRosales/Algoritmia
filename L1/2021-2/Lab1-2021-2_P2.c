#include <stdio.h>
#include <math.h>
//Christian Rosales 2021-2- P2

typedef struct{
	int cliente;
	int cant_acciones;
	double porcentaje;
} Cliente;

void cargabin(int num,int n,int cromo[]){
	int i,res;
	for(i=0;i<n;i++)cromo[i]=0; /*1 0 1 0 0*/
	i=0;
	while(num>0){
		res=num%2;
		num=num/2;
		cromo[i]=res;
		i++;	
	}
}
int main(){
	int T,P,N;
	printf("Ingrese el valor de T: ");
	scanf("%d",&T);
	printf("Ingrese el valor de P: ");
	scanf("%d",&P);
	printf("Ingrese el valor de N: ");
	scanf("%d",&N);
	Cliente arr_clientes[N];
	int i;
	for(i=0;i<N;i++){
		scanf("%d %d %lf",&arr_clientes[i].cliente,&arr_clientes[i].cant_acciones,&arr_clientes[i].porcentaje);
	}
	int opciones = (int)pow(2,N);
	int cromosoma[N];
	int j,k;
	int cantidad_actual,cantidad_solu;
	int posi_solu;
	double comision_max = 0,comision_actual,comision_anterior;
	int numero_soluciones=0;
	for(j=0;j<opciones;j++){
		cantidad_actual = 0;
		comision_actual = 0;
		cargabin(j,N,cromosoma);
		for(k=0;k<N;k++){
			cantidad_actual = cromosoma[k]*arr_clientes[k].cant_acciones + cantidad_actual;
			comision_actual = (cromosoma[k]*arr_clientes[k].cant_acciones * P)*arr_clientes[k].porcentaje + comision_actual;
		}
		
		if(cantidad_actual<=T && comision_actual>comision_max){
			numero_soluciones++;
			comision_max = comision_actual;
			cantidad_solu = cantidad_actual;
			if(numero_soluciones == 1){
				comision_anterior = comision_max;
			}
			//la posi_solu es para la pregunta B, lo siguiente es para el siguiente item
			posi_solu = j;
			//para la pregunta c piden imprimir todas las soluciones, por tal motivo se realizo los cambios necesarios
			//si es necesario para comprobarlo, poner en comentarios la posi_solu y desde la linea 75 hasta 85, pues 
			//hasta ahi la pregunta b
			printf("Solucion numero: %d \n",numero_soluciones);
			printf("Para este conjunto de datos, una solucion con la maxima ganancia debido a las comisiones seria de %.2lf dolares por un total de %d acciones.\n",comision_max,
			cantidad_solu);
			printf("Clientes que se deben de elegir para obtener la mayor ganancia son: \n");
			for(i=0;i<N;i++){
				if(cromosoma[i]==1){
					double ganancia = (arr_clientes[i].cant_acciones*P)*arr_clientes[i].porcentaje;
					printf("- El cliente %d otorga una ganancia de %.2lf dolares por comprar %d acciones. \n",arr_clientes[i].cliente,ganancia,arr_clientes[i].cant_acciones);
				}
			}
			printf("\n");
		}
	}
	printf("Para este conjunto de datos, una solucion con la maxima ganancia debido a las comisiones seria de %.2lf dolares por un total de %d acciones.\n",comision_max,
		cantidad_solu);
	printf("Clientes que se deben de elegir para obtener la mayor ganancia son: \n");
	int cromo_solu[N];
	cargabin(posi_solu,N,cromo_solu);
	for(i=0;i<N;i++){
		if(cromo_solu[i]==1){
			double ganancia = (arr_clientes[i].cant_acciones*P)*arr_clientes[i].porcentaje;
			printf("- El cliente %d otorga una ganancia de %.2lf dolares por comprar %d acciones. \n",arr_clientes[i].cliente,ganancia,arr_clientes[i].cant_acciones);
		}
	}
	return 0;
}
