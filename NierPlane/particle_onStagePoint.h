#pragma once
#include "particle.h"
#include "common.h"

class particle_onStagePoint :public particle
{
public:
	//enemy* parent;
	int width = 20;
	int height = 20;
	int r = 2;
	double angle;
	double speed;
	int maxSpeed;

	POINT destPosition;
	POINT offsetPosition;

	// 每隔destSleep个循环取一次目标点
	int destSleep = 30;

	// 取点循环计数变量,无需更改
	int destNum = 0;

	// 运动范围(矩形
	RECT move_range = { 100,100,GRAPH_WIDTH - 100 , GRAPH_HEIGHT - 100 };

	double vX = 0, vY = 0;			// 速度
	//float p = 0.1;			// 比例(与加速度有关
	float p = 0.8;			// 比例(与加速度有关
	//float p_v = 0.1;
	float sp_v = 0.3;
	float p_v = 0.7;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	

	particle_onStagePoint(int _aliveLoopNum, int _x, int _y);
	//particle_onStagePoint(int _aliveLoopNum, int _x, int _y,int _destX,int _destY);
	particle_onStagePoint(int _aliveLoopNum, int _x, int _y, int _destX, int _destY,int _maxSpeed = 1000);
	~particle_onStagePoint();
	void showParticle();
	void setDestPosition(int _x, int _y);
	static void preRender();
private:
	void move();
	void move1();
};
