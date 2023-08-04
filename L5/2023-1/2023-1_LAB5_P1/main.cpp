/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 24 de junio de 2023, 15:04
 */

#include <iostream>
#include <fstream>

#define MAX 10
#define FILE_NAME "input.txt"// nombre del archivo
using namespace std;

// Variables globales
int *lista;
int y = 0;
int maxBeneficios = -99999;
int soluciones = 0;
int maxSolucion = 0;
// Variable que va a guardar cada uno de los controles de seguridad

typedef struct {
    int idControl;
    int inversion;
    int cntRequesitos;
    int *requisitos;
    int beneficios;
} ControlDeSeguridad;

// Lectura de archivos desde un TXT

void lecturaArchivos(ControlDeSeguridad **control, int *cntControles, int *presupuesto) {
    ifstream archivo(FILE_NAME, ios::in);
    if (!archivo) {
        cout << "No se pudo abrir el siguiente archivos para su lectura: "
                << FILE_NAME << "\n";
        exit(1);
    }
    archivo >> *presupuesto; // Presupuesto del proyecto
    archivo >> *cntControles; // cantidad de controles
    *control = new ControlDeSeguridad[*cntControles];
    for (int i = 0; i < *cntControles; i++) {
        archivo >> (*control)[i].idControl
                >> (*control)[i].inversion
                >> (*control)[i].cntRequesitos;
        int cant = (*control)[i].cntRequesitos;
        if (cant > 0) {
            (*control)[i].requisitos = new int[cant];
            for (int j = 0; j < cant; j++) {
                archivo >> (*control)[i].requisitos[j];
            }
        } else {
            (*control)[i].requisitos = nullptr; // como no tienen predecesores, hagamos que apunte al NULO
        }
        archivo >> (*control)[i].beneficios;
    }
    archivo.close();
}

/* La funcion de validacion es la misma para tanto la pregunta A como para la pregunta B*/
bool valida(int k, int n, ControlDeSeguridad *control) {
    if (control[k].cntRequesitos == 0) {
        return true;
    }
    bool predecesor = false;
    for (int i = 0; i < control[k].cntRequesitos; i++) {
        predecesor = false; // suponemos que el predesor no existe
        for (int j = 0; j < n; j++) {
            if (control[k].requisitos[i] == lista[j]) { // verificamos si el predecesor existe
                predecesor = true;
            }
        }
        if (!predecesor) { // No se encontro el predecesor
            break;
        }
    }
    return predecesor;
}

///////////////////////////////////////////////////////////////////////////////
/*                        FUNCIONES ITEM A                                   */
///////////////////////////////////////////////////////////////////////////////

int empaca(int i, int n, int presupuesto, ControlDeSeguridad *control) {
    if (i == n || presupuesto < 0) {
        return 0;
    }
    if (control[i].inversion - presupuesto == 0 && valida(i, y, control)) {
        soluciones++;
        lista[y] = control[i].idControl;
        cout << "Solucion " << soluciones << ": ";
        for (int z = 0; z <= y; z++) {
            cout << "P" << lista[z] << " ";
        }
        cout << endl;
    }
    lista[y] = control[i].idControl;
    y++;
    if (valida(i, y, control) && empaca(i + 1, n, presupuesto - control[i].inversion, control)) {
        return 1;
    } else {
        y--;
        return empaca(i + 1, n, presupuesto, control);
    }
}
///////////////////////////////////////////////////////////////////////////////
/*                        FUNCIONES ITEM B                                   */
///////////////////////////////////////////////////////////////////////////////

int calcularBeneficios(int k, int cnt, ControlDeSeguridad *control) {
    int beneficio = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < cnt; j++) {
            if (lista[i] == control[j].idControl) {
                beneficio += control[j].beneficios;
                break;
            }
        }
    }
    return beneficio;
}

int empacaBeneficio(int i, int n, int presupuesto, ControlDeSeguridad *control) {
    if (i == n || presupuesto < 0) {
        return 0;
    }
    if (control[i].inversion - presupuesto == 0 && valida(i, y, control)) {
        soluciones++;
        lista[y] = control[i].idControl;
        cout << "Solucion " << soluciones << ": ";
        for (int z = 0; z <= y; z++) {
            cout << "P" << lista[z] << " ";
        }
        cout << endl;
        // Calculamos los beneficios
        int beneficios = calcularBeneficios(y, n, control);
        cout << "Beneficio: " << beneficios << endl;
        if (beneficios > maxBeneficios) {
            maxBeneficios = beneficios;
            maxSolucion = soluciones;
        }
    }
    lista[y] = control[i].idControl;
    y++;
    if (valida(i, y, control) && empacaBeneficio(i + 1, n, presupuesto - control[i].inversion, control)) {
        return 1;
    } else {
        y--;
        return empacaBeneficio(i + 1, n, presupuesto, control);
    }
}

int main() {
    ControlDeSeguridad *controles;
    int cntControles, presupuesto;
    lecturaArchivos(&controles, &cntControles, &presupuesto);
    lista = new int[cntControles];
    // Verificacion de la lectura de datos
    /*for (int i = 0; i < cntControles; i++) {
        cout << controles[i].idControl << " "
                << controles[i].inversion << " "
                << controles[i].cntRequesitos<< " ";
        int cant = controles[i].cntRequesitos;
        if (cant > 0) {
            for (int j = 0; j < cant; j++) {
                cout << controles[i].requisitos[j] << " ";
            }
        }
        cout << controles[i].beneficios << endl;
    }*/
    cout << "PREGUNTA A:\n";
    empaca(0, cntControles, presupuesto, controles);
    cout << "///////////////////////////////////////\n";
    cout << "PREGUNTA B:\n";
    soluciones = 0;
    empacaBeneficio(0, cntControles, presupuesto, controles);
    cout << "La solución que nos presenta el mayor beneficios es: " << maxSolucion
            << " con un total de beneficio de: " << maxBeneficios;

    return 0;
}
