#include <stdio.h>
#include <stdlib.h>


void binarySearch3d(int* positions, int startL, int endL, int startW, int endW, int startH, int endH,int meteor[][4]);
int calculateWeight(int startL, int endL, int startW, int endW, int startH, int endH,int meteor[][4]);




// 4 columnas 3 filas



int main(){
	int length=4;
	int width=3;	
	int height=0;
	/*
	printf("Ingresar dimensiones del meteorito (L,W,H): ");
	scanf("%d %d %d",&length,&width);
	*/
	
	int meteor[3][4]={{1,0,0,0},
					{0,0,0,0},
					{0,0,0,0}};
					
	// Posicion (1,2)			
	
	
	int positions[3];
	
	binarySearch3d(positions,0,length-1,0,width-1,0,0,meteor);
	
	printf("La posicion del vibrandio en el meteorito es (%d,%d). \n",positions[0]+1,positions[1]+1);
	
	return 0;
}


void binarySearch3d(int positions[], int startL, int endL, int startW, int endW, int startH, int endH,int meteor[][4]){
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
	
	binarySearch3d(positions,startL_2,endL_2,startW_2,endW_2,0,0,meteor);
}

int calculateWeight(int startL, int endL, int startW, int endW, int startH, int endH,int meteor[][4]){
	int weight =0;
	int i,j,k;

	
		for(j=startW; j<= endW; j++){
			for(k=startL; k<=endL; k++){
				weight += meteor[j][k];
			}
		}
	
	printf("%d\n",weight);
	return weight;
}
