#include <stdio.h>
#include <stdlib.h>

int binarySearch(double item,int startPos,int endPos,double* array);
void calculateIBd(int companies,int time,double ibm,double** stocksTable);
void doubleMerge(int startPos,int currentMidPos,int endPos,double* array1,int* array2);
void doubleMergeSort(int startPos,int endPos,double* array1,int* array2);

int main() {
    int companies;
    printf("Ingresar numero de companias: ");
    scanf("%d",&companies);

    int time;
    printf("Ingresar periodo de tiempo: ");
    scanf("%d",&time);

    double ibm;
    printf("Ingresar IBm: ");
    scanf("%lf",&ibm);

    double** stocksTable = (double**)malloc(time*sizeof(double*));
    for (int i=0;i<time;i++) {
        stocksTable[i] = (double*)malloc(companies*sizeof(double));
        printf("Ingresar valores de acciones para dia %d: ",(i+1));
        for (int j=0;j<companies;j++) {
            scanf("%lf",&stocksTable[i][j]);
        }
    }

    printf("Dia IBd   Decision Monto Acciones\n");
    calculateIBd(companies,time,ibm,stocksTable);

    free(stocksTable);

    return 0;
}

int binarySearch(double item,int startPos,int endPos,double* array) {
    if (startPos>=endPos) {
        return ((item>array[startPos]) ? (startPos+1) : startPos);
    }

    int currentMidPos = (startPos+endPos)/2;
    if (item==array[currentMidPos]) {
        return currentMidPos+1;
    } else if (item>array[currentMidPos]) {
        return binarySearch(item,currentMidPos+1,endPos,array);
    } else {
        return binarySearch(item,startPos,currentMidPos-1,array);
    }
}

void calculateIBd(int companies,int time,double ibm,double** stocksTable) {
    int* companyNames = (int*)malloc(companies*sizeof(int));
    for (int i=0;i<time;i++) {
        printf("%d   ",(i+1));

        double ibd = 0;
        for (int j=0;j<companies;j++) {
            ibd += stocksTable[i][j]/companies;
            companyNames[j] = j;
        }
        printf("%.3f ",ibd);

        printf((ibd<=ibm) ? "Compra   " : "Venta    ");

        doubleMergeSort(0,companies-1,stocksTable[i],companyNames);

        int operationPosition = binarySearch(ibd,0,companies-1,stocksTable[i]);
        double totalOperations = 0;
        if (ibm>=ibd) {
            for (int j=0;j<operationPosition;j++) {
                totalOperations += stocksTable[i][j];
            }
        } else {
            for (int j=operationPosition;j<companies;j++) {
                totalOperations += stocksTable[i][j];
            }
        }
        printf("%2.0f    ",totalOperations);

        if (ibm>=ibd) {
            for (int j=0;j<operationPosition;j++) {
                printf("%c",('A'+companyNames[j]));
            }
        } else {
            for (int j=operationPosition;j<companies;j++) {
                printf("%c",('A'+companyNames[j]));
            }
        }

        printf("\n");
    }

    free(companyNames);
}

void doubleMerge(int startPos,int currentMidPos,int endPos,double* array1,int* array2) {
    int size1 = currentMidPos-startPos+1;
    int size2 = endPos-currentMidPos;

    double* array11 = (double*)malloc(size1*sizeof(double));
    int* array21 = (int*)malloc(size1*sizeof(int));
    for (int i=0;i<size1;i++) {
        array11[i] = array1[startPos+i];
        array21[i] = array2[startPos+i];
    }

    double* array12 = (double*)malloc((size2)*sizeof(double));
    int* array22 = (int*)malloc((size2)*sizeof(int));
    for (int i=0;i<size2;i++) {
        array12[i] = array1[currentMidPos+i+1];
        array22[i] = array2[currentMidPos+i+1];
    }

    int i = 0;
    int j = 0;
    int k = startPos;
    while ((i<size1) && (j<size2)) {
        if (array11[i]<=array12[j]) {
            array1[k] = array11[i];
            array2[k] = array21[i];
            i++;
        } else {
            array1[k] = array12[j];
            array2[k] = array22[j];
            j++;
        }
        k++;
    }

    while (i<size1) {
        array1[k] = array11[i];
        array2[k] = array21[i];
        i++;
        k++;
    }

    while (j<size2) {
        array1[k] = array12[j];
        array2[k] = array22[j];
        j++;
        k++;
    }

    free(array11);
    free(array12);
    free(array21);
    free(array22);
}

void doubleMergeSort(int startPos,int endPos,double* array1,int* array2) {
    if (startPos>=endPos) {
        return;
    }

    int currentMidPos = (startPos+endPos)/2;
    doubleMergeSort(startPos,currentMidPos,array1,array2);
    doubleMergeSort(currentMidPos+1,endPos,array1,array2);
    doubleMerge(startPos,currentMidPos,endPos,array1,array2);
}