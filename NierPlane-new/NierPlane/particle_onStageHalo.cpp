#include "particle_onStageHalo.h"

static IMAGE* rstageImg[15];
static IMAGE* bstageImg[15];


void drawStrip1(int left, int top, int right, int bottom, IMAGE* img, COLORREF _minColor = 0) {
	COLORREF minColor = _minColor;
	int centerX = (right - left) / 2;
	int centerY = (bottom - top) / 2;
	double radius = (right - left) / 2;
	double baseP = (double)centerX / (double)centerY;
	double p = (double)centerX / (double)centerY;
	COLORREF fillColor = getfillcolor();
	DWORD* imgBuffer = GetImageBuffer(img);

	fillColor = RGB(
		GetRValue(fillColor) - GetRValue(minColor),
		GetGValue(fillColor) - GetGValue(minColor),
		GetBValue(fillColor) - GetBValue(minColor)
	);
	int minr = GetRValue(minColor);
	int ming = GetGValue(minColor);
	int minb = GetBValue(minColor);

	int r = GetRValue(fillColor);
	int g = GetGValue(fillColor);
	int b = GetBValue(fillColor);

	double light;
	for (int i = 0; i < (right - left); i++) {
		for (int j = 0; j < (bottom - top); j++) {
			light = sqrt(pow(i - radius, 2) + pow((centerY - j) * p, 2));
			if (light > radius)continue;
			//light = radius - light;
			light /= radius;
			light = (cos(light * 3.14) + 1) / 2;
			imgBuffer[j * (right - left) + i] = BGR(RGB(
				(int)(light * r + minr),
				(int)(light * g + ming),
				(int)(light * b + minb)
			));
		}
	}
	//myputimage(left, top, img);
}


void particle_onStageHalo::preRender() {
	double bwidth[15] = { 600,625,650,675,700,725,750,825,900,975,975,975,975,975,975 };
	//double bwidth[15] = { 300,375,450,525,600,675,750,825,900,975,975,975,975,975,975 };
	double bheight[15] = { 35,36,37,38,39,40,41,42,43,44 ,36,28,20,12,0};
	//double bheight[15] = { 25,26,27,28,29,30,31,32,33,34 ,28,21,14,7,0};
	double rwidth[15] = { 90,102,114,123,132,144,164,180,190,200,200,200,200,200,200 };
	double rheight[15] = { 55,62, 70,77, 85,92 ,100,107 ,115,122 ,96,72,48,24,0 };

	for (int i = 0; i < 15; i++) {
		bstageImg[i] = new IMAGE(bwidth[i], bheight[i]);
		rstageImg[i] = new IMAGE(rwidth[i], rheight[i]);
		setfillcolor(RGB(130, 100, 130));
		drawStrip1(0, 0, bwidth[i], bheight[i],bstageImg[i]);

		setfillcolor(RGB(200, 10, 50));

		drawStrip1(0,0, rwidth[i], rheight[i],rstageImg[i], RGB(0, 0, 0));
		
	}
}


void particle_onStageHalo::showParticle() {
	if (aliveLoopIndex > aliveLoopNum) {
		this->~particle_onStageHalo();
		return;
	}
	myputimage(x - bstageImg[aliveLoopIndex]->getwidth() / 2, y - bstageImg[aliveLoopIndex]->getheight() / 2, bstageImg[aliveLoopIndex]);
	myputimage(x - rstageImg[aliveLoopIndex]->getwidth() / 2, y - rstageImg[aliveLoopIndex]->getheight() / 2, rstageImg[aliveLoopIndex]);
	
	aliveStep++;
	if (aliveStep >= 2) {
		
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
particle_onStageHalo::particle_onStageHalo(int _aliveLoopNum, int _x, int _y) {
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
particle_onStageHalo::~particle_onStageHalo() {
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
