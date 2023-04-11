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

	// ÿ��destSleep��ѭ��ȡһ��Ŀ���
	int destSleep = 30;

	// ȡ��ѭ����������,�������
	int destNum = 0;

	// �˶���Χ(����
	RECT move_range = { 100,100,GRAPH_WIDTH - 100 , GRAPH_HEIGHT - 100 };

	double vX = 0, vY = 0;			// �ٶ�
	//float p = 0.1;			// ����(����ٶ��й�
	float p = 0.8;			// ����(����ٶ��й�
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
