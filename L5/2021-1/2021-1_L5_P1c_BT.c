/*
 * Laboratorio 5 (2021-1), pregunta 1c usando Backtracking
 * Desarrollado por Johan Baldeón
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct ProjectData{
	int id;
	double gain;
} TProjectData;

int is_valid (int n, TProjectData *projects[], int solution[]){
	for (int i=0; i<n; i++)
		if ( solution[i] == 1 &&  ( (i+1<n && solution[i+1] == 1) || 
									(i+2<n && solution[i+2] == 1 ) )
		   ) 
			return 0;		
	return 1;	
}

double get_final_profit (int n,  TProjectData *projects[], int solution[], double previous_profit) {
	double total_profit = 0;
	for (int i=0; i<n; i++)
		if (solution[i] == 1 )
			total_profit += projects[i]->gain;
	if (total_profit > previous_profit)
		return total_profit;
	else
		return previous_profit;	
}

/*
* Función que actualiza el arreglo final_solution con la selección de los proyectos que se deberían 
* de ejecutar, también retorna la ganancia final por dicha selección.
*/
void update_solution(int n, TProjectData *projects[], int solution[n], int final_solution[n], 
					double *final_profit_ptr){
	double total_profit = 0;
	for (int i=0; i<n; i++){
		if (solution[i] == 1)
			total_profit += projects[i]->gain;
	}
	if (total_profit > *final_profit_ptr){
		for (int i=0; i<n; i++)
			final_solution[i] = solution[i];
		*final_profit_ptr = total_profit;
	}
}

/*
* Función recursiva que, usando el algoritmo de backtracking, busca encontrar la combinación de proyectos 
* que busca optimizar la ganancia considerando los proyectos a seleccionar.
*/
void optimize_profitability(int n, int stage, TProjectData *projects[], int solution[n], 
							int final_solution[n], double *final_profit_ptr){
	int i=0;
	if (stage > n - 1) return;
	do {
		solution[stage] = i;
		if (is_valid(n, projects, solution)){
			if (stage == n-1)
				update_solution(n, projects, solution, final_solution, final_profit_ptr);				
			else	
				optimize_profitability(n, stage+1, projects, solution, final_solution, final_profit_ptr);
		}
		i++;
	} while (solution[stage] != 1);
	solution[stage] = -1;
}

void show_report(int n, TProjectData *projects[], int solution[n], double final_profit){
	printf("Los proyectos que se deben de elegir son: \n");
	for (int i=0; i <n; i++)
		if (solution[i] == 1)
			printf("\t%d con %.2lf K de ganancia.\n",projects[i]->id, projects[i]->gain);
	printf("La máxima ganancia sería de %.2lf K soles.\n", final_profit);	
}

int main(){
	int n, stage=0;
	double final_profit=0;
	printf("Ingrese la cantidad de proyectos (N): ");
	scanf("%d", &n);
	TProjectData* projects[n];
	int solution[n], final_solution[n];
	for (int i=0; i<n; i++){		
		solution[i] = final_solution[i] = -1;		
		projects[i] = (TProjectData *) malloc(sizeof(TProjectData)) ;
		projects[i]->id = i+1;
		printf("Ingrese la ganancia para el proyecto %d: ", i+1);
		scanf("%lf", &projects[i]->gain);
	}

	optimize_profitability(n, stage, projects, solution, final_solution, &final_profit);
	show_report(n, projects, final_solution, final_profit);
	return 0;
}