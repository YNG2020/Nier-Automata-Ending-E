#include "particle_planeHit4.h"

#define redFrameNum 10

IMAGE* RedScreen[redFrameNum];

COLORREF drawRedScreen(int x, int y,double n) {
	double u = static_cast<double> (x) / GRAPH_WIDTH;
	double v = static_cast<double> (y) / GRAPH_HEIGHT;

	u -= 0.5;
	v -= 0.5;
	//u *= static_cast<double>(GRAPH_WIDTH) / GRAPH_HEIGHT;

	double r = 0, g = 0, b = 0;
	double d = 0.9 + 0.0125 * n - sqrt((pow(u, 2) + pow(v, 2)));

	double glow = 0.01 / d * 3;

	if (glow < 0.078)glow = 0;
	glow = clamp(glow, 0., 1.);
	if (d < 0) {
		r = 1;
		g = b = 0;
	}

	r += glow;
	/*g += glow;
	b += glow;*/

	r *= 255;
	g *= 255;
	b *= 255;

	r = clamp(r, 0.0, 255.0);
	g = clamp(g, 0.0, 255.0);
	b = clamp(b, 0.0, 255.0);

	return RGB(static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b));
}

void particle_planeHit4::preRender() {

	for (int i = 0; i < redFrameNum; i++) {
		RedScreen[i] = new IMAGE(GRAPH_WIDTH, GRAPH_HEIGHT);
		DWORD* redScreenBuffer = GetImageBuffer(RedScreen[i]);
		for (int y = 0; y < GRAPH_HEIGHT; y++) {
			for (int x = 0; x < GRAPH_WIDTH; x++) {
				redScreenBuffer[y * GRAPH_WIDTH + x] = BGR(drawRedScreen(x, y, i));
			}
		}
	}
}

void particle_planeHit4::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_planeHit4();

	int _index = clamp(aliveLoopIndex, 0, redFrameNum - 1);

	myputimage(0, 0, RedScreen[_index]);

	aliveStep++;
	if (aliveStep >= 0) {
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
particle_planeHit4::particle_planeHit4(int _aliveLoopNum, int _x, int _y) {
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
particle_planeHit4::~particle_planeHit4() {
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

