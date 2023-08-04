/*
 * Laboratorio 5 (2021-1), pregunta 1a y 1b usando Backtracking
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

/*
* Función que retorna la ganancia final por la selección de proyectos de acuerdo con el arreglo solution.
*/
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
* Función recursiva que, usando el algoritmo de backtracking, busca optimizar la ganancia.
*/
void optimize_profitability(int n, int stage, TProjectData *projects[], int solution[n], double *final_profit_ptr){
	int i=0;
	if (stage > n - 1) return;
	do {
		solution[stage] = i;
		if (is_valid(n, projects, solution)){
			if (stage == n-1)
				*final_profit_ptr = get_final_profit(n, projects, solution, *final_profit_ptr);
			else	
				optimize_profitability(n, stage+1, projects, solution, final_profit_ptr);
		}
		i++;
	} while (solution[stage] != 1);
	solution[stage] = -1;
}

int main(){
	int n, stage=0;
	double final_profit=0;
	printf("Ingrese la cantidad de proyectos (N): ");
	scanf("%d", &n);

	TProjectData* projects[n];
	int solution[n];

	for (int i=0; i<n; i++){		
		solution[i] = -1;
		projects[i] = (TProjectData *) malloc(sizeof(TProjectData)) ;
		projects[i]->id = i+1;
		printf("Ingrese la ganancia para el proyecto %d: ", i+1);
		scanf("%lf", &projects[i]->gain);
	}

	optimize_profitability(n, stage, projects, solution, &final_profit);
	printf("La máxima ganancia sería de %.2lf soles.\n", final_profit);

	return 0;
}