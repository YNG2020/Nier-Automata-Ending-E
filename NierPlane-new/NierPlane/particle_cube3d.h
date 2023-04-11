#pragma once
#include <graphics.h>
#include <math.h>
#include "particle.h"
struct Point_3d {
	Point_3d(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
	Point_3d() {}
	void setX(double _x) { x = _x; }
	void setY(double _y) { y = _y; }
	void setZ(double _z) { z = _z; }
	double x, y, z;
};
struct Cube {
public:
	Cube(int _x = 0, int _y = 0,int cubeType = 0,double _cubeSize = 2) {
		x = _x;
		y = _y;
		cubeSize = _cubeSize;
		Point_3d p3[8] = {
		{2 * cubeSize,2 * cubeSize,2 * cubeSize},{2 * cubeSize,-2 * cubeSize,2 * cubeSize},{-2 * cubeSize,-2 * cubeSize,2 * cubeSize},{-2 * cubeSize,2 * cubeSize,2 * cubeSize},
		{2 * cubeSize,2 * cubeSize,-2 * cubeSize},{2 * cubeSize,-2 * cubeSize,-2 * cubeSize},{-2 * cubeSize,-2 * cubeSize,-2 * cubeSize},{-2 * cubeSize,2 * cubeSize,-2 * cubeSize}
		};
		for (int i = 0; i < 8; i++) {
			nowCubePoint[i] = p3[i];
			/*nowCubePoint[i].setX(p3[i].x);
			nowCubePoint[i].setY(p3[i].y);
			nowCubePoint[i].setZ(p3[i].z);*/
		}
		
		double xyAngle = (double)(rand() % 628) / 100;
		double xzAngle = (double)(rand() % 628) / 100;
		rotate(xyAngle,xzAngle);
		if (cubeType == 0) {
			showCubeP = &Cube::showAllSide;
		}
		else if(cubeType == 1) {
			showCubeP = &Cube::showAllLine;
		}
	}
	int x, y;
	void (Cube::* showCubeP)(COLORREF);	
	double cubeSize = 2;
	//COLORREF side_color = 0xffffff;
	COLORREF line_color = 0xffffff;
	Point_3d nowCubePoint[8];

	void showCube(COLORREF color) {
		setlinestyle(PS_SOLID, 1);
		(this->*showCubeP)(color);
		//showAllSide(color);
		//showAllLine();
	}
	void showAllSide(COLORREF color) {
		setfillcolor(color);
		int matrix[6][4]{
			{0,1,2,3},
			{4,5,6,7},
			{0,1,5,4},
			{1,2,6,5},
			{2,3,7,6},
			{3,0,4,7}
		};
		POINT pts[4];
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				pts[j] = { (int)nowCubePoint[matrix[i][j]].x + x,(int)nowCubePoint[matrix[i][j]].y + y };
			}
			solidpolygon(pts, 4);
		}
	}
	void showAllLine(COLORREF color) {
		setlinecolor(color);
		for (int i = 0; i < 4; i++) {
			line(static_cast<int>(this->nowCubePoint[i].x) + x, static_cast<int>(this->nowCubePoint[i].y) + y,
				static_cast<int>(this->nowCubePoint[(i + 1) % 4].x) + x, static_cast<int>(this->nowCubePoint[(i + 1) % 4].y) + y);
			line(static_cast<int>(this->nowCubePoint[i + 4].x) + x, static_cast<int>(this->nowCubePoint[i + 4].y) + y,
				static_cast<int>(this->nowCubePoint[(i + 1) % 4 + 4].x) + x, static_cast<int>(this->nowCubePoint[(i + 1) % 4 + 4].y) + y);
			line(static_cast<int>(this->nowCubePoint[i].x) + x, static_cast<int>(this->nowCubePoint[i].y) + y,
				static_cast<int>(this->nowCubePoint[i + 4].x) + x, static_cast<int>(this->nowCubePoint[i + 4].y) + y);
		}
	}
	void rotate(double xyAngle = 3.14 / 20, double xzAngle = 3.14 / 50) {
		rotateXY(xyAngle);
		rotateXZ(xzAngle);
	}
	void rotateXY(double xyAngle) {
		double cos_angle = cos(xyAngle);
		double sin_angle = sin(xyAngle);
		double rx, ry;
		for (int i = 0; i < 8; i++) {
			rx = this->nowCubePoint[i].x;
			ry = this->nowCubePoint[i].y;
			this->nowCubePoint[i].setX(cos_angle * rx - sin_angle * ry);
			this->nowCubePoint[i].setY(sin_angle * rx + cos_angle * ry);
		}
	}
	void rotateXZ(double xzAngle) {
		double cos_angle = cos(xzAngle);
		double sin_angle = sin(xzAngle);
		double rx, rz;
		for (int i = 0; i < 8; i++) {
			rx = this->nowCubePoint[i].x;
			rz = this->nowCubePoint[i].z;
			this->nowCubePoint[i].setX(cos_angle * rx - sin_angle * rz);
			this->nowCubePoint[i].setZ(sin_angle * rx + cos_angle * rz);
		}
	}
	void showAllPoint() {
		COLORREF pointColor[8]{ RED,GREEN,BLUE,YELLOW,CYAN ,MAGENTA ,0X00AAAA,BROWN };
		for (int i = 0; i < 8; i++) {
			setfillcolor(pointColor[i]);
			fillcircle(static_cast<int>(nowCubePoint[i].x) + x, static_cast<int>(nowCubePoint[i].y) + y, 3);
		}
		setfillcolor(0);
	}
};

class particle_cube3d :public particle
{
public:
	int width = 20;
	int height = 20;

	Cube* cube;
	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	particle_cube3d(int _aliveLoopNum, int _x, int _y);
	~particle_cube3d();
	void showParticle();
private:

};