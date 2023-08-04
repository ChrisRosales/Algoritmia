#include<stdio.h>

void sePuedeRepartir(int prod[], int n){
	int i, j, sum, res;
	int sol[2][n+1];
	
	sol[0][0] = 0;
	sol[1][0] = 0;
	
	for(i=1;i<=n;i++)
		sol[0][i] = prod[i-1];
	
	for(i=1;i<=n;i++){
		sum = sol[0][i] + sol[0][i-1];
		if(sum<3){
			sol[1][i] = sum - 3;
		}
		else{
			res = sum%3;
			sol[1][i] = res + sol[1][i-1];
		}
	}
	
	int sePuede = sol[1][n]%3;
	
	if(sePuede==0){
		printf("SI se puede realizar la reparticion entre los 3 clientes.\n");
		for(i=0;i<2;i++){
			for(j=0;j<=n;j++){
				printf("%d ", sol[i][j]);
			}
			putchar('\n');
		}	
	}
	else
		printf("NO se puede realizar la reparticion entre los 3 clientes.\n");
}

int main(){
	//parte A
	int prod[5] = {6, 4, 3, 2, 3};
	int n=5;
	sePuedeRepartir(prod, n);
	return 0;
}
