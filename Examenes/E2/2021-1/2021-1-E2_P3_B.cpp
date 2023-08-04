#include <iostream>
#define N 16

using namespace std;

int solucion[N];
int posSolucion=0;
int cantSoluciones = 0;

int encontrarSoluciones(int almacen[N],int n,int peso,int pos){
	int indice, seccion, esPar;
	if (pos==n || peso<0){
		return 0;
	}
	if (almacen[pos]==peso){
		/*Voy a mostrar la solucion encontrada*/
		cantSoluciones++;
		solucion[posSolucion] = pos;
		cout << "Resultado " << cantSoluciones << ": ";
		for (int i=0; i<=posSolucion; i++){
			cout << almacen[solucion[i]] << "k" << " ";
		}
		cout << "Ubicaciones: ";
		for (int i=0; i<=posSolucion; i++){
			indice = solucion[i];
			seccion = (indice/4) + 1;
			esPar = (indice % 2) == 0;
			if (indice%4<2){
				cout << "I";
			} 
			else {
				cout << "D";
			}
			if (esPar){
				cout << "A";
			}
			else{
				cout << "B";
			}
			cout << seccion << " ";
		}
		cout << endl;
		//return 1;
		return 0;
	}
	solucion[posSolucion] = pos; /*Marcamos que este caso es una posible solucion*/
	posSolucion++;
	if (encontrarSoluciones(almacen,n,peso-almacen[pos],pos+1)){
		return 1;
	}
	/*Aqui voy a desmarcar, asumiendo que no encontre una posible solucion*/
	posSolucion--;
	encontrarSoluciones(almacen,n,peso,pos+1);
}

int main(){
	int almacen[N] = {7,9,8,18,17,12,6,7,14,11,10,15,19,8,12,11};
	int n=16; /*Como tiene 4 secciones y hay 4 filas por cada seccion es 16*/
	int peso=23;
	encontrarSoluciones(almacen,n,peso,0);
	return 0;
}
