#include "particle_onStagePoint.h"

static IMAGE* redHaloImg;


struct redHalo {
	double r = 50;
	COLORREF maxColor = RGB(70, 30, 30);
	COLORREF minColor = 0;
};

void drawRedHalo2(redHalo hc, int width, int height, COLORREF maxColor = 0xffffff) {
	COLORREF stepColor;
	int stepZ;
	double z;
	double offset = 5;
	double base = sqrt((pow(hc.r + offset, 2) - pow(hc.r, 2)));
	for (int i = hc.r; i > 0; i--) {
		z = i / hc.r * 3.14;
		z = (cos(z) + 1) / 2;
		stepColor = RGB(
			(GetRValue(maxColor) * z),
			(GetGValue(maxColor) * z),
			(GetBValue(maxColor) * z)
		);

		setfillcolor(stepColor);

		solidcircle(width / 2, height / 2, i);
	}

}
void drawRedHalo(int r, IMAGE* img1) {
	IMAGE* nowWorkingImage = GetWorkingImage();
	redHalo hc;
	SetWorkingImage(img1);
	hc.r = r;
	drawRedHalo2(hc, img1->getwidth(), img1->getheight(), hc.maxColor);
	Blur_step_weight_25_float(GetImageBuffer(img1), 2, img1->getwidth(), img1->getheight());
	//Blur_step_weight_25_float(GetImageBuffer(img1), 1, img1->getwidth(), img1->getheight());
	SetWorkingImage(nowWorkingImage);
	//putimage(x - img1.getwidth() / 2, y - img1.getheight() / 2, &img1);
}

void particle_onStagePoint::preRender() {
	redHaloImg = new IMAGE(70,70);
	drawRedHalo(20, redHaloImg);
}

void particle_onStagePoint::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_onStagePoint();
	setfillcolor(fillColor);

	myputimage(x - redHaloImg->getwidth() / 2, y - redHaloImg->getheight() / 2, redHaloImg);
	setfillcolor(0xffffff);
	solidcircle(x, y, r);
	//solidrectangle(x - r, y - r, x + r, y + r);
	//solidpolygon(offsetPoint, 4);
	aliveStep++;
	move();
	if (aliveStep >= 2) {
		fillColor -= stepColor;
		aliveStep = 0;
		aliveLoopIndex++;
	}
}

