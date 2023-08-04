#include <stdio.h>

#define MAX_COL 100

// Variable para saber el max de columnas de la matriz
int maxCol;

// Variables que guardan la potencia y la columna del
// mayor impacto
int col;
int potencia;

// Función que busca la posición de la fila donde se encuentra
// el mayor impacto
int busqueda(int A[][MAX_COL], int col, int K, int ini, int fin) {
    if (ini > fin)
        return ini;

    int med = (ini + fin) / 2;

    if (A[med][col] == K)
        return med;

    if (A[med - 1][col] == 0)
        return busqueda(A, col, K, med, fin);
    else
        return busqueda(A, col, K, ini, med - 1);
}

// Suma los valores de cada subparte del territorio
int calcularPeso(int iniL, int finL, int iniW, int finW, int territorio[][MAX_COL]) {
    int peso = 0;
    int i, j;
    for (j = iniW; j <= finW; j++) {
        for (i = iniL; i <= finL; i++) {
            peso += territorio[j][i];
        }
    }
    return peso;
}

// Busca la columna donde está el mayor impacto, para ello suma los pesos de
// cada subparte del territorio, finalmente devuelve el valor del impacto y 
// la columna donde se encuentra ese impacto
void mostrarCol(int territorio[][MAX_COL], int iniL, int finL, int iniW, int finW) {
    int iniL_2 = iniL, finL_2 = finL, medioL;
    medioL = (iniL + finL) / 2;

    if ((iniL == finL) && (iniW == finW)) {
        col = iniL;
        potencia = territorio[iniW][iniL + 1];
        return;
    }

    if (iniL != finL) {
        int pesoL_1 = calcularPeso(iniL, medioL, iniW, finW, territorio);
        int pesoL_2 = calcularPeso(medioL + 1, finL, iniW, finW, territorio);

        if (pesoL_1 > pesoL_2)
            finL_2 = medioL;
        else
            iniL_2 = medioL + 1;
    }

    int iniW_2 = iniW, finW_2 = finW, medioW;
    medioW = (iniW + finW) / 2;

    if (iniW != finW) {
        int pesoW_1 = calcularPeso(iniL_2, finL_2, iniW, medioW, territorio);
        int pesoW_2 = calcularPeso(iniL_2, finL_2, medioW + 1, finW, territorio);

        if (pesoW_1 > pesoW_2)
            finW_2 = medioW;
        else
            iniW_2 = medioW + 1;
    }

    mostrarCol(territorio, iniL_2, finL_2, iniW_2, finW_2);
}

int main() {
    int n, m;
    printf("Ingrese las dimensiones del terreno:\n");
    scanf("%d %d", &n, &m);

    printf("Ingrese los valores propios del territorio:\n");
    int territorio[m][MAX_COL], i, j;
    maxCol = n;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &territorio[i][j]);
        }
    }

    // Parte A
    mostrarCol(territorio, 0, n - 1, 0, m - 1);
    printf("Para este juego de datos, la potencia más alta de la bomba es %d,", potencia);
    printf(" y la columna donde se ubica es %d.\n", col + 1);

    // Parte B
    // Para saber la fila donde está el mayor impacto, se realiza una búsqueda binaria
    int posFila = busqueda(territorio, col + 1, potencia, 0, m - 1);
    printf("La fila con el mayor impacto es la %d.\n", posFila);

    return 0;
}
/*
7 10
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 1 1 1
0 0 0 0 1 2 2
0 0 0 0 1 2 3
0 0 0 0 1 2 2
0 0 0 0 1 1 1
0 0 0 0 0 0 0
*/

/*
7 8
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 1 1 1 0 0 0
0 1 2 1 0 0 0
0 1 1 1 0 0 0
0 0 0 0 0 0 0
*/
