#pragma once
#include "particle.h"

class particle_enemyHit1 :public particle
{
public:
	int width = 40;
	int height = 40;
	int length = 20;
	COLORREF fillColor = 0xffffff;
	COLORREF baseColor = 0xffffff;
	particle_enemyHit1(int _aliveLoopNum, int _x, int _y);
	~particle_enemyHit1();
	void showParticle();
private:

};
