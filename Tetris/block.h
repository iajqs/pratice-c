#include <stdio.h>
#include <iostream>

	
class Block // class declaration
{

	
	public:
		int x; // 横坐标，以左上角为标志位 
		int y; // 纵坐标，以左上角为标志位 
		int type; // 方块类型 
		int director; // 旋转方向 0:向左，1向右 
		int shape[4][4]; // 格子大小 
		int shapes[8][4][4]; 
	public:
		/* 设置方块属性 */ 
		void set(int _x, int _y, int _shape){
			x = _x;
			y = _y;
			if(_shape != -1){
				for(int i = 0; i < 4; i++)
					for(int j = 0; j < 4; j++)
						shape[i][j] = shapes[_shape][i][j];	
				type = _shape;
				director = 0;
			}
	
		}
		void generate(){
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 4; j++)
					for(int k = 0; k < 4; k++)
						shapes[i][j][k] = 0;
						
			/* 石头 */
			shapes[0][1][1] = 1;
			/* 棍子 */
			shapes[1][1][0] = shapes[1][1][1] = shapes[1][1][2] = shapes[1][1][3] = 1;
			/* 七 (左）*/
			shapes[2][0][0] = shapes[2][0][1] = shapes[2][1][1] = shapes[2][2][1] = 1;
			/* 七 (右) */
			shapes[3][0][1] = shapes[3][0][2] = shapes[3][1][1] = shapes[3][2][1] = 1;
			/* 凸 */ 
			shapes[4][0][1] = shapes[4][1][0] = shapes[4][1][1] = shapes[4][2][1] = 1;
			/* 田 */
			shapes[5][1][1] = shapes[5][1][2] = shapes[5][2][1] = shapes[5][2][2] = 1;
			/* Z(左) */
			shapes[6][0][0] = shapes[6][0][1] = shapes[6][1][1] = shapes[6][1][2] = 1;
			/* Z(右)*/
			shapes[7][0][2] = shapes[7][0][1] = shapes[7][1][1] = shapes[7][1][0] = 1;
			
		}
 }; 
