#pragma once
#include "particle.h"

class particle_planeHit1 :public particle
{
public:
	double startRadius = 20;
	double endRadius = 90;
	double border = 3;
	double stepRadius;
	int aliveStep = 0;

	COLORREF fillColor = 0xffffff;
	COLORREF baseColor = 0xffffff;
	particle_planeHit1(int _aliveLoopNum, int _x, int _y);
	~particle_planeHit1();
	void showParticle();
private:

};