#pragma once
#include "common.h"


class bullet
{
public:
	bullet(int x,int y,double angle);
	~bullet();
	
	
	POINT pts[4];
	double x;
	double y;
	double xSpeed;
	double ySpeed;
	double angle = 3.14 / 2;
	static int width;
	static int height;
	int border = 32;
	
	double speed = 30;
	IMAGE* bulletImg;
	int move();
	static int getBulletNum() { return bulletNum; }
	static int preRenderStatic();
	static int preRenderStatic2();
	
	void drawBullet();
	void drawBulletWithoutBorder();
	bullet* lastBullet;
	bullet* nextBullet;
	static bullet* theLastBullet;
	
private:
	void preRender();
	void clearBullet();
	void drawBulletImg();
	void drawBulletRect();
	
	static int bulletNum;
	POINT offsetPoint[4];
	POINT borderOffset[4];
	double sin_angle;
	double cos_angle;

};
