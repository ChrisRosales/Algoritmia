#include <stdio.h>
#define MAX_N 1000

/* Estructura que representa a mi producto con los campos descritos en el enunciado */
typedef struct {
  int posicion;
  int producto;
  int stock;
} Producto;

Producto productos[MAX_N];

/* Retorna si a[2 * pos] = a[2 * pos + 1]
 * Complejidad en Tiempo: O(1) */
int Check(int n, int pos) {
  int cur = 2 * pos;
  int next = 2 * pos + 1;
  if (next  == n) return 0;
  if (productos[cur].producto != productos[next].producto) return 0;
  return 1;
}

/* Retorna la posicion del ultimo elemento sin emparejar, por lo tanto,
 * este elemento no matchea con el siguiente, y los anteriores a el si
 * estan en parejas. Un peque~no ejemplo es el siguiente
 * A A | B B | C C | ... | E E | E F | F G | ... | H I | I
 * Complejidad en Tiempo: O(lg(n)) */
int Buscar(int n, int izq, int der) {
  if (der - izq <= 1) return (2 * der);
  /* Divido el rango total en dos partes y en el caso de que el par de elementos
   * actuales sean iguales, busco en la mitad derecha, sino en la mitad izquierda
   * manteniendo la invariante 
   * Complejidad en Tiempo: O(lg(n)) */
  int mid = (izq + der) / 2;
  if (Check(n, mid)) return Buscar(n, mid, der);
  return Buscar(n, izq, mid);
}

int main(void) {
  int n;
  printf("Cantidad de productos: ");
  scanf("%d", &n);
  /* Leemos los valores de cada uno de los productos */
  int i;
  for ( i = 0; i < n; i++) {
    productos[i].posicion = i;
    printf("Posicion %d\n", i);
    printf("Producto: ");
    scanf("%d", &productos[i].producto);
    printf("Stock: ");
    scanf("%d", &productos[i].stock);
  }
  /* Busco la posicion del ultimo que aparece 3 veces, y guardo la de sus dos anteriores
   * para manipularlo en la impresion y suma con mas facilidad */
  int ultima_posicion = Buscar(n, 0, n / 2);
  int pos1 = ultima_posicion - 2;
  int pos2 = ultima_posicion - 1;
  int pos3 = ultima_posicion;
  int stock = productos[pos1].stock + productos[pos2].stock + productos[pos3].stock;
  printf("Las cajas se encuentran en las posicinoes %d, %d y %d.\n", pos1, pos2, pos3);
  printf("Las cajas son del producto %d.\n", productos[pos1].producto);
  printf("Su stock suma %d.\n", stock);
  return 0;
}
