#include <stdio.h>
#include <stdlib.h>
#include "lde.h"

void append_node(TList * list_ptr, TNode *new_node_ptr){
	new_node_ptr->next = NULL;
	//printf("%d - %s", new_node_ptr->element.id, new_node_ptr->element.documentId);
	
	if (list_ptr->first == NULL){
		new_node_ptr->prev = NULL;
		list_ptr->first = new_node_ptr;
		list_ptr->last = new_node_ptr;		
	} else {
		list_ptr->last->next = new_node_ptr;
		new_node_ptr->prev = list_ptr->last;
		list_ptr->last = new_node_ptr;
	}	
}

void show_list(TList list, char txnType){
	if (list.first != NULL && list.last != NULL &&
		list.first->element.txnType == txnType)
		printf("Op. %d, Fecha: %s, Tipo ope.: %c\n",
			list.first->element.id, 
			list.first->element.timedate,
			list.first->element.txnType);

	if (list.first != list.last){
		list.first = list.first->next;
		show_list(list, txnType);
	}
}

int list_size(TList list, char txnType){
	if (list.first == NULL)
		return 0;
	else {		
		if (list.first->element.txnType == txnType){
			list.first = list.first->next;
			return 1 + list_size(list, txnType);
		} else {
			list.first = list.first->next;
			return list_size(list, txnType);		
		}
	}
}

void reverse(TList *list_ptr) {
	if (list_ptr->last == list_ptr->first){
		TNode * aux_node = list_ptr->last->prev;
		list_ptr->last->prev = list_ptr->last->next;
		list_ptr->last->next = aux_node;
		return;
	} else {
		TNode *last_node = list_ptr->last;
		TNode *first_node = list_ptr->first;
		TNode *aux_node = list_ptr->last->prev;
		list_ptr->last->prev = list_ptr->last->next;
		list_ptr->last->next = aux_node;
		list_ptr->last = aux_node;
		reverse(list_ptr);
		list_ptr->first = last_node;
		list_ptr->last = first_node;
	}
}

void finalize_list(TList list){
	if (list.first != NULL){
		TNode *ptr_to_free = list.first;
		list.first = list.first->next;
		free(ptr_to_free);
		finalize_list(list);
	}
}
