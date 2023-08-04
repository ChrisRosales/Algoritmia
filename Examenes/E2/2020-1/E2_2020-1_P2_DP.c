#include <stdio.h>

void mostrarFormas(int n, int formas[]) {
    printf("Por ejemplo, si hay %d cajas, existen %d formas para enviarlas:\n", n, formas[n]);
	int i,j;
    for ( i = 1; i <= n; i++) {
        printf("Forma %d: ", i);

        if (i == 1) {
            printf("{%d}", i);
        } else {
            printf("{%d", i);
            for ( j = 1; j < i; j++) {
                printf(", %d", j);
            }
            printf("}");
        }

        printf("\n");
    }
}

void contarFormas(int n) {
    int formas[n + 1];
    formas[0] = 1;
    formas[1] = 1;
	int i;
    for ( i = 2; i <= n; i++) {
        formas[i] = formas[i - 1] + formas[i - 2];
    }

    mostrarFormas(n, formas);
}

int main() {
    int n;
    printf("Ingrese el número de cajas: ");
    scanf("%d", &n);

    contarFormas(n);

    return 0;
}


