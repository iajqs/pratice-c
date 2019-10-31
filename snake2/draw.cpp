#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
#include<time.h>
#include<windows.h>//控制台编程主要头文件
using namespace std;
void pos(int x,int y);//确定光标位置
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
struct snake{	
	int i;
	int j;
	struct snake *next;
	};


//设置光标位置
void pos(int x,int y){
    COORD posPoint = {x,y}; //设置坐标
    SetConsoleCursorPosition(hOut,posPoint);
}

void update(int x, int y, int sign){
	pos(x * 2, y);
	switch(sign){
		case 0: //增加蛇首 
			cout << "●";
			break;
		case 1: //增加蛇身 
			cout << "■";
			break;
		case 2: //增加星星
			cout << "★";	
			break; 
		case 3: //删除蛇身
			cout << "□"; 
			break;
	}

}
//	墙体，蛇身
//   空□
void initMap(int **map, int height, int weight){

	// 这里有一个需要关注的地方， 那就是边界是墙，那么到时候在判定的时候， 
	// 我们要将墙体的大小算进到整个地图大小中，也就是height是包含了墙体了的 
	for(int i = 0; i < height; i++){
		for(int j = 0; j < weight; j++){
			if(i == 0 || i == height - 1){
				map[i][j] = 1; 
			}else if(j == 0 || j == weight - 1){
				map[i][j] = 1; 
			}else{
				map[i][j] = 0; 
			}
		}
	} 
	return;
}
void draw(int **map, int *star, int height, int weight){
	// 这里有一个需要关注的地方， 那就是边界是墙，那么到时候在判定的时候， 
	// 我们要将墙体的大小算进到整个地图大小中，也就是height是包含了墙体了的 

	/* 清空屏幕 */
	system("cls");
	pos(0, 0);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < weight; j++){
			if(map[i][j] == 1){
				cout << "■";	// 蛇身和墙体 
			}else if(map[i][j] == 2){
				cout << "●";	// 蛇首 
			}else if(i == star[0] && j == star[1]){
				cout << "★";	// 星星 
			}else{
				cout << "□"; 	// 可移动区域 
			}
		}
		cout << endl;
	} 
	return;
}

void drawSnake(int **map, struct snake snake){
	struct snake *p = snake.next;
	map[p->i][p->j] = 2;	// 蛇头
	p = p->next;
	while(p){
		map[p->i][p->j] = 1;
		p = p->next;
	}
	return;
}
