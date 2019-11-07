#include<stdio.h>
#include "block.h"

int checkCrash(int **map, Block *block){
	int x = block->x;
	int y = block->y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block->shape[i][j] == 1 && map[x+i][y+j] == 1){
				return 1;
			}
		}
	}
	return 0;
}

int _checkLine(int **map, int line, int width){
	for(int i = 0; i < width; i++){
		if(map[line][i] == 0)
			return 0;
	}
	return 1;
}
int checkLine(int **map, int height, int width){
	int indexL = -1;
	for(int i = 0; i < height - 1; i++){
		int sign = 0;
		if(_checkLine(map, i, width) == 1){
			indexL = i;
			break;
		}
	}
	
	if(indexL != -1){
		for(int i = indexL; i > 0; i--){
			for(int j = 0; j < width; j++){
				map[i][j] = map[i-1][j];
			}
		}
	}else{
		return 0;
	} 

	return 1;
}
