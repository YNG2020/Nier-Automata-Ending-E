#pragma once
#include "particle.h"

class particle_enemyHit2 :public particle
{
public:
	int width = 40;
	int height = 40;
	int length = 15;
	double x, y;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF baseColor = 0xffffff;
	particle_enemyHit2(int _aliveLoopNum, int _x, int _y);
	~particle_enemyHit2();
	void showParticle();
private:
};
