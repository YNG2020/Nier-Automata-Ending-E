#include "particle_smallSquare.h"

void particle_smallSquare::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_smallSquare();
	setfillcolor(fillColor);

	//solidcircle(x, y, r);
	solidrectangle(x - r, y - r, x + r, y + r);
	//solidpolygon(offsetPoint, 4);
	aliveStep++;
	move();
	if (aliveStep >= 3) {
		fillColor -= stepColor;
		xSpeed -= xStepSpeed;
		ySpeed -= yStepSpeed;
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
particle_smallSquare::particle_smallSquare(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	double speed = (double)(rand() % 1000) / 50;
	double angle = (double)(rand() % 628) / 100;
	r = (rand() % 3);

	stepColor = RGB(
		GetRValue(fillColor) / aliveLoopNum,
		GetGValue(fillColor) / aliveLoopNum,
		GetBValue(fillColor) / aliveLoopNum
	);

	xSpeed = speed * cos(angle);
	xStepSpeed = speed * cos(angle) / aliveLoopNum;
	ySpeed = speed * sin(angle);
	yStepSpeed = speed * sin(angle) / aliveLoopNum;

	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_smallSquare::~particle_smallSquare() {
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
void particle_smallSquare::move() {
	x += xSpeed;
	y += ySpeed;
	if (x < 0 || y < 0) {
		this->~particle_smallSquare();
	}
	if (x > GRAPH_WIDTH || y > GRAPH_HEIGHT) {
		this->~particle_smallSquare();
	}
}