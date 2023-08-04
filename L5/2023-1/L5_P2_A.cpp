#include <iostream>

using namespace std;

bool canFulfillOrders(int* lotSizes, int n, int* orderSizes, int m) {
    bool dp[10001] = { false };

    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = 10000; j >= lotSizes[i]; j--) {
            if (dp[j - lotSizes[i]]) {
                dp[j] = true;
            }
        }
    }

    // Agregamos un bucle adicional para imprimir la matriz de soluciones
    cout << "Matriz de soluciones de la programación dinámica:" << endl;
    for (int i = 0; i <= 10000; i++) {
        cout << dp[i] << " ";
        if (i % 10 == 0 && i != 0) {
            cout << endl;
        }
    }
    cout << endl;

    for (int i = 0; i < m; i++) {
        if (!dp[orderSizes[i]]) {
            return false;
        }
    }
	
    return true;
}

int main() {
    int n, m;
    cout << "Ingrese la cantidad de tipos de lotes producidos: ";
    cin >> n;

    int lotSizes[n];
    cout << "Ingrese los tamaños de los tipos de lotes producidos: ";
    for (int i = 0; i < n; i++) {
        cin >> lotSizes[i];
    }

    cout << "Ingrese la cantidad de pedidos: ";
    cin >> m;

    int orderSizes[m];
    cout << "Ingrese los tamaños de los pedidos: ";
    for (int i = 0; i < m; i++) {
        cin >> orderSizes[i];
    }

    if (canFulfillOrders(lotSizes, n, orderSizes, m)) {
        cout << "Se pueden atender todos los pedidos." << endl;
    } else {
        cout << "No se pueden atender todos los pedidos." << endl;
    }

    return 0;
}
/*
4
5 2 8 4
3
9 6 12

4
5 2 8 4
2
4 3

*/
