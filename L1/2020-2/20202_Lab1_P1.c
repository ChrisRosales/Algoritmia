#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Trabajador {
    double rotura;
    int salario;
} Trabajador;

int minT=4, maxT=7;
int presupuesto=20;

void mostrarRespuesta(int index,int presupuestoGasto,double PromedioRoturas,
									int leerTrabajadores,int** CombinaTrabajadores) {
    printf("\nObreros:   ");
    for (int i=0;i<leerTrabajadores;i++) {
        printf("%d ",(i+1));
    }
    printf("\nSeleccion: ");
    for (int i=0;i<leerTrabajadores;i++) {
        printf("%d ",CombinaTrabajadores[index][i]);
    }
    printf("\nCosto total: %d, fallas promedio %f\n",presupuestoGasto,PromedioRoturas);
}

void MinimizarPerdidas(int leerTrabajadores,Trabajador* trabajadores) {
	double PromedioMinimoFallas = INFINITY;

    int Combinaciones = pow(2,leerTrabajadores);

    int** CombinaTrabajadores = (int**)malloc(Combinaciones*sizeof(int*));
    int* presupuestoGasto = (int*)malloc(Combinaciones*sizeof(int));
    double* PromedioRoturas = (double*)malloc(Combinaciones*sizeof(double));

    for (int i=0; i<Combinaciones;i++) {
        CombinaTrabajadores[i] = (int*)malloc(leerTrabajadores*sizeof(int));
        for (int j=0;j<leerTrabajadores;j++) {
            CombinaTrabajadores[i][j] = 0;
        }
        //lleno con 1 las posibles conbinaciones
        int temp = i;
        int j = 0;
        while(temp>0) {
            CombinaTrabajadores[i][j] = temp%2;
            temp /= 2;
            j++;
        }
		//recorremos la matriz de 0 y 1 y multiplamos el valor de 0 y 1 por
		//el valor de cada columna y lo vamos acumulando esto dara como
		//resultado de todas las combimaciones con 1.
        int PresupuestoActual = 0;
        int TrabajadoresActuales = 0;
        double PromedioRoturasActual = 0;
        for (int j=0;j<leerTrabajadores;j++) {
            PresupuestoActual += CombinaTrabajadores[i][j]*trabajadores[j].salario;
            TrabajadoresActuales += CombinaTrabajadores[i][j];
            PromedioRoturasActual += CombinaTrabajadores[i][j]*trabajadores[j].rotura;
        }

        PromedioRoturasActual /= TrabajadoresActuales;

        if ((TrabajadoresActuales>=minT) && 
                (TrabajadoresActuales<=maxT) && 
                (PresupuestoActual<=presupuesto) &&
                (PromedioRoturasActual<PromedioMinimoFallas)) {
            PromedioMinimoFallas = PromedioRoturasActual;
        }
        presupuestoGasto[i] = PresupuestoActual;
        PromedioRoturas[i] = PromedioRoturasActual;
    }

    for (int i=0;i<Combinaciones;i++) {
        if((PromedioRoturas[i]==PromedioMinimoFallas) &&
                (presupuestoGasto[i]<=presupuesto)) {
            mostrarRespuesta(i,presupuestoGasto[i],PromedioRoturas[i],
										leerTrabajadores,CombinaTrabajadores);
        }
    }    

    free(CombinaTrabajadores);
}

int leerArchivo(int totalTrab,Trabajador* trabajadores) {
    int leerTrabajadores = totalTrab;
    FILE* file = fopen("20202_Lab1_1.txt","r");
    for (int i=0;i<totalTrab;i++) {
    	//variable asignada permite saber cuando ya no hay mas trabajadores porque devuelve -1
        int indicador = fscanf(file,"%lf %d",&trabajadores[i].rotura,&trabajadores[i].salario);
        if (indicador<2) {
            leerTrabajadores = i;
            break;
        }
    }
    fclose(file);
    return leerTrabajadores;
}

int main() {
    int totalTrabajadores = 12;

    Trabajador* trabajadores = (Trabajador*)malloc(totalTrabajadores*sizeof(Trabajador));

    int leerTrabajadores = leerArchivo(totalTrabajadores,trabajadores);
    printf("Se han encontrado %d obreros",leerTrabajadores);

    printf("\n\nTodas las soluciones:");
    MinimizarPerdidas(leerTrabajadores,trabajadores);

    free(trabajadores);

    return 0;
}








