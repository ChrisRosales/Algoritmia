/* 
 * File:   main.cpp
 * Author: Jesus Huayhua Flores
 * Codigo: 20196201
 * 
 * Created on 20 de mayo de 2023, 8:05
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <csignal>
#include "lista.h"

#define FILE_NAME "input.txt"

using namespace std;


void leerGuerreros(int *n, int *cnt, Lista *warriors);
void insertarGuerros(Lista *warrios, Lista *bowser, Lista *peach, Lista *donkey);
void eliminarCabeza(Lista *L);
void insertarOrdenar(Lista *L, Elemento e);
void mostrarEjercito(Lista L);
void mostrarNivelEjercito(Lista L);
void batalla(Lista *bowser, Lista *peach, Lista *donkey, int n);
int leveEjercito(Lista L);
void fusionar(Lista &L1, Lista &L2);
void EliminaNodo(Lista *L,Elemento e);
int main(int argc, char** argv) {
    Lista bowser, peach, donkey; // listas de los ejercitos
    Lista warriors;
    int n, cnt_guerreros; // cantidad de batallas, y cantidad de guerreros en general
    construir(&bowser);
    construir(&peach);
    construir(&donkey);
    construir(&warriors);
    // ingresamos el nombre de los ejercitos
    bowser.ejercicito = "Bowser";
    peach.ejercicito = "Peach";
    donkey.ejercicito = "DonKey Kong";
    warriors.ejercicito = "Lista Guerreros";
    // insertamos los guerreros
    leerGuerreros(&n, &cnt_guerreros, &warriors);
    insertarGuerros(&warriors, &bowser, &peach, &donkey);
    //    mostrarEjercito(warriors);
    mostrarEjercito(bowser);
    mostrarNivelEjercito(bowser);
    mostrarEjercito(peach);
    mostrarNivelEjercito(peach);
    mostrarEjercito(donkey);
    mostrarNivelEjercito(donkey);
    batalla(&bowser, &peach, &donkey, n);
    return 0;
}

void leerGuerreros(int *n, int *cnt, Lista *warriors) {
    ifstream archivo(FILE_NAME, ios::in);
    if (!archivo) {
        cout << "No se pudo abrir el archvo\n";
        exit(1);
    }
    cout << "Ingrese el valor de n: ";
    archivo >> *n;
    cout << "Ingrese la cantidad de guerreros: ";
    archivo >> *cnt;
    Elemento aux;
    for (int i = 0; i < *cnt; i++) {
        archivo >> aux;
        insertarFinal(warriors, aux);
    }
    archivo.close();
}

void insertarGuerros(Lista *warrios, Lista *bowser, Lista *peach, Lista *donkey) {
    while (!esListaVacia(*warrios)) {
        int ejercitio = warrios->cabeza->elem % 10;
        Elemento level = warrios->cabeza->elem / 10;
        switch (ejercitio) {
            case 1:
                bowser->numEjercitio = 1;
                insertarOrdenar(bowser, level);
                break;
            case 2:
                peach->numEjercitio = 2;
                insertarOrdenar(peach, level);
                break;
            case 3:
                donkey->numEjercitio = 3;
                insertarOrdenar(donkey, level);
                break;
        }
        eliminarCabeza(warrios); // eliminamos la cabeza
    }
}

void insertarOrdenar(Lista *L, Elemento e) {
    if (esListaVacia(*L)) {
        Nodo *nuevo = crearNodo(e, nullptr);
        L->cabeza = nuevo;
        L->cola = nuevo;
    } else {
        Nodo *ant = ubicarAnterior(*L, e);
        if (ant == nullptr) { // insertamos al final
            if (L->cabeza->elem > e)
                insertarComienzo(L, e);
            else {
                Nodo *nuevo = crearNodo(e, nullptr);
                L->cola->sig = nuevo;
                L->cola = nuevo;
            }
        } else {
            Nodo *nuevo = crearNodo(e, nullptr);
            nuevo->sig = ant->sig;
            ant->sig = nuevo;
        }
    }
}

void eliminarCabeza(Lista *L) { // eliminamos la cabeza
    if (esListaVacia(*L)) return; // no hay nada que eliminar
    Nodo *del = L->cabeza;
    Nodo *aux = L->cabeza->sig;
    L->cabeza = aux;
    delete del;

}

void mostrarEjercito(Lista L) {
    cout << "\nEjercito " << L.numEjercitio << " - ";
    mostrar(L);
}

void mostrarNivelEjercito(Lista L) {
    if(L.cabeza == nullptr) return;
    Nodo *aux = L.cabeza;
    int sumLevel = 0;
    while (aux != nullptr) {
        sumLevel += aux->elem;
        aux = aux->sig;
    }
    cout << "Nivel de Ataque Total del Ejercito " << L.numEjercitio << ":" << sumLevel << endl;
}

void batalla(Lista *bowser, Lista *peach, Lista *donkey, int n) {
    bool refuerzo = true;
    while (!esListaVacia(*bowser) and !esListaVacia(*peach)) {
        cout << "\nInicia la batalla: \n";
        // mostarmos a los ejercitos
        mostrarEjercito(*bowser);
        mostrarEjercito(*peach);
        Nodo *soldadoB, *soldadoP; // soldado de Bowser y Peach, para recorrer la lista
        soldadoB = bowser->cabeza;
        soldadoP = peach->cabeza;
        Elemento peleadorB = soldadoB->elem;
        Elemento peleadorP = soldadoP->elem;
        // pelas
        for (int i = 0; i < n; i++) {
            cout << "Pelea " << (i + 1) << ":"
                    << peleadorB << " vs " << peleadorP;
            // Nos preparamos para la sgte batalla
            soldadoB = soldadoB->sig;
            soldadoP = soldadoP->sig;
            // la pelea
            // el Profeso Allasi, dijo que no se tiene que considerar 
            // caso de empate
            if (peleadorB > peleadorP) { // la pelea la gana bowser
                cout << ",gana " << peleadorB << endl;
                EliminaNodo(peach, peleadorP);
            } else if (peleadorB < peleadorP) { // la pele la gana peach
                cout << ",gana " << peleadorP << endl;
                EliminaNodo(bowser, peleadorB);
            }
            // una de los 2 ejercitos ya no pueden pelear, porque se quedaron sin soldados
            // Y el ejercito de peach ya no necesita ayudanecesita ayuda
            if (soldadoB == nullptr or (soldadoP == nullptr and !refuerzo)) {
                break;
            }
            // los siguiente peleadores
            peleadorB = soldadoB->elem;
            peleadorP = soldadoP->elem;
            // Peach no necesita todavia los refuerzos
            if (leveEjercito(*bowser) < leveEjercito(*peach)) continue;
        }
        // mostramos el nivel de ataue
        mostrarNivelEjercito(*bowser);
        mostrarNivelEjercito(*peach);
        if (refuerzo) { // usamos los refuerzos
            refuerzo = false;
            fusionar(*peach, *donkey); // fucionamos la lista
            cout << "El ejército de DonKey Kong se une al ejército de Peach" << endl;
        } else {
            cout << "Ya no se puede unir nadie al ejército de Peach" << endl;
        }
    }
    if(esListaVacia(*peach)){
        cout << "Gana la batalla " << bowser->ejercicito;
    }else{
        cout << "gana la batalla " << peach->ejercicito;
    }
}

int leveEjercito(Lista L) {
    Nodo *aux = L.cabeza;
    int sumLevel = 0;
    while (aux != nullptr) {
        sumLevel += aux->elem;
        aux = aux->sig;
    }
    return sumLevel;
}


// Codigo extraido de la semana 8, del zip PolloTiko, del profesor CUEVA

void fusionar(Lista &L1, Lista &L2) {
    if (L1.cola->elem < L2.cabeza->elem) { //L1 contiene solo elementos menores a L2
        L1.cola->sig = L2.cabeza;
        L1.cola = L2.cola;
    } else
        if (L2.cola->elem < L1.cabeza->elem) { //L2 contiene solo elementos menores a L1
        L2.cola->sig = L1.cabeza;
        L1.cabeza = L2.cabeza;
    } else { //Hay que fusionar
        Nodo *F_ini, *F_fin;
        F_ini = NULL;
        F_fin = NULL;

        while (!esListaVacia(L1) && !esListaVacia(L2)) {
            if (L1.cabeza->elem <= L2.cabeza->elem) { //Pasa L1
                if (F_ini == NULL) {
                    F_ini = L1.cabeza;
                    F_fin = L1.cabeza;
                } else {
                    F_fin->sig = L1.cabeza;
                    F_fin = L1.cabeza;
                }
                L1.cabeza = L1.cabeza->sig;
            } else
                if (L1.cabeza->elem > L2.cabeza->elem) {
                if (F_ini == NULL) {
                    F_ini = L2.cabeza;
                    F_fin = L2.cabeza;
                } else {
                    F_fin->sig = L2.cabeza;
                    F_fin = L2.cabeza;
                }
                L2.cabeza = L2.cabeza->sig;
            }
        }

        //Puede ser que alguna lista aun tenga elementos, repasamos ambas
        while (!esListaVacia(L1)) {
            if (F_ini == NULL) {
                F_ini = L1.cabeza;
                F_fin = L1.cabeza;
            } else {
                F_fin->sig = L1.cabeza;
                F_fin = L1.cabeza;
            }
            L1.cabeza = L1.cabeza->sig;
        }

        while (!esListaVacia(L2)) {
            if (F_ini == NULL) {
                F_ini = L2.cabeza;
                F_fin = L2.cabeza;
            } else {
                F_fin->sig = L2.cabeza;
                F_fin = L2.cabeza;
            }
            L2.cabeza = L2.cabeza->sig;
        }

        L1.cabeza = F_ini;
        L1.cola = F_fin;
    }
}

void EliminaNodo(Lista *L,Elemento e){
    Nodo *rec,*ant = nullptr;
    rec = L->cabeza;
    while (rec->elem != e ) {
        ant = rec;
        rec = rec->sig;
    }
    // rec tiene el nodo a eliminar
    if(rec == L->cabeza){ // eliminamos cabez
        eliminarCabeza(L);
    }else{
        ant->sig = rec->sig;
        delete rec;
    }
}