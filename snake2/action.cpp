#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include <time.h>
#include <windows.h>
using namespace std;

extern void update(int x, int y, int sign);

int direct_x = 0;
int direct_y = 0;
int height = 0;
int weight = 0;
int ch = 0;
int mustMove = 0;
int speed = 1000;
struct snake{	
	int i;
	int j;
	struct snake *next;
	};
// w: 119
// s: 115
// a: 97
// d: 100

void setMaxMove(int value){
	mustMove = value;
}
void initAction(int x, int y, int h, int w, int c, int s){
	direct_x = x;
	direct_y = y;
	height = h;
	weight = w;
	ch = c;
	speed = s;
}

/* 运动检查 */
int check_action(struct snake *s, int x, int y){
	// 不能后退
	if((x != 0 && direct_x != 0 && x != direct_x) || (y != 0 && direct_y != 0 && y != direct_y))
		return 0;
	// 一开始也不可以后退，这时候由于没有运动方向，所以没办法确定那个是正确的方向 
	if(direct_x == 0 && direct_y == 0 && x == 1)
		return 0; 
	return 1;
} 
/* 死亡检查 */
int check_dead(struct snake *s){
	// 不能撞墙
	struct snake *p = s->next;
	while(p){
		if(p->i == 0 || p->i == height - 1 || p->j == 0 || p->j == weight - 1){
			return 0;
		}
		p = p->next;
	}
	// 不能撞自己
	p = s->next;
	while(p){
		struct snake *q = p->next;
		while(q){
			if(p->i == q->i && p->j == q->j){
				return 0;
			}
			q = q->next;
		}
		p = p->next;
	}
	return 1;
} 

int check_star(struct snake *s, int* star){
	struct snake *p = s->next;
	if(p->i == star[0] && p->j == star[1])
		return 1;
	return 0;
}
void getAction(){
	int sign = 0; // 是否已输入按键 
    double duration;	// 已检测时长 
     
    clock_t start, finish;
    start = clock();
	while(1){
		if(_kbhit() && sign == 0){
			int _ch = _getch();
			if(_ch == 119 || _ch == 115 || _ch == 97 || _ch == 100){
				ch = _ch;
				sign = 1;
			}

		}else if(_kbhit() && sign == 1){
			_getch();
		}
 		finish = clock();
    	duration = (double)(finish - start);
    	if(duration > speed)
			break;
	}

	return;
}

int _move(struct snake *s, int* star, int x, int y){
	/* 运动检查 */
	if(!check_action(s, x, y)){
		x = direct_x;
		y = direct_y;
	}
	if(x == 0 && y == 0){
		return 0;
	}
	/* 修改目前运动方向 */
	direct_x = x;
	direct_y = y;
	
	/* 增加新节点 */
	struct snake *top = s->next;
	struct snake *p = s->next;

	struct snake *Ntop;
	Ntop = (struct snake*)malloc(sizeof(struct snake));
	Ntop->i = top->i + x;
	Ntop->j = top->j + y;
	s->next = Ntop;
	Ntop->next = top;

	/* 检查是否吃到星星 */
	if(check_star(s, star) == 1){
		// 更新蛇 
		update(Ntop->j, Ntop->i, 0);
		update(top->j, top->i, 1);
		return 2; 
	}
	
	/* 删除旧节点 */
	while(p->next->next != NULL){
		p = p->next;
	}
	// 更新蛇 
	update(p->next->j, p->next->i, 3);  // 去尾 
	update(Ntop->j, Ntop->i, 0);	// 前进 
	update(top->j, top->i, 1);	// 蛇头变蛇身 
	p->next = NULL;
	return 0;
}
int move(struct snake *s, int *star){
	int sign = 0;
	switch(ch){
		case 119:
			/* 向上走 */
			sign = _move(s, star, -1, 0);
			break;
		case 115:
			/* 向下走 */ 
			sign = _move(s, star, 1, 0);
			break;
		case 97:
			/* 向左走 */
			sign = _move(s, star, 0, -1);
			break;
		case 100:
			/* 向右走 */
			sign = _move(s, star, 0, 1);
			break;
	}
	if(sign == 2){ // 吃到了星星 
		return 2;
	}
	/* 死亡检查 */
	return check_dead(s);
}
