#pragma once
#include <graphics.h>
#include <math.h>
#include "particle.h"


class particle_onStagePoint2 :public particle
{
public:
	float source1_x, source1_y;		// ����Դ1
	float source2_x, source2_y;		// ����Դ2
	float source3_x, source3_y;		// ����Դ3
	float source4_x, source4_y;		// ����Դ4

	float vX, vY;			// �ٶ�

//#define source1_k (float)5000	// ����Դ1ǿ��
//#define source2_k (float)5000	// ����Դ2ǿ��
//#define source3_k (float)15000	// ����Դ3ǿ��
//#define source4_k (float)50000	// ����Դ4ǿ��

#define source1_k (float)2500	// ����Դ1ǿ��
#define source2_k (float)2500	// ����Դ2ǿ��
#define source3_k (float)7500	// ����Դ3ǿ��
#define source4_k (float)15000	// ����Դ4ǿ��

	int lr = 1;
	int ori_x_range = 100;	// ���ӳ�ʼx���귶Χ
	int ori_y_range = 30;	// ���ӳ�ʼy���귶Χ
	int ori_vX_range = 5;	// ���ӳ�ʼx�����ٶȷ�Χ
	int ori_vY_range = 2;	// ���ӳ�ʼy�����ٶȷ�Χ
	int vX_min = -10;		// ���ӳ�ʼx������Сֵ
	int vY_min = -3;		// ���ӳ�ʼy������Сֵ

	// ȡ��ѭ����������,�������
	int destNum = 0;

	int aliveStep = 10;
	COLORREF fillColor = 0xffffff;
	COLORREF stepColor = 0x111111;

	particle_onStagePoint2(int _aliveLoopNum, int _x, int _y);
	//particle_onStagePoint2(int _aliveLoopNum, int _x, int _y,int _destX,int _destY);
	particle_onStagePoint2(int _aliveLoopNum, int _x, int _y, int _destX, int _destY, int _maxSpeed = 1000);
	~particle_onStagePoint2();
	void showParticle();
	void setDestPosition(int _x, int _y);
	static void preRender();
private:
	void move();
};