#include <stdio.h>
#include <stdlib.h>

void binarySearch3d(int* positions, int startL, int endL, int startW, int endW, int startH, int endH,int*** meteor);
int calculateWeight(int startL, int endL, int startW, int endW, int startH, int endH,int*** meteor);
void readData(int length,int width,int height,int*** meteor);

int main(){
	int length;
	int width;	
	int height;
	printf("Ingresar dimensiones del meteorito (L,W,H): ");
	scanf("%d %d %d",&length,&width,&height);
	
	int*** meteor = (int ***)malloc(height*sizeof(int**));
	readData(length,width,height,meteor);
	
	int* positions = (int*)malloc(3*sizeof(int));
	binarySearch3d(positions,0,length-1,0,width-1,0,height-1,meteor);
	
	printf("La posicion del vibrandio en el meteorito es (%d,%d,%d). \n",positions[0]+1,positions[1]+1,positions[2]+1);
	
	return 0;
}

void binarySearch3d(int* positions, int startL, int endL, int startW, int endW, int startH, int endH,int*** meteor){
	if((startL== endL) && (startW==endW) && (startH==endH)){
		positions[0] = startL;
		positions[1] = startW;
		positions[2] = startH;
		return;
	}
	
	int startL_2 = startL;
	int endL_2 = endL;
	int midL = (startL + endL)/2;
	if(startL != endL){
		int weight1 = calculateWeight(startL,midL,startW,endW,startH,endH,meteor);
		int weight2 = calculateWeight(midL+1,endL,startW,endW,startH,endH,meteor);
		if(weight1>weight2){
			endL_2 = midL;
		} else{
			startL_2 = midL+1;
		}
	}
	
	int startW_2 = startW;
	int endW_2 = endW;
	int midW = (startW+endW)/2;
	if(startW!=endW){
		int weight1 = calculateWeight(startL_2,endL_2,startW,midW,startH,endH,meteor);
		int weight2 = calculateWeight(startL_2,endL_2,midW+1,endW,startH,endH,meteor);
		if(weight1>weight2){
			endW_2 = midW;
		} else{
			startW_2 = midW+1;
		}
	}
	int startH_2 = startH;
	int endH_2 = endH;
	int midH = (startH+endH)/2;
	if(startH!=endH){
		int weight1 = calculateWeight(startL_2,endL_2,startW_2,endW_2,startH,midH,meteor);
		int weight2 = calculateWeight(startL_2,endL_2,startW_2,endW_2,midH+1,endH,meteor);
		if(weight1>weight2){
			endH_2 = midH;
		} else{
			startH_2 = midH+1;
		}
	}
	binarySearch3d(positions,startL_2,endL_2,startW_2,endW_2,startH_2,endH_2,meteor);
}
int calculateWeight(int startL, int endL, int startW, int endW, int startH, int endH,int*** meteor){
	int weight =0;
	int i,j,k;
	for(i=startH; i<= endH; i++){
		for(j=startW; j<= endW; j++){
			for(k=startL; k<=endL; k++){
				weight += meteor[i][j][k];
			}
		}
	}
	return weight;
}
void readData(int length,int width,int height,int*** meteor){
	printf("Ingresar la configuracion del meteorito: \n");
	int i,j,k;
	for(i=0; i<height; i++){
		meteor[i] = (int**)malloc(width*sizeof(int*));
		for(j=0; j<width; j++){
			meteor[i][j] = (int*)malloc(length*sizeof(int));
			for(k=0 ; k<length; k++){
				scanf("%d",&meteor[i][j][k]);
			}
		}
	}
}
