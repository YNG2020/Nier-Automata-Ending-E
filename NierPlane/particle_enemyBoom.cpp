#include "particle_enemyBoom.h"

static IMAGE boomImg[2];

particle_enemyBoom::particle_enemyBoom(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;


	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_enemyBoom::~particle_enemyBoom() {
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
void particle_enemyBoom::showParticle() {
	if (aliveLoopIndex >= aliveLoopNum) {
		delete this;
		return;
	}

	aliveStep++;
	//putimage(x - width / 2, y - height / 2, &boomImg);
	//fillrectdwangle(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	width = (boomImg + aliveLoopIndex / 2)->getwidth();
	height = (boomImg + aliveLoopIndex / 2)->getheight();

	myputimage(x - width / 2, y - height / 2, boomImg + aliveLoopIndex/2);
	if (aliveStep >= 2) {
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
void particle_enemyBoom::loadBoomImg() {
	loadimage(boomImg, L"picture//boom4.png");
	loadimage(boomImg + 1, L"picture//boom3.png");
}