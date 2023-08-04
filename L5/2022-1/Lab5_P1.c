#include <stdio.h>
#include <stdlib.h>

void solveParenthesisAll(int currentPosition,int leftTotal,int rightTotal,int leftRemove,int rightRemove,int stringLength,char* string,int* solutionArray);

int main() {
    int stringLength;
    printf("Ingresar cantidad de caracteres a leer: ");
    scanf("%d",&stringLength);

    char* string = (char*)malloc(stringLength*sizeof(char));
    printf("Ingresar string: ");
    int i;
    for ( i=0;i<stringLength;i++) {
        scanf(" %c",&string[i]);
    }

    printf("Se leyo el string: ");
    for ( i=0;i<stringLength;i++) {
        printf("%c",string[i]);
    }

    int* solutionArray = (int*)calloc(stringLength,sizeof(int));

    int left = 0;
    int right = 0;
    for ( i=0;i<stringLength;i++) {
        if (string[i]=='(') {
            left++;
        } else if (string[i]==')') {
            right = ((left==0) ? (right+1) : left);
            left = ((left>0) ? (left-1) : left);
        }
    }
    solveParenthesisAll(0,0,0,left,right,stringLength,string,solutionArray);

    return 0;
}

void solveParenthesisAll(int currentPosition,int leftTotal,int rightTotal,int leftRemove,int rightRemove,int stringLength,char* string,int* solutionArray) {
    int i;
	if (currentPosition==stringLength) {
        if ((leftRemove==0) && (rightRemove==0)) {
            printf("\nUna solucion: ");
            for ( i=0;i<stringLength;i++) {
                if (solutionArray[i]) {
                    printf("%c",string[i]);
                }            
            }
        }
    } else {
        if ((string[currentPosition]=='(') && (leftRemove>0)) {
            solveParenthesisAll(currentPosition+1,leftTotal,rightTotal,leftRemove-1,rightRemove,stringLength,string,solutionArray);
        } else if ((string[currentPosition]==')') && (rightRemove>0)) {
            solveParenthesisAll(currentPosition+1,leftTotal,rightTotal,leftRemove,rightRemove-1,stringLength,string,solutionArray);
        }

        solutionArray[currentPosition] = 1;

        if ((string[currentPosition]!='(') && (string[currentPosition]!=')')) {
            solveParenthesisAll(currentPosition+1,leftTotal,rightTotal,leftRemove,rightRemove,stringLength,string,solutionArray);
        } else if (string[currentPosition]=='(') {
            solveParenthesisAll(currentPosition+1,leftTotal+1,rightTotal,leftRemove,rightRemove,stringLength,string,solutionArray);
        } else if (rightTotal<leftTotal) {
            solveParenthesisAll(currentPosition+1,leftTotal,rightTotal+1,leftRemove,rightRemove,stringLength,string,solutionArray);
        }

        solutionArray[currentPosition] = 0;
    }
}
