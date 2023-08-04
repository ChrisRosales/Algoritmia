#include <stdio.h>
#include <math.h>
#define MAX 4

void cargabin(int num,int n,int cromo[]){
	int res,i;
	for(i=0;i<n;i++) cromo[i]=0;
	i=0;
	while(num>0){
		res = num%2;
		num = num/2;
		cromo[i]=res;
		i++;
	}
}

void imprimesol(int almacen[][MAX],int i,int j,int k,int n){
	int cromo[n],p;
	cargabin(i,n,cromo);
	for(p=0;p<n;p++){
		if(cromo[p])
			printf("%d ",almacen[0][p]);
	}
	printf("\n");
	cargabin(j,n,cromo);
	for(p=0;p<n;p++){
		if(cromo[p])
			printf("%d ",almacen[1][p]);
	}
	printf("\n");
		cargabin(k,n,cromo);
	for(p=0;p<n;p++){
		if(cromo[p])
			printf("%d ",almacen[2][p]);
	}
	printf("\n");	
	
}


int main(){
	int i,j,l,k,peso,cont,mvalor=0,mcomb;
	int capacidad=20,n = 4,m=5;
	
	int almacen[][MAX]={{2,5,6,10},
						{7,8,15,3},
						{11,9,6,4}};
	
	int cromo1[n],cromo2[n],cromo3[n];
	int opcion= (int)pow(2,n);
	
	for(i=0;i<opcion;i++)
		for(j=0;j<opcion;j++)
			for(k=0;k<opcion;k++){
				peso = 0;
				cont=0;
				cargabin(i,n,cromo1);
				cargabin(j,n,cromo2);  
				cargabin(k,n,cromo3);
				for(l=0;l<n;l++){
					if(cromo1[l]){
						peso=peso+almacen[0][l];
						cont++;
					}
				} 
				for(l=0;l<n;l++){
					if(cromo2[l]){
						peso=peso+almacen[1][l];
						cont++;
					}
				} 				
				for(l=0;l<n;l++){
					if(cromo3[l]){
						peso=peso+almacen[2][l];
						cont++;
					}
				} 				
				if(peso==capacidad && cont == m){
					printf("Si hay solucion\n");
					imprimesol(almacen,i,j,k,n);
				}
			}
	
	return 0;
}
