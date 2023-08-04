#include <iostream>


using namespace std;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int sum(int arr[], int from, int to) {
    int total = 0;
    for (int i = from; i <= to; i++) {
        total += arr[i];
    }
    return total;
}

int maxTasks(int arr[], int n, int k) {
    int i, j, p, temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int dp[k + 1][n + 1];

    // k = 1
    for (i = 1; i <= n; i++) {
        dp[1][i] = sum(arr, 0, i - 1);
    }

    // n = 1
    for (i = 1; i <= k; i++) {
        dp[i][1] = arr[0];
    }

    // 2 o más
    for (i = 2; i <= k; i++) {
        for (j = 2; j <= n; j++) {
            int maximo = INT_MAX;

            for (p = 1; p <= j; p++) {
                maximo = min(maximo, max(dp[i - 1][p], sum(arr, p, j - 1)));
            }

            dp[i][j] = maximo;
        }
    }

    for (i = 1; i <= k; i++) {
        for (j = 1; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[k][n];
}

int main() {
    int arr[] = { 10, 25, 40, 45, 60 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    cout << "El tiempo máximo que si se divide la línea en "<<k<<" partes "<<"es: " << maxTasks(arr, n, k) << endl;
    return 0;
}

