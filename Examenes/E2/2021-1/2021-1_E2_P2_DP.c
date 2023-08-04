/*
 * Examen 2 (2021-1), pregunta 2 usando Programación Dinámica
 * Desarrollado por Johan Baldeón
 * Datos del archivo "2021-1_E2_P2_data.txt":
10000 // T: Cantidad tope de acciones que se pueden comprar.
4 // P: Precio de una acción
6 // N: Cantidad de clientes
1 John 3000 0.1 // Id, Nombre, Cant. de acciones (Si), % de comisión (Ci)
2 Ron 3800 0.02
3 Micky 2800 0.15
4 Vicky 3500 0.05
5 Ceci 3200 0.08
6 Isa 3400 0.03

===========================================================================================================
     Agrupados de:            0           1           2           3           4           5           6
Hasta el cliente
 		0				[   0,   0] [   0,   0] [   0,   0] [   0,   0] [   0,   0] [   0,   0] [   0,   0] 
 1 -               John [   0,   0] [1200,3000] [1200,3000] [1200,3000] [1200,3000] [1200,3000] [1200,3000] 
 2 -                Ron [   0,   0] [1200,3000] [1504,6800] [1504,6800] [1504,6800] [1504,6800] [1504,6800] 
 3 -              Micky [   0,   0] [1680,2800] [2880,5800] [3184,9600] [3184,9600] [3184,9600] [3184,9600] 
 4 -              Vicky [   0,   0] [1680,2800] [2880,5800] [3580,9300] [3580,9300] [3580,9300] [3580,9300] 
 5 -               Ceci [   0,   0] [1680,2800] [2880,5800] [3904,9000] [3904,9000] [3904,9000] [3904,9000] 
 6 -                Isa [   0,   0] [1680,2800] [2880,5800] [3904,9000] [3904,9000] [3904,9000] [3904,9000] 

Para este conjunto de datos, la máxima ganancia debido a las comisiones sería de 3904.00 dólares por un total de 9000 acciones.

Clientes que se deben de elegir para obtener la mayor ganancia:
 - Cliente 1 - John, ganancia = 1200.00 dólares por comprar 3000 acciones.
 - Cliente 3 - Micky, ganancia = 1680.00 dólares por comprar 2800 acciones.
 - Cliente 5 - Ceci, ganancia = 1024.00 dólares por comprar 3200 acciones. 
 */

#include <stdio.h>
#include <stdlib.h>

const char*FILE_NAME = "2021-1_E2_P2_data.txt";

typedef struct CustomerData{
	int id;
	char name[50];
	int stocks_to_buy;
	double comission;
	double gain;
	int selected; 	//Atributo que permite marcar un cliente		
} TCustomerData;

// Estructura que permite guardar la ganancia y la cantidad de acciones, este es el tipo de dato que
// se guardaría en cada una de las celdas de la matriz de trazabilidad del algoritmo de PD. 
typedef struct GainStocksQuantity{
	double gain;
	int stocks_quantity;
}TGainStocksQuantity;

int read_data(int *T_ptr, double *P_ptr, int *N_ptr, TCustomerData *** customers_ptr) {
	int result, i, j;
	FILE *file = fopen(FILE_NAME, "r");
  	if (file == NULL) {
	  printf("El archivo no se ha podido abrir para lectura.\n");
	  return -1;
  	}	
  	if (!feof(file)) {
	    result = fscanf(file, "%d", T_ptr);	    	    
		if (result != 1) {
			printf("No se puede leer la cantidad tope de acciones que se pueden comprar.");
			return -1;
		}
	    result = fscanf(file, "%lf", P_ptr);	    	    
		if (result != 1) {
			printf("No se puede leer el precio de una acción.");
			return -1;
		}
	    result = fscanf(file, "%d", N_ptr);	    	    
		if (result != 1) {
			printf("No se puede leer la cantidad de clientes.");
			return -1;
		}		
  	}  	

  	*customers_ptr = (TCustomerData **)malloc(sizeof(TCustomerData *) * (*N_ptr));
  	for (i=0; i < *N_ptr; i++) {
		(*customers_ptr)[i] = (TCustomerData *) malloc(sizeof(TCustomerData));
		fscanf(file, "%d", &(*customers_ptr)[i]->id);	    	    
		fscanf(file, "%s", (*customers_ptr)[i]->name);	    	    
		fscanf(file, "%d", &(*customers_ptr)[i]->stocks_to_buy);
		fscanf(file, "%lf", &(*customers_ptr)[i]->comission);
		(*customers_ptr)[i]->gain = *P_ptr * (*customers_ptr)[i]->comission * (*customers_ptr)[i]->stocks_to_buy;
	}	
	if (fclose(file)!=0) {
	    printf("No se ha podido cerrar el archivo.\n");
		return -1;
	} 
	return 1; 
}

//Opcional: Función que imprime la tabla con las ganancias luego de haber aplicado el algoritmo de programación dinámica
void print_dp_matrix(int max_grouped_of, TGainStocksQuantity *G[][max_grouped_of+1], TCustomerData* customers[]) {

	printf("\n.      Agrupados de:  ");
	for (int j=0; j<=max_grouped_of; j++)
		printf("%12d", j);

	printf("\nHasta el cliente\n");
	for (int i=0; i<=max_grouped_of; i++){
		if (i==0) printf("\t0\t\t");
		else
			printf("%2d - %18s ", customers[i-1]->id, customers[i-1]->name);
		for (int j=0; j<=max_grouped_of; j++)
			printf("[%4.0lf, %4d]", G[i][j]->gain, G[i][j]->stocks_quantity);
		printf("\n");
	}

}

