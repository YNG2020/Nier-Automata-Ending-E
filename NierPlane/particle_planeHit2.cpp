#pragma once
#include "particle_planeHit2.h"

#define HOLO_IMG_NUM 18
static IMAGE* HOLOIMG[HOLO_IMG_NUM];

particle_planeHit2* particle_planeHit2::nowPlaneHit = nullptr;

#define HOLO_IMG_SIZE 350

struct myPoint {
	myPoint() {}
	myPoint(double _x, double _y) { x = _x, y = _y; }
	double x = 0;
	double y = 0;
};

template<class T>
T convertor(T num, T(*fun)(T)) {
	return fun(num);
}
const double startR = 30;
const double endR = 140;

COLORREF drawHolo1(int x, int y, double radius,double Radius, int graph_wid = GRAPH_WIDTH, int graph_height = GRAPH_HEIGHT) {
	double u = static_cast<double> (x) / graph_wid;
	double v = static_cast<double> (y) / graph_height;

	radius /= graph_height;
	Radius /= graph_height;

	u -= 0.5;
	v -= 0.5;
	u *= static_cast<double>(graph_wid) / graph_height;
	double r = 0, g = 0, b = 0;
	double d = radius - sqrt((pow(u, 2) + pow(v, 2)));
	Radius -= radius;
	clamp(d, 0., 1.);

	double glow = 0.01 / d * 1;
	glow = clamp(glow, 0., 1.);

	if (d <= 0) {
		if (d <= -Radius) {
			r = g = b = 0;
		}
		else r = g = b = 1;
	}

	r += glow;
	g += glow;
	b += glow;

	r *= 255;
	g *= 255;
	b *= 255;


	/*r -= 10;
	g -= 10;
	b -= 10;*/
	r = clamp(r, 0.0, 255.0);
	g = clamp(g, 0.0, 255.0);
	b = clamp(b, 0.0, 255.0);
	//if (r < 6) r = 0;
	//if (g < 6) g = 0;
	//if (b < 6) b = 0;
	return RGB(static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b));
}

void particle_planeHit2::preRender() {
	double r = startR;
	
	const int _aliveNum = 12;
	double stepR = (endR - startR) / _aliveNum;
	DWORD* imgBuffer;
	for (int i = 0; i < HOLO_IMG_NUM; i++) {
		HOLOIMG[i] = new IMAGE(HOLO_IMG_SIZE, HOLO_IMG_SIZE);
		imgBuffer = GetImageBuffer(HOLOIMG[i]);
		for (int y = 0; y < HOLO_IMG_SIZE; y++) {
			for (int x = 0; x < HOLO_IMG_SIZE; x++) {
				imgBuffer[y * HOLO_IMG_SIZE + x] = drawHolo1(x, y, r, r + 10, HOLO_IMG_SIZE, HOLO_IMG_SIZE);
			}
		}
		r += stepR;
	}
}
double particle_planeHit2::getNowR() {
	return nowR;
}
void particle_planeHit2::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_planeHit2();
	if (aliveLoopIndex >= 18)return;
	nowR += stepR;
	myputimage(x - HOLO_IMG_SIZE / 2, y - HOLO_IMG_SIZE / 2, HOLOIMG[aliveLoopIndex]);
	if (++aliveStep >= 0) {
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
particle_planeHit2::particle_planeHit2(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	nowPlaneHit = this;
	nowR = startR;
	stepR = (endR - startR) / _aliveLoopNum;

	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_planeHit2::~particle_planeHit2() {
	nowPlaneHit = nullptr;
	if (lastParticlePtr != nullptr) {
		lastParticlePtr->nextParticlePtr = nextParticlePtr;
	}
	else {
		totalLastParticlePtr = nextParticlePtr;
	}
	if (nextParticlePtr != nullptr) {
		nextParticlePtr->lastParticlePtr = lastParticlePtr;
	}


	for (int i = 0; i < 50; i++) {
		new particle_planeHit3(rand() % 4 + 1, rand() % 20 + x, rand() % 20 + y , endR);
	}
	particleCount--;
}