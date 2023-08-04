/* 
 * File:   main.cpp
 * Pregunta: 2
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 22 de abril de 2023, 16:40
 */

#include <iostream>
#include <iomanip>
#include <cmath>

void CargarCromosoma(int *cromosoma, int size, int num);
void LeerDatos(int *nivel, int *cnt_robots, int **niveles, int **peso_vidrio, int **robots);
void OrdenarDatos(int nivel, int *niveles, int *peso_vidrio);
void cambiarValores(int *peso_vidrio, int i, int j);
int peso_maximo_robot(int *robots, int cnt_robots);
bool esValido(int * cromosoma, int size, int nivel, int *peso_vidrio, int robot_max_peso);
void imprimriResultado(int solucion, int *cromosoma, int size);
// FUnciones item C
void ordernarRobots(int *robots, int cnt_robots);

using namespace std;

int main(int argc, char** argv) {

    cout << "\n=========================================================\n"
            << "ITEM B\n"
            << "=========================================================\n";
    int nivel, cnt_robots;
    int *niveles, *peso_vidrio, *robots;
    LeerDatos(&nivel, &cnt_robots, &niveles, &peso_vidrio, &robots);
    // Vamos a ordenar los datos según los niveles
    // para que sea más facil realiza la busqueda de los paquetes
    OrdenarDatos(nivel, niveles, peso_vidrio);

    // No necesitamos ver para todos los robots; solo para el más pesado; los demás van a tener que seguir
    // ese mismo camiono
    int robot_max_peso = peso_maximo_robot(robots, cnt_robots);
    cout << "PESO: " << robot_max_peso << endl;
    int combinaciones = pow(2, nivel * 2);
    int size = nivel * 2;
    int *cromosoma = new int[size];
    int solucion = 1;

    for (int i = 1; i < combinaciones; i++) {
        CargarCromosoma(cromosoma, size, i);
        if (!esValido(cromosoma, size, nivel, peso_vidrio, robot_max_peso)) continue;
        imprimriResultado(solucion, cromosoma, size);
        solucion++;
    }
    // Borar arreglos creados dinámicamente
    // Porque vamos a volver a leer, así se puede ingresar un robot que sobrepase el peso de los demás
    delete[] niveles;
    delete[] peso_vidrio;
    delete[] robots;
    cout << "\n=========================================================\n"
            << "ITEM C\n"
            << "=========================================================\n";
    // Para el problema anterior, solo usamos el peso maximo; para esta ocación
    // ordenaremos el peso de los robots de forma descendente
    LeerDatos(&nivel, &cnt_robots, &niveles, &peso_vidrio, &robots);
    solucion = 0;
    int index_robot = 0;
    OrdenarDatos(nivel, niveles, peso_vidrio);
    ordernarRobots(robots, cnt_robots);
    while (solucion == 0 && index_robot < cnt_robots) {
        for (int i = 1; i < combinaciones; i++) {
            CargarCromosoma(cromosoma, size, i);
            if (!esValido(cromosoma, size, nivel, peso_vidrio, robots[index_robot])) continue;
            solucion++;
            imprimriResultado(solucion, cromosoma, size);
        }
        // suponemos que no se pudo encontrar un camino, porque el robot era muy pesado
        if (solucion == 0) {
            index_robot++;
        }
    }
    if (solucion == 0 || index_robot > 0) { // como mínimo un roboto no ingreso, o ninguno puede pasar el puente
        cout << "El peso de los robots que no puede pasar por que tiene demasiado peso son los siguiente: \n";
        for (int i = 0; i < index_robot; i++) {
            cout << robots[i] << "\n";
        }
    }

    // Borrrar arreglos creados dinamicamente:
    delete[] niveles;
    delete[] peso_vidrio;
    delete[] robots;
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

void LeerDatos(int *nivel, int *cnt_robots, int **niveles, int **peso_vidrio, int **robots) {
    cout << "Ingrese los niveles que tiene el puente: ";
    cin >> *nivel;
    cout << "Ingrese la cantidad de robots: ";
    cin >> *cnt_robots;
    // La forma como voy a guardar los datos es de la siguiente forma
    // Un arreglo para los niveles, según se valla ingresando 
    // Y para los vidrios va a ser en juegos de pares
    // primero el izquierdo y luego el derecho
    (*niveles) = new int[*nivel];
    (*peso_vidrio) = new int[2 * (*nivel)];
    for (int i = 0; i < *nivel; i++) {
        cout << "Ingrese el nivel: ";
        cin >> (*niveles)[i];
        cout << "Ingrese sus pesos, primero izquierda y luego derecha: ";
        for (int j = i * 2; j < i * 2 + 2; j++) {
            cin >> (*peso_vidrio)[j];
        }
    }
    cout << "Ingrese el peso de los robots: ";
    (*robots) = new int[*cnt_robots];
    for (int i = 0; i < *cnt_robots; i++) {
        cin >> (*robots)[i];
    }
}

void OrdenarDatos(int nivel, int *niveles, int *peso_vidrio) {
    for (int i = 0; i < nivel - 1; i++) {
        for (int j = i + 1; j < nivel; j++) {
            if (niveles[j] < niveles[i]) {
                // cambimos niveles
                int aux = niveles[i];
                niveles[i] = niveles[j];
                niveles[j] = aux;
                // Cambiar valores
                cambiarValores(peso_vidrio, i * 2, j * 2);
            }
        }
    }

}

void cambiarValores(int *peso_vidrio, int i, int j) {
    int aux = peso_vidrio[i];
    peso_vidrio[i] = peso_vidrio[j];
    peso_vidrio[j] = aux;
    aux = peso_vidrio[i + 1];
    peso_vidrio[i + 1] = peso_vidrio[j + 1];
    peso_vidrio[j + 1] = aux;
}

int peso_maximo_robot(int *robots, int cnt_robots) {
    int max = 0;
    for (int i = 0; i < cnt_robots; i++) {
        max = robots[i] > max ? robots[i] : max;
    }
    return max;
}

bool esValido(int *cromosoma, int size, int nivel, int *peso_vidrio, int robot_max_peso) {
    // para validar que no se este usando las 2 direcciones al mismo tiempo
    bool *niveles = new bool[nivel];
    for (int i = 0; i < nivel; i++) {
        niveles[i] = false;
    }

    for (int i = 0; i < size; i++) {
        if (!cromosoma[i]) continue;
        if (niveles[i / 2]) {
            delete[] niveles;
            return false; // el nivel ya fue usado
        }
        niveles[i / 2] = true; // El nivel esta siendo usado
        // se rompio el piso
        if (peso_vidrio[i] < robot_max_peso) {
            delete[] niveles;
            return false; // rompio el piso
        }
    }
    for (int i = 0; i < nivel; i++) {
        if (niveles[i] == false) // no se uso un nivel
            return false;
    }

    // Borramos el arreglo uxiliar
    delete[] niveles;
    return true;
}

void imprimriResultado(int solucion, int *cromosoma, int size) {
    cout << "Solucion: " << solucion << "\n";
    for (int i = 0; i < size; i++) {
        if (!cromosoma[i]) continue;
        cout << "Nivel: " << (i / 2 + 1);
        if (i % 2 == 0) {
            cout << " Izquierda\n";
        } else {
            cout << " Derecha\n";
        }
    }
}

void ordernarRobots(int *robots, int cnt_robots) {
    for (int i = 0; i < cnt_robots - 1; i++) {
        for (int j = i + 1; j < cnt_robots; j++) {
            if (robots[j] >= robots[i]) {
                int aux = robots[i];
                robots[i] = robots[j];
                robots[j] = aux;
            }
        }
    }
}