#include <stdio.h>
#include <stdlib.h>
#include "lde.h"

int main(){
	int i=1, must_read=1;
	char res;
	TList list;
	list.first = NULL;
	list.last = NULL;
	while (must_read){
		printf("Ingrese los datos de la operación %d:\n",i);

		TNode * node = (TNode *)malloc(sizeof(TNode));	
		node->element.id = i;
		printf("Fecha y hora: ");
		scanf("%s", node->element.timedate);
		printf("Tipo de documento: ");
		scanf("%s", node->element.docType);
		printf("Número de documento: ");
		scanf("%s", node->element.documentId);
		printf("Tipo de operación: ");
		scanf(" %c", &node->element.txnType);
		printf("Precio de la acción: ");
		scanf("%lf", &node->element.price);
		printf("Número de acciones: ");
		scanf("%d", &node->element.quantity);

		append_node(&list, node);
		
		printf("¿Desea ingresar más datos? [S,N]: ");
		scanf(" %c", &res);
		if (res =='N' || res == 'n') must_read = 0;
		else if (res =='S' || res == 's') i++;
	}

	printf("Para mostrar las operaciones ingresadas de un tipo, ingrese el tipo de operación (C) o (V): ");
	scanf(" %c", &res);
	show_list(list, res);
	printf("La cantidad total de operaciones del tipo %c es %d.\n", res, list_size(list, res));
	printf("\nSe hace la reversa.\n");
	reverse(&list);
	printf("Para mostrar las operaciones de un tipo luego de la reversa, ingrese el tipo de operación (C) o (V): ");
	scanf(" %c", &res);
	show_list(list, res);
	printf("La cantidad total de operaciones del tipo %c es %d", res, list_size(list, res));

	return 0;
}