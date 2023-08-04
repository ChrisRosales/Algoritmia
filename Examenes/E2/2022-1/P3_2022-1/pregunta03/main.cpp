/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * Pregunta3 del 2022-1
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "abb.h"
using namespace std;

const char *input01 = "input01.txt";
//const char *input02 = "input02.txt";

// Funciones
void leerPalabra(ifstream &file, ABB *palabra, int cnt);
void balword(int cont, int cnt_palabra, ABB palabra);
void impresion_Inicial(int cont, int cnt);
bool verificacion(int cnt, ABB palabra, string posible_palabra, int i = 1, bool centinela = true);
bool ordenCorrecto(NodoABB *palabra, Elemento e);

int main() {
    // Arbol binario con la palabra
    ABB palabra;
    construir(&palabra);
    int cnt_palabra;
    // Apertura del archivo
    ifstream file(input01, ios::in);
    if (!file) {
        cout << "No se pudo abrir el archivo : " << input01 << endl;
    }
    file >> cnt_palabra;
    // Leemos la palabra del archivo
    leerPalabra(file, &palabra, cnt_palabra);
    //    mostrarEnOrden(palabra.raiz); // se utilizo para comprobar la correcta lectura de la palabra
    file.close(); // Cerramos el archivo, pues ya fue leido perfectamente
    cout << "BIENVENIDO AL JUEGO BALWORD\n"
            << "DESCUBRE LA PALABRA DE " << cnt_palabra << "LETRAS. "
            << "TIENES MAXIMO " << cnt_palabra << "INTENTOS\n";
    impresion_Inicial(1, cnt_palabra);
    int cont = 1;
    balword(cont, cnt_palabra, palabra);
    return 0;
}

void leerPalabra(ifstream &file, ABB *palabra, int cnt) {
    if (cnt == 0) return;
    Elemento e;
    file >> e.id >> e.letra;
    insertar(palabra, e);
    leerPalabra(file, palabra, cnt - 1);
}

void balword(int cont, int cnt, ABB palabra) {
    if (cont > cnt) {
        cout << "Lo siento se acabaron los intentos.\n";
        return;
    }
    char posible_palabra[10];
    cout << "\nIntento " << cont << ": ";
    cin >> posible_palabra;
    // Hasta que ingrese una palabra con la longitud adecuada
    while (strlen(posible_palabra) != cnt) {
        cout << "La longitud de la palabra ingresada no es la correcta. Vuelva a intentarlo.";
        cout << "\nIntento " << cont << ": ";
        cin >> posible_palabra;
    }
    // pasamos a verificar la palabra
    if (verificacion(cnt, palabra, posible_palabra)) {
        cout << "\nFelicitaciones por haber resuelto el reto\n";
        return;
    }
    cout << endl; // salto de linea para mayor orden
    balword(cont + 1, cnt, palabra); // nos movemos al sgte intento
}

void impresion_Inicial(int cont, int cnt) {
    if (cont == cnt) {
        cout << endl;
        return;
    }
    cout << '-';
    impresion_Inicial(cont + 1, cnt);
}

bool verificacion(int cnt, ABB palabra, string posible_palabra, int i, bool centinela) {
    if (i > cnt) {
        return centinela;
    }
    Elemento e;
    e.id = i;
    e.letra = posible_palabra[i - 1];
    if (buscar(palabra.raiz, e)) { // verificamos si la letra se encuentra en la palabra
        if (ordenCorrecto(palabra.raiz, e)) {
            cout << e.letra << " ";
        } else {
            cout << e.letra << "(X) ";
            centinela = false;
        }
    } else {// EN caso de no encontrar se imprimra un espacio en blanco
        cout << "_ ";
        centinela = false;
    }
    // verificamos la siguiente letra
    return verificacion(cnt, palabra, posible_palabra, i + 1, centinela);
}

bool ordenCorrecto(NodoABB *palabra, Elemento e) {
    if (palabra != nullptr) {
        if (palabra->elem.letra == e.letra) {
            return palabra->elem.id == e.id;
        } else if (e.id < palabra->elem.id) {
            return ordenCorrecto(palabra->hizq, e);
        } else {
            return ordenCorrecto(palabra->hder, e);
        }
    }
    return false;
}