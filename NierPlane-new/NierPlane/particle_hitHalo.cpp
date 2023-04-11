#include "particle_hitHalo.h"

static IMAGE* hitImg[8];


void drawHalo1(halo hc, int width, int height, double offset = 5) {
	COLORREF stepColor;
	COLORREF maxColor = 0xffffff;
	int stepZ;
	double z;
	double base = sqrt((pow(hc.r + offset, 2) - pow(hc.r, 2)));
	for (int i = hc.r; i > 10; i--) {
		z = sqrt((pow(hc.r + offset, 2) - pow(i, 2)));
		z -= base;
		z /= hc.r;
		z *= 0xff;

		stepZ = (int)z;
		stepZ /= 4;
		stepZ *= 4;
		stepColor = RGB(
			(stepZ),
			(stepZ),
			(stepZ)
		);
		setfillcolor(stepColor);

		solidcircle(width / 2, height / 2, i);
	}
}
void drawHalo2(halo hc, int width, int height, COLORREF maxColor = 0xffffff) {
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
void drawHalo(int r, IMAGE* img1) {
	IMAGE* nowWorkingImage = GetWorkingImage();
	halo hc;
	hc.r = r * 1.6;
	SetWorkingImage(img1);
	//halo hc2;
	drawHalo1(hc, img1->getwidth(), img1->getheight(), 10);
	hc.r = r;
	drawHalo2(hc, img1->getwidth(), img1->getheight(), 0xcccccc);
	Blur_step_weight_25_float(GetImageBuffer(img1), 2, img1->getwidth(), img1->getheight());
	SetWorkingImage(nowWorkingImage);
	//putimage(x - img1.getwidth() / 2, y - img1.getheight() / 2, &img1);
}
void particle_hitHalo::preRenderHitImg() {
	int r = rand() % 10 + 10;
	for (int i = 0; i < 8; i++) {
		r = 20 + i * 30 / 8;
		hitImg[i] = new IMAGE(r * 3.2 + 10, r * 3.2 + 10);
		drawHalo(r, hitImg[i]);
	}
	
	//drawHalo(30, hitImg2);
	//drawHalo(40, hitImg3);

	/*r += rand() % 10 + 10;
	hitImg4 = new IMAGE(r * 3.2 + 10, r * 3.2 + 10);
	drawHalo(r, hitImg4);*/
}
particle_hitHalo::particle_hitHalo(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;
	hitImgIndex[0] = rand() % 6;
	hitImgIndex[1] = rand() % (8 - hitImgIndex[0]) + hitImgIndex[0];

	//preRenderHitImg();

	for (int i = 0; i < 10; i++) {
		new particle_smallSquare(rand() % 5 + 5, rand() % 20 + x, rand() % 20 + y);
	}

	if (totalLastParticlePtr != nullptr) {
		nextParticlePtr = totalLastParticlePtr;
		totalLastParticlePtr->lastParticlePtr = this;
	}
	totalLastParticlePtr = this;
};
particle_hitHalo::~particle_hitHalo() {
	
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
void particle_hitHalo::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_hitHalo();

	showHalo();
	aliveStep++;

	if (aliveStep >= 0) {
		fillColor -= stepColor;
		aliveStep = 0;
		aliveLoopIndex++;
	}
}
void particle_hitHalo::showHalo() {
	if (aliveLoopIndex > aliveLoopNum * 3 / 4) {
		IMAGE* ip = hitImg[hitImgIndex[1]];
		myputimage(x - ip->getwidth() / 2, y - ip->getheight() / 2, ip);
	}
	/*else if (aliveLoopIndex > aliveLoopNum * 2 / 4) {
		myputimage(x - hitImg3.getwidth() / 2, y - hitImg3.getheight() / 2, &hitImg3);
	}
	else if (aliveLoopIndex > aliveLoopNum * 1 / 4) {
		myputimage(x - hitImg2.getwidth() / 2, y - hitImg2.getheight() / 2, &hitImg2);
	}*/
	else if (aliveLoopIndex > 0) {
		IMAGE* ip = hitImg[hitImgIndex[0]];
		myputimage(x - ip->getwidth() / 2, y - ip->getheight() / 2, ip);
	}
}