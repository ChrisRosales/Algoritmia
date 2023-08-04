#include <iostream>
using namespace std;
#define N 5
#define M 6

void merge(int A[], int inicial, int medio, int final, int B[]) {
	int longitud1 = (medio + 1) - inicial;
	int longitud2 = final - medio;
	int P[longitud1 + 1];
	int Q[longitud2 + 1];
	int Muno[longitud1 + 1];
	int Ndos[longitud2 + 1];

	P[longitud1] = 999999;
	Q[longitud2] = 999999;
	Muno[longitud1] = 999999;
	Ndos[longitud2] = 999999;

	for (int i = inicial; i <= medio; i++) {
		P[i - inicial] = A[i];
		Muno[i - inicial] = B[i];
	}
	for (int i = medio + 1; i <= final; i++) {
		Q[i - (medio + 1)] = A[i];
		Ndos[i - (medio + 1)] = B[i];
	}
	int p = 0;
	int q = 0;
	int muno = 0;
	int mdos = 0;
	for (int i = inicial; i <= final; i++) {
		if (P[p] < Q[q]) {
			A[i] = P[p++];
			B[i] = Muno[muno++];
		} else {
			A[i] = Q[q++];
			B[i] = Ndos[mdos++];
		}
	}
}

void mergesort(int A[], int inicial, int final, int B[]) {
	if (inicial == final)
		return;
	int medio = (inicial + final) / 2;
	mergesort(A, inicial, medio, B);
	mergesort(A, medio + 1, final, B);
	merge(A, inicial, medio, final, B);
}

void guardararr(int arrcop[], int matriz_registro[][M]) {
	int k = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			arrcop[k] = matriz_registro[i][j];
			k++;
		}
	}
}

int cuentaCeros(int numero[], int inicio, int fin, int codvirus, int arrcopinstrucc[]) {
	if (inicio > fin) {
		return 0;
	}
	int medio = (inicio + fin) / 2;
	if (numero[medio] == codvirus) {
		return arrcopinstrucc[medio] + cuentaCeros(numero, inicio, medio - 1, codvirus, arrcopinstrucc) + cuentaCeros(numero, medio + 1, fin, codvirus, arrcopinstrucc);
	} else {
		return cuentaCeros(numero, inicio, medio - 1, codvirus, arrcopinstrucc) + cuentaCeros(numero, medio + 1, fin, codvirus, arrcopinstrucc);
	}
}

int main() {
	int cantarr = N * M;
	int codvirus, sum;
	int arrcop[cantarr], arrcopinstrucc[cantarr];
	int matriz_registro[N][M] = {
		{-1, -2, -3, -4, -5, -6},
		{-7, -8, 1, -9, 2, -10},
		{-11, 1, 2, -12, -13, -14},
		{-15, -16, -17, 1, -18, -19},
		{-20, 1, 2, -21, -22, -23}
	};
	int matriz_lineas_instruccion[N][M] = {
		{10, 5, 8, 9, 8, 1},
		{10, 5, 2, 8, 2, 3},
		{4, 2, 1, 4, 8, 1},
		{1, 2, 4, 3, 5, 3},
		{8, 3, 3, 8, 5, 3}
	};

	guardararr(arrcop, matriz_registro);
	guardararr(arrcopinstrucc, matriz_lineas_instruccion);
	mergesort(arrcop, 0, cantarr - 1, arrcopinstrucc);

	cout << "Ingrese el código de virus a buscar: ";
	cin >> codvirus;
	sum = cuentaCeros(arrcop, 0, cantarr - 1, codvirus, arrcopinstrucc);

	if (sum == 0) {
		cout << "El código de virus a buscar no se encuentra" << endl;
	} else {
		cout << "Para el virus de registro " << codvirus << ", se obtienen " << sum << " coincidencias en total." << endl;
	}

	return 0;
}

