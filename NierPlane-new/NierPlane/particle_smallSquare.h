#pragma once
#include "particle.h"

class particle_smallSquare :public particle
{
public:
	int width = 20;
	int height = 20;
	int r;
	double x, y;

	double xSpeed;
	double xStepSpeed;
	double ySpeed;
	double yStepSpeed;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	particle_smallSquare(int _aliveLoopNum, int _x, int _y);
	~particle_smallSquare();
	void showParticle();
private:
	void move();
};
