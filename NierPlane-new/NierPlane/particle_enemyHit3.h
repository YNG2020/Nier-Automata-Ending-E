#pragma once
#include "particle.h"

class particle_enemyHit3 :public particle
{
public:
	int length = 15;
	double x, y;

	int baseH = 20;
	int baseW = 20;
	POINT baseP[8] = {
			{0 + baseH / 2,-3 * baseH + baseH / 2},
			{-1 * baseW + baseW/2,-2 * baseH + baseH / 2},
			{-2 * baseW + baseW / 2,-1 * baseH + baseH / 2},
			{-3 * baseW + baseW / 2,0 + baseH / 2},
			{2 * baseW + baseW / 2,-1 * baseH + baseH / 2},
			{1 * baseW + baseW / 2,0 + baseH / 2} ,
			{0 + baseW / 2,1 * baseH + baseH / 2},
			{-1 * baseW + baseW / 2,2 * baseH + baseH / 2}
	};
	
	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF baseColor = 0xffffff;

	particle_enemyHit3(int _aliveLoopNum, int _x, int _y);
	~particle_enemyHit3();
	void showParticle();
	static void preRender();
private:
}; 
