#include <limits.h>
#include <stdio.h>

int min(int a,int b){
    if (a<b) return a;
    return b;
}
int max(int a,int b){
    if (a>b) return a;
    return b;
    
}

int sum(int arr[], int from, int to)
{	int i;
  int total = 0;
  for (i = from; i <= to; i++)
    total += arr[i];
  return total;
}

int maxtareas(int arr[], int n, int k)
{ int i,j,p,temp;

    for (i=0; i < n; i++) 
       for(j=i+1;j<n;j++)
           if (arr[i]>arr[j])
           {
               temp=arr[i];
               arr[i]=arr[j];
               arr[j]=temp;
           } 


  int dp[k + 1][n + 1];
  // k=1
  for (i = 1; i <= n; i++)
    dp[1][i] = sum(arr, 0, i - 1);
  // n=1
  for (i = 1; i <= k; i++)
    dp[i][1] = arr[0];

  // 2 a mas 
  for ( i = 2; i <= k; i++) { 
    for ( j = 2; j <= n; j++) {

      int maximo = INT_MAX;

      for ( p = 1; p <= j; p++)
	  
        maximo = min(maximo, max(dp[i - 1][p],
              sum(arr, p, j - 1)));  

      dp[i][j] = maximo;
    }
  }
  for ( i = 1; i <= k; i++) { 
    for ( j = 1; j <= n; j++)
		printf("%d ", dp[i][j]);
	printf("\n");	
	}	
  return dp[k][n];
}


int main()
{
  int arr[] = { 15, 30, 60, 45, 10 };
  //int arr[] = { 10, 15, 30, 45, 60 };
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 4 ;
  printf("Tiempo maximo es:%d",maxtareas(arr, n, k));
  return 0;
}

