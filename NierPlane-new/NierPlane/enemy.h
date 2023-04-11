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
	/// 敌人的主要构造函数
	/// </summary>
	/// <param name="_pos">初始出现的位置</param>
	/// <param name="_width">敌人的宽度(与文字和hitbox有关)</param>
	/// <param name="_height">敌人的高度(与文字和hitbox有关)</param>
	/// <param name="_life">敌人的血量</param>
	/// <param name="_name">敌人显示的文本</param>
	/// <param name="_p">敌人的移动比例(pid的p, 与移动有关)</param>
	/// <param name="_p_v">敌人的惯性变量(与移动有关)</param>
	/// <param name="_moveRange">敌人的移动范围, 类型为矩形(long 左,long 上,long 右,long 下)</param>
	/// <param name="_shootType">敌人的设计模式, 5种</param>
	enemy(POINT _pos, int _life, int _fontSize ,
		LPCTSTR _name, double _p, double _p_v, RECT _moveRange, 
		SHOOT_TYPE _shootType = one_bullet,double _shootSpeedRatio = 1,EnemyType _enemyType = normalType);
	
	enemy(POINT _pos, int _width, int _height, int _life, int _fontSize,
		LPCTSTR _name, float _p, float _p_v, RECT _moveRange,
		SHOOT_TYPE _shootType = one_bullet, double _shootSpeedRatio = 1);

	~enemy();
	
	// 当前位置
	POINT nowPosition;

	//////////////// 随机移动相关
	// 是否移动
	bool isMove = false;
	// 目标位置, 与随机移动有关, 默认与初始点相同
	POINT destPosition;

	// 每隔destSleep个循环取一次目标点
	int destSleep = 30;
	 
	// 取点循环计数变量,无需更改
	int destNum = 0;

	// 运动范围(矩形
	RECT move_range = { 100,100,GRAPH_WIDTH - 100 , GRAPH_HEIGHT - 100 };

	double vX = 0, vY = 0;			// 速度
	double p = 3;			// 比例(与加速度有关
	double p_v = 0.3;		// 动量(与转向速度有关,越小越平滑
	////////////////////////////////////////

	// 长宽
	int width = 60;
	int height = 40;

	// 是否可以受到攻击
	bool isHit = false;
	// 血量
	int blood = 10;
	// 速度
	int speed = 2;
	
	// 是否开始射击, false为不射击
	bool isShoot = false;
	// 每移动shootSleep次射击一次
	int shootSleep = 10;
	// 射击计数,无需设置
	int shootNum = 0;
	int (enemy::* shoot_enemy)() = &enemy::shoot_one;
	int shoot();

	bool isOnstage = false;
	// 出场粒子
	particle_onStagePoint* plist[100];
	
	particle_onStagePoint2* p2list[100];
	int pIndex = 0;
	// 与入场有关,无需设置, 最好为0
	int stageIndex = 0;
	int stageY = 0;

	// 射击子弹的角度
	double angle = 3.14 / 4;


	// 字号
	int fontSize = 15;
	// 显示的敌人文字
	//char* name;
	LPCTSTR name;
	// 敌人链组的前后元素
	enemy* last_enemy = nullptr;
	enemy* next_enemy = nullptr;

	// 敌人数量
	static int enemyNum;
	// 被击落敌人数量
	static int totalCount;
	// 链组尾元素
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