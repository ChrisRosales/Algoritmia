/* 
 * File:   main.cpp
 * Pregunta: 1
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 22 de abril de 2023, 14:52
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void CargarCromosoma(int *cromosoma, int size, int num);
void leerDatos(int *cantidad_camiones, int **camiones, int *cantidad_paquetes, int **paquetes);
bool esValido(int *cromosoma, int size, int *camiones, int cnt_camiones, int *paquetes, int cnt_paquetes, int *carga_camiones);
int calcular_minimo(int *camiones, int cnt_camiones, int *carga_camiones);
int calcular_maximo(int *camiones, int cnt_camiones, int *carga_camiones);
void imprimirResultado(int *cromosoma, int size, int cnt_paquetes, int diferencia);
// FUncion usada para el item C
bool todosCamiones(int *cromosoma, int size, int cnt_camiones, int cnt_paquetes);

int main(int argc, char** argv) {

    cout << "\n=========================================================\n"
            << "ITEM B\n"
            << "=========================================================\n";

    int cantidad_camiones, // M
            cantidad_paquetes; // N
    int *camiones, *paquetes;

    leerDatos(&cantidad_camiones, &camiones, &cantidad_paquetes, &paquetes);

    /*
     * Para poder encontrar la cantidad de casos posibles
     * es si por ejemplo el primer camión puede tener todos los camiones
     * por lo tanto las combinaciones son : 
     * pow(2,M*N);
     * 0000  0000  0000
     * 1er   2do   3ero
     * 
     */
    int size = cantidad_camiones * cantidad_paquetes;
    int combinaciones = pow(2, size);
    int *cromosoma = (int *) new int[size];
    int combinacion_final; // variable que nos va a guardar la mejor combinacio
    int diferencia = 99999;

    for (int i = 1; i < combinaciones; i++) {
        CargarCromosoma(cromosoma, size, i);
        // Arreglo para saber cual a sido la carga que se le esta poniendo a cada camion
        int carga_camiones[cantidad_camiones];
        // En caso no es valido; avanzamos al siguiente cromosoma
        if (!esValido(cromosoma, size, camiones, cantidad_camiones, paquetes, cantidad_paquetes, carga_camiones)) continue;
        // Calcularemos la cantidad maxima y minima para poder ver la diferencia
        int minimo = calcular_minimo(camiones, cantidad_camiones, carga_camiones);
        int maximo = calcular_maximo(camiones, cantidad_camiones, carga_camiones);

        if (maximo - minimo <= diferencia) {
            combinacion_final = i;
            diferencia = maximo - minimo;
        }
    }

    CargarCromosoma(cromosoma, size, combinacion_final);
    // La impresión de los resultados no son las mismas que las soluciones mostradas en el enunciado
    // Pero cumplen con las indicaciones propuestas en el problema
    imprimirResultado(cromosoma, size, cantidad_paquetes, diferencia);


    cout << "\n=========================================================\n"
            << "ITEM C\n"
            << "=========================================================\n";
    diferencia = 99999; // Debemos de volver a cargar la diferencia
    for (int i = 1; i < combinaciones; i++) {
        CargarCromosoma(cromosoma, size, i);
        // Arreglo para saber cual a sido la carga que se le esta poniendo a cada camion
        int carga_camiones[cantidad_camiones];
        // En caso no es valido; avanzamos al siguiente cromosoma
        if (!esValido(cromosoma, size, camiones, cantidad_camiones, paquetes, cantidad_paquetes, carga_camiones)
                || !todosCamiones(cromosoma, size, cantidad_camiones, cantidad_paquetes)) continue;
        // Calcularemos la cantidad maxima y minima para poder ver la diferencia
        int minimo = calcular_minimo(camiones, cantidad_camiones, carga_camiones);
        int maximo = calcular_maximo(camiones, cantidad_camiones, carga_camiones);

        if (maximo - minimo <= diferencia) {
            combinacion_final = i;
            diferencia = maximo - minimo;
        }
    }
    CargarCromosoma(cromosoma, size, combinacion_final);
    imprimirResultado(cromosoma, size, cantidad_paquetes, diferencia);
    // Borramos los arreglos creados dinámicamente
    delete[] camiones;
    delete[] paquetes;
    delete[] cromosoma;
    return 0;
}

/**
 * Función para cargar el cromosoma
 * @param cromosoma: arreglo de carga
 * @param size: tamaño del cromosoma
 * @param num: numero que se va a pasar a binario
 */
void CargarCromosoma(int *cromosoma, int size, int num) {
    int i = size - 1;
    while (num != 0) {
        cromosoma[i] = num % 2;
        num /= 2;
        i--;
    }
    for (int j = 0; j <= i; j++) {
        cromosoma[j] = 0;
    }
}

/**
 * Vamos a leer la cantidad de camiones, y la cantidad de paquetes, 
 * así mismo vamos a crear un arreglo dinámico para poder almacenar los valores que
 * se tenga por cada camion y paquete
 * @param cantidad_camiones
 * @param camiones
 * @param cantidad_paquetes
 * @param paquetes
 */
void leerDatos(int *cantidad_camiones, int **camiones, int *cantidad_paquetes, int **paquetes) {
    cout << "Datos de Ingreso: ";
    cin >> *cantidad_camiones >> *cantidad_paquetes;
    cout << "Capacidades en Kg: ";
    (*camiones) = new int[*cantidad_camiones];
    for (int i = 0; i < *cantidad_camiones; i++) {
        cin >> (*camiones)[i];
    }
    cout << "Paqetes en Kg: ";
    (*paquetes) = new int[*cantidad_paquetes];
    for (int i = 0; i < *cantidad_paquetes; i++) {
        cin >> (*paquetes)[i];
    }
}

