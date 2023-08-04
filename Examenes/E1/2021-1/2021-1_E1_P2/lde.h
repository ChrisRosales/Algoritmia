#ifndef LDE_H
#define LDE_H
//#include <stdio.h>
//#include <stdlib.h>

typedef struct listElement {
	int id;
	char timedate[15];
	char docType[3];
	char documentId[16];
	char txnType;
	double price;
	int quantity;	
} ListElement;

typedef struct Node {
	ListElement element;

	struct Node * next;
	struct Node * prev;
} TNode;

typedef struct List {
	TNode* first;
	TNode* last;
} TList;

/*Prototipos de funciones*/
	void append_node(TList * list_ptr, TNode *node_ptr);
	void show_list(TList list, char txnType);
	int list_size(TList list, char txnType);
	void reverse(TList *list_ptr);
	void finalize_list(TList list);

#endif