/*
Función que, usando el algoritmo de programación dinámica, busca optimizar la ganancia para el corredor de bolsa.
						 | {0, 0}										, i == 0 || j == 0
						 |
						 | {G[i-1,j], stocks[i-1,j] }					, stocks_i > MAX_STOCKS						 

{G[i,j], stocks[i,j]} = <
						 | {max(G[i-1,j], G[i,j-1]), Acciones del máximo}, stocks[i-1, j-1] + stocks_i > MAX_STOCKS
						 |
						 | {max(G[i-1,j], G[i,j-1], G[i-1, j-1] + g_i), Acciones del máximo}, stocks[i-1, j-1] + stocks_i <= MAX_STOCKS
*/

TGainStocksQuantity* optimize_profitability_dp(int T, double P, int N, int max_grouped_of, 
						TGainStocksQuantity * G[][max_grouped_of+1], TCustomerData* customers[]) {

	TGainStocksQuantity* result = (TGainStocksQuantity *) malloc(sizeof(TGainStocksQuantity));
	int i, j;
	for (i=0; i<=N; i++)
		for (j=0; j<=max_grouped_of; j++)
			if (i==0 || j ==0){
				G[i][j] = (TGainStocksQuantity *) malloc(sizeof(TGainStocksQuantity));
				G[i][j]->gain = 0;
				G[i][j]->stocks_quantity = 0;
			} else 
				if (customers[i-1]->stocks_to_buy > T)
					G[i][j]= G[i-1][j];
				else
					if (G[i-1][j-1]->stocks_quantity + customers[i-1]->stocks_to_buy > T){
						if (G[i-1][j]->gain > G[i][j-1]->gain)
							G[i][j] = G[i-1][j]; 
						else
							G[i][j] = G[i][j-1]; 
					} else {
						if (G[i-1][j]->gain > G[i][j-1]->gain && G[i-1][j]->gain > G[i-1][j-1]->gain + customers[i-1]->gain)
							G[i][j] = G[i-1][j];
						else if (G[i][j-1]->gain > G[i-1][j]->gain && G[i][j-1]->gain > G[i-1][j-1]->gain + customers[i-1]->gain)
							G[i][j] = G[i][j-1];
						else {							
							G[i][j] =  (TGainStocksQuantity*)malloc(sizeof(TGainStocksQuantity));
							G[i][j]->gain = G[i-1][j-1]->gain + customers[i-1]->gain;
							G[i][j]->stocks_quantity = G[i-1][j-1]->stocks_quantity + customers[i-1]->stocks_to_buy;
						}
					}	
	result->gain = G[i-1][j-1]->gain;
	result->stocks_quantity = G[i-1][j-1]->stocks_quantity;
	return result;
}							

/*
* Parte c: Función que va marcando los clientes como seleccionados cada vez que hay un cambio en la misma columna
* de la matriz de ganancias.
*/
void select_customers_and_show(int N, int max_grouped_of, TGainStocksQuantity *G[][max_grouped_of+1], 
								TCustomerData*customers[]){
	int i=N,j=max_grouped_of;
	while (i>0){
		if (G[i][j]->gain == G[i-1][j-1]->gain && G[i][j]->gain == G[i-1][j]->gain && G[i][j]->gain ==G[i][j-1]->gain) {
			j--;
		} else 
			if (G[i][j] != G[i-1][j]) {
				customers[i-1]->selected = 1;
				j--;
				i--;
			} else {
				i--;				
			}
	}	
	
	printf("Clientes que se deben de elegir para obtener la mayor ganancia:\n");
	for (i=0; i<N; i++)
		if (customers[i]->selected == 1)
			printf(" - Cliente %d - %s, ganancia = %.2lf dólares por comprar %d acciones.\n",
					customers[i]->id, customers[i]->name, customers[i]->gain, customers[i]->stocks_to_buy);
}

int main(){
	TCustomerData **customers;
	int T, N, max_grouped_of; // N: Cantidad de clientes, T: Cantidad tope de acciones que se pueden comprar.
	double P; // P: Precio de una acción.

	read_data(&T, &P, &N, &customers);
	max_grouped_of = N;
	TGainStocksQuantity* G[N+1][max_grouped_of + 1];

	TGainStocksQuantity* result = optimize_profitability_dp(T, P, N, max_grouped_of, G, customers); 

	//Opcional: Impresión de la tabla con las ganancias luego de haber aplicado el algoritmo de programación dinámica
	print_dp_matrix(max_grouped_of, G, customers);	

	printf("\nPara este conjunto de datos, la máxima ganancia debido a las comisiones sería de %.2lf dólares por un total de %d acciones.",
			result->gain, result->stocks_quantity);

	//Parte c: Invocamos a una función que selecciona los clientes y los muestra
	select_customers_and_show(N, max_grouped_of, G, customers);
	return 0;
}