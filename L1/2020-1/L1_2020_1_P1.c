#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_PERSONAS 100
#define MAX_MOVS 100

int main(){
    int numPersonas, radio, numRuta;
    int personas[MAX_PERSONAS][3];
    int ruta[MAX_MOVS][2];

    scanf("%d", &numPersonas);
    scanf("%d", &radio);

    for(int i = 0; i < numPersonas; i++)
        scanf("%d %d %d", &personas[i][0], &personas[i][1], &personas[i][2]);
    
    scanf("%d", &numRuta);

    for(int i = 0; i < numRuta; i++)
        scanf("%d %d", &ruta[i][0], &ruta[i][1]);
    
    for(int i = 0; i < numRuta; i++){
        for(int j = 0; j < numPersonas; j++){
            if(personas[j][0] == 1){
                int distX = ruta[i][0] - personas[j][1];
                int distY = ruta[i][1] - personas[j][2];
                float dist = sqrt(distX*distX + distY*distY);
                if(dist <= radio){
                    printf("Persona podria haberse contagiago en su movimiento %d por la persona %d con nivel de cercania %f\n", i+1, j+1, dist);
                }
            }

        }
    }

    return 0;
}