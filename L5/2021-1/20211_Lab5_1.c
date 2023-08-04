#include <stdio.h>
#include <stdlib.h>

#define max(x,y) (((x)>(y)) ? (x) : (y))

void findAllMaxProjects(int projectsNumber,int maxValue,int* projectsGain,int** maxGain);
void findMaxProjects(int projectsNumber,int maxValue,int* projectsGain,int** maxGain);
int maximizeGain(int projectsNumber,int* projectsGain,int** maxGain);

int main() {
    int projectsNumber;
    printf("Ingresar cantidad de proyectos: ");
    scanf("%d",&projectsNumber);
    
    int* projectsGain = (int*)malloc(projectsNumber*sizeof(int));
    for (int i=0;i<projectsNumber;i++) {
        printf("Ingresar ganancia de proyecto %d: ",(i+1));
        scanf("%d",&projectsGain[i]);
    }

    int** maxGain = (int**)malloc(projectsNumber*sizeof(int*));
    int maxValue = maximizeGain(projectsNumber,projectsGain,maxGain);
    printf("La maxima ganancia es %d\n",maxValue);

    findMaxProjects(projectsNumber,maxValue,projectsGain,maxGain);

    findAllMaxProjects(projectsNumber,maxValue,projectsGain,maxGain);

    free(projectsGain);
    free(maxGain);

    return 0;
}

// Por ahora no funciona, y no sabemos por qué :D
void findAllMaxProjects(int projectsNumber,int maxValue,int* projectsGain,int** maxGain) {
    for (int i=(projectsNumber-1);i>=0;i--) {
        if (maxGain[i][1]==maxValue) {
            printf("%02d ",(i+1));
            findAllMaxProjects(i,maxValue,projectsGain,maxGain);
            maxValue -= projectsGain[i];
            i -= 2;
        }
    }
    printf("\n");
}

void findMaxProjects(int projectsNumber,int maxValue,int* projectsGain,int** maxGain) {
    for (int i=(projectsNumber-1);i>=0;i--) {
        if (maxGain[i][1]==maxValue) {
            printf("%02d ",(i+1));
            maxValue -= projectsGain[i];
            i -= 2;
        }
    }
}

int maximizeGain(int projectsNumber,int* projectsGain,int** maxGain) {
    for (int i=0;i<projectsNumber;i++) {
        maxGain[i] = (int*)calloc(2,sizeof(int));
    }

    maxGain[0][0] = 0;
    maxGain[0][1] = projectsGain[0];

    maxGain[1][0] = projectsGain[0];
    maxGain[1][1] = projectsGain[1];

    maxGain[2][0] = max(projectsGain[0],projectsGain[1]);
    maxGain[2][1] = projectsGain[2];

    for (int i=3;i<projectsNumber;i++) {
        maxGain[i][0] = max(max(max(maxGain[i-1][1],maxGain[i-2][1]),maxGain[i-1][0]),maxGain[i-2][0]);
        maxGain[i][1] = projectsGain[i] + max(maxGain[i-3][1],maxGain[i-3][0]);
    }

    for (int i=0;i<projectsNumber;i++) {
        printf("%02d %02d\n",maxGain[i][0],maxGain[i][1]);
    }

    int maxValue = max(max(maxGain[projectsNumber-1][1],
                           maxGain[projectsNumber-2][1]),
                       maxGain[projectsNumber-3][1]);
    return maxValue;
}