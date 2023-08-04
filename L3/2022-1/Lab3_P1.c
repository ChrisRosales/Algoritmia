#include <stdio.h>
int max(int a,int b){
	return (a>b)?a:b;
}
int max3(int a,int b,int c){
	return max(max(a,b),c);
}
int mezcla(int arr[],int ini,int medio,int fin){
	int i,cizq=0,cder=0;
	
	for(i=medio;i>ini;i--){
		if(arr[i]>arr[i-1])cizq++;
		else
			break;
	}
	for(i=medio;i<fin;i++){
		if(arr[i+1]>arr[i])cder++;
		else
		 	break;
	}
	
	return cder+cizq+1;
	
}


int intervalomax(int arr[],int ini,int fin){
	int medio,izq,der,centro;
	if(ini==fin) return 1;
	
	medio = (ini+fin)/2;
	izq=intervalomax(arr,ini,medio);
	der=intervalomax(arr,medio+1,fin);
	centro=mezcla(arr,ini,medio,fin);
	
	return max3(izq,der,centro);
}


int main(){
	int n=8;
	int arr[]={10,20,15,10,12,10,13,18};
	
	printf("El maximo es:%d",intervalomax(arr,0,n-1));
	
	
	return 0;
}
