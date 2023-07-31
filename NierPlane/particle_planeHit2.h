#pragma once
#include "particle.h"
#include "particle_planeHit3.h"

class particle_planeHit2 :public particle
{
public:
	int aliveStep = 0;
	double stepR = 0;
	COLORREF fillColor = 0xffffff;
	COLORREF baseColor = 0xffffff;
	double nowR = 0;
	static particle_planeHit2* nowPlaneHit;
	particle_planeHit2(int _aliveLoopNum, int _x, int _y);
	~particle_planeHit2();
	void showParticle();
	double getNowR();
	static void preRender();
private:

};