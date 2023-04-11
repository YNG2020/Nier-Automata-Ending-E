#include "player.h"

player* player::mainPlayer = nullptr;

player::player(bool _isMain)
{
	isMain = _isMain;
	if (isMain) {
		shootMusic.open_music(_T("shooting3.mp3"));
		player::mainPlayer = this;
		isShow = true;
		creatGuard();
	}
	
}

player::~player()
{
}

void player::showPlayers() {
	setlinestyle(PS_SOLID, 1);
	this->showPlayer();
	this->guardAngle += this->angularSpeed;
	this->guardAngle = this->guardAngle > 2 * 3.14 ? 0 : this->guardAngle;
	if (isGuardExist) {
		for (int i = 0; i < 6; i++) {
			double cos_angle = cos(guardAngle + i * 3.14 / 3);
			double sin_angle = sin(guardAngle + i * 3.14 / 3);
			guard[i]->move(plane_x + cos_angle * guardR, plane_y + sin_angle * guardR);
			guard[i]->showPlayer();
		}
	}
}
void player::showPlayer() {
	if (!isShow) return;
	double cos_angle = -cos(angle);
	double sin_angle = -sin(angle);
	POINT pts[4];
	
	COLORREF lineColor = RGB(60, 60, 50);
	
	if (status[1]) {
		setlinecolor(lineColor);
		setfillcolor(RGB(255, 255, 255));
		for (int i = 0; i < 3; i++) {
			pts[i].x = plane_x + sin_angle * basePlayer.left_triangle[i].x - cos_angle * basePlayer.left_triangle[i].y;
			pts[i].y = plane_y + cos_angle * basePlayer.left_triangle[i].x + sin_angle * basePlayer.left_triangle[i].y;
		}
		fillpolygon(pts, 3);
		for (int i = 0; i < 4; i++) {
			pts[i].x = plane_x + sin_angle * basePlayer.left_square[i].x - cos_angle * basePlayer.left_square[i].y;
			pts[i].y = plane_y + cos_angle * basePlayer.left_square[i].x + sin_angle * basePlayer.left_square[i].y;
		}
		solidpolygon(pts, 4);
	}
	if (status[2]) {
		for (int i = 0; i < 3; i++) {
			pts[i].x = plane_x + sin_angle * basePlayer.right_triangle[i].x - cos_angle * basePlayer.right_triangle[i].y;
			pts[i].y = plane_y + cos_angle * basePlayer.right_triangle[i].x + sin_angle * basePlayer.right_triangle[i].y;
		}
		fillpolygon(pts, 3);

		for (int i = 0; i < 4; i++) {
			pts[i].x = plane_x + sin_angle * basePlayer.right_square[i].x - cos_angle * basePlayer.right_square[i].y;
			pts[i].y = plane_y + cos_angle * basePlayer.right_square[i].x + sin_angle * basePlayer.right_square[i].y;
		}
		solidpolygon(pts, 4);
	}
	setfillcolor(lineColor);
	solidcircle(plane_x, plane_y, 5);
	setlinecolor(lineColor);
	setfillcolor(RGB(255, 255, 255));
	if (status[0]) {
		
		pts[0].x = plane_x + sin_angle * basePlayer.pie_base.x - cos_angle * basePlayer.pie_base.y;
		pts[0].y = plane_y + cos_angle * basePlayer.pie_base.x + sin_angle * basePlayer.pie_base.y;

		pts[1].x = plane_x + sin_angle * basePlayer.pie_c1.x - cos_angle * basePlayer.pie_c1.y;
		pts[1].y = plane_y + cos_angle * basePlayer.pie_c1.x + sin_angle * basePlayer.pie_c1.y;

		fillpie(pts[1].x - basePlayer.pie_r1, pts[1].y - basePlayer.pie_r1,
			pts[1].x + basePlayer.pie_r1, pts[1].y + basePlayer.pie_r1, angle - basePlayer.pie_angle1, angle + basePlayer.pie_angle1);
		setlinecolor(RGB(255, 255, 255));
		fillpie(pts[0].x - basePlayer.pie_r, pts[0].y - basePlayer.pie_r,
			pts[0].x + basePlayer.pie_r, pts[0].y + basePlayer.pie_r, angle - basePlayer.pie_angle, angle + basePlayer.pie_angle);
		
	}
	
}


