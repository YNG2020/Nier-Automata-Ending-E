#include "enemyBullet.h"
int enemyBullet::bulletNum = 0;
static IMAGE* bulletImg_1;

void drawEnemyBullet_1(int _x, int _y) {
	int r = 50;
#define EBWIDTH 50
	IMAGE* imgEB = new IMAGE(EBWIDTH, EBWIDTH);

	IMAGE* nowWorkingImg = GetWorkingImage();
	SetWorkingImage(imgEB);

	setfillcolor(RGB(146, 64, 94));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 18);
	setfillcolor(RGB(130, 19, 57));
	//setfillcolor(RGB(130, 56, 78));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 17);
	setfillcolor(RGB(223, 22, 78));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 14);
	int border;
	DWORD* imgBuffer = GetImageBuffer(imgEB);
	setlinecolor(RGB(200, 100, 160));
	circle(EBWIDTH / 2, EBWIDTH / 2, 18);
	Blur_step_weight_25(imgBuffer, 1, EBWIDTH, EBWIDTH);

	SetWorkingImage(nowWorkingImg);

	putimage(_x - EBWIDTH / 2, _y - EBWIDTH / 2, imgEB);
}

enemyBullet* enemyBullet::theLastEnemyBullet = nullptr;
enemyBullet::enemyBullet(int _x, int _y, double _angle)
{
	bulletNum++;
	x = (double)_x;
	y = (double)_y;
	angle = -_angle;
	sin_angle = sin(angle);
	cos_angle = cos(angle);

	lastBullet = theLastEnemyBullet;
	nextBullet = nullptr;
	if (lastBullet != nullptr) {
		lastBullet->nextBullet = this;
	}
	theLastEnemyBullet = this;
	int step_height_x = (int)(cos_angle * height / 2);
	int step_height_y = (int)(sin_angle * height / 2);
	int step_width_x = -(int)(sin_angle * width / 2);
	int step_width_y = (int)(cos_angle * width / 2);

	offsetPoint[0] = { step_height_x + step_width_x,step_height_y + step_width_y };
	offsetPoint[1] = { step_height_x - step_width_x,step_height_y - step_width_y };
	offsetPoint[2] = { -step_height_x - step_width_x,-step_height_y - step_width_y };
	offsetPoint[3] = { -step_height_x + step_width_x,-step_height_y + step_width_y };

	for (int i = 0; i < 4; i++) {
		pts[i].x = offsetPoint[i].x + x;
		pts[i].y = offsetPoint[i].y + y;
	}

}

enemyBullet::~enemyBullet()
{

	if (this->lastBullet != nullptr) {
		this->lastBullet->nextBullet = this->nextBullet;
	}
	if (this->nextBullet != nullptr) {
		this->nextBullet->lastBullet = this->lastBullet;
	}
	if (theLastEnemyBullet == this) {
		theLastEnemyBullet = this->lastBullet;
	}
	for (int i = 0; i < 5; i++) {
		new particle_smallSquare(rand() % 5 + 5, rand() % 20 + x, rand() % 20 + y);
	}
	//hideBullet();
	bulletNum--;
}
int enemyBullet::move() {

	/*int x1 = min(min(pts[0].x, pts[1].x), min(pts[2].x, pts[3].x));
	int y1 = min(min(pts[0].y, pts[1].y), min(pts[2].y, pts[3].y));
	int x2 = max(max(pts[0].x, pts[1].x), max(pts[2].x, pts[3].x));
	int y2 = max(max(pts[0].y, pts[1].y), max(pts[2].y, pts[3].y));

	clearrectangle(x1, y1, x2, y2);*/


	//clearpolygon(pts, 4);
	hideBullet();
	x -= (speed * cos_angle);
	y -= (speed * sin_angle);
	if (x < 0 || y < 0) {
		return 1;
	}
	if (x >= GRAPH_WIDTH || y >= GRAPH_HEIGHT) {
		return 1;
	}
	/*for (int i = 0; i < 4; i++) {
		pts[i].x = offsetPoint[i].x + x;
		pts[i].y = offsetPoint[i].y + y;
		
	}*/
	return 0;
}
void enemyBullet::hideBullet() {
	/*clearcircle(x, y, width / 2);*/
}
void enemyBullet::preRender() {
#define EBWIDTH 50
	bulletImg_1 = new IMAGE(EBWIDTH, EBWIDTH);



	IMAGE* nowWorkingImg = GetWorkingImage();
	SetWorkingImage(bulletImg_1);

	setfillcolor(RGB(146, 64, 94));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 18);
	setfillcolor(RGB(130, 19, 57));
	//setfillcolor(RGB(130, 56, 78));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 17);
	setfillcolor(RGB(223, 22, 78));
	solidcircle(EBWIDTH / 2, EBWIDTH / 2, 14);
	int border;
	DWORD* imgBuffer = GetImageBuffer(bulletImg_1);
	setlinecolor(RGB(200, 100, 160));
	circle(EBWIDTH / 2, EBWIDTH / 2, 18);
	Blur_step_weight_25(imgBuffer, 1, EBWIDTH, EBWIDTH);

	SetWorkingImage(nowWorkingImg);
}
void enemyBullet::drawBullet() {
	int _x = (int)x;
	int _y = (int)y;
	myputimage(_x - EBWIDTH / 2, _y - EBWIDTH / 2, bulletImg_1);
	//putimage(_x - EBWIDTH / 2, _y - EBWIDTH / 2, bulletImg_2);
}
void enemyBullet::drawBulletWithoutBorder() {
	//solidpolygon(pts, 4);
#define EnemyBulletColor (RGB(200,0,80))
	//setbkmode(TRANSPARENT);
	//setrop2(R2_MERGEPEN);
	
	setfillcolor(EnemyBulletColor);
	
	solidcircle(x, y, width / 2);
	
	//setrop2(R2_COPYPEN);
};
