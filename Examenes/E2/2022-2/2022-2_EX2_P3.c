#include <stdio.h>

//funcion sacada de la semana 15 paideia, problema de las canastas
int buscapresupuesto(int arr[],int n,int sum){
	int i,j;
	int dp[n+1][sum+1];
	//Por favor ordenar el arreglo previamente para
	//obtener mejores resultados
	
	for(i=0;i<=n;i++)
		dp[i][0]=1;
		
	for(i=1;i<=sum;i++)
		dp[0][i]=0;
	
	
	for(i=1;i<=n;i++){
		for(j=1;j<=sum;j++){
			dp[i][j]=dp[i-1][j];
			
			if(j-arr[i-1]>=0 && dp[i][j]==0)
				dp[i][j]=dp[i-1][j-arr[i-1]];
		}
	}
	for(i=sum;i>0;i--)	
		if(dp[n][i]==1) return i;
	
}
//esto es demasiado similar al return que se puede ver en el problema de las canastas, solo q aqui se adapta de otra forma 
//en lugar de sumar, se resta:
void llenar_arreglos(int arr_turnos[],int cant,int turno_manhana_max,int turno_tarde_max,int turno_noche_max,int arr_tareas[]){
	arr_turnos[0]=turno_manhana_max-buscapresupuesto(arr_tareas,5,turno_manhana_max);
	arr_turnos[1]=turno_tarde_max-buscapresupuesto(arr_tareas,5,turno_tarde_max);
	arr_turnos[2]=turno_noche_max-buscapresupuesto(arr_tareas,5,turno_noche_max);
	//aqui terminamos de llenar los datos, pues en el problema de las canastas era solo un return (numero-funcion)
}
/*int pregunta3B_BT(int i,int n,int peso_bt,int arr_tareas[],int *cant_bt){
    if(arr_tareas[i]==peso_bt && arr_tareas[i]!=0 && cant_bt==1)
    {
        if(arr_tareas[i]!=0)
        {    
			printf("%d ",arr_tareas[i]);      
        }
        arr_tareas[i]=0;
        return 1;
    }
}
*/
int main(){
	int num_tareas = 5;
	int arr_tareas[5] = {1, 3, 6, 10, 16};
	int i,inico_bt;
	int cant_bt;
	int turno_manhana_max = 8;
	int turno_tarde_max = 16;
	int turno_noche_max = 24;
	
	int arr_turnos[3];
	llenar_arreglos(arr_turnos,3,turno_manhana_max,turno_tarde_max,turno_noche_max,arr_tareas);	
	//Pregunta 3A:
	printf("Los desperdicio de los turnos son: \n");
	for(i=0;i<3;i++){
		printf("Desperdicio de horas del turno %d: ",i+1);
		printf("%d \n",arr_turnos[i]);
	}
	//Pregunta 3B:
	int peso_bt=100;
	
//	int pregunta3B_BT(inico_bt,5,peso_bt,arr_tareas,&cant_bt);
	return 0;
}
