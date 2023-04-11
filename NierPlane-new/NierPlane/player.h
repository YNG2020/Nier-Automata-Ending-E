#pragma once
#include "common.h"
#include "bullet.h"
#include "particle_cube3d.h"
#include "particle_planeHit1.h"
#include "particle_planeHit2.h"
#include "particle_planeHit4.h"
#include "MyMusic.h"
#define maxGuardNum 6

static MyMusic shootMusic(1000);

struct PLAYER {

	// 初始化图标的一些常量
	long ratio = 2;						// 图标缩放因子
	int parallelogram2diamond = 2;			// y方向上菱形与平行四边形的距离
	int parallelogram2parallelogram = 1;	// x方向上两平行四边形的距离
	int square2parallelogram = 1;			// y方向上正方形与平行四边形的距离


	// 以下均为每个部件（共5个）所有4点的相对坐标
	// diagram
	POINT diamond_base = { 0,0 };
	POINT diamond[4] = {
		diamond_base,
		(diamond_base.x + 7) * ratio, (diamond_base.y - 5) * ratio,
		(diamond_base.x) * ratio, (diamond_base.y - 20) * ratio,
		(diamond_base.x - 7) * ratio, (diamond_base.y - 5) * ratio
	};
	int pie_r = 30;
	int pie_r1 = 20;
	double pie_angle = 3.14 / 10;
	double pie_angle1 = 3.14 * 6 / 32;
	// 
	int pie_center = 36;
	int pie_center1 = 21;
	//POINT pie_base = { 0,-pie_r };
	POINT pie_c1 = { 0,-pie_center1 };
	POINT pie_base = { 0,-pie_center };


	// left_parallelogram
	//POINT left_parallelogram_base = { -parallelogram2parallelogram,parallelogram2diamond };
	POINT left_triangle_base = { 0 * ratio,-pie_center };
	int left_triangle_x_length = -7 * ratio;
	int left_triangle_y_length = 25 * ratio;
	int left_triangle_y_offset = 19 * ratio;
	POINT left_triangle[3] = {
		left_triangle_base,
		left_triangle_base.x,left_triangle_base.y + left_triangle_y_length,
		left_triangle_base.x + left_triangle_x_length,left_triangle_base.y + left_triangle_y_offset
	};

	// right_triangle
	POINT right_triangle_base = { 0 * ratio,-pie_center };
	int right_triangle_x_length = 7 * ratio;
	int right_triangle_y_length = 25 * ratio;
	int right_triangle_y_offset = 19 * ratio;

	POINT right_triangle[3] = {
		right_triangle_base,
		right_triangle_base.x,right_triangle_base.y + right_triangle_y_length,
		right_triangle_base.x + right_triangle_x_length,right_triangle_base.y + right_triangle_y_offset
	};


	// left_square
	POINT left_square_base = { -7 * ratio ,4 * ratio };
	int left_square_x_length = 2 * ratio;
	POINT left_square[4] = {
		left_square_base,
		left_square_base.x - left_square_x_length, left_square_base.y,
		left_square_base.x - left_square_x_length, left_square_base.y + left_square_x_length,
		left_square_base.x, left_square_base.y + left_square_x_length
	};

	// right_square
	POINT right_square_base = { 7 * ratio ,4 * ratio };
	int right_square_x_length = 2 * ratio;
	POINT right_square[4] = {
		right_square_base,
		right_square_base.x + right_square_x_length, right_square_base.y,
		right_square_base.x + right_square_x_length, right_square_base.y + right_square_x_length,
		right_square_base.x, right_square_base.y + right_square_x_length
	};


};
class player
{
public:
	player(bool _isMain = false);
	~player();

	static player* mainPlayer;

	PLAYER basePlayer;
	double angle = 3.14 / 2;
	double angleSpeed = 3.14 / 50;
	int plane_x = GRAPH_WIDTH / 2;
	int plane_y = GRAPH_HEIGHT / 2;
	int speed = 10;
	int last_x = GRAPH_WIDTH / 2;
	int last_y = 0;

	bool isShow = false;
	bool isMain = false;
	bool isShoot = false;
	bool isMove = true;
	bool isCouldHit = true;



	int moveParticleIndex = 0;

	bool status[3] = { true,true,true };

	int blood = 3;

	void move(int x, int y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void setAngle(double angle);


	
	int hit();
	void showPlayers();
	void showPlayer();
	void clearPlayer();
	void shoot();

	
	void setGuards();


	bool isGuardExist = false;

	int nowGuardNum = 0;
	int guardR = 80;
	//6个护卫的角速度和当前角度(其中一个)
	double angularSpeed = 3.14 / 100;
	double guardAngle = 0;
	player* guard[6] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
private:
	void addGuard();
	void decGuard();
	void creatGuard();
	void letAllGuardShoot();
	void letAllGuardShow();


};

