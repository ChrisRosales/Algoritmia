/*
 * Laboratorio 5 (2021-1), pregunta 2 de optimización de la rentabilidad utilizando Backtracking.
 * Desarrollado por Johan Baldeón
 *
 * Por ejemplo, si:
 * 		N=4
 * 		T=7000
 *  				 E1 	 E2   	 E3   	 E4
 * Cant. acciones  	 3000 	 4000 	 2000 	 5000
 * % Rentabilidad     0.5  	  0.6     0.1  	  0.9
 * Precio/acción      3.0     2.0     4.0  	  1.9
 * ---------------------------------------------- 
 * Rentabilidad   13500.0 12800.0  8800.0 18050.0
 *
 * Las acciones que se deben comprar corresponden a las siguientes empresas:
 *		E3 con 2000 acciones y una rentabilidad de 8800.00
 *		E4 con 5000 acciones y una rentabilidad de 18050.00
 * Son 7000 acciones en total a comprar.
 * La máxima rentabilidad sería de 26850.00 soles.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Operation {
	int id;
	char company_name[50];
	double price;	
	double profitability;
	int quantity;	
} TOperation;

/*
* Función que valida si la cantidad de acciones que se comprarían no excede el límite máximo T
* El parámetro solution[] corresponde al arreglo con la selección de las operaciones de compra,
* donde si está con 0 significa que no se ha elegido y 1 representa que sí se elige dicha operación.
* El parámetro operations[] corresponde al arreglo de punteros a estructuras que representan operaciones. 
*/
int is_valid(int N, int T, int solution[], TOperation * operations[]){
	int total_stocks = 0;
	for (int i = 0; i < N; ++i)
	{
		if (solution[i] == 1){
			total_stocks += operations[i]->quantity;
		}
	}
	return total_stocks <= T;
}

/*
* Función que actualiza el arreglo final_solution con la selección de las operaciones de compra 
* que se deberían de concretar, también retorna la cantidad total de acciones a comprar y el monto
* de rentabilidad total por las acciones que se comprarían.
*/
void update_solution(int N, int solution[], TOperation * operations[], int final_solution[], 
					int *stocks_quantity, double *final_profit){
	double total_profit = 0;
	int total_stocks = 0, i;
	for (i=0; i< N; i++){
		if (solution[i] == 1){
			total_profit += (operations[i]->price * operations[i]->quantity)*(1+operations[i]->profitability);
			total_stocks += operations[i]->quantity;
		}
	}
	if (total_profit > *final_profit){
		for (i=0; i< N; i++)
			final_solution[i] = solution[i];
		*final_profit = total_profit;
		*stocks_quantity = total_stocks;	 
	}
}

/*
* Función recursiva que, usando el algoritmo de backtracking, busca encontrar la combinación de operaciones 
* de compra de acciones de las empresas que busca optimizar rentabilidad considerando el límite de acciones 
* total a comprar.
*/
void optimize_profitability_rec(int N, int T, int solution[], int step, TOperation * operations[], 
								int final_solution[], int *stocks_quantity, double *final_profit){
	int i=0;
	if (step == N) return;
	do {
		solution[step] = i;
		if (is_valid(N,T,solution, operations)){
			if (step == N - 1)
				update_solution(N, solution, operations, 
					final_solution, stocks_quantity, final_profit);
			else
				optimize_profitability_rec(N, T, solution, step+1, 
					operations, final_solution, stocks_quantity,
					final_profit);
		}
		i++;
	} while (solution[step] != 1);	
	solution[step] = -1;
}

void show_report(int N, TOperation * operations[], int final_solution[], int stocks_quantity, double final_profit){
	printf("Las acciones que se deben comprar corresponden a las siguientes empresas:\n");
	for (int i=0; i<N; i++){
		if (final_solution[i] == 1){
			printf("\t%s con %d acciones y una rentabilidad de %.2lf\n",
			 operations[i]->company_name, operations[i]->quantity, 
			 operations[i]->quantity * operations[i]->price * (1 + operations[i]->profitability));
		}
	}
	printf("Son %d acciones en total a comprar.\n", stocks_quantity);
	printf("La máxima rentabilidad sería de %.2lf soles.\n", final_profit);
}

int main(){	
	int step = 0, i, N, T;	
	printf("Ingrese la cantidad de empresas (N): ");
	scanf("%d", &N);
	printf("Ingrese la cantidad de acciones máxima a comprar en total (T): ");
	scanf("%d", &T);

	int solution[N], final_solution[N], stocks_quantity;
	double final_profit=0;
	TOperation* operations[N];

	for (i=0; i<N; i++){
		solution[i] = final_solution[i] = -1;
	 	operations[i] = (TOperation *) malloc(sizeof(TOperation));	 	
	 	operations[i]->id = i;
	 	printf("Ingrese el nombre de la empresa %d: ", i+1);
	 	scanf("%s",operations[i]->company_name);
	 	printf("Ingrese la cantidad de acciones (C%d) que se deben comprar de la empresa %d: ", i+1, i+1);
	 	scanf("%d",&operations[i]->quantity);
	 	printf("Ingrese el porcentaje de rentabilidad (R%d) por las acciones de la empresa %d: ", i+1, i+1);
	 	scanf("%lf",&operations[i]->profitability);
	 	printf("Ingrese el precio de una acción de la empresa %d: ", i+1);
	 	scanf("%lf",&operations[i]->price);
	}

	optimize_profitability_rec(N, T, solution, step, operations, final_solution,
				&stocks_quantity, &final_profit);
	show_report(N, operations, final_solution, stocks_quantity, final_profit);
	
	return 0;
}