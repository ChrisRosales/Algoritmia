#include <stdio.h>
#include <stdlib.h>

void leerData(int ncols,int nrows,int** terrain);
int exploraRecursividad(int ncols,int nrows,int x,int y,int direction,int** terrain,int firstIteration);

int main() {
    int ncol;
    int nfilas;
    printf("Ingresar dimensiones xmax,ymax: ");
    scanf("%d %d",&ncol,&nfilas);

    int inicioX;
    int inicioY;
    printf("Ingresar punto de inicio x,y: ");
    scanf("%d %d",&inicioX,&inicioY);

    int direction;
    printf("Ingresar direccion 0-arriba 1-derecha 2-abajo 3-izquierda: ");
    scanf("%d",&direction);

    int** terreno = (int**)malloc(ncol*sizeof(int*));
    leerData(ncol,nfilas,terreno);

    int unidades = exploraRecursividad(ncol,nfilas,inicioX,inicioY,direction,terreno,1);
    printf("Se encontraron %d unidades!",unidades);
    return 0;
}

int exploraRecursividad(int ncol,int nfilas,int x,int y,int direction,int** terreno,int primeraIteracion) {
	
	if((x<0) || (x>=ncol) || (y<0) || (y>=nfilas)){
		return 0;
	}
	
	int unidades=0;
	
	switch(direction){
		case 0://arriba
		case 2://abajo
			if(primeraIteracion){
				for(int i=0;i<nfilas;i++){
					if(terreno[x][i]==1)
						unidades+=1;
					else
						unidades+=0;
				}
			}
			for(int i=0;i<ncol;i++){
				if(i==x){
					continue;
				}
				if(terreno[y][i]==1)
					unidades+=1;
				else
					unidades+=0;
			}
			break;
		case 1: //derecha
		case 3: //izquierda
			if(primeraIteracion){
				for(int i=0;i<ncol;i++){
					if(terreno[y][i]==1)
						unidades+=1;
					else
						unidades+=0;
				}
			}
			for(int i=0;i<nfilas;i++){
				if(i==y){
					continue;
				}
				if(terreno[x][i]==1)
					unidades+=1;
				else
					unidades+=0;
			}
			break;
	}
	
	
	int siguienteX;
	int siguienteY;
	
	switch(direction){
		case 0:
			siguienteX=x;
			siguienteY=y-1;
			break;
		case 1:
			siguienteX=x+1;
			siguienteY=y;
			break;
		case 2:
			siguienteX=x;
			siguienteY=y+1;
			break;
		case 3:
			siguienteX=x-1;
			siguienteY=y;
			break;
	}

	return unidades+exploraRecursividad(ncol,nfilas,siguienteX,siguienteY,direction,terreno,0);

}

void leerData(int ncol,int nfilas,int** terreno) {
    printf("Ingresar condiciones del terreno:\n");
    for (int i=0;i<ncol;i++) {
        terreno[i] = (int*)malloc(nfilas*sizeof(int));
        for (int j=0;j<nfilas;j++) {
            scanf("%d",&terreno[i][j]);
        }
    }
}