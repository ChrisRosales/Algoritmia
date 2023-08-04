/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: rodri
 *
 * Created on 9 de julio de 2022, 11:37 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void show_answers(int n,int solution[],char *digits){
	int i;
    for( i=0;i<n;i++){
        printf("%c:%d ",digits[i],solution[i]);
    }
    printf("\n ");
}
int is_valid(int n,int solution[],int step,char*digits){
    int digit_O;
    int i,j;
    for( j=0;j<n;j++){
        if(digits[j]=='O')digit_O=solution[j];
    }
    if(digit_O==0)return 0;
    for( i=0;i<=step;i++){
        for( j=0;j<strlen(digits);j++){
            if(digits[i]=='S' && digits[j]=='O' && solution[j]!=-1 && (4*solution[i])%10!=solution[j]%10){
                return 0;
            }else if(digits[i]=='O' && digits[j]=='H' && solution[j]!=-1 && (4*solution[i])%10!=solution[j]%10){
                return 0;
            }else {
                if(digits[i]=='D' && digits[j]=='C' && solution[j]!=-1 && (4*solution[i])%10!=solution[j]%10){
                    return 0;
                }else if(digits[i]=='D' && digits[j]=='C' && solution[j]!=-1 && (4*solution[i])!=(digit_O*10+solution[j]%10)){
                    return 0;
                }
            }
        }
    }
    return 1;
}
void backstacking(int n,int solution[],int step,char*digits){
    int i=0;
    if(n==step){
        show_answers(n,solution,digits);
        return ;
    }
    do{
        solution[step]=i;
        if(is_valid(n,solution,step,digits)){
         backstacking(n,solution,step+1,digits);            
        }
        i++;
    }while(solution[step]!=9);
    solution[step]=-1;
}
int main(int argc, char** argv) {
    int n=5;
    char digits[6]="DOSCH";
    int solution[n];
    int i;
    for( i=0;i<n;i++){
        solution[i]=-1;
    }
    backstacking(n,solution,0,digits);
    return (EXIT_SUCCESS);
}

