#include "particle_planeHit3.h"



void particle_planeHit3::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_planeHit3();
	setfillcolor(fillColor);

	//solidcircle(x, y, r);
	POINT _pts[4] = {
		{pts[0].x + x,pts[0].y + y},
		{pts[1].x + x,pts[1].y + y},
		{pts[2].x + x,pts[2].y + y},
		{pts[3].x + x,pts[3].y + y}
	};
	solidpolygon(_pts,4);
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
particle_planeHit3::particle_planeHit3(int _aliveLoopNum, int _x, int _y,double radius = 0) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	
	double speed = (double)(rand() % 100) / 50;
	double angle = (double)(rand() % 628) / 100;

	x = _x + cos(angle) * radius;
	y = _y + sin(angle) * radius;

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
particle_planeHit3::~particle_planeHit3() {
	
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
void particle_planeHit3::move() {
	x += xSpeed;
	y += ySpeed;
	if (x < 0 || y < 0) {
		this->~particle_planeHit3();
	}
	if (x > GRAPH_WIDTH || y > GRAPH_HEIGHT) {
		this->~particle_planeHit3();
	}
}