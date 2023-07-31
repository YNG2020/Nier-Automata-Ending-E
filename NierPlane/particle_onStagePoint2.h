#pragma once
#include <graphics.h>
#include <math.h>
#include "particle.h"


class particle_onStagePoint2 :public particle
{
public:
	float source1_x, source1_y;		// 引力源1
	float source2_x, source2_y;		// 引力源2
	float source3_x, source3_y;		// 引力源3
	float source4_x, source4_y;		// 引力源4

	float vX, vY;			// 速度

//#define source1_k (float)5000	// 引力源1强度
//#define source2_k (float)5000	// 引力源2强度
//#define source3_k (float)15000	// 引力源3强度
//#define source4_k (float)50000	// 引力源4强度

#define source1_k (float)2500	// 引力源1强度
#define source2_k (float)2500	// 引力源2强度
#define source3_k (float)7500	// 引力源3强度
#define source4_k (float)15000	// 引力源4强度

	int lr = 1;
	int ori_x_range = 100;	// 粒子初始x坐标范围
	int ori_y_range = 30;	// 粒子初始y坐标范围
	int ori_vX_range = 5;	// 粒子初始x方向速度范围
	int ori_vY_range = 2;	// 粒子初始y方向速度范围
	int vX_min = -10;		// 粒子初始x方向最小值
	int vY_min = -3;		// 粒子初始y方向最小值

	// 取点循环计数变量,无需更改
	int destNum = 0;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	particle_onStagePoint2(int _aliveLoopNum, int _x, int _y);
	//particle_onStagePoint2(int _aliveLoopNum, int _x, int _y,int _destX,int _destY);
	particle_onStagePoint2(int _aliveLoopNum, int _x, int _y, int _destX, int _destY, int _maxSpeed = 1000);
	~particle_onStagePoint2();
	void showParticle();
	void setDestPosition(int _x, int _y);
	static void preRender();
private:
	void move();
};