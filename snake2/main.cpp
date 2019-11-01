#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#define random(x) (rand()%x)

using namespace std;

struct snake{	
	int i;
	int j;
	struct snake *next;
	};
	
/* draw */
extern void initMap(int **map, int height, int weight);
extern void draw(int **map, int *star, int height, int weight);
extern void drawSnake(int **map, struct snake snake);
extern void update(int x, int y, int sign);
extern void pos(int x,int y);
/* action */
extern void getAction();
extern int move(struct snake *s, int *star);
extern void initAction(int x, int y, int h, int w, int c, int s); 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct snake generateSnake(){
	cout << "开始生成" << endl; 
	struct snake *s;
	s = (struct snake*)malloc(sizeof(struct snake));
	struct snake *p = s;
	int x[6] = {2, 3, 4, 5, 5, 5};
	int y[6] = {2, 2, 2, 2, 3, 4};
	for(int i = 0; i < 6; i++){
		struct snake *node;
		node = (struct snake*)malloc(sizeof(struct snake));
		p->next = node;		
		p = p->next;
		p->i = x[i];
		p->j = y[i];
	}
	p->next = NULL;
	cout << "生成成功" << endl; 
	return *s;
}

/* 生成星星 */
void generateStar(int **map, int *star, int height, int weight){
	int sum = 0;
	int index = 0;
	// 计算有多少空格 
	for(int i = 0; i < height; i++)
		for(int j = 0; j < weight; j++)
			if(map[i][j] == 0)
				sum += 1;
	// 随机生成空格下标 
	index = random(sum) + 1;
	// 选中index个空格作为星星的生成位置 
	for(int i = 0; i < height; i++)
		for(int j = 0; j < weight; j++){
			if(map[i][j] == 0)
				index -= 1;
				
			if(index == 0){
				star[0] = i;
				star[1] = j;
				return;
			}
		}
	return;
}

int _move(struct snake *s, int *star){
	int result = move(s, star);
	return result; 
} 

int main(int argc, char** argv) {

	/* 超参数 */
	int height = 15;
	int weight = 15;
	int speed = 200;	// 运动速度，越小越快（其实是延时时长） 
	/* 绘制初始地图 */
	int **map;
	map = (int**) new int*[height];
	/* 初始化地图 */
	for(int i = 0; i < height; i++){
		*(map + i) = new int[weight];
	}
	
	while(1){
		/* 生成蛇 */
		struct snake s = generateSnake();
		initMap(map, height, weight);
		drawSnake(map, s);
		/* 生成星星 */ 
		int star[2] = {0, 0};
		generateStar(map, star, height, weight);
		/* 绘制地图 */
		draw(map, star, height, weight);
		/* 初始化运动参数，纵轴方向，横轴方向，地图高度，地图宽度, 方向按键值, 运动速度（越小越快） */
		initAction(0, 0, height, weight, 0, speed);
		while(1){
			getAction();
			int result = _move(&s, star);
			
			if(result == 0) //如果死了，那就宣判结束 
				break;
			
			// 需要在新的星星之前先将新蛇绘制到地图中去，不然会导致在刚吃下星星的位置生成星星 
			initMap(map, height, weight);	
			drawSnake(map, s);
			
			if(result == 2) {// 星星被吃掉了， 我们生成新的星星 
				generateStar(map, star, height, weight);
				update(star[1], star[0], 2); 
			}
		}
		pos(0, height);
		printf("你输了\n");
		system("pause");
	}

	return 0;
}
