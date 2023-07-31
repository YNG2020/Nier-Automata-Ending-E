#include "particle_enemyHit3.h"

POINT rotateRect[4];

void particle_enemyHit3::preRender() {
	int rectWidth = 30;
	int rectHeight = 10;
	double cosAngle = cos(3.14 / 4);
	double sinAngle = sin(3.14 / 4);

	POINT baseRect[4] = {

			{-rectWidth / 2,-rectHeight / 2},
			{-rectWidth / 2,rectHeight / 2},
			{rectWidth / 2,rectHeight / 2},
			{rectWidth / 2,-rectHeight / 2}
	};
	for (int i = 0; i < 4; i++) {
		rotateRect[i].x = baseRect[i].x * cosAngle - baseRect[i].y * sinAngle;
		rotateRect[i].y = baseRect[i].x * sinAngle + baseRect[i].y * cosAngle;
	}
}
void particle_enemyHit3::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_enemyHit3();
	POINT pts[4];
	int stepX, stepY;
	setfillcolor(fillColor);
	for (int i = 0; i < 8; i++) {
		stepX = baseP[i].x;
		stepY = baseP[i].y;
		for (int j = 0; j < 4; j++) {
			pts[j].x = x + stepX + rotateRect[j].x;
			pts[j].y = y + stepY + rotateRect[j].y;
		}
		
		solidpolygon(pts, 4);
	}
	fillColor = RGB(GetRValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum,
		GetGValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum,
		GetBValue(baseColor) * (aliveLoopNum - aliveLoopIndex) / aliveLoopNum
	);
	/*solidcircle(x, y, width);*/
	aliveLoopIndex++;
}
particle_enemyHit3::particle_enemyHit3(int _aliveLoopNum, int _x, int _y) {
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
particle_enemyHit3::~particle_enemyHit3() {
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