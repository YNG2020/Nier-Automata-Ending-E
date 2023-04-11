#pragma once
#include "particle.h"
#include "particle_smallSquare.h"
#include "common.h"


struct halo {
	double r = 50;
	COLORREF maxColor = 0xffffff;
	COLORREF minColor = 0;
};

class particle_hitHalo :public particle
{
public:
	int width = 20;
	int height = 20;
	int r;

	int hitImgIndex[2];

	double x, y;

	double xSpeed;
	double xStepSpeed;
	double ySpeed;
	double yStepSpeed;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	//IMAGE hitImg5(100, 100);

	//IMAGE* hitImg1;
	//IMAGE* hitImg2;
	//IMAGE* hitImg3;
	//IMAGE* hitImg4;

	particle_hitHalo(int _aliveLoopNum, int _x, int _y);
	~particle_hitHalo();
	void showParticle();
	void showHalo();
	static void preRenderHitImg();
private:
	void move();
};