#include <stdio.h>
#include <stdlib.h>

int solu[100];
int cont = 0;
int cant = 0;
//buscamos predecesores
int valido (int pred) {
	if (pred == -1) return 1;
	int i;
	for (i = 0; i < cont; i++) {
		if (solu[i] == pred) return 1; //encontrado
	}
	return 0;// nohay
}
// validamos que los predecesores esten en la lista
int es_valido(int n, int proy[100][3], int num) {
	int j, k, flag = 1;
	for (j = 0; j < cont; j++) {
		for (k = 0; k < n; k++) {
			if (solu[j] == proy[k][0])  {
				if (!valido(proy[k][2])) flag = 0; // validamos el pred
			}
		}
	}
	int validez = flag && valido(num);
	return validez;
}

int seleccionar_mult(int i, int n, int p, int proy[100][3]) {
	if (i >= n || p <= 0) return 0;
	if (proy[i][1] == p && es_valido(n,proy,proy[i][2])) {
		solu[cont] = proy[i][0];
		int k;
		if (cant == 0) printf("Hay soluciones:\n");
		for (k = 0; k <= cont; k++)
			printf("P%d ",solu[k]);
		printf("\n");
		cant++;
		if (cant != 1) return 0;
	}
	solu[cont++] = proy[i][0];
	if (seleccionar_mult(i+1,n,p-proy[i][1],proy)) {
		printf("P%d ",proy[i][0]);
		return 1;		
	} else {
		cont--;
		return seleccionar_mult(i+1,n,p,proy);
	}
}

int seleccionar_una(int i, int n, int p, int proy[100][3]) {
	if (i >= n || p <= 0) return 0;
	if (proy[i][1] == p && es_valido(n,proy,proy[i][2])) {	
		printf("Hay Solucion: ");	
		printf("P%d ",proy[i][0]);
		return 1;
	}
	if (seleccionar_una(i+1,n,p-proy[i][1],proy)) {
		printf("P%d ",proy[i][0]);
		return 1;		
	} else {
		return seleccionar_una(i+1,n,p,proy);
	}
}


int main () {
	int n, p;
	printf("Ingrese la cantidad de proyectos: ");
	scanf("%d",&n); // para la lectura de este archivo tomar N = 8
	printf("Ingrese el presupuesto maximo: ");
	scanf("%d",&p);
	FILE *arch = fopen("texto.txt","r");
	int proy[100][3];
	int i = 0;
	while (1) {
		fscanf(arch,"%d %d %d",&proy[i][0],&proy[i][1],&proy[i][2]);
		if (feof(arch)) break;
		// si precedesor == -1 significa que no tiene predecesor
		i++;
	}
	fclose(arch);
	seleccionar_una(0,n,p,proy);
	printf("\n");
	seleccionar_mult(0,n,p,proy);
	return 0;
}
