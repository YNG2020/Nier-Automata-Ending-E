#pragma once
#include "enemy.h"

int enemy::enemyNum = 0;
int enemy::totalCount = 0;
enemy* enemy::lastEnemy = nullptr;


static LOGFONT myFontStyle;
void enemy::mySetFontStyle() {
	LOGFONT f;
	gettextstyle(&f);      // 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;  // 设置输出效果为抗锯齿  
	f.lfWeight = FW_BLACK;
	myFontStyle = f;
}

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
enemy::enemy(POINT _pos, int _width, int _height, int _life,
	int _fontSize, LPCTSTR _name,
	float _p, float _p_v, RECT _moveRange,
	SHOOT_TYPE _shootType, double _shootSpeedRatio) {
	move_range = _moveRange;
	p = _p;
	p_v = _p_v;
	//enemy(_pos, _width, _height, _life, 0, _name, nullptr);
	destPosition = nowPosition = _pos;
	stageY = nowPosition.y;
	width = _width;
	height = _height;
	blood = _life;
	speed = 0;
	fontSize = _fontSize;
	name = _name;
	switch (_shootType)
	{
	case one_bullet:
		shoot_enemy = &enemy::shoot_one;
		shootSleep = (float)35 / _shootSpeedRatio;
		break;
	case four_bullet:
		shoot_enemy = &enemy::shoot_four;
		shootSleep = (float)20 / _shootSpeedRatio;
		break;
	case six_bullet:
		shoot_enemy = &enemy::shoot_six;
		shootSleep = (float)20 / _shootSpeedRatio;
		break;
	case double_four_bullet:
		shoot_enemy = &enemy::shoot_double_four;
		shootSleep = (float)20 / _shootSpeedRatio;
		break;
	case double_six_bullet:
		shoot_enemy = &enemy::shoot_double_six;
		shootSleep = (float)20 / _shootSpeedRatio;
		break;
	default:
		break;
	}
	//showEnemy();


	last_enemy = lastEnemy;
	next_enemy = nullptr;
	if (last_enemy != nullptr) {
		last_enemy->next_enemy = this;
	}
	lastEnemy = this;
	enemyNum++;
}
	/// </summary>
	/// <param name="_pos">初始出现的位置</param>
	/// <param name="_width">敌人的宽度(与文字和hitbox有关)</param>
	/// <param name="_height">敌人的高度(与文字和hitbox有关)</param>
	/// <param name="_life">敌人的血量</param>
	/// <param name="_name">敌人显示的文本</param>
	/// <param name="_p">敌人的移动比例(pid的p, 与移动有关)</param>
	/// <param name="_p_v">敌人的惯性变量(与移动有关)</param>
	/// <param name="_moveRange">敌人的移动范围, 类型为矩形(long 左,long 上,long 右,long 下)</param>
	/// <param name="_shootType">敌人的射击模式, 6种</param>