/**
 * Funcion que va a evaluar si el cromosoma es valido
 * 1) que cada paquete solo sea asignado a cada camion, ya que no pueden haber repeticiones
 * 2) de que si los paquetes asignado a dicho camion, no exedan la carga que puede llevar el camion
 * @param cromosoma
 * @param size
 * @param camiones
 * @param cnt_camiones
 * @param paquetes
 * @param cnt_paquetes
 * @return 
 */
bool esValido(int *cromosoma, int size, int *camiones, int cnt_camiones, int *paquetes, int cnt_paquetes, int *carga_camiones) {
    // Iniciamos la carga de los camiones en 0
    for (int i = 0; i < cnt_camiones; i++) {
        carga_camiones[i] = 0;
    }

    int index_camion = 0; // empezamos por el primer camion

    /*Este arreglo nos va a servir para poder saber si ya se cargo el paquete a un camion*/
    bool paquetes_usados[cnt_paquetes];
    for (int i = 0; i < cnt_paquetes; i++) {
        paquetes_usados[i] = false;
    }

    for (int i = 0; i < size; i++) {
        // Si el cromosoma no es valido; entonces se continua con el siguiente
        if (!cromosoma[i]) continue;
        if (i / cnt_paquetes != index_camion) {
            index_camion++; // nos movemos al siguiente camion
        }
        // Para este momento, ya validamos que cromosoma es valido, osea que el paquete fue escogido para cargalo en uno de los camiones
        // Pero si ya fue esgocido, será verdadero, y por lo tanto se tiene que retornar falso
        if (paquetes_usados[i % cnt_paquetes])
            return false;
        // Validamos que el paquete ya es usado
        paquetes_usados[i % cnt_paquetes] = true;
        carga_camiones[index_camion] += paquetes[i % cnt_paquetes];
        // Sobre exedio la carga posible del camion; por lo tanto es false
        if (carga_camiones[index_camion] > camiones[index_camion])
            return false;
    }
    // Si acabo el recorrido, y no encontro ningún incoveniente para cargar en dicho orden
    // Entonces retornamos true
    return true;

}
/* Puede que mi validar no sea más claro, por lo que se va intentar explicar lo que se esta haciendo
 * con el primer caso de prueba que esta en el ENUNCIADO
 * =========================================
 * Para saber a que camión se esta haciendo referencia
 * 0 1 2 3   / 4 == 0
 * 4 5 6 7   / 4 == 1
 * 8 9 10 11 / 4 == 2
 * ===============================
 * Para saber si el paquete esta siendo usado
 * 0 4 8  % 4 == 0 // paquete 0
 * 1 5 9  % 4 == 1 // paquete 1
 * 2 6 10 % 4 == 2 // paquete 2
 * 3 7 11 % 4 == 3 // paquete 3
 * ===========================================
 * Donde el 4 es cnt_paquetes
 */

/**
 * Calcular la minima diferencia entre la carga del camion y los pesos de los paquetes
 * asignados
 * 
 * @param camiones
 * @param cnt_camiones
 * @param carga_camiones
 * @return 
 */
int calcular_minimo(int *camiones, int cnt_camiones, int *carga_camiones) {
    int minimo = 99999;
    for (int i = 0; i < cnt_camiones; i++) {
        minimo = camiones[i] - carga_camiones[i] <= minimo ? camiones[i] - carga_camiones[i] : minimo;
    }
    return minimo;
}

/**
 * Calcular la maxima diferencia entre la carga del camion y los pesos de los paquetes
 * @param camiones
 * @param cnt_camiones
 * @param carga_camiones
 * @return 
 */
int calcular_maximo(int *camiones, int cnt_camiones, int *carga_camiones) {
    int maximo = 0;
    for (int i = 0; i < cnt_camiones; i++) {
        maximo = camiones[i] - carga_camiones[i] >= maximo ? camiones[i] - carga_camiones[i] : maximo;
    }
    return maximo;
}

void imprimirResultado(int *cromosoma, int size, int cnt_paquetes, int diferencia) {
    for (int i = 0; i < size; i++) {
        if (!cromosoma[i]) continue;
        cout << "Camion: " << (i / cnt_paquetes + 1) << " Paquete: " << (i % cnt_paquetes + 1) << "\n";
    }
    cout << "Diferencia maxima: " << diferencia << "\n";
}

/**
 * Funcion utilizada en el item C; con esta funcion vamos a poder validar si todos los camiones estan siendo usado
 * @param cromosoma
 * @param size
 * @param camiones
 * @return 
 */
bool todosCamiones(int *cromosoma, int size, int cnt_camiones, int cnt_paquetes) {
    bool *camiones_usados = new bool [cnt_camiones];
    for (int i = 0; i < cnt_camiones; i++) {
        camiones_usados[i] = false;
    }

    for (int i = 0; i < size; i++) {
        if (!cromosoma[i]) continue;
        camiones_usados[i / cnt_paquetes] = true;
    }
    for (int i = 0; i < cnt_camiones; i++) {
        if (camiones_usados[i] == false)
            return false;
    }
    delete[] camiones_usados;
    return true;
}
