void player::clearPlayer() {

}
void player::setGuards() {
	isShoot = true;
	isMove = true;
	isGuardExist = true;
	nowGuardNum = 6;
	letAllGuardShoot();
	letAllGuardShow();
	status[0] = true;
	status[1] = true;
	status[2] = true;
	blood = 3;
}
int player::hit() {
	if (!isCouldHit)return 0;
	isCouldHit = false;
	blood--;
	new particle_planeHit1(12, plane_x, plane_y);
	new particle_planeHit2(12, plane_x, plane_y);
	new particle_planeHit4(10, plane_x, plane_y);
	status[blood] = false;
	if (blood <= 0) {
		isShoot = false;
		isMove = false;
		return 1;
	}
	return 0;
}


void player::shoot() {
#define BULLET_OFFSET 40
	
	if ( isShoot) {
		if (isMain) {
			std::thread([]() {
				//shootMusic.play_music();
				mciSendString(TEXT("open sounds//shooting3.wav"), NULL, NULL, NULL);
				mciSendString(TEXT("play sounds//shooting3.wav"), NULL, NULL, NULL);//≤•∑≈“Ù¿÷
				Sleep(360);
				mciSendString(TEXT("close sounds//shooting3.wav"), NULL, NULL, NULL);//≤•∑≈“Ù¿÷
				}).detach();
		}
		
		new bullet( plane_x - (int)(cos( angle) * BULLET_OFFSET), 
				plane_y + (int)(sin( angle) * BULLET_OFFSET),
				angle);
		if (isGuardExist) {
			for (int i = 0; i < 6; i++) {
				guard[i]->shoot();
				if (i % 6 == 0) {
					std::thread([]() {
						mciSendString(TEXT("open sounds//shooting3.wav"), NULL, NULL, NULL);
						mciSendString(TEXT("play sounds//shooting3.wav"), NULL, NULL, NULL);//≤•∑≈“Ù¿÷
						Sleep(360);
						mciSendString(TEXT("close sounds//shooting3.wav"), NULL, NULL, NULL);//≤•∑≈“Ù¿÷
						}).detach();
				}
			}
		}
	}
}
void player::setAngle(double _angle) {
	angle = _angle;
	if (isGuardExist) {
		for (int i = 0; i < 6; i++) {
			guard[i]->setAngle(angle);
		}
	}
}
void player::move(int x,int y) {
	plane_x = clamp(x, 0, GRAPH_WIDTH);
	plane_y = clamp(y, 0, GRAPH_HEIGHT);
	moveParticleIndex++;
#define _offset 10
	if (isMain && moveParticleIndex >= 2) {
	//if (isMain && moveParticleIndex >= 2) {
		moveParticleIndex = 0;
		new particle_cube3d(10, plane_x + cos(angle) * _offset + rand() % 20 - 10, plane_y - sin(angle) * _offset + rand() % 20 - 10);
	}
}

void player::moveUp() {
	move(plane_x, plane_y - speed);
}
void player::moveDown() {
	move(plane_x, plane_y + speed);
}
void player::moveLeft() {
	move(plane_x - speed, plane_y);
}
void player::moveRight() {
	move(plane_x + speed, plane_y);
}

void player::creatGuard() {
	for (int i = 0; i < maxGuardNum; i++) {
		guard[i] = new player();
		guard[i]->blood = 3;
		guard[i]->angle = angle;
	}
	move(plane_x, plane_y);
}

void player::letAllGuardShoot() {
	for (int i = 0; i < maxGuardNum; i++) {
		guard[i]->isShoot = true;
	}
}
void player::letAllGuardShow() {
	for (int i = 0; i < maxGuardNum; i++) {
		guard[i]->isShow = true;
	}
}

void player::addGuard() {
	if (nowGuardNum >= maxGuardNum) {
		return;
	}
	player* p = guard[nowGuardNum];
	nowGuardNum++;

	p->isShow = true;
	p->isShoot = true;
}
void player::decGuard() {
	if (nowGuardNum <= 0) {
		return;
	}
	nowGuardNum--;
	player* p = guard[nowGuardNum];

	p->isShow = false;
	p->isShoot = false;
}
//void player::
//void player::
//void player::
//void player::
//void player::
//void player::