//particle_onStagePoint::particle_onStagePoint(int _aliveLoopNum, int _x, int _y, int _destX, int _destY) {
//	particle_onStagePoint(_aliveLoopNum, _x, _y, _destX, _destY, 1000);
//}
particle_onStagePoint::particle_onStagePoint(int _aliveLoopNum, int _x, int _y,int _destX,int _destY, int _maxSpeed) {
	maxSpeed = _maxSpeed;
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	offsetPosition.x = destPosition.x = _destX;
	offsetPosition.y = destPosition.y = _destY;

	speed = (double)(rand() % maxSpeed) / 10;
	//angle = (double)(rand() % 628) / 100;
	angle = (double)(rand() % (628));
	if (angle < 314) {
		angle -= 157;
		angle /= 36;
	}
	else
	{
		angle -= 314;
		angle -= 157;
		angle /= 36;
		angle += 314;
	}
	angle -= 80;
	angle = angle / 100;
	

	vX = cos(angle) * speed;
	vY = sin(angle) * speed;
	//r = 10;
	r = rand() % 2;

	stepColor = RGB(
		GetRValue(fillColor) / aliveLoopNum,
		GetGValue(fillColor) / aliveLoopNum,
		GetBValue(fillColor) / aliveLoopNum
	);
	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_onStagePoint::particle_onStagePoint(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	offsetPosition.x = destPosition.x = x;
	offsetPosition.y = destPosition.y = y;

	speed = (double)(rand() % 1000) / 50;
	angle = (double)(rand() % 628) / 100;
	vX = cos(angle) * speed;
	vY = sin(angle) * speed;
	r = 0;
	//r = rand() % 2;

	stepColor = RGB(
		GetRValue(fillColor) / aliveLoopNum,
		GetGValue(fillColor) / aliveLoopNum,
		GetBValue(fillColor) / aliveLoopNum
	);
	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_onStagePoint::~particle_onStagePoint() {
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

void particle_onStagePoint::setDestPosition(int _x, int _y) {
	if (this == nullptr)return;
	destPosition.x = _x;
	destPosition.y = _y;
}
void particle_onStagePoint::move1() {
	float _x = x;
	float _y = y;
	float errorX = _x - destPosition.x;
	float errorY = _y - destPosition.y;

	//double destAngle = -atan2(-errorY, -errorX);

	//double detAngle = angle - destAngle;
	//detAngle *= p;
	//vX = (cos(detAngle) * vX - sin(detAngle) * vY);
	//vY = (cos(detAngle) * vY + sin(detAngle) * vX);

	//vX *= (1 - p_v);
	//vY *= (1 - p_v);


	vX = p_v * (p * errorX) + (1 - p_v) * vX;
	vY = p_v * (p * errorY) + (1 - p_v) * vY;

	float nextX = _x - vX;
	float nextY = _y - vY;

	if (nextX > GRAPH_WIDTH) { nextX = GRAPH_WIDTH;	vX *= -1; }
	else if (nextX < 0) { nextX = 0;		vX *= -1; }
	if (nextY > GRAPH_HEIGHT) { nextY = GRAPH_HEIGHT;	vY *= -1; }
	else if (nextY < 0) { nextY = 0;		vY *= -1; }

	//int detX = destPosition.x - x;
	//int detY = destPosition.y - y;

	


	//offsetPosition.x = (detX * cos(3.14 / 5) - detY * sin(3.14 / 5));
	//offsetPosition.y = (detX * sin(3.14 / 5) + detY * cos(3.14 / 5));

	//offsetPosition.x += destPosition.x;
	//offsetPosition.x += x;
	//offsetPosition.y += destPosition.y;
	//offsetPosition.y += y;

	x = nextX;
	y = nextY;
	return ;
}

void particle_onStagePoint::move() {
	float _x = x;
	float _y = y;
	float errorX = _x - destPosition.x;
	float errorY = _y - destPosition.y;

	double errorSpeed = sqrt(pow(errorX, 2) + pow(errorY, 2));
	speed = sp_v * errorSpeed / 10 + (1 - sp_v) * speed;

	p_v = 1 - (float)aliveLoopIndex / (float)aliveLoopNum;
	if (aliveLoopIndex > 10 && errorSpeed < 100) {
		p_v = 0.1;
	}

	//double destAngle = -atan2(-errorY, -errorX);

	//double detAngle = angle - destAngle;
	//detAngle *= p;
	//vX = (cos(detAngle) * vX - sin(detAngle) * vY);
	//vY = (cos(detAngle) * vY + sin(detAngle) * vX);

	//vX *= (1 - p_v);
	//vY *= (1 - p_v);
	
	double nowAngle;
	if (errorX < 0) {
		nowAngle = angle;
	}

	double destAngle = atan2(errorY, errorX);
	
	if (abs(destAngle - angle) > abs(destAngle + 6.28 - angle)) {
		destAngle += 6.28;
	}
	double errorAngle = destAngle - angle;
	errorAngle = abs(errorAngle);
	angle = p_v * angle  + (1 - p_v) * (errorAngle + angle);

	/*if (angle < 0 || angle >3.14) {
		int a;
	}*/
	
	vX = speed * cos(angle);
	vY = speed * sin(angle);
	//vX = p_v * (p * errorX) + (1 - p_v) * vX;
	//vY = p_v * (p * errorY) + (1 - p_v) * vY;

	float nextX = _x - vX;
	float nextY = _y - vY;

	if (nextX > GRAPH_WIDTH) { nextX = GRAPH_WIDTH;	vX *= -1; }
	else if (nextX < 0) { nextX = 0;		vX *= -1; }
	if (nextY > GRAPH_HEIGHT) { nextY = GRAPH_HEIGHT;	vY *= -1; }
	else if (nextY < 0) { nextY = 0;		vY *= -1; }

	//int detX = destPosition.x - x;
	//int detY = destPosition.y - y;




	//offsetPosition.x = (detX * cos(3.14 / 5) - detY * sin(3.14 / 5));
	//offsetPosition.y = (detX * sin(3.14 / 5) + detY * cos(3.14 / 5));

	//offsetPosition.x += destPosition.x;
	//offsetPosition.x += x;
	//offsetPosition.y += destPosition.y;
	//offsetPosition.y += y;

	x = nextX;
	y = nextY;
	return;
}