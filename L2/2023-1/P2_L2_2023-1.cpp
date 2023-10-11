#include <iostream>
#define MAX 10

//Solucionado por: Piero Alvarez Castillo 

using namespace std;

void hanoi(int n,int origen[],int fin[],int aux[],
		int *indiceOrigen,int *indiceFin,int *indiceAux){
	//Condición de salida:			
	if(n==1){	
		//Mueve el valor del arreglo origen al destino:	
		if(fin[*indiceFin]!=0){//Significa que ya tiene un valor apilado
			(*indiceFin)++;
			fin[*indiceFin]=origen[*indiceOrigen];
			origen[*indiceOrigen]=0;
			if(*indiceOrigen!=0){//En caso ya no le queden más valores, no se disminuye el indice				
				(*indiceOrigen)--;
			}
		}else if(fin[*indiceFin]==0){//Significa que es el primer valor a apilar
			fin[*indiceFin]=origen[*indiceOrigen];
			origen[*indiceOrigen]=0;
			if(*indiceOrigen!=0){				
				(*indiceOrigen)--;
			}
		}
		return;
	}
	hanoi(n-1,origen,aux,fin, indiceOrigen, indiceAux, indiceFin);
	//Mueve el valor del arreglo origen al destino:	
		if(fin[*indiceFin]!=0){//Significa que ya tiene un valor apilado
			(*indiceFin)++;
			fin[*indiceFin]=origen[*indiceOrigen];
			origen[*indiceOrigen]=0;
			if(*indiceOrigen!=0){//En caso ya no le queden más valores, no se disminuye el indice				
				(*indiceOrigen)--;
			}
		}else if(fin[*indiceFin]==0){//Significa que es el primer valor a apilar
			fin[*indiceFin]=origen[*indiceOrigen];
			origen[*indiceOrigen]=0;
			if(*indiceOrigen!=0){//En caso ya no le queden más valores, no se disminuye el indice				
				(*indiceOrigen)--;
			}
		}
	hanoi(n-1,aux,fin,origen, indiceAux, indiceFin, indiceOrigen);
}

/*Esta función halla el menor índice de la primera columna de una matriz,
también devuelve el menor valor dentro de la primera columna*/
void menor_recursivo(int i,int almacen_origen[][MAX],int cant_pilas_origen,
	int *menor,int *menor_fila){
	//Condición de salida:
	if(i==cant_pilas_origen) return;
	
	if(almacen_origen[i][0]<(*menor)){
		(*menor)=almacen_origen[i][0];
		(*menor_fila)=i;
	}
	menor_recursivo(i+1,almacen_origen,cant_pilas_origen, menor, menor_fila);
}

void trasladar_pilas(int almacen_origen[][MAX],int max_barricas_origen,int cant_pilas_origen,
  int almacen_destino[][MAX],int max_barricas_destino,int cant_pilas_destino,int barricas_por_pila[]){  	
  	//Condición de salida:
  	if(cant_pilas_destino==1) return;
  	//Halla el menor de la primera columna de la matriz:
  	int menor_valor=9999999,menor_fila;  	
  	menor_recursivo(0,almacen_origen,cant_pilas_origen,&menor_valor,&menor_fila);//El 0 representa el "i" que va a iterar en la recursión
  	//cout<<"menor fila: "<<menor_valor<<endl;
  	//Restringe la cantidad de barricas que entran en el almacen destino:
  	if(barricas_por_pila[menor_fila]<=max_barricas_destino){
  		int indice_origen=barricas_por_pila[menor_fila]-1;
  		int indicefin=0,indiceaux=0;
  		hanoi(barricas_por_pila[menor_fila],almacen_origen[menor_fila],
		  almacen_destino[cant_pilas_destino-1],almacen_destino[0],&indice_origen,&indicefin,&indiceaux);
		almacen_origen[menor_fila][0]=9999999;//Para que ya no considere esta fila en la siguiente iteración
		trasladar_pilas(almacen_origen,max_barricas_origen,cant_pilas_origen,almacen_destino,max_barricas_destino,cant_pilas_destino-1,barricas_por_pila);	
	}else{
		//Para que ya no considere el caso en el que la fila se exceda la cantidad de barricas del almacén destino
		almacen_origen[menor_fila][0]=9999999;
		trasladar_pilas(almacen_origen,max_barricas_origen,cant_pilas_origen,almacen_destino,max_barricas_destino,cant_pilas_destino,barricas_por_pila);
	}  	
}

int main(){
	int max_barricas_origen=5,max_barricas_destino=4;
	int cant_pilas_origen=7,cant_pilas_destino=5;
	int almacen_origen[][MAX]={{2010100,2010050,2010050},
							  {2021100,2021100,2021050,2021050},
							  {2018050,2018050,2018025,2018025,2018025},
							  {2015100,2015050,2015025},
							  {2020100,2020100},
							  {2019100,2019050,2019050,2019025},
							  {2022100,2022100}};
	int barricas_por_pila[]={3,4,5,3,2,4,2};
	int almacen_destino[MAX][MAX];
	//Solo empleo la iterativa para rellenar el almacén destino de ceros para simular que está vacío
	for(int i=0;i<cant_pilas_destino;i++){
		for(int j=0;j<max_barricas_destino;j++){
			almacen_destino[i][j]=0;
		}
	}	
	//Buscar_menor:
	trasladar_pilas(almacen_origen,max_barricas_origen,cant_pilas_origen,almacen_destino,max_barricas_destino,cant_pilas_destino,barricas_por_pila);
	int anio,peso;
	cout<<"Almacen Destino: "<<endl;
	for(int i=0;i<cant_pilas_destino;i++){
		for(int j=0;j<max_barricas_destino;j++){
			if(almacen_destino[i][j]==0)	cout<<almacen_destino[i][j]<<" ";
			else{
				anio=almacen_destino[i][j]/1000;
				peso=almacen_destino[i][j]%1000;
				cout<<anio<<"-"<<peso<<" ";
			}
		}
		cout<<endl;
	}			
	return 0;
}
