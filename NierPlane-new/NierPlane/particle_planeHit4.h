#pragma once
#include "particle.h"

class particle_planeHit4 :public particle
{
public:

	int aliveStep = 10;

	particle_planeHit4(int _aliveLoopNum, int _x, int _y);
	~particle_planeHit4();
	void showParticle();
	static void preRender();
private:
};
