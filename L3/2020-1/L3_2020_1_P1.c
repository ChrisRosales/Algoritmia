/*
	Propuesto y desarrollado por Johan Baldeón
	Tramas de datos de productos para ingresar por teclado a la DB:
	{	
	77512345678920015990000040005060,
	77512341234560009690000400050030,
	77512349876540009990000300039035,
	77512346969690001990003000100010,
	77512346669990014990000110010020,
	77512349696960006990000200026025
	}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 32
#define GTIN_DIGITS 13
#define PRICE_DIGITS 7
#define STOCK_DIGITS 5
#define MIN_STOCK_DIGITS 4
#define DISCOUNT_DIGITS 3
const char * MIN_STREAM = "00000000000000000000000000000000"; 

/* Prototipos */
int get_stock_diff(char * stream);
double get_final_price(char * stream);
int searchStockDiffNaturalMinIndex(char *db[], int left, int right);
void quick_sort_by_stock_diff(char *db[], int left_limit, int right_limit);
void regroup(char *db[], int size, int *offers_num);
void merge(char *db[], int ini, int mid, int end);
void merge_sort_for_offers(char *db[], int ini, int end);
void show_offers(char *db[], int ini, int end);

int main(){
	int n, i, offers_num;
	printf("Ingrese la cantidad de productos a registrar: ");
	scanf("%d", &n);
	char *db[n];
	for (i=0; i<n; i++){
		db[i] = malloc(MAX_DIGITS * sizeof(char)+1);
		printf("Ingrese la trama del producto %d (32 dígitos): ", i+1 );
		scanf("%s", db[i]);
	}
	regroup(db, i, &offers_num);
	for (i=0; i<n; i++){
		printf("Trama %d: %s\n", i+1, db[i]);
	}	

	printf("Número de ofertas: %d\n", offers_num);	

	merge_sort_for_offers(db, 0, offers_num-1);
	/*
	for (i=0; i<offers_num; i++){
		printf("Trama del producto %d: %s\n", i+1, db[i] );
	}	
	*/
	show_offers(db, 0, offers_num-1);

	for (i=0; i<n; i++){
		free (db[i]);
	}		
}

void regroup(char *db[], int size, int *offers_num){
	quick_sort_by_stock_diff(db, 0, size-1);
	*offers_num = searchStockDiffNaturalMinIndex(db, 0, size-1);
}

int search_min(int array[], int ini, int n){
	int medio, left_min, right_min;
	medio = (ini+n+1)/2;

	if (medio==0 || medio == ini){
		if (array[ini] < array[n]) return array[ini];
		else return array[n];
	} else {
		left_min = search_min(array, ini, medio-1);
		right_min = search_min(array, medio, n);
		if (left_min < right_min) return left_min;
		else return right_min;
	}	
}

int searchStockDiffNaturalMinIndex(char *db[], int left, int right){
	int mid, left_min_index, right_min_index, diff1, diff2;
	mid = (left+right+1)/2;

	if (mid==0 || mid == left){
		diff1 = get_stock_diff(db[left]);
		diff2 = get_stock_diff(db[right]);
		if ((diff1>=0 && diff2>=0 && diff1 < diff2) ||
			(diff1>=0 && diff2 <0) )
			return left;		
		else if (diff1 < 0 && diff2 < 0)
			return right+1;
		else 
			return right;
	} else {
		left_min_index = searchStockDiffNaturalMinIndex(db, left, mid-1);
		right_min_index = searchStockDiffNaturalMinIndex(db, mid, right);
		diff1 = get_stock_diff(db[left_min_index]);
		diff2 = get_stock_diff(db[right_min_index]);
		if ((diff1>=0 && diff2>=0 && diff1 < diff2) ||
			(diff1>=0 && diff2 <0)
			)
			return left_min_index;
		else if (diff1 < 0 && diff2 < 0)
			return right_min_index + 1;
		else
		 	return right_min_index;
	}
}

void quick_sort_by_stock_diff(char *db[], int left_limit, int right_limit){
	int left, right, pivot;
	char *aux = malloc(sizeof(char) * MAX_DIGITS + 1);
	left = left_limit;
	right = right_limit;
	pivot = get_stock_diff(db[(left + right)/2]);

	do {
		while (get_stock_diff(db[left]) < pivot && left < right_limit) left++;
		while (pivot < get_stock_diff(db[right]) && right > left_limit) right--;
		if (left < right){
			strcpy(aux, db[left]);
			strcpy(db[left], db[right]);
			strcpy(db[right], aux);
			left++;
			right--;
		} else if (left == right) {
			left++;
			right--;			
		}
	} while ( left <= right );
	if (left_limit < right) quick_sort_by_stock_diff(db, left_limit, right);
	if (left < right_limit) quick_sort_by_stock_diff(db, left, right_limit);
}

