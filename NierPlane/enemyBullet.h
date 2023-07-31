#pragma once
#include "common.h"
#include "particle_smallSquare.h"

class enemyBullet
{
public:
	enemyBullet(int x, int y, double angle);
	~enemyBullet();


	POINT pts[4];
	double x;
	double y;
	double angle = 3.14 / 2;
	//int width = 10;
	int width = 30;
	int height = 20;
	double speed = 8;
	int move();
	static int getBulletNum() { return bulletNum; }


	enemyBullet* lastBullet;
	enemyBullet* nextBullet;
	void drawBulletWithoutBorder();
	void drawBullet();
	void hideBullet();
	static enemyBullet* theLastEnemyBullet;
	static void preRender();
private:
	static int bulletNum;

	POINT offsetPoint[4];
	double sin_angle;
	double cos_angle;

};