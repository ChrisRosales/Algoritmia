#include <stdio.h>
#include <stdlib.h>

int flag=0;
//Falta parte c

int findUbi(int N,int M,int sol[],int ubi[],int prod[],int x){
	int i,j;
	//Impresion de solucion
	if(x==N){
		printf("{");
		for(i=0;i<M;i++) printf(" %d ",sol[i]);
		printf("}\n");
		return 1;
	} 
	for(i=0;i<M;i++){
		if(sol[i]+prod[x]<=ubi[i]){
			sol[i]+=prod[x];			
			if(findUbi(N,M,sol,ubi,prod,x+1)) flag=1;
			sol[i]-=prod[x];
		}
	}
	return 0;
}

int main(){
	//Ingreso de datos:
	int i,N,M;
	printf("Ingrese la cantidad de productos(N): ");
	scanf("%d",&N);
	int prod[N];
	printf("Ingrese la agrupacion:\n");
	for(i=0;i<N;i++) scanf("%d",&prod[i]);
	printf("Ingrese la cantidad de ubicaciones(M): ");
	scanf("%d",&M);
	int ubi[M];
	printf("Ingrese la capacidad de cada ubicacion:\n");
	for(i=0;i<M;i++) scanf("%d",&ubi[i]);
	int solUb[M];
	for(i=0;i<M;i++) solUb[i]=0;
	int solProd[N];
	for(i=0;i<N;i++) solProd[i]=prod[i];
	printf("%-15s\n","Ubicaciones");
	findUbi(N,M,solUb,ubi,prod,0);
	
	if(!flag) printf("No se encontro ubicacion");
	return 0;
}
