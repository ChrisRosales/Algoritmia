#include <stdio.h>
#include <stdlib.h>

void ingresar_datos(int *n, int *c, int **pedido, int ***almacen) {
    int i, j;

    printf("Ingrese el tamaño del almacén (n): ");
    scanf("%d", n);

    printf("Ingrese la cantidad de productos en el pedido (c): ");
    scanf("%d", c);

    *pedido = (int*)malloc((*c) * sizeof(int));
    printf("Ingrese los pesos de los productos en el pedido:\n");
    for (i = 0; i < *c; i++) {
        scanf("%d", &(*pedido)[i]);
    }

    *almacen = (int**)malloc((*n) * sizeof(int*));
    printf("Ingrese los pesos de los productos en el almacén:\n");
    for (i = 0; i < *n; i++) {
        (*almacen)[i] = (int*)malloc((*n) * sizeof(int));
        for (j = 0; j < *n; j++) {
            scanf("%d", &(*almacen)[i][j]);
        }
    }
}

int backtrack(int i, int j, int peso_actual, int n, int **almacen, int **productos, int *pedido, int c) {
    if (i >= n || j >= n || peso_actual < 0) {
        return 0;
    }

    if (peso_actual == 0) {
        return 1;
    }

    if (productos[i][j] != 0 || almacen[i][j] == 0) {
        return 0;
    }

    productos[i][j] = almacen[i][j];

    if (backtrack(i + 1, j, peso_actual - almacen[i][j], n, almacen, productos, pedido, c)) {
        return 1;
    }

    if (backtrack(i, j + 1, peso_actual - almacen[i][j], n, almacen, productos, pedido, c)) {
        return 1;
    }

    productos[i][j] = 0;

    return 0;
}

int despachar_pedido(int n, int c, int *pedido, int **almacen, int ***productos) {
    int i, j, peso_total = 0;

    for (i = 0; i < c; i++) {
        peso_total += pedido[i];
    }

    if (peso_total == 0) {
        *productos = NULL;
        return 1;
    }

    *productos = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        (*productos)[i] = (int*)calloc(n, sizeof(int));
    }

    return backtrack(0, 0, peso_total, n, almacen, *productos, pedido, c);
}

void mostrar_almacen(int **productos, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (productos[i][j] == 0) {
                printf("0 ");
            } else {
                printf("%d ", productos[i][j]);
            }
        }
        printf("\n");
    }
}

void liberar_memoria(int n, int c, int *pedido, int **almacen, int **productos) {
    int i;

    free(pedido);

    for (i = 0; i < n; i++) {
        free(almacen[i]);
        free(productos[i]);
    }

    free(almacen);
    free(productos);
}

int main() {
    int n, c;
    int *pedido;
    int **almacen;
    int **productos;
    int es_posible_despachar;

    ingresar_datos(&n, &c, &pedido, &almacen);

    es_posible_despachar = despachar_pedido(n, c, pedido, almacen, &productos);

    if (es_posible_despachar) {
        printf("Se puede despachar. Las ubicaciones del pedido son las siguientes:\n");
        mostrar_almacen(productos, n);
    } else {
        printf("No se puede despachar el pedido.\n");
    }

    liberar_memoria(n, c, pedido, almacen, productos);

    return 0;
}


/*
5
4 
5 7 7 8
2 8 6 6 7
7 6 8 5 10
2 9 10 7 6
5 9 8 11 7
3 2 8 10 3
*/

