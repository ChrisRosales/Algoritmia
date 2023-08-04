#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

const int VEHICLES_TYPE_NUM=4;
const double SERVICE_KMS=5000;
const char *FILE_NAME = "2021-1_L1_P1_data.txt";

typedef struct VehicleTypeData {
	int id;
	int loading_capacity;
	int performance_km_gal;
	int maintenance_cost;
	int vehicles_number;
} TVehicleTypeData;

int read_data(int *M_ptr, int *D_ptr, int *P_ptr, TVehicleTypeData ** vehicles_type) {
	int result, i, j;
	FILE *file = fopen(FILE_NAME, "r");
  	if (file == NULL) {
	  printf("El archivo no se ha podido abrir para lectura.\n");
	  return -1;
  	}	
  	if (!feof(file)) {
	    result = fscanf(file, "%d", M_ptr);	    	    
		if (result != 1) {
			printf("No se puede leer la carga total M de toneladas.");
			return -1;
		}
		result = fscanf(file, "%d", D_ptr);
		if (result != 1) {
			printf("No se puede leer la distancia D entre dos ciudades.");
			return -1;
		}		
		result = fscanf(file, "%d", P_ptr);
		if (result != 1) {
			printf("No se puede leer el precio de combustible en soles.");
			return -1;
		}		
  	}  	
  	for (i=0; i < VEHICLES_TYPE_NUM; i++) {
		vehicles_type[i] = (TVehicleTypeData *) malloc(sizeof(TVehicleTypeData));
	    result = fscanf(file, "%d %d %d %d %d", &vehicles_type[i]->id, 
	    				&vehicles_type[i]->loading_capacity, &vehicles_type[i]->performance_km_gal, 
	    				&vehicles_type[i]->maintenance_cost, &vehicles_type[i]->vehicles_number);
		if (result != 5) {
			printf("No se pueden leer los datos del tipo de vehículo.");
			return -1;
		}
	}	
	if (fclose(file)!=0) {
	    printf("No se ha podido cerrar el archivo.\n");
		return -1;
	} 
	return 1; 
}

void fill_final_chromosome(int size, int chromosome[], int final_chromosome[]) {
	int i;
	for (i=0; i<size; i++){
		final_chromosome[i] = chromosome[i];
	}
}

void calc_totals(TVehicleTypeData **vehicles_types, int n, int M, int D, int P, int chromosome[],
				int *total_weight, double *total_cost){
	int i, j, accum_vehicles, type_index;
	double prop_dist = D / SERVICE_KMS;
	*total_weight = 0;
	*total_cost = 0;
	for (i=0; i<n; i++){
		accum_vehicles=0;
		for (j=0; j<VEHICLES_TYPE_NUM; j++){
			accum_vehicles += vehicles_types[j]->vehicles_number;
			if (i < accum_vehicles){
				type_index = j;
				break;
			}
		}
		*total_weight += chromosome[i] * vehicles_types[type_index]->loading_capacity;
		*total_cost += chromosome[i] * (vehicles_types[type_index]->maintenance_cost * prop_dist +
							P * (1.0 * D) / vehicles_types[type_index]->performance_km_gal);
	}

}

int is_valid(TVehicleTypeData **vehicles_types, int n, int M, int D, int P, int chromosome[]){
	int i, j, total_weight=0, type_index, accum_vehicles;
	double prop_dist = D / SERVICE_KMS;

	for (i=0; i<n; i++){
		if (chromosome[i]){
			accum_vehicles=0;
			for (j=0; j < VEHICLES_TYPE_NUM; j++) {
				accum_vehicles+= vehicles_types[j]->vehicles_number;
				if (i< accum_vehicles){
					type_index = j;
					break;
				}
			}
			total_weight += vehicles_types[type_index]->loading_capacity;
		}
	}
	if (total_weight < M)
		return 0;
	else
		return 1;
}

void fill_chromosome(int n, int size, int chromosome[]){
	int i=size-1,j;
	while ( n != 0) {
		chromosome[i] = n%2;
		n /= 2;
		i--;
	}
	for (j=0; j<=i; j++)
		chromosome[j] = 0;
}

void show_selected_vehicle_types(TVehicleTypeData **vehicles_types, int n, int D, int P, 
								int final_chromosome[]){
	int i, j, prev_num=0, accum_vehicles;
	double maintenance_cost, prop_dist = D / SERVICE_KMS, fuel_cost;

	for (i=0; i < VEHICLES_TYPE_NUM;  i++){
		accum_vehicles = 0;
		maintenance_cost =0;
		fuel_cost = 0;
		for (j=prev_num; j< prev_num + vehicles_types[i]->vehicles_number; j++){
			if (final_chromosome[j] == 1){
				accum_vehicles++;
				maintenance_cost += vehicles_types[i]->maintenance_cost * prop_dist;
				fuel_cost += P *(1.0 *D) / vehicles_types[i]->performance_km_gal;
			}
		}
		prev_num = j;
		if (accum_vehicles > 0)
			printf(" - Tipo %d, cant. de vehículos: %d, mantenimiento (S/.): %.2lf, combustible (S/.): %.2lf \n",
					vehicles_types[i]->id, accum_vehicles, maintenance_cost, fuel_cost);
	}
}

int main() {
	int M, D, P, result, i, n=0;
	TVehicleTypeData **vehicles_types;
	vehicles_types = (TVehicleTypeData **) malloc(sizeof(TVehicleTypeData *) * (VEHICLES_TYPE_NUM));
	result = read_data(&M, &D, &P, vehicles_types);

	for (i=0; i<VEHICLES_TYPE_NUM; i++)
		n += vehicles_types[i]->vehicles_number;

	int lim = pow(2, n);
	int chromosome[n];
	int final_chromosome[n];
	int total_weight=0;
	double total_cost=0;
	int lower_total_cost = INT_MAX;

	for (i=0; i < lim; i++){
		fill_chromosome(i, n,chromosome);
		if (is_valid(vehicles_types, n, M, D, P, chromosome)) {
			calc_totals(vehicles_types, n, M, D, P, chromosome, &total_weight, &total_cost);
			if (total_cost <= lower_total_cost){
				fill_final_chromosome(n, chromosome, final_chromosome);
				lower_total_cost = total_cost;
			}
		}
	}
	show_selected_vehicle_types(vehicles_types, n, D, P, final_chromosome);

	return 0;
}

