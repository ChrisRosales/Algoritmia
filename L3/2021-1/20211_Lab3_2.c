#include <stdio.h>

void merge(int A[], int ini, int med, int fin)
{	int l1,l2,i;
    int p = 0,q = 0;
    
	l1 = med - ini + 1;
    l2 = fin -med;

    int P[l1 + 1];
    int Q[l2 + 1];

    //Copiar arreglos
    for(i = ini; i <=med; i++)
        P[i-ini] = A[i];

    P[l1] = 1000000;

    for(i = med+1; i <= fin; i++)
        Q[i-med-1] = A[i];

    Q[l2] = 1000000;

    for(i = ini; i <= fin; i++){
        if(P[p] < Q[q])
            A[i] = P[p++];
        else
            A[i] = Q[q++];
    }
}
void mergesort(int A[], int ini, int fin){
    if(ini == fin)
        return;

    int med = (ini + fin)/2;
    mergesort(A, ini, med);
    mergesort(A, med+1, fin);
    merge(A, ini, med, fin);
}
int clasifica(int arr[],int ini,int fin,double porc,int cont,int total)
{
	int medio,conteo;
	double parc;
	medio = (ini+fin)/2;
	
	if(ini>fin){
		conteo=cont+medio-ini+1;
		parc = 1.0*(total-conteo)/total;
	//	printf("conteo1:%d %lf\n",conteo,parc);
		if(parc < porc) return 0;
		return 1; 
	}
		
	if(arr[medio]==0){
		conteo=cont+medio-ini+1;
		parc = 1.0*(total-conteo)/total;
	//	printf("conteo2:%d %lf\n",conteo,parc);
		if( parc < porc  ) return 0;
		return clasifica(arr,medio+1,fin,porc,conteo,total);
	}
	else	
		return clasifica(arr,ini,medio-1,porc,cont,total);
}

int main()
{	int i,j,n=8,m=6;
	int cod[][8]={	{0,0,0,1,1,0,-1,-1},
					{1,0,1,1,1,0,1,0},
					{0,1,1,1,1,1,1,1},
					{1,1,1,1,1,0,1,-1},
					{1,0,0,0,0,1,-1,-1},
					{1,1,0,1,0,1,1,-1}};

	int result[][2]= {{6,0},{8,0},{8,0},{7,0},{6,0},{7,0}};
					
	double porc=0.70;
	/*ordenamiento si cuenta pero con complejidad mxnxlog(n)*/
	for(i=0;i<m;i++)
		mergesort(cod[i],0,result[i][0]-1);
	printf("\n");
	/*solo para ver si esta ordenado no cuenta la complejidad*/
	for(i=0;i<m;i++)
	{	for(j=0;j<result[i][0];j++)
			printf("%d ",cod[i][j]);
		printf("\n");
	}
	printf("\n");
	/*Debe ser complejidad mxlog(n)*/
	for(i=0;i<m;i++)
	{	
		result[i][1]=clasifica(cod[i],0,result[i][0]-1,porc,0,result[i][0]);
		printf("%d ",result[i][1]);
	}	
	printf("\n");
}
