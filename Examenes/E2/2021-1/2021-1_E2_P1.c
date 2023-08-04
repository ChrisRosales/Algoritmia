#include <stdio.h>

int costo=0;

int validarSiEsPosibleVacuna(int ciudades[6][6],int equipo[6],int vacuna,int i,int solucion[6],int cantCiudades){
	int j;
	//Este es para el caso de la vacuna Fisher
	if (vacuna==1 && equipo[i]==0)
		return 0;
	for (j=0; j<cantCiudades; j++){
		if (ciudades[i][j]==1 && solucion[j]==vacuna)
			return 0;
		if (ciudades[j][i]==1 && solucion[j]==vacuna)
			return 0;
	}
	return 1;
}

void imprimeSolucion(int solucion[6],int cantCiudades){
	int i;
	for (i=0; i<cantCiudades; i++){
		printf("%d ",solucion[i]);
	}
	printf("\n");
}

int encontrarSoluciones(int ciudades[6][6],int equipo[6],int costos[4],int solucion[6],int i,int cantCiudades){
	int vac;
	if (i==cantCiudades){
		printf("Hay solución: \n");
		imprimeSolucion(solucion,cantCiudades);
		printf("Costo es: %d\n",costo);
		return 0;
	}
	/*Si es que no he colocado vacuna en esa ciudad*/
	if (solucion[i]==0){
		for (vac=1; vac<=4; vac++){
			if (validarSiEsPosibleVacuna(ciudades,equipo,vac,i,solucion,cantCiudades)){
				solucion[i] = vac;
				costo = costo + costos[vac-1];
				if (encontrarSoluciones(ciudades,equipo,costos,solucion,i+1,cantCiudades))
					return 1;
				solucion[i] = 0;
				costo = costo - costos[vac-1];
			}
		}
	}
	return 0;
}

int main(){
	int ciudades[6][6] = {{0,1,1,0,0,1},
					{1,0,1,1,0,0},
					{1,1,0,1,0,1},
					{0,1,1,0,1,1},
					{0,0,0,1,0,1},
					{1,0,1,1,1,0}};
	int equipo[6] = {0,0,1,0,1,0};
	int costos[4] = {10,5,12,8};
	int solucion[6] = {0}; /*Aqui ponemos las vacunas de las ciudades en 0*/
	encontrarSoluciones(ciudades,equipo,costos,solucion,0,6);
	return 0;
}
