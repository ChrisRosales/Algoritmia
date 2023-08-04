#include <iostream>
#include <climits>

using namespace std;

int maxganancia(int k,int n,int precios[]){
	int gana[k+1][n];
	
	for(int i=0;i<n;i++) gana[0][i]=0;
	for(int i=0;i<=k;i++) gana[i][0]=0;
	
	for(int i=1;i<=k;i++)
		for(int j=1;j<n;j++){
			int maximo = INT_MIN;
			
			for(int m=0;m<j;m++)
				maximo=max(maximo,precios[j]-precios[m]+gana[i-1][m]);
			// seleccionar entre el maximo local y maximo de todo el recorrido
			gana[i][j]=max(maximo,gana[i][j-1]);
			
		}
	
	for(int i=0;i<=k;i++){
		cout << endl;
		for(int j=0;j<n;j++)
			cout << gana[i][j] << " ";
	}
		
	
	
	return gana[k][n-1];
	
}


int main(){
	int k=2;
	
	int precios[]={315,322,385,375,365,380};
	int n = 6;
	
	cout <<endl<< "La ganancia maxima:" << maxganancia(k,n,precios);
	
	return 0;	
}


