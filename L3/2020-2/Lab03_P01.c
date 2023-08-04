#include <stdio.h>
#define MAX_N 1000

/* Estructura que representa a mi producto con los campos descritos en el enunciado */
typedef struct {
  int posicion;
  int producto;
  int stock;
} Producto;

Producto productos[MAX_N];

/* Retorna la primera posicion del mayor elemento */
/* Complejidad en Tiempo: O(lg(n)) */
int BuscarCima(int izq, int der) {
  if (izq == der) return izq;
  int mid = (izq + der) / 2;
  if (productos[mid].producto >= productos[mid + 1].producto) {
    return BuscarCima(izq, mid);
  } else {
    return BuscarCima(mid + 1, der);
  }
}

/* Retorna 1 si es que el producto actual es menor o igual al objetivo
 * Complejidad en Tiempo: O(1) */
int CheckIzquierda(int pos, int objetivo) {
  return (productos[pos].producto <= objetivo);
}

/* Busco la posicion del ultimo elemento menor o igual que el objetivo
 * En caso que en esta posicion el elemento sea distinto al objetivo
 * retornare -1, en otro caso, retorno su posicion
 * Complejidad en Tiempo: O(lg(n)) */
int BuscarIzquierda(int izq, int der, int objetivo) {
  /* Verifico al menos tener un rango donde analizar */
  if (izq > der) return -1;
  /* Verifico que al menos el primero cumpla, sino, ninguno cumpliria */
  /* FFFFFFFFFF */
  if (!CheckIzquierda(izq, objetivo)) return -1;
  /* Si es que el extremo derecho cumple, solo le queda ser o no ser */
  /* TTTTTTTTTT  */
  if (CheckIzquierda(der, objetivo)) {
    if (productos[der].producto == objetivo) return der;
    return -1;
  }
  /* Si el rango tiene longitud menor o igual a 2, entonces la invariante implica que en el izquierdo debe estar */
  /* TF */
  if (der - izq <= 1) {
    if (productos[izq].producto == objetivo) return izq;
    return -1;
  }
  /* Partimos el intervalo a la mitad y analizamos recursivamente esto manteniendo la invariante */
  /* TT...TF...FF */
  int mid = (izq + der) / 2;
  if (CheckIzquierda(mid, objetivo)) return BuscarIzquierda(mid, der, objetivo);
  return BuscarIzquierda(izq, mid, objetivo);
}


/* Retorna 1 si que el producto actual tiene codigo menor o igual al objetivo
 * Complejidad en Tiempo: O(1) */
int CheckDerecha(int pos, int objetivo) {
  return (productos[pos].producto <= objetivo);
}

/* Retorna la posicion del primer elemento menor o igual al objetivo
 * En caso que en esta posicion el elemento sea distinto al objetivo
 * retornare -1, en otro caso, retorno la posicion
 * Complejidad en Tiempo: O(lg(n)) */
int BuscarDerecha(int izq, int der, int objetivo) {
  /* Verifico que el rango a analizar es valido */
  if (izq > der) return -1;
  /* Vertifico que al menos el ultimo cumpla, sino ninguno cumpliria */
  /* FFFFFFFFFF */
  if (!CheckDerecha(der, objetivo)) return -1;
  /* Si es que el extremo izquierdao cumple, solo le queda ser o no ser */
  /* TTTTTTTTTT */
  if (CheckDerecha(izq, objetivo)) {
    if (productos[izq].producto == objetivo) return izq;
    return -1;
  }
  /* Si el rango tiene longitud menor o igual a 2 y hemos llegado hasta aqui, chequeamos la derecha */
  /* FT */
  if (der - izq <= 1) {
    if (productos[der].producto == objetivo) return der;
    return -1;
  }
  /* Partimos el intervalo a la mitad y analizamos recursivamente manteniendo la siguiente invariante */
  /* FF...FT...TT */
  int mid = (izq + der) / 2;
  if (CheckDerecha(mid, objetivo)) return BuscarDerecha(izq, mid, objetivo);
  return BuscarDerecha(mid, der, objetivo);
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
  int objetivo;
  printf("Producto a buscar: ");
  scanf("%d", &objetivo);
  /* Primero buscare la posicion del producto cuyo codigo es el mayor */
  int cumbre = BuscarCima(0, n - 1);
  /* Ahora busco la posicion donde aparece el producto en [0, cumbre]*/
  int izquierda = BuscarIzquierda(0, cumbre, objetivo);
  /* Ahora busco la posicion donde aparece el producto en [cumbre + 1, n - 1] */
  int derecha = BuscarDerecha(cumbre + 1, n - 1, objetivo);
  /* Si en ninguna de las dos partes del arreglo aparece, entonces notifico al usuario */
  if (izquierda == -1 && derecha == -1) {
    printf("La cantidad de stock del producto %d es 0 cajas.\n", objetivo);
    printf("El producto no se encuentra en el almacen.\n");
    return 0;
  }
  /* Si es que aparecio al menos una vez, entonces sumamos y presentamos en pantalla */
  int stock = 0;
  if (izquierda != -1) stock += productos[izquierda].stock;
  if (derecha != -1) stock += productos[derecha].stock;
  printf("La cantidad de stock del producto %d es %d caja(s).\n", objetivo, stock);
  printf("El producto se encuentra en la(s) posicion(es) ");
  if (izquierda != -1) printf("%d", izquierda);
  if (izquierda != -1 && derecha != -1) printf(" y ");
  if (derecha != -1) printf("%d", derecha);
  printf(" dentro del almacen.\n");
  return 0;
}
