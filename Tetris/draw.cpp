#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include <windows.h>//控制台编程主要头文件
#include "block.h"
using namespace std;
void pos(int x,int y);//确定光标位置
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄

/*超参数*/
int height = 0;
int width = 0;
int promptH = 8;
int promptW = 8; 
void drawInit(int h, int w){
	height = h;
	width = w;
}

//设置光标位置
void pos(int x,int y){
    COORD posPoint = {x * 2, y}; //设置坐标
    SetConsoleCursorPosition(hOut,posPoint);
}

//	墙体，蛇身
//   空□
void initMap(int **map){
	// 这里有一个需要关注的地方， 那就是边界是墙，那么到时候在判定的时候， 
	// 我们要将墙体的大小算进到整个地图大小中，也就是height是包含了墙体了的 
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(i == height - 1){
				map[i][j] = 1; 
			}else if(j == 0 || j == width - 1){
				map[i][j] = 1; 
			}else{
				map[i][j] = 0; 
			}
		}
	} 
	return;
}

void drawMap(int **map){
	// 这里有一个需要关注的地方， 那就是边界是墙，那么到时候在判定的时候， 
	// 我们要将墙体的大小算进到整个地图大小中，也就是height是包含了墙体了的 

	/* 清空屏幕 */
//	system("cls");
	pos(0, 0);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(map[i][j] == 1){
				cout << "■";	// 墙体 
			}else{
				cout << "□"; 	// 可移动区域 
			}
		}
		cout << endl;
	} 
	return;
}

void drawBlock(Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(y + j, x + i);
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				std::cout << "■";
			}
		}
	}
	pos(0,height);
}

void cleanBlock(Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(y + j, x + i);
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				std::cout << "□";
			}
		}
	}
	pos(0,height);
} 

void addBlock(int **map, Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				map[x+i][y+j] = block.shape[i][j];
			}
		}
	}
}

void cleanLine(int **map){
	drawMap(map);
	pos(0,height);
}

void drawPrompt(){
	/* 加入提示：提示下一个方块的形状 */
	/**
		1. 为了方便起见，我们这个提示的大小直接固定，如果你有想要修改的意向，这一部分的操作也是个可展开细做的地方。 
		2. 提示部分放在右上角最顶部 
	**/ 
	int promptH = 8;
	int promptW = 8; 
	pos(width, 0);
	for(int i = 0; i < promptH; i++){
		for(int j = 0; j < promptW; j++){
			pos(width + j, i);
			if(i == promptH - 1 || i == 0){
				std::cout << "■";
			}else if(j == 0 || j == promptW - 1){
				std::cout << "■";
			}
		}
	} 
	pos(0,height);
} 

void _drawPrompt(Block block){
	/* 加入提示：提示下一个方块的形状 */
	/**
		1. 为了方便起见，我们这个提示的大小直接固定，如果你有想要修改的意向，这一部分的操作也是个可展开细做的地方。 
		2. 提示部分放在右上角最顶部 
	**/ 
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(width + 2 + j, 3 + i);
			if(block.shape[i][j] == 1){
				std::cout << "■";
			}else{
				std::cout << "  ";
			}
		}
	}
	pos(0,height);
} 

void _drawNumber(int points[5][3], int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
		    COORD posPoint = {2 * y + j, x + i}; //设置坐标
		    SetConsoleCursorPosition(hOut,posPoint);
			if(points[i][j] == 1){
				cout << "+";
			}else{
				cout << " ";
			} 

		}
	}
	pos(0, height);
}

void drawNumber(int number, int x, int y){
	if(number == 0){
		int points[5][3] = {
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 1}
			};
		_drawNumber(points, x, y);
	}else if(number == 1){
		int points[5][3] = {
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1}
			};
		_drawNumber(points, x, y);
	}else if(number == 2){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 3){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 4){
		int points[5][3] = {
			{1, 0, 1},
			{1, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{0, 0, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 5){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 6){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 7){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 8){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 9){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}
	return;
}

void drawScore(int score){
	/* 展示已获得的分数 */
	drawNumber(score % 10, promptH + 1, width + 6);
	score = score / 10;
	drawNumber(score % 10, promptH + 1, width + 3);
	score = score / 10;
	drawNumber(score % 10, promptH + 1, width + 0);

//	pos(width + 2, promptH + 2);
//	cout << score;
//	pos(0,height);
} 
