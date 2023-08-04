#include <stdio.h>

int max(int a,int b){
    if (a>b) return a;
    return b;
    
}

int maximopeso(int arr[], int n, int K)
{	int i,j,temp;
	
    for (i=0; i < n; i++) 
       for(j=i+1;j<n;j++)
           if (arr[i]>arr[j])
           {
               temp=arr[i];
               arr[i]=arr[j];
               arr[j]=temp;
           } 
           
	int dp[n];

	dp[0] = 0;

	for (i = 1; i < n; i++)
	{
		dp[i] = dp[i-1];

		if (arr[i] - arr[i-1] < K)
		{
			if (i >= 2)
				dp[i] = max(dp[i], dp[i-2] + arr[i] + arr[i-1]);
			else
				dp[i] = max(dp[i], arr[i] + arr[i-1]);
		}
	}

	return dp[n - 1];
}

int main()
{
	int arr[] = {3, 25, 18, 15, 4, 12, 6};
	int N = sizeof(arr)/sizeof(int);

	int K = 5;
	
	printf("%d",maximopeso(arr, N, K));
	return 0;
}


