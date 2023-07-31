#include "particle_cube3d.h"

particle_cube3d::particle_cube3d(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
	cube = new Cube(x, y, rand() % 2, (double)(rand()%20)/10 + 0.5);
};
particle_cube3d::~particle_cube3d() {
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
void particle_cube3d::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_cube3d();
	
	cube->showCube(fillColor);
	aliveStep++;

	if (aliveStep >= 2) {
		cube->rotate();
		fillColor -= stepColor;
		aliveStep = 0;
		aliveLoopIndex++;
	}
}