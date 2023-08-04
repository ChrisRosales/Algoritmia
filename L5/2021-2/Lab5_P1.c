/*
 * Examen 2 (2021-1), pregunta 3a
 * Desarrollado por Johan Baldeón
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const int MAX_LEN=12;

int is_valid(int N, int solution[], int step, int digits[]){
	int i, marked_digit = 0, digits_count=1;
	int count = 1, aux_num;
	if (solution[0] == 0) return 0;
	int j;
	for (i=1; i <= step; i++){
		if (solution[i] != solution[i-1]) {
			count++;
			if (digits_count > 3 || count >4) 
				return 0;
			
			aux_num = 0;
			for ( j=digits_count-1; j>=0; j--)
				aux_num += digits[i-(j+1)] * pow(10,j);
			
			if (aux_num > 255 || (digits_count==2 && aux_num < 10) || (digits_count==3 && aux_num < 100)) {
				return 0;													
			}
			digits_count = 1;
		}
		else 
			digits_count++;
	}
	aux_num = 0;
	for ( j=digits_count-1; j>=0; j--)
		aux_num += digits[i-(j+1)] * pow(10,j);

	if (aux_num > 255 || (digits_count==2 && aux_num < 10) || (digits_count==3 && aux_num < 100)) {
		return 0;													
	}

	if ( (step == N-1 && count != 4) || (step < N-1 && count >4) || digits_count > 3) // || 
		return 0;
	else 
		return 1;
}

void print_solution(int N, int solution[], int digits[]) {
	int i=0;
	printf("%d", digits[i]);
	for (i=1; i<N; i++)
		if (solution[i] != solution[i-1]){
			printf(".");
			printf("%d", digits[i]);			
		} else 
			printf("%d", digits[i]);
	printf("\n");	
}

void get_IPs_rec(int N, int solution[], int step, int digits[]){
	int i=0;
	if (step == N) {
		print_solution(N, solution, digits);
		return;
	}
	do {
		solution[step] = i;
		if (is_valid(N, solution, step, digits)){
			get_IPs_rec(N, solution, step+1, digits);
		}
		i++;
	} while (solution[step] != 1);	
	solution[step] = -1;
}

int main(){
	char *data = (char*)malloc(sizeof(char) * (MAX_LEN+1));
	printf("Ingrese una cadena de sólo dígitos: ");
	scanf("%s", data);
	int i;
	int N = strlen(data);
	if (N <= MAX_LEN) {
		int solution[N], digits[N];
		for ( i=0; i<N; i++){
			digits[i] =  data[i]-'0'; // atoi(&data[i]);  NO FUNCIONA
			solution[i] = -1;			
		}		
		get_IPs_rec(N, solution, 0, digits);
	} else
		printf("No se pueden obtener direcciones por ser una cadena muy larga.\n");
	return 0;
}
