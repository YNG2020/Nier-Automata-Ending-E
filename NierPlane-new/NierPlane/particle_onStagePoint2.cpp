#include "particle_onStagePoint2.h"

static IMAGE* redHaloImg[10];

struct redHalo {
	double r = 50;
	COLORREF maxColor = RGB(70, 30, 30);
	COLORREF minColor = 0;
};

void drawRedHalo2_2(redHalo hc, int width, int height, COLORREF maxColor = 0xffffff) {
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
void drawRedHalo2_1(int r, IMAGE* img1, redHalo hc) {
	IMAGE* nowWorkingImage = GetWorkingImage();
	
	SetWorkingImage(img1);
	hc.r = r;
	drawRedHalo2_2(hc, img1->getwidth(), img1->getheight(), hc.maxColor);
	Blur_step_weight_25_float(GetImageBuffer(img1), 2, img1->getwidth(), img1->getheight());
	//Blur_step_weight_25_float(GetImageBuffer(img1), 1, img1->getwidth(), img1->getheight());
	SetWorkingImage(nowWorkingImage);
	//putimage(x - img1.getwidth() / 2, y - img1.getheight() / 2, &img1);
}

void particle_onStagePoint2::preRender() {
	redHalo hc;
	COLORREF stepColor = RGB(
		GetRValue(hc.maxColor) / 10,
		GetGValue(hc.maxColor) / 10,
		GetBValue(hc.maxColor) / 10
	);
	for (int i = 0; i < 10; i++) {
		redHaloImg[i] = new IMAGE(70, 70);
		drawRedHalo2_1(20, redHaloImg[i],hc);
		hc.maxColor -= stepColor;
	}
	
	
}

void particle_onStagePoint2::showParticle() {
	if (aliveLoopIndex > aliveLoopNum)this->~particle_onStagePoint2();

	int imgIndex = min(9,aliveLoopIndex * 10 / aliveLoopNum);

	myputimage(x - redHaloImg[imgIndex]->getwidth() / 2, y - redHaloImg[imgIndex]->getheight() / 2, redHaloImg[imgIndex]);
	setfillcolor(fillColor);
	solidcircle(x, y, 1);
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

particle_onStagePoint2::particle_onStagePoint2(int _aliveLoopNum, int _x, int _y) {
	particleCount++;
	aliveLoopNum = _aliveLoopNum;
	x = _x;
	y = _y;


#define particle_width_offset 100
#define particle_height_offset 30

//#define source1_x_offset 3
//#define source1_y_offset 0		// 引力源1偏移量
#define source1_x_offset 2
#define source1_y_offset 0		// 引力源1偏移量

//#define source2_x_offset 3
//#define source2_y_offset 0		// 引力源2偏移量
#define source2_x_offset 2
#define source2_y_offset 0		// 引力源2偏移量


//#define source3_x_offset 2
//#define source3_y_offset 2		// 引力源3偏移量
#define source3_x_offset 1.5
#define source3_y_offset 1		// 引力源3偏移量

#define source4_x_offset 0
//#define source4_x_offset 1
#define source4_y_offset 0		// 引力源4偏移量
#define particle_x_offset 3


	lr = (rand() % 2 == 1 ? 1 : -1);

	x = _x + particle_width_offset * particle_x_offset * lr + rand() % (ori_x_range)-(ori_x_range) / 2;
	y = _y + rand() % ori_y_range - ori_y_range / 2;

	source1_x = _x - source1_x_offset * particle_width_offset;
	source2_x = _x + source2_x_offset * particle_width_offset;
	source3_x = _x + lr * source3_x_offset * particle_width_offset;
	source4_x = _x + lr * source4_x_offset * particle_width_offset;
	source1_y = _y;
	source2_y = _y;
	source3_y = _y + lr * source3_y_offset * particle_height_offset;
	source4_y = _y;

	vX = lr * vX_min + rand() % ori_vX_range - ori_vX_range / 2;

	vY = lr * vY_min + rand() % ori_vY_range - ori_vY_range / 2;

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

particle_onStagePoint2::~particle_onStagePoint2() {
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

void particle_onStagePoint2::move() {
	// 差1
	float dX1 = x - this->source1_x;
	float dY1 = y - this->source1_y;

	float cita1 = 0;

	// 差2
	float dX2 = x - this->source2_x;
	float dY2 = y - this->source2_y;

	float cita2 = 0;

	// 差3
	float dX3 = x - this->source3_x;
	float dY3 = y - this->source3_y;

	float cita3 = 0;

	// 差4
	float dX4 = x - this->source4_x;
	float dY4 = y - this->source4_y;

	float cita4 = 0;

	// 求角度θ1
	if (dX1 == 0.0)
		cita1 = 3.1415926 / 2.0;
	else
		cita1 = atan(fabs(dY1 / dX1));

	if ((dX1 < 0.0) && (dY1 >= 0.0))
		cita1 = 3.1415926 - cita1;
	else if ((dX1 < 0.0) && (dY1 < 0.0))
		cita1 = 3.1415926 + cita1;
	else if ((dX1 >= 0.0) && (dY1 < 0.0))
		cita1 = 3.1415926 * 2.0 - cita1;

	// else dx1 >0 && dy1 > 0, cita1 等于原值

	if (dX2 == 0.0)
		cita2 = 3.1415926 / 2.0;
	else
		cita2 = atan(fabs(dY2 / dX2));


	if ((dX2 < 0.0) && (dY2 >= 0.0))
		cita2 = 3.1415926 - cita2;
	else if ((dX2 < 0.0) && (dY2 < 0.0))
		cita2 = 3.1415926 + cita2;
	else if ((dX2 >= 0.0) && (dY2 < 0.0))
		cita2 = 3.1415926 * 2.0 - cita2;

	// 
	if (dX3 == 0.0)
		cita3 = 3.1415926 / 2.0;
	else
		cita3 = atan(fabs(dY3 / dX3));

	if ((dX3 < 0.0) && (dY3 >= 0.0))
		cita3 = 3.1415926 - cita3;
	else if ((dX3 < 0.0) && (dY3 < 0.0))
		cita3 = 3.1415926 + cita3;
	else if ((dX3 >= 0.0) && (dY3 < 0.0))
		cita3 = 3.1415926 * 2.0 - cita3;

	// 
	if (dX4 == 0.0)
		cita4 = 3.1415926 / 2.0;
	else
		cita4 = atan(fabs(dY4 / dX4));

	if ((dX4 < 0.0) && (dY4 >= 0.0))
		cita4 = 3.1415926 - cita4;
	else if ((dX4 < 0.0) && (dY4 < 0.0))
		cita4 = 3.1415926 + cita4;
	else if ((dX4 >= 0.0) && (dY4 < 0.0))
		cita4 = 3.1415926 * 2.0 - cita4;

	float cos_cita1 = cos(cita1);
	float sin_cita1 = sin(cita1);
	float r_square1 = (dX1 * dX1 + dY1 * dY1) + 1000;		// 加1000是为了避免病态值
	r_square1 = max(5000, r_square1);

	float cos_cita2 = cos(cita2);
	float sin_cita2 = sin(cita2);
	float r_square2 = (dX2 * dX2 + dY2 * dY2) + 1500;		// 加1500是为了避免病态值
	r_square2 = max(5000, r_square2);

	float cos_cita3 = cos(cita3);
	float sin_cita3 = sin(cita3);
	float r_square3 = (dX3 * dX3 + dY3 * dY3) + 1500;		// 加1500是为了避免病态值
	r_square3 = max(5000, r_square3);

	float cos_cita4 = cos(cita4);
	float sin_cita4 = sin(cita4);
	float r_square4 = (dX4 * dX4 + dY4 * dY4) + 1500;		// 加1500是为了避免病态值
	r_square4 = max(5000, r_square4);

	float vX = -(source1_k * cos_cita1 / r_square1 + source2_k * cos_cita2 / r_square2 + source3_k * cos_cita3 / r_square3 + source4_k * cos_cita4 / r_square4)	// 强度乘距离(引力)
		+ this->vX;																	// 惯性 
	float vY = -(source1_k * sin_cita1 / r_square1 + source2_k * sin_cita2 / r_square2 + source3_k * sin_cita3 / r_square3 + source4_k * sin_cita4 / r_square4)
		+ this->vY;

	vX = min(15, vX);
	vY = min(15, vY);

	float nextX = x + vX;
	float nextY = y + vY;

	if (abs(nextX - source4_x + lr * source4_x_offset * particle_width_offset) < 5 && abs(nextY - source4_y) < 5) {
		this->vX = vX / 10;
		this->vY = vY / 10;
		
		nextX = x + vX / 10;
		nextY = y + vY / 10;
	}

	this->vX = vX;
	this->vY = vY;

	this->x = nextX;
	this->y = nextY;
}

void particle_onStagePoint2::setDestPosition(int _x, int _y) {
	//source4_x = _x + lr * source4_x_offset * particle_width_offset;
	source4_x = _x;
	source4_y = _y;
}