#include <stdio.h>

int elem;

int divide(int i,int n,int peso,int p[])
{	int valor;
	if(i>=n||peso<0 )
		return 0;
	if(p[i]==peso && p[i]!=0 && elem==1)
	{
		if(p[i]!=0)
		{	printf("%d ",p[i]);
			
		}
		//int lista[]={0,5,3,1,3,0};
		p[i]=0;
		return 1;
	}
	if (p[i]!=0 ) elem--;
    
	if(divide(i+1,n,peso-p[i],p))
	{
		if(p[i]!=0){
			printf("%d ",p[i]);
			elem--;
		}
		p[i]=0;
		return 1;
	}
	else
	{ elem++;
		return(divide(i+1,n,peso,p));
	}
	
}

int main()
{
	int lista[]={4,5,3,1,3,2};
	int i,p=6,n=3,m=2;
	int peso;
	int sum=0;
	int cont=n;	
	
	if(p==n*m)
	{
		for(i=0;i<p;i++)
		{
			sum=sum+lista[i];
		}
		peso=sum/n;
		
		for(i=0;i<n;i++)
		{
			elem=m;
			cont=cont-divide(0,p,peso,lista);
			printf("\n");
		}
	
		if(cont==0)
			printf("\nHay solucion");
		else	
			printf("\nNo hay solucion");
	}
	else
		printf("\nLa cantidad de paletas ingresadas debe ser nxm");
	

	return 0;
}