enemy::enemy(POINT _pos,int _life, 
	int _fontSize ,LPCTSTR _name, 
	double _p, double _p_v, RECT _moveRange,
	SHOOT_TYPE _shootType, double _shootSpeedRatio, EnemyType _enemyType) {
	move_range = _moveRange;
	p = _p;
	p_v = _p_v;
	destPosition = nowPosition = _pos;
	stageY = nowPosition.y;

	fontSize = _fontSize;
	settextstyle(fontSize, 0, _T("宋体"));
	width = max(textwidth(_name) * 1.25, 50);
	height = max(textheight(_name) * 1.5, 50 );
	blood = _life;
	speed = 0;
	
	name = _name;
	memset(static_cast<void*>(plist), 0, 100 * sizeof(particle_onStagePoint*));
	memset(static_cast<void*>(p2list), 0, 100 * sizeof(particle_onStagePoint2*));
	switch (_shootType)
	{
	case zero_bullet:
		shoot_enemy = &enemy::shoot_zero;
		shootSleep = static_cast<float>(35) / _shootSpeedRatio;
		break;
	case one_bullet:
		shoot_enemy = &enemy::shoot_one;
		shootSleep = static_cast<float>(35) / _shootSpeedRatio;
		break;
	case four_bullet:
		shoot_enemy = &enemy::shoot_four;
		shootSleep = static_cast<float>(20) / _shootSpeedRatio;
		break;
	case six_bullet:
		shoot_enemy = &enemy::shoot_six;
		shootSleep = static_cast<float>(20) / _shootSpeedRatio;
		break;
	case double_four_bullet:
		shoot_enemy = &enemy::shoot_double_four;
		shootSleep = static_cast<float>(20) / _shootSpeedRatio;
		break;
	case double_six_bullet:
		shoot_enemy = &enemy::shoot_double_six;
		shootSleep = static_cast<float>(20) / _shootSpeedRatio;
		break;
	default:
		break;
	}
	//showEnemy();


	last_enemy = lastEnemy;
	next_enemy = nullptr;
	if (last_enemy != nullptr) {
		last_enemy->next_enemy = this;
	}
	lastEnemy = this;
	enemyNum++;
}
enemy::~enemy() {
	std::thread([]() {
		mciSendString(TEXT("open sounds//cracking.mp3"), NULL, NULL, NULL);//打开音乐文件
		mciSendString(TEXT("play sounds//cracking.wav"), NULL, NULL, NULL);//播放音乐
		Sleep(100);
		mciSendString(TEXT("close sounds//cracking.wav"), NULL, NULL, NULL);//播放音乐
		}).detach();
	if (this->last_enemy != nullptr) {
		this->last_enemy->next_enemy = this->next_enemy;
	}
	if (this->next_enemy != nullptr) {
		this->next_enemy->last_enemy = this->last_enemy;
	}
	else if (this->next_enemy == nullptr) {
		lastEnemy = this->last_enemy;
	}
	clearrectangle(nowPosition.x - width / 2, nowPosition.y - height / 2,
		nowPosition.x + width / 2, nowPosition.y + height / 2);
	enemyNum--;

	for (int i = 0; i < 100; i++) {
		new particle_smallSquare(rand() % 10 + 10, rand() % 20 + nowPosition.x, rand() % 20 + nowPosition.y);
	}

	new particle_enemyBoom(4,(int)nowPosition.x, (int)nowPosition.y);
	totalCount++;
}
int enemy::hit(int x,int y) {
	this->blood--;
	if (this->blood == 0) {
		this->~enemy();
		return 1;
	}
	showEnemy();
	int random = rand() % 3;
	if (random == 0) {
		//new particle_enemyHit3(1, x, y);
		new particle_enemyHit1(8, x, y);
	}
	else if (random == 1) {
		//new particle_enemyHit3(1, x, y);
		new particle_enemyHit2(8, x, y);
	}
	else if (random == 2) {
		new particle_enemyHit3(8, x, y);
	}
	new particle_hitHalo(1, x, y);
	
	return 0;
}
int enemy::hit() {
	return hit(nowPosition.x, nowPosition.y);
}
int enemy::move() {
	if (destSleep == 0 || !isMove)return 0;
	if ((destNum++ % destSleep) == 0){
		destPosition = { (rand() % (move_range.right - move_range.left)) + move_range.left ,
			(rand() % (move_range.top - move_range.bottom)) + move_range.top };
	}
	float x = nowPosition.x;
	float y = nowPosition.y;
	float errorX = x - destPosition.x;
	float errorY = y - destPosition.y;

	vX = p_v * (p * errorX) + (1 - p_v) * vX;
	vY = p_v * (p * errorY) + (1 - p_v) * vY;

	//限制v的范围, 令其速度不至于太快
	vX = min(vX, 10);
	vY = min(vY, 10);	
	
	vX = max(vX, -10);
	vY = max(vY, -10);


	float nextX = x - vX;
	float nextY = y - vY;

	if (nextX > GRAPH_WIDTH) { nextX = GRAPH_WIDTH;	vX *= -1; }
	else if (nextX < 0) { nextX = 0;		vX *= -1; }
	if (nextY > GRAPH_HEIGHT) { nextY = GRAPH_HEIGHT;	vY *= -1; }
	else if (nextY < 0) { nextY = 0;		vY *= -1; }

	nowPosition = {(int)nextX,(int)nextY};
	if (pIndex < 20) {
		for (int i = 0; i <50; i++) {
			p2list[i]->setDestPosition(nowPosition.x, nowPosition.y);
		}
		pIndex++;
	}
	


	return 0;
}
int enemy::move(int _x, int _y) {
	nowPosition.x = _x;
	nowPosition.y = _y;

	if (nowPosition.x < 0 || nowPosition.y < 0) {
		return 1;
	}
	else if (nowPosition.x >= GRAPH_WIDTH || nowPosition.y >= GRAPH_HEIGHT) {
		return 1;
	}
	return 0;
}
int enemy::BuckleBlood(int count) {
	blood -= count;
	if (blood < 0) {
		return 1;
	}
	else return 0;
}

int enemy::shoot() {
	return (this->*shoot_enemy)();
}


