#ifndef LSE_H
#define LSE_H

typedef struct{
    int tiempo;
    int num;
} ElementoLista;

typedef struct nodoLista {
    ElementoLista elemento;    
    struct nodoLista *sig;
} NodoLista;

typedef struct {
    int longitud;
    NodoLista *cabeza;
} Lista;

void construir_lista(Lista *);
int es_lista_vacia(Lista);
NodoLista *crear_nuevo_nodo(ElementoLista, NodoLista *);
void insertar_al_inicio(Lista *tad, ElementoLista);
void insertar_al_final(Lista *tad, ElementoLista);
void insertar_en_orden(Lista *tad, ElementoLista);
int longitud(Lista);
void imprime(Lista);
NodoLista *obtener_ultimo_nodo(Lista);
ElementoLista retorna_cabeza(Lista);
void elimina_cabeza(Lista *);
void elimina_cola(Lista *);
void elimina_nodo(Lista *, ElementoLista);
void destruir_lista(Lista *);

#endif