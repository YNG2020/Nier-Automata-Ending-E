#pragma once
#include "particle.h"

class particle_planeHit3 :public particle
{
public:
	
	const POINT width{ -5,5 };
	const POINT height{ 10,10 };
	int r;
	double x, y;

	POINT pts[4] = {
		{width.x + height.x,width.y + height.y} ,
		{width.x - height.x,width.y - height.y} ,
		{-width.x - height.x,-width.y - height.y} ,
		{-width.x + height.x,-width.y + height.y}
	};

	double xSpeed;
	double xStepSpeed;
	double ySpeed;
	double yStepSpeed;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;
	
	particle_planeHit3(int _aliveLoopNum, int _x, int _y,double radius);
	~particle_planeHit3();
	void showParticle();
private:
	void move();
};
