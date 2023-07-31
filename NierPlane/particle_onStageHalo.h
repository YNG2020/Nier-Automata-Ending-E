#pragma once
#include "particle.h"

class particle_onStageHalo :public particle
{
public:
	
	double x, y;

	int aliveStep = 10;

	particle_onStageHalo(int _aliveLoopNum, int _x, int _y);
	~particle_onStageHalo();
	void showParticle();
	static void preRender();
private:
	void move();
};