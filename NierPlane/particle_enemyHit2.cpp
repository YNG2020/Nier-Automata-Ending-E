#include "particle_enemyHit2.h"

void particle_enemyHit2::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_enemyHit2();
	setfillcolor(fillColor);

	POINT baseP[4] = {
		x - width / 2,y - height / 2,
		x - width / 2,y + height / 2,
		x + width / 2,y + height / 2,
		x + width / 2,y - height / 2
	};

	mysolidrectangle(baseP[0].x, baseP[0].y - length, baseP[3].x, baseP[3].y);
	mysolidrectangle(baseP[1].x, baseP[1].y, baseP[2].x, baseP[2].y + length);
	mysolidrectangle(baseP[0].x - length, baseP[0].y, baseP[1].x, baseP[1].y);
	mysolidrectangle(baseP[3].x, baseP[3].y, baseP[2].x + length, baseP[2].y);

	setfillcolor(0x222222);
	mysolidrectangle(baseP[0].x - length, baseP[0].y - length, baseP[0].x, baseP[0].y);
	mysolidrectangle(baseP[1].x - length, baseP[1].y, baseP[1].x, baseP[1].y + length);
	mysolidrectangle(baseP[2].x, baseP[2].y, baseP[2].x + length, baseP[2].y + length);
	mysolidrectangle(baseP[3].x, baseP[3].y - length, baseP[3].x + length, baseP[3].y);

	setfillcolor(0x222222);
	mysolidrectangle(baseP[0].x, baseP[0].y, baseP[2].x, baseP[2].y);

	fillColor = RGB(GetRValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum,
		GetGValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum,
		GetBValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum
	);
	/*solidcircle(x, y, width);*/
	aliveLoopIndex++;
}
particle_enemyHit2::particle_enemyHit2(int _aliveLoopNum, int _x, int _y) {
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
particle_enemyHit2::~particle_enemyHit2() {
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