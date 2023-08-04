#include <stdio.h>

//codigo del profe Cueva del problema de MaxContagios:
int max(int a,int b){
	return (a>b)?a:b;
}
int max3(int a,int b,int c){
	return max(max(a,b),c);
}
//Aqui se cambia por el "==" pues estamos buscando que se repita el peso
int mezcla(int arr[],int ini,int medio,int fin){
	int i,cizq=0,cder=0;
	
	for(i=medio;i>ini;i--){
		if(arr[i]==arr[i-1])cizq++;
		else
			break;
	}
	for(i=medio;i<fin;i++){
		if(arr[i+1]==arr[i])cder++;
		else
		 	break;
	}
	
	return cder+cizq+1;
	
}

int intervalomax(int arr[],int ini,int fin,int peso,int arr_dias_consecutivos[], int dias[]){
	int medio,izq,der,centro;
	if(ini==fin){
		if(arr[ini]==peso){
			arr_dias_consecutivos[ini] = dias[ini];
		}
		return 1;
	} 
	medio = (ini+fin)/2;
	izq=intervalomax(arr,ini,medio,peso,arr_dias_consecutivos,dias);
	der=intervalomax(arr,medio+1,fin,peso,arr_dias_consecutivos,dias);
	centro=mezcla(arr,ini,medio,fin);
	
	return max3(izq,der,centro);
} 
//hasta aqui es su solucion y se procedera a realizar ciertas modificaciones para que 
//muestre el intervalo de dias.

//nuestra funcion que nos devuelva el menor dia, inspirida en el problema del maximo
int menor_peso_arreglo(int arr_dias[],int pos_ini,int pos_fin){
	int medio;
	
	medio = (pos_ini+pos_fin)/2;
	
	if(pos_ini==pos_fin)
		return arr_dias[pos_ini];
		
	if(pos_fin-pos_ini==1){
		if(arr_dias[pos_fin]<arr_dias[pos_ini])	
			return arr_dias[pos_fin];
		else	
			return arr_dias[pos_ini];
	}	
	if(arr_dias[medio]<arr_dias[medio+1] && medio+1<=pos_fin)
		return menor_peso_arreglo(arr_dias,pos_ini,medio);
	else
		return menor_peso_arreglo(arr_dias,medio+1,pos_fin);		
}


int main(){
	int n,i;
	//lectura de datos:
	printf("Ingrese la cantidad de dias: ");
	scanf("%d",&n);
	int arr_dias[n];
	printf("Ingrese los datos de los dias del paciente: \n");
	for(i=0; i<n; i++){
		scanf("%d",&arr_dias[i]);
	}
	//Datos utilizados:
	// 30 
	// 98 95 92 89 91 92 89 89 92 93 94 92 91 90 88 88 88 89 90 91 88 88 90 90 92 89 90 88 90 91
		
	int dias[n];
	for(i=0;i<n; i++){
		dias[i] = i+1;
	}
	/*for(i=0; i<n; i++){
		printf("%d ",dias[i]);
	}*/
	int peso_menor;
	//aqui se invoca una funcion recursiva, y la complejidad hasta entoces es log n
	peso_menor = menor_peso_arreglo(arr_dias,0,n-1);
	
	printf("El menor peso fue de %d.\n",peso_menor);
	
	int arr_dias_consecutivos[n];
	for(i=0;i<n;i++){
		arr_dias_consecutivos[i]=0;
	}
	//aqui se invoca otra funcion recursiva, y la complejidad aumenta en log n
	int num_dias_max = intervalomax(arr_dias,0,n-1,peso_menor,arr_dias_consecutivos,dias);
	//se le resta uno porque en el problema del Minsa siempre contaba 1 demás, entonces para que este conforme se debería restar 1 a la vez
	printf("El menor peso se repite: %d veces\n",num_dias_max);
	
	printf("El rango de dias en que lo obtuvo fue del:  "); //15 al 17.
	int cont=0;
	for(i=0;i<n;i++){
		if(arr_dias_consecutivos[i]!=0 &&cont<num_dias_max){
			printf("%d ",arr_dias_consecutivos[i]);
			cont++;
		}
	}
	
	return 0;
}
