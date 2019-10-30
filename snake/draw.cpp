#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
using namespace std;

struct snake{	
	int i;
	int j;
	struct snake *next;
	};


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
