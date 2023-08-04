/*
 * Laboratorio 2 (2021-1), pregunta 2
 * Desarrollado por Johan Baldeón usando Divide y Vencerás
 * Datos del archivo "2021-1_L2_P2_data.txt":

36
7
6
2
1 3 4 5 6 7 1 2 1
2 3 4 5 7 1 2 6 1
3 3 4 5 2 1 6 8 0
4 3 4 5 6 2 1 9 0
5 3 4 5 7 8 9 2 1
6 3 4 5 8 9 7 6 1

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const char *FILE_NAME = "2021-1_L2_P2_data.txt";

typedef struct CompanyData{
	char name;
	int stock_price;
} TCompanyData;

typedef struct DayData{
	int id;	
	int companies_number;
	TCompanyData *companies;
	int tendence;
} TDayData;

int read_data(int *P_ptr, int *C_ptr, int *T_ptr, int *B_ptr, TDayData ***days_ptr) { 
	int result, i, j;
	FILE *file = fopen(FILE_NAME, "r");
  	if (file == NULL) {
	  printf("El archivo no se ha podido abrir para lectura.\n");
	  return -1;
  	}	
  	if (!feof(file)) {
	    result = fscanf(file, "%d", P_ptr);
		if (result != 1) {
			printf("No se puede leer el presupuesto P.");
			return -1;
		}
	    result = fscanf(file, "%d", C_ptr);	    	    
		if (result != 1) {
			printf("No se puede leer la cantidad C de empresas.");
			return -1;
		}		
		result = fscanf(file, "%d", T_ptr);
		if (result != 1) {
			printf("No se puede leer la cantidad T de días.");
			return -1;
		}		
		result = fscanf(file, "%d", B_ptr);
		if (result != 1) {
			printf("No se puede leer la cantidad inicial B de empresas.");
			return -1;
		}		
  	}  	
  	
  	*days_ptr = (TDayData **)malloc(sizeof(TDayData *) * (*T_ptr));
  	for (i=0; i < *T_ptr; i++) {
		(*days_ptr)[i] = (TDayData *) malloc(sizeof(TDayData));
		fscanf(file, "%d", &(*days_ptr)[i]->id);
		(*days_ptr)[i]->companies_number = *C_ptr;
		
		(*days_ptr)[i]->companies = (TCompanyData *)malloc(sizeof(TCompanyData) * (*days_ptr)[i]->companies_number);
		for (j=0; j< (*days_ptr)[i]->companies_number; j++) {
			(*days_ptr)[i]->companies[j].name = 'A' + j;		
	    	fscanf(file, "%d", &(*days_ptr)[i]->companies[j].stock_price);
	    }
	    fscanf(file, "%d", &(*days_ptr)[i]->tendence);	    
	}
	if (fclose(file)!=0) {
	    printf("No se ha podido cerrar el archivo.\n");
		return -1;
	} 
	return 1; 
}

void asc_merge(TCompanyData *companies, int ini, int mid, int end){
	int i, p=0, q=0;
	TCompanyData left_array[mid-ini+2];
	TCompanyData right_array[end-mid+1];

	for (i =ini; i<=mid; i++)
		left_array[i-ini] = companies[i];
	left_array[i-ini].stock_price = INT_MAX;

	for (i=mid+1; i <= end; i++)
		right_array[i-mid-1] = companies[i];
	right_array[end-mid].stock_price = INT_MAX;

	for(i=ini; i <= end; i++)
		if (left_array[p].stock_price < right_array[q].stock_price)
			companies[i] = left_array[p++];
		else
			companies[i] = right_array[q++];
}	

void desc_merge(TCompanyData *companies, int ini, int mid, int end){
	int i, p=0, q=0;
	TCompanyData left_array[mid-ini+2];
	TCompanyData right_array[end-mid+1];

	for (i =ini; i<=mid; i++)
		left_array[i-ini] = companies[i];
	left_array[i-ini].stock_price = -1;

	for (i=mid+1; i <= end; i++)
		right_array[i-mid-1] = companies[i];
	right_array[end-mid].stock_price = -1;

	for(i=ini; i <= end; i++)
		if (left_array[p].stock_price > right_array[q].stock_price)
			companies[i] = left_array[p++];
		else
			companies[i] = right_array[q++];
}	

void merge_sort(TCompanyData *companies, int ini, int end, int is_asc){
	if (ini == end) return;
	int mid = (ini + end) / 2;
	merge_sort(companies, ini, mid, is_asc);
	merge_sort(companies, mid+1, end, is_asc);
	if (is_asc)
		asc_merge(companies, ini, mid, end);
	else
		desc_merge(companies, ini, mid, end);
}

int calc_and_show_selected_companies_stocks(TCompanyData *companies, int budget, 
							int selected_companies_number, int company_number, int total_to_buy){	
	if (selected_companies_number < company_number) return total_to_buy;	
	total_to_buy += companies[company_number-1].stock_price;
	if (total_to_buy > budget) {
		total_to_buy -= companies[company_number-1].stock_price;
	} else  {
		printf("(%c) %d, ", companies[company_number-1].name, 
						  companies[company_number-1].stock_price);
		total_to_buy = calc_and_show_selected_companies_stocks(companies, budget,
										selected_companies_number, company_number+1, total_to_buy); 
	}
	return total_to_buy;
}

void stocks_purchase(TDayData ** days, int day_number, int C, int T, int B, int budget, int ini_budget) {//, int total_to_buy){
	int company_number=1; 
	int total_to_buy=0; 
	char tendence = days[day_number-1]->tendence ? '-' : '+';
	if (day_number > T) return;
	if (tendence == '-') 
		merge_sort(days[day_number-1]->companies, 0, C-1, 0);
	else
		merge_sort(days[day_number-1]->companies, 0, C-1, 1);

	printf("\nDía %d: ($ %c) Presupuesto = %d, ",  day_number, tendence, budget);
	total_to_buy = calc_and_show_selected_companies_stocks(days[day_number-1]->companies, budget, B, company_number, total_to_buy);
	budget -= total_to_buy;
	if (budget <= 0 || (budget > 0 && total_to_buy == 0)){
		printf("\nSólo ha podido comprar acciones hasta el día %d, tiene %d dólares en acciones y le ha quedado %d dólar(es) de presupuesto.\n", 
				day_number-1, ini_budget - budget, budget);
		return;
	} else {
		if (days[day_number]->tendence) B++;
		else B--;
		stocks_purchase(days, day_number+1, C, T, B, budget, ini_budget);
	}
}

int main(){
	int budget, C, T, B, ini_budget, day_number=1, i,j; //, total_to_buy=0;
	TDayData ** days;
	/*
	// Lectura de datos por consola
	printf("P: ");
	scanf("%d", &budget);
	printf("C: ");
	scanf("%d", &C);
	printf("T: ");
	scanf("%d", &T);
	printf("B: ");
	scanf("%d", &B);
	days = (TDayData **)malloc(sizeof(TDayData *) * T);
	for (int i=0; i<T; i++){
		days[i] = (TDayData *) malloc(sizeof(TDayData));
		days[i]->companies_number = C;
		days[i]->companies = (TCompanyData *)malloc(sizeof(TCompanyData) * days[i]->companies_number);
		printf("Día %d. Ingrese los precios de cada acción de las %d empresas: ", i+1, C);
		for (int j=0; j<C; j++){			
			scanf("%d", &days[i]->companies[j].stock_price);
			days[i]->companies[j].name = 'A' + j;
		}
		printf("Ingrese la tendencia de tipo de cambio (0: Sube, 1: Baja) para el día %d: ", i+1);
		scanf("%d", &days[i]->tendence);
	}
	*/

	//Lectura de datos mediante archivo de texto
	read_data(&budget, &C, &T, &B, &days);

	/* Presentación de los datos leídos */	
	/*
	printf("P = %d,  C = %d,  T = %d  B = %d\n", budget, C, T, B);	
  	for (i=0; i<T; i++){
	    printf("Día: %d, cant. de empresas: %d, tendencia: %d ", 
	    	days[i]->id, days[i]->companies_number, days[i]->tendence);
		for (j=0; j< days[i]->companies_number; j++){
			printf("%c-%d, ", (days[i]->companies + j)->name, 					
				days[i]->companies[j].stock_price); 					
		}
		printf("\n");
	}
	*/
	/* Fin de presentación de los datos leídos */

	ini_budget = budget;
	stocks_purchase(days, day_number, C, T, B, budget, ini_budget);
	return 0;
}