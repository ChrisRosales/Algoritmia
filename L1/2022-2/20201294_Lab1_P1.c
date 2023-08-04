#include <stdio.h>
#include <math.h>
//Christian Rosales 20201294
//3:03 pm
//creamos el tipo de dato herramienta, que soporte los datos que
//cargaremos: 
typedef struct{
	int tipo;
	int precio;
	int cant;
} Herramienta;

//codigo de carga binario del profe Cueva:
void cargabin(int num,int n,int cromo[]){
	int i,res;
	for(i=0;i<n;i++)cromo[i]=0; /*1 0 1 0 0*/
	i=0;
	while(num>0){
		res=num%2;
		num=num/2;
		cromo[i]=res;
		i++;	
	}
}

int main(){
	int M, P;
	printf("Ingrese el valor de M: ");
	scanf("%d",&M);
	printf("Ingrese el valor de P: ");
	scanf("%d",&P);
	//vemos que el n es 8 y como no nos solicita que se ingrese este dato
	//lo definimos aqui mismo:
	int n=8;
	//nuestro arreglo de herramientas:
	Herramienta arr_herramientas[n];
	//nuestros varibales contadores:
	int i,j,k;
	printf("Ingrese los datos: \n");
	for(i=0; i<n; i++){
		scanf("%d %d %d",&arr_herramientas[i].tipo, &arr_herramientas[i].precio, &arr_herramientas[i].cant);
	}
	int opciones = (int)pow(2,n);
	int cromosoma[n];
	
	int cant_herramientas;
	int importes_parcial;
	//como nos piden que sean de diferentes tipos
	//creamos un contador para cado tipo
	//de tal manera que si uno de ellos excede o iguala a 2 no tomamos en cuenta
	//dicha combinacion:
	int cant_t1, cant_t2, cant_t3, cant_t4, cant_t5, cant_t6, cant_t7, cant_t8;
	//cant_de_solus que se necesita para mostrar la pregunta: B
	int cant_solus=0;	
	int posi_solu;
	int monto_solu, cant_solu;
	int herramientas_max = 0;
	int cant_seleccionados;
	
	for(i=0; i<opciones; i++){
		//inicializamos nuestros datos que nos importan:
		cant_herramientas = 0;
		cant_seleccionados = 0;
		importes_parcial = 0;
		cant_t1 = 0;
		cant_t2 = 0;
		cant_t3 = 0;
		cant_t4 = 0;
		cant_t5 = 0;
		cant_t6 = 0;
		cant_t7 = 0;
		cant_t8 = 0;
		//cargamos la combinacion
		cargabin(i,n,cromosoma);
		//recorremos el arreglo de cromosomas:
		for(j=0; j<n; j++){
			if(cromosoma[j] == 1){
				cant_seleccionados++;
				if(arr_herramientas[j].tipo == 1){
					cant_t1++;
				} else if(arr_herramientas[j].tipo == 2){
					cant_t2++;
				} else if(arr_herramientas[j].tipo == 3){
					cant_t3++;
				} else if(arr_herramientas[j].tipo == 4){
					cant_t4++;
				} else if(arr_herramientas[j].tipo == 5){
					cant_t5++;
				} else if(arr_herramientas[j].tipo == 6){
					cant_t6++;
				} else if(arr_herramientas[j].tipo == 7){
					cant_t7++;
				} else{
					cant_t8++;
				}
				cant_herramientas = (arr_herramientas[j].cant) + cant_herramientas;
				importes_parcial = (arr_herramientas[j].cant*arr_herramientas[j].precio) + importes_parcial;
			}
		}
		//tambien aqui una observacion
		//un jp menciono que para imprimir todas las solus deberian imprimir solo las que tengan 9 como cant_herramientas maximas
		//aunque aqui imprima todas las souciones, lo q se haria para atender a lo solicitado seria cambiar el "cant_herramientas<=10" por
		//"cant_herramientas == 9", de tal manera que muestre todas las de 9, a continuacion se probara si afecta en algo. 
		// OJO: cuando se hizo lo de cant_herramientas == 9, mostro solo 1 solucion xd. Como si solo existiera una solucion, por lo que se dejo a <=10
		// para que muestre todas las soluciones
		if(cant_seleccionados<=M && cant_herramientas<=10 && cant_herramientas>herramientas_max && importes_parcial<=P && cant_t1<2 && cant_t2<2 && cant_t3<2 && cant_t4<2 
			&& cant_t5<2 && cant_t6<2 && cant_t7<2 && cant_t8<2){
			//la posi_solu sera necesario para la pregunta A:
			posi_solu = i;
			monto_solu = importes_parcial;
			herramientas_max = cant_herramientas;
			//hasta aqui la pregunta A.
			
			//Pregunta B:
			// a diferencia de la pregunta A, nos piden todas las soluciones, por lo cual
			// no es necesario almacenar la combinacion con la respuesta dentro de una variable como posi_soli
			// tambien al momento de impresion, si gustan pongan en comentarios a partir de "int cromo_solu[n]", para que no imprima 
			// cosas extras.
			// por lo que se procede a imprimir todas las respuestas: 
			cant_solus++;
			printf("\nSolucion numero: %d \n",cant_solus);
			printf("Tipos de herramientas usados: ");
			for(k=0; k<n; k++){
				if(cromosoma[k]==1){
					printf("%d ",arr_herramientas[k].tipo);
				}
			}
			printf("\nMonto Total: %d \n",importes_parcial);
			printf("Cantidad de herramientas: %d",herramientas_max);
			printf("\n");
			//Hasta aqui es la pregunta B.
			
		}
	}
	//pregunta A nos piden una solu, por ello usaremos el posi_solu y le metemos en carga_bin
	// para ello creamos un cromosoma extra el cual luego recorreremos:
	printf("\nPregunta 1.a: \n");
	int cromo_solu[n];
	cargabin(posi_solu,n,cromo_solu);
	printf("Mejor Solucion: \n");
	for(i=0; i<n; i++){
		if(cromo_solu[i]==1){
			printf("%d ",arr_herramientas[i].tipo);
		}
	}
	printf("\nMonto Total: %d \n",monto_solu);
	printf("Cantidad de herramientas: %d ",herramientas_max);
	//Hasta aqui es la pregunta A, si es necesario a partir de la linea 137, pongan en comentarios para que solo imprima lo necesario para 
	//la pregunta A, del caso contrario imprimira cosas extra.
	/* Datos utilizados: 
		4
		19
		1 4 3
		2 5 2
		3 4 1 
		4 2 1
		5 6 3
		6 3 3
		7 4 2
		8 1 4
	*/
	return 0;
}
