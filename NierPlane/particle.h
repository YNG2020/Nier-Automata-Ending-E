#pragma once
#include <graphics.h>
#include <math.h>
#include "common.h"
class particle {
public:
	/*particle(int _aliveLoopNum, int _x, int _y) {
		particleCount++;
		aliveLoopNum = aliveLoopNum;
		x = _x;
		y = _y;
		if (totalLastParticlePtr != nullptr) {
			nextParticlePtr = totalLastParticlePtr;
			totalLastParticlePtr->lastParticlePtr = this;
		}
		totalLastParticlePtr = this;
	}*/
	static particle* totalLastParticlePtr;

	particle* lastParticlePtr = nullptr;
	particle* nextParticlePtr = nullptr;
	static int particleCount;
	int aliveLoopNum = 10;
	int aliveLoopIndex = 0;
	int x;
	int y;
	virtual void showParticle() = 0;
};