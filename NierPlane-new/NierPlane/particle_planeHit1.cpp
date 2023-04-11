#pragma once
#include "particle_planeHit1.h"

void particle_planeHit1::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_planeHit1();
	setlinestyle(PS_SOLID, border);
	setfillcolor(WHITE);
	circle(x, y, static_cast<int>(startRadius + aliveLoopIndex * stepRadius));
	if (++aliveStep >= 0) {

		aliveStep = 0;
		aliveLoopIndex++;
	}
}
particle_planeHit1::particle_planeHit1(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;

	stepRadius = (endRadius - startRadius) / _aliveLoopNum;

	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_planeHit1::~particle_planeHit1() {
	if (lastParticlePtr != nullptr) {
		lastParticlePtr->nextParticlePtr = nextParticlePtr;
	}
	else {
		totalLastParticlePtr = nextParticlePtr;
	}
	if (nextParticlePtr != nullptr) {
		nextParticlePtr->lastParticlePtr = lastParticlePtr;
	}

	particleCount--;
}
