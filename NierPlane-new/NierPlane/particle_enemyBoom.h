#pragma once
#include "particle.h"

class particle_enemyBoom :public particle
{
public:
	int width = 20;
	int height = 20;
	int x, y;
	int aliveStep = 10;
	

	particle_enemyBoom(int _aliveLoopNum, int _x, int _y);
	~particle_enemyBoom();
	void showParticle();
	static void loadBoomImg();
private:

};