int get_stock_diff(char * stream){
	char *str_stock = malloc(STOCK_DIGITS*sizeof(char));
	char *str_min_stock = malloc(MIN_STOCK_DIGITS*sizeof(char));;
	strncpy (str_stock, stream + GTIN_DIGITS + PRICE_DIGITS, STOCK_DIGITS);
	strncpy (str_min_stock, stream + GTIN_DIGITS + PRICE_DIGITS + STOCK_DIGITS, MIN_STOCK_DIGITS);
	return atoi(str_stock) - atoi(str_min_stock);
}

double get_final_price(char * stream){
	char *str_price = malloc(PRICE_DIGITS*sizeof(char));
	char *str_discount = malloc(DISCOUNT_DIGITS*sizeof(char));
	strncpy (str_price, stream + GTIN_DIGITS, PRICE_DIGITS);
	strncpy (str_discount, stream + GTIN_DIGITS + PRICE_DIGITS + STOCK_DIGITS + MIN_STOCK_DIGITS, DISCOUNT_DIGITS);
	double price = atoi(str_price)/100.0;
	int discount = atoi(str_discount);
	double final_price = price * ((100 - discount) /100.0);
	//printf("Trama: %s, precio=%.2f, descuento=%d, P.F.=%.3f\n", stream, price, discount, final_price);	
	return final_price;
}

void merge(char *db[], int ini, int mid, int end) {
	//printf("merge: ini = %d, mid = %d, end = %d\n", ini, mid, end);
	int l1, l2, i;
	int p=0, q=0;

	l1 = mid - ini + 1;
	l2 = end - mid;

	char *leftArray[l1+1];
	char *rightArray[l2+1];

	for (i = ini; i<=mid; i++){
		leftArray[i-ini] = (char *)malloc(sizeof(char)*MAX_DIGITS + 1);
		strcpy(leftArray[i-ini], db[i]);
	}
	//printf("MIN_STREAM = %s\n", MIN_STREAM);
	leftArray[l1] = (char *)malloc(sizeof(char)*MAX_DIGITS + 1);
	strcpy(leftArray[l1], MIN_STREAM);
	//printf("leftArray[l1=%d] = %s\n", l1, leftArray[l1]);

	for (i=mid+1; i<=end; i++) {
		rightArray[i-mid-1] = (char *)malloc(sizeof(char)*MAX_DIGITS + 1);
		strcpy(rightArray[i-mid-1], db[i]);	
	}
	rightArray[l2] = (char *)malloc(sizeof(char)*MAX_DIGITS + 1);
	strcpy(rightArray[l2], MIN_STREAM);
	//printf("rightArray[l2=%d] = %s\n", l2, rightArray[l2]);

	for (i=ini; i<=end; i++){
		//if (strcmp(leftArray[p],rightArray[q]) < 0 ){
		if ( get_final_price(leftArray[p]) > get_final_price(rightArray[q]) ){
			strcpy(db[i], leftArray[p++]);
		}
		else {
			strcpy(db[i], rightArray[q++]);
		}
	}
}

void merge_sort_for_offers(char *db[], int ini, int end){	
    if(ini == end)
        return;

    int mid = (ini + end)/2;
    merge_sort_for_offers(db, ini, mid);
    merge_sort_for_offers(db, mid+1, end);
    //printf("Begin merge_sort_for_offers: ini = %d, mid=%d, end=%d\n", ini, mid, end);

    merge(db, ini, mid, end);	
}

void show_offers(char *db[], int ini, int end){
	int i;
	printf("Los productos del pasillo de ofertas son:\n");
	for (i=ini; i<=end; i++){
		char *str_discount = malloc(DISCOUNT_DIGITS*sizeof(char));
		strncpy (str_discount, db[i] + GTIN_DIGITS + PRICE_DIGITS + STOCK_DIGITS + MIN_STOCK_DIGITS, DISCOUNT_DIGITS);
		printf("\t%s | %d descuento | P.F.: S/. %.3lf\n", db[i], atoi(str_discount), get_final_price(db[i]));
	}	
}
