/*
 * Laboratorio 2 (2021-2), pregunta 1
 * Desarrollado por Johan Baldeón
 * Datos del archivo "2021-2_L2_P1_data.txt":

200000
7
7
1 5 5100 4100 4000 5000 3000 3500 2800 1 3
2 10 4400 4000 4100 3800 4500 4200 4300 1 4
3 15 29000 31000 32000 30000 33000 35000 34000 0 1
4 45 90500 90000 91000 93000 89000 85000 92000 0 1
5 10 6800 7000 6000 6500 6800 6900 6700 1 3
6 5 10500 10000 9000 9500 11000 10800 8500 0 1
7 10 10000 9000 11000 12000 9500 10500 11500 1 2

*/
#include <stdio.h>
#include <stdlib.h>

const char *FILE_NAME = "2021-2_L2_P1_data.txt";

typedef struct ConsultantData{
	char name;
	int price;
} TConsultantData;

typedef struct PhaseData{
	int id;
	double percentage; 
	int consultants_number;	
	TConsultantData *consultants;
	int choose_economic;
	int consultants_num_to_choose;
} TPhaseData;

int read_data(int *P_ptr, int *NF_ptr, int *N_ptr, TPhaseData ***phases_ptr) { 
	int result, i, j;
	FILE *file = fopen(FILE_NAME, "r");
  	if (file == NULL) {
	  printf("El archivo no se ha podido abrir para lectura.\n");
	  return -1;
  	}	
  	if (!feof(file)) {
	    fscanf(file, "%d", P_ptr);
	    fscanf(file, "%d", NF_ptr);
		fscanf(file, "%d", N_ptr);
  	}  	
  	
  	*phases_ptr = (TPhaseData **)malloc(sizeof(TPhaseData *) * (*NF_ptr));
  	for (i=0; i < *NF_ptr; i++) {
		(*phases_ptr)[i] = (TPhaseData *) malloc(sizeof(TPhaseData));
		fscanf(file, "%d", &(*phases_ptr)[i]->id);
		fscanf(file, "%lf", &(*phases_ptr)[i]->percentage);
		(*phases_ptr)[i]->consultants_number = *N_ptr;
		
		(*phases_ptr)[i]->consultants = (TConsultantData *)malloc(sizeof(TPhaseData) * (*phases_ptr)[i]->consultants_number);
		for (j=0; j< (*phases_ptr)[i]->consultants_number; j++) {
			(*phases_ptr)[i]->consultants[j].name = 'A' + j;		
	    	fscanf(file, "%d", &(*phases_ptr)[i]->consultants[j].price);
	    }
	    fscanf(file, "%d", &(*phases_ptr)[i]->choose_economic);	    
	    fscanf(file, "%d", &(*phases_ptr)[i]->consultants_num_to_choose);	    
	}
	if (fclose(file)!=0) {
	    printf("No se ha podido cerrar el archivo.\n");
		return -1;
	} 
	return 1; 
}


int main(){
	int budget, NF, N, ini_budget, phase_number=1, i,j, total_cost=0, savings=0;
	TPhaseData ** phases;

	//Lectura de datos mediante archivo de texto
	read_data(&budget, &NF, &N, &phases);

	/* Presentación de los datos leídos */	
	/*
	printf("P = %d,  NF = %d,  N = %d \n", budget, NF, N);	
  	for (i=0; i<NF; i++){
	    printf("Fase: %d, Porc. a invertir: %.2lf, cant. de consultoras: %d, elige econ.: %d, cant. a elegir: %d\n",	     			
	    	phases[i]->id, phases[i]->percentage, phases[i]->consultants_number, 
	    	phases[i]->choose_economic, phases[i]->consultants_num_to_choose);
		for (j=0; j< phases[i]->consultants_number; j++){
			printf("%c-%d, ", phases[i]->consultants[j].name, 					
				phases[i]->consultants[j].price); 					
		}
		printf("\n\n");
	}
	*/
	/* Fin de presentación de los datos leídos */

	return 0;
}