#include <stdio.h>

void merge(int A[],int B[], int ini, int med, int fin)
{	int l1,l2,i;
    int p = 0,q = 0;
    
	l1 = med - ini + 1;
    l2 = fin -med;

    int P[l1 + 1];
    int Q[l2 + 1];
    int P1[l1 + 1];
    int Q1[l2 + 1];


    //Copiar arreglos
    for(i = ini; i <=med; i++){
	    P[i-ini] = A[i];
	    P1[i-ini] = B[i];
	}
    

    P[l1] = 1000000;

    for(i = med+1; i <= fin; i++)
    {
    	Q[i-med-1] = A[i];
    	Q1[i-med-1] = B[i];
	}
     

    Q[l2] = 1000000;

    for(i = ini; i <= fin; i++){
        if(P[p] < Q[q])
        {	    A[i] = P[p];
        		B[i] = P1[p++];
		}
        
        else{
			A[i] = Q[q];
			B[i] = Q1[q++];
		}
    }
}

void mergesort(int A[],int B[], int ini, int fin){
    if(ini == fin)
        return;

    int med = (ini + fin)/2;
    mergesort(A,B, ini, med);
    mergesort(A,B, med+1, fin);
    merge(A,B, ini, med, fin);
}


int cuenta(int arr1[],int arr2[],int ant,int cat,int ini,int fin,int cont)
{
	int medio;
	medio = (ini+fin)/2;
	
	if(ini>fin)
		return cont; //k=3
		
	if(arr1[medio]*100+arr2[medio]<cat*100+ant)// 7 <= 3
		return cuenta(arr1,arr2,ant,cat,medio+1,fin,cont+medio-ini+1);
	else	
		return cuenta(arr1,arr2,ant,cat,ini,medio-1,cont);
}

int main()
{	int i,n=8;
	int cod[]={1989,1489,1590,1909,1000,1320,1021,1317};
	int ano[]=  {2,4,5,3,10,10,10,12};
	int nivel[]={1,1,1,2,2, 2, 3, 3};
	int sueldo[]={3,4,4,6,6,5,7,8};
	int ant=5,cat=2,m;
	
	// Respuesta c	
	m=cuenta(nivel,ano,ant,cat,0,n-1,0);
	printf("Hay %d consultores para lo requerido\n",n-m); 
	
	//Respuesta d
	int P=12,suma=0;
	mergesort(sueldo,cod,m,n-1);
	printf("Con %d alcanzan los siguientes consultores:\n",P);	
    for(i = m; i < n; i++){
    	if(suma+sueldo[i]<=P)
        printf("%d-%d ", sueldo[i],cod[i]);
   		suma = suma + sueldo[i];
    }
	
	printf("\n");
	for(i = 0; i < n; i++){
        printf("%d-%d ", sueldo[i],cod[i]);
    }

}
