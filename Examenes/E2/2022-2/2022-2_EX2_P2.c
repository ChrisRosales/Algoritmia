#include <stdio.h>
//bubble sort del profe cueva seman 2:
void ordenar_arreglo_bub(int arr[],int n){
	int i,j,aux;	
	for(i=0;i<=n-2;i++){
		for(j=0;j<=n-2-i;j++){
			if(arr[j+1]<arr[j]){
				aux = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = aux;
			}
		}
	}
}
//funcion con dp, similar a lo realizado en lab5 :
void encontrar_posibles_combinaciones(int num_buscado[], int num_principal[],int n,int m,int *formas_distintas){
	//arreglo de soluciones:
	int dp_formas[n+1][m+1];
	//variables auxiliares, para evitar modificar de forma erronea el arreglo de soluciones 
	int forma_anterior;
	int suma_parcial_formas;
	//variables de indice:
	int i,j;
	//inicializamos, de una manera similar del lab5:
	for(i=0;i<n+1;i++){
		dp_formas[i][0] = 0;
	}
	for(j=0;j<m+1;j++){
		dp_formas[0][j] = 1;
	}
	//a partir de aqui podemos iniciar el pd, se supone que como estamos almacenando soluciones
	//en teoria la utlima deberia devolvernos la solucion que buscamos:
	for(i=1;i<n+1;i++){
		for(j=1;j<m+1;j++){
			//aqui se evalua cuando son diferentes y se procede a evaluar:
			if(num_buscado[i-1] != num_principal[j-1]){
				forma_anterior = dp_formas[i][j-1];
				dp_formas[i][j] = forma_anterior;												
			} else{
				suma_parcial_formas = dp_formas[i-1][j-1]+dp_formas[i][j-1];
				dp_formas[i][j] = suma_parcial_formas;
			}
			//en teoria sale para todos los casos, gracias a Dios 
		}
	}
	//almacenamos la mejor solucion:
	(*formas_distintas) = dp_formas[n][m];
}
int main(){
	int m,n,i;
	int formas_distintas=0;
	m=6;
	n=8;
	//Caso 2, Saliooo 
	int arr_num_buscado[m];
	int arr_num_principal[n];
	printf("Datos del numero a buscar: ");
	//9 5 3 3 4 6
	//9 5 3 3 4 6 
	for(i=0;i<m;i++){
		scanf("%d",&arr_num_buscado[i]);
	}
	printf("Datos del numero principal: ");
	//9 5 3 3 3 4 6
	//9 5 5 3 3 3 4 6
	for(i=0;i<n;i++){
		scanf("%d",&arr_num_principal[i]);
	}
	//impresion de los numeros originalmente:
	printf("Arreglos iniciales: \n");
	printf("Numero a buscar: ");
	for(i=0;i<m;i++){
		printf("%d",arr_num_buscado[i]);
	}
	printf("\nDentro del numero: ");
	for(i=0;i<m;i++){
		printf("%d",arr_num_principal[i]);
	}
	//ordenamos los arreglos:
	//de manera ascendente:
	ordenar_arreglo_bub(arr_num_buscado,m);
	ordenar_arreglo_bub(arr_num_principal,n);
	//impresion de los arreglos ordenado
	printf("\nArreglos ordenados: \n");
	printf("Numero a buscar: ");
	for(i=0;i<m;i++){
		printf("%d",arr_num_buscado[i]);
	}
	printf("\nDentro del numero: ");
	for(i=0;i<m;i++){
		printf("%d",arr_num_principal[i]);
	}
	//en la funcion se pasa de manera inversa el m y n, pues cometi un error al momento de crearlo:
	encontrar_posibles_combinaciones(arr_num_buscado,arr_num_principal,m,n,&formas_distintas);
	//impresion:
	printf("\nEl numero buscado se puede armar de %d formas distintas",formas_distintas);
	/*
	m=6
	n=7
	9 5 3 3 4 6
	9 5 3 3 3 4 6
	*/
	
	/*
	m=6
	n=8
	9 5 3 3 4 6 
	9 5 5 3 3 3 4 6
	*/
	return 0;
}
