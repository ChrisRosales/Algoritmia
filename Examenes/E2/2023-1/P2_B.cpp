#include <iostream>

using namespace std;

int calcularCombinaciones(int n) {
    // Creamos un arreglo de tamaño 2 para almacenar los resultados
    int dp[2] = { 0 };

    // Caso base: con 0 columnas, hay una combinación posible (ninguna ave)
    dp[0] = 1;

    // Caso base: con 1 columna, hay tres combinaciones posibles
    dp[1] = 3;

    // Calculamos las combinaciones para el resto de las columnas
    for (int i = 2; i <= n; i++) {
        // El número de combinaciones en la columna actual para los canarios es igual al número de combinaciones
        // en la columna anterior solo para los agapornis, ya que no se pueden colocar dos agapornis juntos
        int combinacionesCanarios = dp[1];

        // El número de combinaciones en la columna actual para los agapornis es igual a la suma de las combinaciones
        // en la columna anterior para ambos tipos de aves (canarios y agapornis)
        int combinacionesAgapornis = dp[0] + dp[1];

        // Actualizamos los valores en el arreglo
        dp[0] = combinacionesCanarios;
        dp[1] = combinacionesAgapornis;
    }

    // El resultado final es la suma de las combinaciones en la última columna para ambos tipos de aves
    int combinacionesTotales = dp[0] + dp[1];

    // Devolvemos el resultado
    return combinacionesTotales;
}

int main() {
    int n = 2; // Número de columnas

    int combinaciones = calcularCombinaciones(n);

    cout << "Se pueden formar " << combinaciones << " combinaciones con " << n << " columnas." << endl;

    return 0;
}

