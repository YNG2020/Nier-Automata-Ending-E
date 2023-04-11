#pragma once
#include "common.h"
#include "enemyBullet.h"
#include "enemyBullet_2.h"
#include "particle.h"
#include "particle_enemyHit1.h"
#include "particle_smallSquare.h"
#include "particle_enemyBoom.h"
#include "particle_hitHalo.h"
#include "particle_enemyHit2.h"
#include "particle_enemyHit3.h"
#include "particle_onStageHalo.h"
#include "particle_onStagePoint.h"
#include "particle_onStagePoint2.h"


#define STAGE_STEP 10

enum EnemyType
{
	normalType = 0, speedType, attackType,
};
enum SHOOT_TYPE{
	zero_bullet,
	one_bullet,
	four_bullet,
	six_bullet,
	double_four_bullet,
	double_six_bullet};

class enemy {
public:	
	/// <summary>
	/// ���˵���Ҫ���캯��
	/// </summary>
	/// <param name="_pos">��ʼ���ֵ�λ��</param>
	/// <param name="_width">���˵Ŀ��(�����ֺ�hitbox�й�)</param>
	/// <param name="_height">���˵ĸ߶�(�����ֺ�hitbox�й�)</param>
	/// <param name="_life">���˵�Ѫ��</param>
	/// <param name="_name">������ʾ���ı�</param>
	/// <param name="_p">���˵��ƶ�����(pid��p, ���ƶ��й�)</param>
	/// <param name="_p_v">���˵Ĺ��Ա���(���ƶ��й�)</param>
	/// <param name="_moveRange">���˵��ƶ���Χ, ����Ϊ����(long ��,long ��,long ��,long ��)</param>
	/// <param name="_shootType">���˵����ģʽ, 5��</param>
	enemy(POINT _pos, int _life, int _fontSize ,
		LPCTSTR _name, double _p, double _p_v, RECT _moveRange, 
		SHOOT_TYPE _shootType = one_bullet,double _shootSpeedRatio = 1,EnemyType _enemyType = normalType);
	
	enemy(POINT _pos, int _width, int _height, int _life, int _fontSize,
		LPCTSTR _name, float _p, float _p_v, RECT _moveRange,
		SHOOT_TYPE _shootType = one_bullet, double _shootSpeedRatio = 1);

	~enemy();
	
	// ��ǰλ��
	POINT nowPosition;

	//////////////// ����ƶ����
	// �Ƿ��ƶ�
	bool isMove = false;
	// Ŀ��λ��, ������ƶ��й�, Ĭ�����ʼ����ͬ
	POINT destPosition;

	// ÿ��destSleep��ѭ��ȡһ��Ŀ���
	int destSleep = 30;
	 
	// ȡ��ѭ����������,�������
	int destNum = 0;

	// �˶���Χ(����
	RECT move_range = { 100,100,GRAPH_WIDTH - 100 , GRAPH_HEIGHT - 100 };

	double vX = 0, vY = 0;			// �ٶ�
	double p = 3;			// ����(����ٶ��й�
	double p_v = 0.3;		// ����(��ת���ٶ��й�,ԽСԽƽ��
	////////////////////////////////////////

	// ����
	int width = 60;
	int height = 40;

	// �Ƿ�����ܵ�����
	bool isHit = false;
	// Ѫ��
	int blood = 10;
	// �ٶ�
	int speed = 2;
	
	// �Ƿ�ʼ���, falseΪ�����
	bool isShoot = false;
	// ÿ�ƶ�shootSleep�����һ��
	int shootSleep = 10;
	// �������,��������
	int shootNum = 0;
	int (enemy::* shoot_enemy)() = &enemy::shoot_one;
	int shoot();

	bool isOnstage = false;
	// ��������
	particle_onStagePoint* plist[100];
	
	particle_onStagePoint2* p2list[100];
	int pIndex = 0;
	// ���볡�й�,��������, ���Ϊ0
	int stageIndex = 0;
	int stageY = 0;

	// ����ӵ��ĽǶ�
	double angle = 3.14 / 4;


	// �ֺ�
	int fontSize = 15;
	// ��ʾ�ĵ�������
	//char* name;
	LPCTSTR name;
	// ���������ǰ��Ԫ��
	enemy* last_enemy = nullptr;
	enemy* next_enemy = nullptr;

	// ��������
	static int enemyNum;
	// �������������
	static int totalCount;
	// ����βԪ��
	static enemy* lastEnemy;

	int move();
	int move(int _x, int _y);
	int BuckleBlood(int count);
	
	int shoot_zero();
	int shoot_one();
	int shoot_four();
	int shoot_six();
	int shoot_double_four();
	int shoot_double_six();
	int hit();
	int hit(int x,int y);
	int showEnemy();
	int showEnemy(int x,int y);
	int hideEnemy();
	int showEnemyRect(int x,int y);
	int showEnemyText(int x,int y);
	int onstage(int x, int y, int i);
	int onstage(int i);
	static void mySetFontStyle();
};


struct enemyContainer
{
public:
	enemyContainer(POINT _pos, int _width, int _height, int _life, 
		int _fontSize, LPCTSTR _name, 
		double _p, double _p_v, RECT _moveRange, SHOOT_TYPE _shootType = one_bullet, double _shootSpeedRatio = 1, EnemyType _enemyType = normalType) {
		pos = _pos;
		width = _width;
		height = _height;
		life = _life;
		fontSize = _fontSize;
		name = _name;
		p = _p;
		p_v = _p_v;
		moveRange = _moveRange;
		shootType = _shootType;
		shootSpeedRatio = _shootSpeedRatio;
		enemyType = _enemyType;
		
	}
	enemy* thisEnemy = nullptr;
	POINT pos;
	int width;
	int height;
	int life;
	int fontSize;
	LPCTSTR name;
	double p;
	double p_v;
	RECT moveRange;
	SHOOT_TYPE shootType;
	EnemyType enemyType;
	double shootSpeedRatio;
	void createEnemy(double _degreeOfDifficulty = 1) {

		int _life = life;
		double _p = p;
		double _shootSpeedRatio = shootSpeedRatio;

		switch (enemyType)
		{
		case normalType:
			_life += static_cast<int>(clamp(life * _degreeOfDifficulty * 0.3, 0., 50.));
			_shootSpeedRatio *= clamp(shootSpeedRatio * _degreeOfDifficulty * 1.05, 1., 40.);
			break;
		case speedType:
			_p *= static_cast<int>(clamp(p * _degreeOfDifficulty * 1.05, 0., 0.1));
			_shootSpeedRatio *= clamp(shootSpeedRatio * _degreeOfDifficulty * 0.1, 0.3, 40.);
			break;
		case attackType:
			_p *= static_cast<int>(clamp(p * _degreeOfDifficulty * 0.5, 0., 0.1));
			shootSpeedRatio *= clamp(shootSpeedRatio * _degreeOfDifficulty * 1.5, 1., 40.);
			break;
		default:
			break;
		}
		this->thisEnemy = new enemy(pos, width, height, _life, fontSize, name, _p, p_v, moveRange, shootType, _shootSpeedRatio);
	}
};