int enemy::showEnemy() {
	//showEnemyRect();
	return showEnemy(nowPosition.x, nowPosition.y);
	
}
int enemy::showEnemy(int x,int y) {
	//showEnemyRect(x,y);
	//static int stageNum = y / STAGE_STEP + 1;
	if (stageIndex < (stageY / STAGE_STEP)) {
		onstage(stageIndex);
		stageIndex++;
	}
	else {
		if (!isOnstage) {
			new particle_onStageHalo(14, nowPosition.x, nowPosition.y);
			for (int i = 0; i < 50; i++) {
				//plist[i] = new particle_onStagePoint(rand() % 5 + 10, rand() % 200 - 100 + nowPosition.x, rand() % 10 - 5 + nowPosition.y, rand() % 20 - 10 + nowPosition.x, rand() % 20 - 10 + nowPosition.y, (width + height)*5);
				p2list[i] = new particle_onStagePoint2(20, rand() % 20 - 10 + nowPosition.x, rand() % 20 - 10 + nowPosition.y);
				//p2list[i] = new particle_onStagePoint2(rand() % 5 + 5, rand() % 20 - 10 + nowPosition.x, rand() % 20 - 10 + nowPosition.y);
			}
			isOnstage = isShoot = isMove = isHit = true;
			return 1;
		}
		//if(!isOnstage)new particle_9(5, nowPosition.x, nowPosition.y);
		
		showEnemyText(x, y);
	}
	
	return 0;
}
int enemy::hideEnemy() {
	/*clearrectangle(nowPosition.x - width / 2, nowPosition.y - height / 2,
		nowPosition.x + width / 2, nowPosition.y + height / 2);*/
	return 0;
}
int enemy::showEnemyRect(int x, int y) {
	solidrectangle(x - width / 2, y - height / 2,
		x + width / 2, y + height / 2);
	return 0;
}
int enemy::showEnemyText(int x, int y) {
	RECT r = { x - width / 2, y - height / 2,
		x + width / 2, y + height / 2 };
	settextstyle(fontSize, 0, _T("宋体"));
	LOGFONT f;
	gettextstyle(&f);      // 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;  // 设置输出效果为抗锯齿  
	f.lfWeight = FW_BLACK;
	settextstyle(&f);      // 设置字体样式
	setbkmode(TRANSPARENT);  // 设置文字背景为透明色
	drawtext(name, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	//drawtext();
	//rectangle(x - width / 2, y - height / 2, x + width / 2, y + height / 2);

	return 0;
}

int enemy::onstage(int x , int y,int i) {
	int stage_y = i * STAGE_STEP;
	stage_y = stage_y > y ? y : stage_y;
	showEnemyText(x, stage_y);
	return 0;
}

int enemy::onstage(int i) {
	onstage(nowPosition.x, nowPosition.y, i);
	return 0;
}

int enemy::shoot_zero() {
	return 0;
}

//单发
int enemy::shoot_one() {
#define OFFSET (10)
	if (!isShoot)return 0;
	angle = ((double)(rand() % 628) / 100);
	new enemyBullet_2(-cos(angle) * ((long)width + OFFSET) / 2 + nowPosition.x,
		sin(angle) * ((long)height + OFFSET) / 2 + nowPosition.y, angle);
	//showEnemy();
	return 0;
}
//均等4发
int enemy::shoot_four() {
#define OFFSET (10)
	if (!isShoot)return 0;
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * (OFFSET) / 2 + nowPosition.x,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * (OFFSET) / 2 + nowPosition.x,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 2);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	angle += 3.14 / 10;
	angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	//showEnemy();
	return 0;
}

//均等6发
int enemy::shoot_six() {
#define OFFSET (10)
	if (!isShoot)return 0;
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * ((double)width + OFFSET) / 2 + nowPosition.x,
				sin(angle) * ((double)height + OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * ((double)width + OFFSET) / 2 + nowPosition.x,
				sin(angle) * ((double)height + OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 3);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	angle += 3.14 / 10;
	angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	//showEnemy();
	return 0;
}

//双4发
int enemy::shoot_double_four() {
#define OFFSET (10)
#define X_OFFSET (width)
	if (!isShoot)return 0;
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * (OFFSET) / 2 + nowPosition.x - X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * (OFFSET) / 2 + nowPosition.x - X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 2);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * (OFFSET) / 2 + nowPosition.x + X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * (OFFSET) / 2 + nowPosition.x + X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 2);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	angle += 3.14 / 40;
	angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	//showEnemy();
	return 0;
}

//双6发
int enemy::shoot_double_six() {
#define OFFSET (10)
#define X_OFFSET (width)
	if (!isShoot)return 0;
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * (OFFSET) / 2 + nowPosition.x - X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * (OFFSET) / 2 + nowPosition.x - X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 3);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			new enemyBullet(-cos(angle) * (OFFSET) / 2 + nowPosition.x + X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}
		else {
			new enemyBullet_2(-cos(angle) * (OFFSET) / 2 + nowPosition.x + X_OFFSET / 2,
				sin(angle) * (OFFSET) / 2 + nowPosition.y, angle);
		}

		angle += (3.14 / 3);
		angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	}
	angle += 3.14 / 40;
	angle = angle > 3.14 * 2 ? angle - 3.14 * 2 : angle;
	//showEnemy();
	return 0;
}
//int enemy::
//int enemy::
//int enemy::