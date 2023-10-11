#include <iostream>
#include <climits>

//Desarrollado por: Piero Alvarez Castillo

using namespace std;

int maxganancia(int n,int M,int grupos[],int particiones[],int ganancias[]){
	//1)Matriz solución:
	int solu[M][n+1];
	
	//2)Inicialización de la primera fila y columna:
	for(int i=0;i<=n;i++) solu[0][i]=0;	//Primera fila(fila auxiliar) inicializada en 0's
	for(int i=0;i<M;i++){ 
		solu[i][0]=0; //Primera columna(columna auxiliar) inicializada en 0
		solu[i][1]=0; //Segunda columna inicializada en 0, porque si el inicio de la partición es igual al fin, el segmento resultante sería 0.
	}
	
	//3)Llenado de la matriz solución:
	for(int i=1;i<M;i++){
		for(int j=2;j<=n;j++){
			int maximo = 0;
			int ganancia_anterior;
			for(int z=0;z<j;z++){
				if(grupos[z]==grupos[j-1]){					
					if(z==0)	ganancia_anterior=0;
					else ganancia_anterior=solu[i-1][j-1];	
					maximo=max(maximo,ganancias[j-1]-ganancias[z]+ganancia_anterior);	
				}
			}				
			// seleccionar entre el maximo local y maximo de todo el recorrido
			solu[i][j]=max(maximo,solu[i][j-1]);			
		}
	}
	
	for(int i=0;i<M-1;i++){
		cout << endl;
		for(int j=0;j<=n;j++)
			cout << solu[i][j] << " ";
	}
		
	
	
	return solu[2][n]; //Devuelvo el de la segunda fila, porque hace referencia a cantidad de cortes para una misma tabla
	
}


int main(){
	
	int M=4,N=10;//N es la cantidad de troncos.
	int ganancias[]={0,40,0,0,30,80,100};
	//Las particiones están representadas en los grupos,el grupo 1 vendría a ser la presentación 1(5 y 10))
	//El grupo 0 vendría a representar la presentación 2 y 4, porque se puede partir en (2,4) y (4,15).
	int grupos[]={0,0,1,2,1,2,0};
	int particiones[]={2,4,5,6,10,12,15};
	int n = 7;
	
	cout <<endl<< "La ganancia maxima que se puede obtener es:" << maxganancia(n,M,grupos,particiones,ganancias)*N;
	
	return 0;	
}


