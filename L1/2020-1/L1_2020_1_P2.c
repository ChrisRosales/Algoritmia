#include <stdio.h>
#include <string.h>
#include <math.h>

/*
* Elaborado por Johan Baldeón
*/

#define MAX 40
int arrSalariesPerHour[] = {16, 19, 22};

int main(){

	//Declaracion de variables:
	int t, MPxH, i;
	int aux[MAX],rpta[MAX];
	
	//Lectura:
	printf("Ingrese la cantidad de trabajadores (t): ");
	scanf("%d",&t);
	printf("Ingrese la meta de marcas de productos por hora (MPxH): ");
	scanf("%d",&MPxH);

	/* Matriz de roles, velocidades de reposición, salario por hora 
		y bonificaciones por marca */
	int matRVSB [t][4], rol, mph, bpm; 


	for(int i = 0;i<t;i++){
		printf("Trabajador %d. Ingrese el rol (1. Despach., 2. Cajero, 3. Supervisor), velocidad de reposición (mph) y bonificación por marca (bpm): ", i+1);
		scanf("%d %d %d", &rol, &mph, &bpm);
		matRVSB[i][0] = rol;
		matRVSB[i][1] = mph;
		matRVSB[i][2] = arrSalariesPerHour[rol-1];
		matRVSB[i][3] = bpm;
	}

	//Algoritmo
	/* El costo mínimo inicial será la suma de todos los costos si se
		aceptan a todos los postulantes
	*/
	int min_cost=0;
	for (int i=0; i<t; i++){
		min_cost += matRVSB[i][2] + matRVSB[i][1] * matRVSB[i][3];
	}
	int max_goal=0;

	//Vamos a trabajar con las pow(2,m) posibilidades 
	for(int i = 0; i < (1<<t); i++){
		
		//Limpiamos el arreglo
		memset(aux,0,sizeof(aux));
		
		int cost = 0, goal = 0;
		for(int j=0; j<t; j++){

			int bin = (1<<j) & i;
			if(bin!=0){
				//Hemos seleccionado un elemento:
				aux[j] = 1;

				cost += matRVSB[j][2] + matRVSB[j][1] * matRVSB[j][3];
				goal += matRVSB[j][1];
			} 
		}

		if (goal>=MPxH){
			//En este caso es posible que sea respuesta!
			if ( (cost < min_cost) || (cost == min_cost && goal > max_goal) ){
				//Guardamos la respuesta
				for(int j =0; j<t; j++){
					rpta[j] = aux[j];
				}
				min_cost = cost;
				max_goal = goal;
			}
		}
	}

	printf("Los trabajadores seleccionados son: ");
	for(int i =0;i < t; i++){
		if(rpta[i]==1){
			printf("%d ",i+1);
		}
	}

	printf("\tEl costo mínimo total es %d\n", min_cost);

	return 0;
}

