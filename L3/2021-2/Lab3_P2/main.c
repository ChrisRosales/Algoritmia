/* 
 * File:   main.c
 * Author: cueva
 *
 * Created on 27 de octubre de 2021, 10:35 PM
 */
#include "Colas.h"
#include "pilas.h"
#include <stdio.h>
#include <stdlib.h>

void ord_burbuja(int arr[],int largo)
{	int i,j,temp;

	for(i=0;i<=largo-2;i++)
	{	printf("\n");
		for(j=0;j<=largo-2-i;j++)	
		{
			if(arr[j+1]<arr[j])
			{	temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;	
			}
			//printf("%d ",arr[j]);
		}	
	}	
}

void Hanoi(int n,Tpila *ini,Tpila *fin, Tpila *aux)
{   int valor;
    
    if (n == 1)
    {
        valor = pop(ini); 
        push(fin,valor);
        return;
    }
    Hanoi(n - 1, ini, aux, fin);
    valor = pop(ini); 
    push(fin,valor);
    Hanoi(n - 1, aux, fin, ini);
    
}

void apila(TCola *linea, Tpila *ini,Tpila *fin, Tpila *aux){
    int dato,cont=0,num=0;
    int lista[100];
    
    while(!cola_vacia(*linea)){
        dato = desencolar(linea);

        cont=num;
        for(int i=0;i<num;i++)
            if(dato<lista[i])
            {   cont=i;
                break;
            }
            
        if(pila_vacia(ini) || dato<=top(ini))
            push(ini,dato);
        else{
            Hanoi(cont,ini,fin,aux);
            push(ini,dato);
            Hanoi(cont,fin,ini,aux);
            imprimepila(*ini);
        }
        lista[num]=dato;
        num++;
        ord_burbuja(lista,num);
    }
}

int main(int argc, char** argv) {
    Tpila pprincipal,pauxiliar,pfinal;
    TCola linea;
    
    crea_cola(&linea);
            
    crear(&pprincipal);
    crear(&pauxiliar);
    crear(&pfinal);
    
    encolar(&linea,2);
    encolar(&linea,8);
    encolar(&linea,10);
    encolar(&linea,8);    
    encolar(&linea,5);    
    encolar(&linea,3);

    apila(&linea,&pprincipal,&pauxiliar,&pfinal);
    
    return (EXIT_SUCCESS);
}

