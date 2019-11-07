#include <bits/stdc++.h>//C++万能头
#include <windows.h>//控制台编程主要头文件
#include <conio.h>//getch()函数
#include <stdlib.h>//system()函数
#include <time.h>
#include "block.h"
#define random(x) (rand()%x)

/* draw */
extern void drawInit(int h, int w);
extern void initMap(int **map);
extern void drawMap(int **map);
extern void drawBlock(Block block);
extern void pos(int x, int y);
extern void cleanLine(int **map); 
extern void drawPrompt();
extern void _drawPrompt(Block block);
extern void drawScore(int score);

/* action */
extern int _action(int **map, Block *block, int c);

/* check */
extern int checkLine(int **map, int height, int width);
extern int checkCrash(int **map, Block *block);

int main()
{
	/* 超参数 */
	int height = 24;
	int width = 15;
	int speed = 750;
	int score = 0;
	/* 绘制初始地图 */
	int **map;
	map = (int**) new int*[height];
	/* 初始化地图 */
	for(int i = 0; i < height; i++){
		*(map + i) = new int[width];
	}
	
	drawInit(height, width);
	initMap(map);
	drawMap(map);
	drawPrompt();

	/* 绘制方块 */
	int index = random(8);
	Block block;
	block.generate();
	block.set(2, 2, index);
	drawBlock(block);
	drawScore(score);
	
	/* 下一个方块 */
	index = random(8);
	Block nextBlock;
	nextBlock.generate();
	nextBlock.set(2, 2, index);
	_drawPrompt(nextBlock);
	
	clock_t start, end;
	while(1){
	    start = clock();
	    end = clock();
	    
	    while(end - start < speed){
			if(_action(map, &block, -1) == 1){
				while(checkLine(map, height, width) == 1){
					cleanLine(map);
					score += random(10);
					drawScore(score);
				}

				index = random(8);
				block.set(2, 2, nextBlock.type);
				drawBlock(block);
				nextBlock.set(2, 2, index);
				_drawPrompt(nextBlock);

				// 死亡检查
				if(checkCrash(map, &block) == 1){
					break;
				} 
			}
			end = clock();
		}
		// 死亡检查
		if(checkCrash(map, &block) == 1){
			break;
		} 
		if(_action(map, &block, 115) == 1){
			while(checkLine(map, height, width) == 1){
				cleanLine(map);
				score += random(10);
				drawScore(score);
			}
			index = random(8);
			block.set(2, 2, nextBlock.type);
			drawBlock(block);
			nextBlock.set(2, 2, index);
			_drawPrompt(nextBlock);

			// 死亡检查
			if(checkCrash(map, &block) == 1){
				break;
			} 
		}
//		std::cout << score << std::endl;
	}
	while(1){
		
	}
//	std::cout << "你输了" << std::endl;
	 
}

