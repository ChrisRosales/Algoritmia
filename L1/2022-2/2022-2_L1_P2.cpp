#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>


#define FILE_NAME "Lab1_P2_data.txt"
#define TAMANO_PAQUETE 10
#define TAMANO_PALABRA 3

using namespace std;
void LeerPalabra(char *paquete,char *palabra);
void PreguntaA(char *paquete,char *palabra);
void PreguntaB(char *paquete,char *palabra);
int main(){
	char paquete[TAMANO_PAQUETE + 1]; // Palabra del paquete
    char palabra[TAMANO_PALABRA + 1]; // Supondremos que toda palabra ingresada es de 3 caracteres
    LeerPalabra(paquete, palabra);
    PreguntaA(paquete, palabra);
    PreguntaB(paquete, palabra);
	return 0;
}
/**
 * Lectura del archivo y por el usuario
 * 
 * @param paquete: Lectura del archivo
 * @param palabra: Lectura por parte del usuario
 */
void LeerPalabra(char *paquete, char *palabra) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se puedo leer el archivo: " << FILE_NAME << "\n";
        exit(1);
    }
    archivo >> paquete;
    if (archivo.fail()) {
        std::cout << "No se pudo leer el paquete del archivo\n";
        exit(1);
    }
    archivo.close();
    std::cout << "Ingrese la palabra(3 caracteres) que se desea buscar: ";
    std::cin >> palabra;
    if (std::cin.fail()) {
        std::cout << "No se pudo leer la palabra\n";
        exit(2);
    }
}


void PreguntaA(char *paquete, char *palabra) {
    int existeLetra[TAMANO_PALABRA];
    for (int i = 0; i < TAMANO_PAQUETE; i++) {
        // Encontramos una solución valida
        // Para este caso, sería la última valida
        if (paquete[i] == palabra[0]) existeLetra[0] = i + 1;
        if (paquete[i] == palabra[1]) existeLetra[1] = i + 1;
        if (paquete[i] == palabra[2]) existeLetra[2] = i + 1;
    }
    // Impresión del caso valido
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Pregunta A\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n"
            << std::setfill('-') << std::setw(30) << "-" << "\n"
            << "Una posible solución es: \n";
    for (int i = 0; i < TAMANO_PALABRA; i++) {
        std::cout << palabra[i] << " = " << existeLetra[i] << "\n";
    }
    std::cout << std::setfill('-') << std::setw(30) << "-" << "\n";
}

/**
 * Todas las soluciones validas
 * @param paquete
 * @param palabra
 */
void PreguntaB(char *paquete, char *palabra) {
    int exiteLetra[TAMANO_PALABRA][TAMANO_PAQUETE];
    int cantLetra[TAMANO_PALABRA] = {0};
    // Guardamos la posición en la que se encuentra cada
    // caracter de la palabra en la frase del paquete
    for (int i = 0; i < TAMANO_PAQUETE; i++) {
        if (paquete[i] == palabra[0]) {
            exiteLetra[0][cantLetra[0]] = i + 1;
            cantLetra[0]++;
        } else if (paquete[i] == palabra[1]) {
            exiteLetra[1][cantLetra[1]] = i + 1;
            cantLetra[1]++;
        } else if (paquete[i] == palabra[2]) {
            exiteLetra[2][cantLetra[2]] = i + 1;
            cantLetra[2]++;
        }
    }
    std::cout << std::setfill('*') << std::setw(30) << "*" << "\n"
            << "Pregunta B\n"
            << std::setfill('*') << std::setw(30) << "*" << "\n";
    // Variables auxiliares
    int i, j, k, casos = 1, centinela = 1;
    i = j = k = 0;
    while (centinela <= cantLetra[0]) {
        // Impresión de los casos posibles
        std::cout << "Caso : " << casos << "\n";
        std::cout << palabra[0] << " = " << exiteLetra[0][i] << "\n"
                  << palabra[1] << " = " << exiteLetra[1][j] << "\n"
                  << palabra[2] << " = " << exiteLetra[2][k] << "\n";
        std::cout << std::setfill('-') << std::setw(30) << "-" << "\n";
        casos++;
        // Algoritmo, para poder imprimir todas las formas validas
        k++;
        if (k >= cantLetra[2]) {
            k = 0;
            j++;
        }
        if (j >= cantLetra[1]) {
            j = 0;
            i++;
            centinela++;
            casos++;
        }
    }
}
