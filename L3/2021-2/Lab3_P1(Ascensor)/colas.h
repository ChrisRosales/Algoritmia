#ifndef COLAS_H
#define COLAS_H
#include "lse.h"

typedef ElementoLista ElementoCola;

typedef struct {
	Lista contenido;    
} Cola;

void construir_cola(Cola *);
int es_cola_vacia(Cola);
void pide_vez(Cola *, ElementoCola);
ElementoCola avanzar(Cola *tad);
void destruir_cola(Cola *tad);

//void enqueue_with_priority(Cola *, ElementoCola);
void enqueue_with_priority2(Cola *, ElementoCola);
void show_queue(Cola);

#endif