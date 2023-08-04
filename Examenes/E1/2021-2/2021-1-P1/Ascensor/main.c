#include <stdio.h>
#include <assert.h>
#include "colas.h"

int main(){
    int i, n, request_quantity, level, is_ascending, actual_level;
    Cola cola;
    construir_cola(&cola);   
    assert(es_cola_vacia(cola));

    printf("Ingrese la cantidad de pisos del edificio: ");
    scanf("%d", &n);
    printf("Movimientos del ascensor en un edificio de %d pisos:\n", n);
    
    ElementoCola request;
    request.level = 1;
    request.is_ascending = 1;
    enqueue_with_priority2(&cola, request);

    printf("\nLa cola de solicitudes del ascensor es:\n");
    show_queue(cola);
    printf("\nEl ascensor está en el piso %d\n", retorna_cabeza(cola.contenido).level);

    printf("\nIngrese la cantidad de solicitudes: ");
    scanf("%d", &request_quantity);

    while (!es_cola_vacia(cola)) {
        i=0;
        while (i < request_quantity){
            printf("Solicitud %d [número_piso y dirección(1:sube,0:baja)]: ",++i);
            scanf("%d %d", &level, &is_ascending);
            
            ElementoCola request;
            request.level = level;
            request.is_ascending = is_ascending;        
            enqueue_with_priority2(&cola, request);            
        }
        avanzar(&cola);
        printf("\nLa cola de solicitudes del ascensor es:\n");
        if (es_cola_vacia(cola)) {
            printf("No hay solicitudes en la cola del ascensor.\n");
            printf("\nEl ascensor está en el piso %d\n", actual_level);
        }
        else {
            show_queue(cola);
            actual_level = retorna_cabeza(cola.contenido).level;
            printf("\nEl ascensor está en el piso %d\n", actual_level);
            printf("\nIngrese la cantidad de solicitudes: ");
            scanf("%d", &request_quantity);
        }
    }
    destruir_cola(&cola);
    return 0;
}