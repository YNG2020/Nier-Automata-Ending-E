#pragma once
#include "nierPlane.h"

#include "common.h"
#include "Timer.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyBullet.h"
#include "player.h"
#include "particle.h"
#include "particle_planeHit2.h"
#include "particle_planeHit4.h"
#include "particle_smallSquare.h"
#include "particle_cube3d.h"
#include "particle_onStagePoint.h"
#include "dialogBox.h"
#include "enemyPage.h"
#include "MusicMCI.h"
#include <thread>
#include <iostream>
#include <mutex>
#include <Vfw.h>
#pragma comment(lib, "VFW32.lib")

#pragma comment(lib,"Winmm.lib")

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

typedef int (*HANDLE_FUNCTION)(enemyContainer*, double, int);

using namespace std;

bool nierPlane::isPrintParam = false;

bool isPause = false;
bool isLeft = false;
bool isRight = false;
bool isUp = false;
bool isDown = false;
bool isCWRotate = false;
bool isCCWRotate = false;

//设置计时器

Timer playerShootTime(100);
Timer enemyTime1(10);
Timer playerMoveTime(10);
Timer listenMouseTime(10);
Timer playerBulletMoveTime(25);
Timer enemyBulletMoveTime(25);
Timer loopTime(MainLoopTime);
Timer printParamTime(500);
Timer pauseTime(500);


int bulletCount = 0;
// 定义互斥锁
mutex mtx;


void openMusicFile();
void addTimersCount();
void reDraw();
void preRender();
void clearAllObj();
void putBlackScreen();
void putDialogBox();

void myGetKeyBoardState();
void myClearKeyBoardState();
void movePlayerBulletIfNotHitEnemyOrEnemyBullet();
bool moveEnemyBulletIfNotHitPlayer();
void movePlayer();
void moveEnemyAndShoot();
void planeHitClearEnemyBulletAndEnemy();
void printParam(long, long, int);
void startPause();
void endPause();


int nierPlane::gameMain() 
{
	clock_t onStageTime = clock();

	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	// 新建玩家
	//player* p1 = new player(true);
	player* p1;

	ExMessage message;		// 定义消息变量

	// 消息标记,提示主线程读取鼠标消息
	bool haveMessage = true;
	bool isMessageEnd = false;
	thread messageThread1([](ExMessage* _message, bool* _haveMessage, bool* _isMessageEnd) {
		while (true) {
			if (*_isMessageEnd) { 
				Sleep(500);
				break; 
			}
			Sleep(1);
			*_message = getmessage(EM_MOUSE);
			*_haveMessage = true;
		}
		}, &message, &haveMessage, &isMessageEnd);

	// 触发函数数量
#define handleNum 50
	// 触发函数列表,包含了需要触发的事件
	HANDLE_FUNCTION handleList[handleNum] = {
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			Sleep(1000);
			enemyVctorList[0].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[1].createEnemy();
			Sleep(500);
			enemyVctorList[2].createEnemy();
			Sleep(500);
			enemyVctorList[3].createEnemy();
			Sleep(500);
			enemyVctorList[4].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[5].createEnemy();
			Sleep(1000);
			enemyVctorList[6].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[7].createEnemy();
			Sleep(1000);
			enemyVctorList[8].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[9].createEnemy();
			Sleep(1000);
			enemyVctorList[10].createEnemy();
			Sleep(500);
			enemyVctorList[11].createEnemy();
			Sleep(500);
			enemyVctorList[12].createEnemy();
			Sleep(500);
			enemyVctorList[13].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[14].createEnemy();
			Sleep(1000);
			enemyVctorList[15].createEnemy();
			Sleep(500);
			enemyVctorList[16].createEnemy();
			Sleep(500);
			enemyVctorList[17].createEnemy();
			Sleep(500);
			enemyVctorList[18].createEnemy();
			Sleep(500);
			enemyVctorList[19].createEnemy();
			Sleep(500);
			enemyVctorList[20].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[21].createEnemy();
			Sleep(500);
			enemyVctorList[22].createEnemy();
			Sleep(500);
			enemyVctorList[23].createEnemy();
			Sleep(500);
			enemyVctorList[24].createEnemy();
			Sleep(500);
			enemyVctorList[25].createEnemy();
			Sleep(500);
			enemyVctorList[26].createEnemy();
			Sleep(500);
			enemyVctorList[27].createEnemy();
			Sleep(500);
			enemyVctorList[28].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {

			enemyVctorList[29].createEnemy();
			Sleep(500);
			enemyVctorList[30].createEnemy();
			Sleep(500);
			enemyVctorList[31].createEnemy();
			Sleep(500);
			enemyVctorList[32].createEnemy();
			Sleep(500);
			enemyVctorList[33].createEnemy();
			Sleep(500);
			enemyVctorList[34].createEnemy();
			Sleep(500);
			enemyVctorList[35].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[36].createEnemy();
			Sleep(1000);
			enemyVctorList[37].createEnemy();
			Sleep(500);
			enemyVctorList[38].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[39].createEnemy();
			Sleep(1000);
			enemyVctorList[40].createEnemy();
			Sleep(500);
			enemyVctorList[41].createEnemy();
			Sleep(500);
			enemyVctorList[42].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[43].createEnemy();
			Sleep(1000);
			enemyVctorList[44].createEnemy();
			Sleep(500);
			enemyVctorList[45].createEnemy();
			Sleep(500);
			enemyVctorList[46].createEnemy();
			Sleep(500);
			enemyVctorList[47].createEnemy();
			Sleep(500);
			enemyVctorList[48].createEnemy();
			Sleep(500);
			enemyVctorList[49].createEnemy();
			Sleep(500);
			enemyVctorList[50].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			Sleep(500);
			enemyVctorList[51].createEnemy();
			Sleep(500);
			enemyVctorList[52].createEnemy();
			Sleep(500);
			enemyVctorList[53].createEnemy();
			Sleep(500);
			enemyVctorList[54].createEnemy();
			Sleep(500);
			enemyVctorList[55].createEnemy();
			Sleep(500);
			enemyVctorList[56].createEnemy();
			Sleep(500);
			enemyVctorList[57].createEnemy();
			Sleep(500);
			enemyVctorList[58].createEnemy();
			Sleep(500);
			enemyVctorList[59].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[60].createEnemy();
			Sleep(100);
			enemyVctorList[61].createEnemy();
			Sleep(500);
			enemyVctorList[62].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[63].createEnemy();
			Sleep(100);
			enemyVctorList[64].createEnemy();
			Sleep(500);
			enemyVctorList[65].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[66].createEnemy();
			Sleep(1000);
			enemyVctorList[67].createEnemy();
			Sleep(500);
			enemyVctorList[68].createEnemy();
			Sleep(500);
			enemyVctorList[69].createEnemy();
			Sleep(500);
			enemyVctorList[70].createEnemy();
			Sleep(500);
			enemyVctorList[71].createEnemy();
			Sleep(500);
			enemyVctorList[72].createEnemy();
			Sleep(500);
			enemyVctorList[73].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[74].createEnemy();
			Sleep(500);
			enemyVctorList[75].createEnemy();
			Sleep(500);
			enemyVctorList[76].createEnemy();
			Sleep(500);
			enemyVctorList[77].createEnemy();
			Sleep(500);
			enemyVctorList[78].createEnemy();
			Sleep(500);
			enemyVctorList[79].createEnemy();
			Sleep(500);
			enemyVctorList[80].createEnemy();
			Sleep(500);
			enemyVctorList[81].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[82].createEnemy();
			Sleep(500);
			enemyVctorList[83].createEnemy();
			Sleep(500);
			enemyVctorList[84].createEnemy();
			Sleep(500);
			enemyVctorList[85].createEnemy();
			Sleep(500);
			enemyVctorList[86].createEnemy();
			Sleep(500);
			enemyVctorList[87].createEnemy();
			Sleep(500);
			enemyVctorList[88].createEnemy();
			Sleep(500);
			enemyVctorList[89].createEnemy();
			Sleep(500);
			enemyVctorList[90].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[91].createEnemy();
			Sleep(500);
			enemyVctorList[92].createEnemy();
			Sleep(250);
			enemyVctorList[93].createEnemy();
			Sleep(250);
			enemyVctorList[94].createEnemy();
			Sleep(250);
			enemyVctorList[95].createEnemy();
			Sleep(250);
			enemyVctorList[96].createEnemy();
			Sleep(250);
			enemyVctorList[97].createEnemy();
			Sleep(250);
			enemyVctorList[98].createEnemy();
			Sleep(250);
			enemyVctorList[99].createEnemy();
			Sleep(250);
			enemyVctorList[100].createEnemy();
			Sleep(250);
			enemyVctorList[101].createEnemy();
			Sleep(250);
			enemyVctorList[102].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[103].createEnemy();
			Sleep(500);
			enemyVctorList[104].createEnemy();
			Sleep(250);
			enemyVctorList[105].createEnemy();
			Sleep(250);
			enemyVctorList[106].createEnemy();
			Sleep(250);
			enemyVctorList[107].createEnemy();
			Sleep(250);
			enemyVctorList[108].createEnemy();
			Sleep(250);
			enemyVctorList[109].createEnemy();
			Sleep(250);
			enemyVctorList[110].createEnemy();
			Sleep(250);
			enemyVctorList[111].createEnemy();
			Sleep(250);
			enemyVctorList[112].createEnemy();
			Sleep(250);
			enemyVctorList[113].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[114].createEnemy();
			Sleep(500);
			enemyVctorList[115].createEnemy();
			Sleep(250);
			enemyVctorList[116].createEnemy();
			Sleep(250);
			enemyVctorList[117].createEnemy();
			Sleep(250);
			enemyVctorList[118].createEnemy();
			Sleep(250);
			enemyVctorList[119].createEnemy();
			Sleep(250);
			enemyVctorList[120].createEnemy();
			Sleep(250);
			enemyVctorList[121].createEnemy();
			Sleep(250);
			enemyVctorList[122].createEnemy();
			Sleep(250);
			enemyVctorList[123].createEnemy();
			Sleep(250);
			enemyVctorList[124].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[125].createEnemy();
			Sleep(500);
			enemyVctorList[126].createEnemy();
			Sleep(250);
			enemyVctorList[127].createEnemy();
			Sleep(250);
			enemyVctorList[128].createEnemy();
			Sleep(250);
			enemyVctorList[129].createEnemy();
			Sleep(250);
			enemyVctorList[130].createEnemy();
			Sleep(250);
			enemyVctorList[131].createEnemy();
			Sleep(250);
			enemyVctorList[132].createEnemy();
			Sleep(250);
			enemyVctorList[133].createEnemy();
			Sleep(250);
			enemyVctorList[134].createEnemy();
			Sleep(250);
			enemyVctorList[135].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[136].createEnemy();
			Sleep(500);
			enemyVctorList[137].createEnemy();
			Sleep(250);
			enemyVctorList[138].createEnemy();
			Sleep(250);
			enemyVctorList[139].createEnemy();
			Sleep(250);
			enemyVctorList[140].createEnemy();
			Sleep(250);
			enemyVctorList[141].createEnemy();
			Sleep(250);
			enemyVctorList[142].createEnemy();
			Sleep(250);
			enemyVctorList[143].createEnemy();
			Sleep(250);
			enemyVctorList[144].createEnemy();
			Sleep(250);
			enemyVctorList[145].createEnemy();
			Sleep(250);
			enemyVctorList[146].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[147].createEnemy();
			Sleep(500);
			enemyVctorList[148].createEnemy();
			Sleep(250);
			enemyVctorList[149].createEnemy();
			Sleep(250);
			enemyVctorList[150].createEnemy();
			Sleep(250);
			enemyVctorList[151].createEnemy();
			Sleep(250);
			enemyVctorList[152].createEnemy();
			Sleep(250);
			enemyVctorList[153].createEnemy();
			Sleep(250);
			enemyVctorList[154].createEnemy();
			Sleep(250);
			enemyVctorList[155].createEnemy();
			Sleep(250);
			enemyVctorList[156].createEnemy();
			Sleep(250);
			enemyVctorList[157].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			enemyVctorList[158].createEnemy();
			Sleep(500);
			enemyVctorList[159].createEnemy();
			Sleep(250);
			enemyVctorList[160].createEnemy();
			Sleep(250);
			enemyVctorList[161].createEnemy();
			Sleep(250);
			enemyVctorList[162].createEnemy();
			Sleep(250);
			enemyVctorList[163].createEnemy();
			Sleep(250);
			enemyVctorList[164].createEnemy();
			Sleep(250);
			enemyVctorList[165].createEnemy();
			Sleep(250);
			enemyVctorList[166].createEnemy();
			Sleep(250);
			enemyVctorList[167].createEnemy();
			Sleep(250);
			enemyVctorList[168].createEnemy();
			Sleep(250);
			enemyVctorList[169].createEnemy();
			Sleep(250);
			enemyVctorList[170].createEnemy();
			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			return 0;
		},
	};
	
	// 一个暂停标记和一个终止标记
	bool isLoopEnd = false;

	IMAGE* imgPtr = new IMAGE(GRAPH_WIDTH, GRAPH_HEIGHT);
	DWORD* graphBuffer = GetImageBuffer();
	DWORD* imgBuffer = GetImageBuffer(imgPtr);

	// 设置背景色
	SetWorkingImage();
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	
	// 对子弹/粒子 进行预渲染
	// 对部分图片/效果预生成
	preRender();

	// 打开音乐文件
	openMusicFile();

	// 延时三秒后己方出现
	while (1) {
		if (clock() - onStageTime > 3000) break;
		Sleep(10);
	}
	p1 = new player(true);


	// 监听标记, 为true时停止监听
	bool isListenEnd = false;
	// 监听线程, 监听目前已击败的敌人数量, 当满足触发条件时触发相应的触发函数
	thread listenT1([](bool* isListenEnd, HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, player* p1) {
		bool handleStatus[handleNum];
		for (int i = 0; i < handleNum; i++) {
			handleStatus[i] = true;
		}
		int nowCount = enemy::totalCount;
		int count = enemy::enemyNum;
		int list = -1;
		while (true) {

			list = -1;
			nowCount = enemy::totalCount;
			count = enemy::enemyNum;
			Sleep(100);
			if (*isListenEnd) {
				Sleep(500);
				break;
			}
			if (handleStatus[++list] && (nowCount == 0)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{
						handleList[list](enemyVctorList, 1, 1);
					}
				, handleList, enemyVctorList, list).join();
				p1->isShoot = true;
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 1)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 5)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 7)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 9)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 14)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 18)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 26)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 36)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 39)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 43)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 49)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 60)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 63)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 66)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 72)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 80)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 91)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 103)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 114)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 125)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 136)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 147)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 158)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
		}
		}, & isListenEnd, handleList, enemyVctorList, p1);

	SetWorkingImage(imgPtr);
	setbkcolor(BACKGROUND_COLOR);

	// 临时起意
	IMAGE img(1520, 830);
	bool time_to_end = false;
	float temp_color = 0.0f;
	DWORD* pbImg = GetImageBuffer(&img);
	
	while (true)
	{
		// 将上一帧渲染好的图片放到屏幕上
		memmove(graphBuffer, imgBuffer, GRAPH_HEIGHT * GRAPH_WIDTH * sizeof(DWORD));

		cleardevice();

		myGetKeyBoardState();

		if (playerBulletMoveTime.isOver()) {
			playerBulletMoveTime.updateTime();
			playerBulletMoveTime.resetCount();
			movePlayerBulletIfNotHitEnemyOrEnemyBullet();
			
		}

		if (particle_planeHit2::nowPlaneHit == nullptr) {
			p1->isCouldHit = true;
		}
		else {
			planeHitClearEnemyBulletAndEnemy();
		}

		if (enemyBulletMoveTime.isOver()) {
			enemyBulletMoveTime.updateTime();
			enemyBulletMoveTime.resetCount();
			isLoopEnd = moveEnemyBulletIfNotHitPlayer();
		}

		if (playerMoveTime.isOver()) {
			playerMoveTime.updateTime();
			playerMoveTime.resetCount();
			movePlayer();
		}

		if (enemyTime1.isOver()) {
			enemyTime1.updateTime();
			enemyTime1.resetCount();
			moveEnemyAndShoot();
		}

		if (playerShootTime.isOver()) {
			playerShootTime.updateTime();
			playerShootTime.resetCount();
			{
				p1->shoot();
			}

		}

		if (listenMouseTime.ifOverTime()) {
			listenMouseTime.updateTime();
			//listenMouseTime.resetCount();
			{
				// 获取一条鼠标消息
				if (haveMessage) {
					haveMessage = false;
					if (message.message == WM_MOUSEMOVE)
					{
						p1->last_x = message.x;
						p1->last_y = message.y;
						p1->clearPlayer();
						int detX = p1->plane_x - message.x;
						int detY = p1->plane_y - message.y;
						p1->angle = -atan2(detY, detX);
					}
				}

			}
		}


		//if (KEY_DOWN('H'))
		//	time_to_end = true;

		// 检测是否超过检测暂停按键的间隔时间
		if (pauseTime.ifOverTime()) {
			if (KEY_DOWN('P')) {
				isPause = !isPause;
				pauseTime.updateTime();
				startPause();
			}
		}

		// 检测否是暂停
		while (isPause){
			if (pauseTime.ifOverTime()) {
				if (KEY_DOWN('P')) {
					isPause = !isPause;
					pauseTime.updateTime();
					endPause();
				}
			}
			Sleep(1);
		}

		// 检测是否超过检测 输出数据按键的间隔时间
		if (printParamTime.ifOverTime()) {
			if (KEY_DOWN(VK_F3)) {
				isPrintParam = !isPrintParam;
				printParamTime.updateTime();
			}
		}

		reDraw();
		addTimersCount();
		myClearKeyBoardState();
		if (isLoopEnd) {
			putBlackScreen();
			p1->~player();
			clearAllObj();
			SetWorkingImage();
			cleardevice();
			isListenEnd = true;
			break;
		}

		//if (time_to_end)
		//{
		//	// 直接对显示缓冲区赋值
		//	if (temp_color >= 255)
		//		break;
		//	for (int i = 0; i < 1520 * 830; i++)
		//		pbImg[i] = BGR(RGB(temp_color, temp_color, temp_color, ));
		//	temp_color += 2.5;
		//	music.turn_down_volumn(10);
		//	myputimage(0, 0, &img, 0);
		//}

		 //输出测试数据
		{
			long loopTime3 = loopTime.getLengthBetweenPreviousAndNow();
			while (!loopTime.ifOverTime()) {
				Sleep(2);
			}
			long loopTime4 = loopTime.getLengthBetweenPreviousAndNow();
			
			if (isPrintParam) {
				int lastEnemyBlood = enemy::lastEnemy == nullptr ? 0 : enemy::lastEnemy->blood;
				
				printParam(loopTime3, loopTime4,lastEnemyBlood);
			}
			
		}
		loopTime.updateTime();// 计时器归零
	}

	isListenEnd = true;
	listenT1.join();
	putDialogBox();

	p1 = new player(true);
	p1->setGuards();

	SetWorkingImage(imgPtr);
	setbkcolor(BACKGROUND_COLOR);

	isLoopEnd = false; // 标志归0
	isListenEnd = false;

	enemy::totalCount = 0; // 击杀数归零
	thread listenT2([](bool* isListenEnd, HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList) {
		bool handleStatus[handleNum];
		for (int i = 0; i < handleNum; i++) {
			handleStatus[i] = true;
		}
		int nowCount = enemy::totalCount;
		int count = enemy::enemyNum;
		int list = -1;
		while (true) {

			list = -1;
			nowCount = enemy::totalCount;
			count = enemy::enemyNum;
			Sleep(100);
			if (*isListenEnd) { 
				Sleep(500);
				break; 
			}
			if (handleStatus[++list] && (nowCount == 0)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 1)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 5)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 7)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 9)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 14)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 18)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 26)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 36)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 39)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 43)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 49)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 60)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 63)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 66)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 72)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 80)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 91)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 103)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 114)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 125)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 136)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 147)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 158)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
		}
		}, & isListenEnd, handleList, enemyVctorList);

	haveMessage = true;

	while (true)
	{

		// 将上一帧渲染好的图片放到屏幕上
		memmove(graphBuffer, imgBuffer, GRAPH_HEIGHT * GRAPH_WIDTH * sizeof(DWORD));

		cleardevice();

		myGetKeyBoardState();

		if (playerBulletMoveTime.isOver()) {
			playerBulletMoveTime.updateTime();
			playerBulletMoveTime.resetCount();
			movePlayerBulletIfNotHitEnemyOrEnemyBullet();

		}

		if (particle_planeHit2::nowPlaneHit == nullptr) {
			p1->isCouldHit = true;
		}
		else {
			planeHitClearEnemyBulletAndEnemy();
		}

		if (enemyBulletMoveTime.isOver()) {
			enemyBulletMoveTime.updateTime();
			enemyBulletMoveTime.resetCount();
			isLoopEnd = moveEnemyBulletIfNotHitPlayer();
		}

		if (playerMoveTime.isOver()) {
			playerMoveTime.updateTime();
			playerMoveTime.resetCount();
			movePlayer();
		}

		if (enemyTime1.isOver()) {
			enemyTime1.updateTime();
			enemyTime1.resetCount();
			moveEnemyAndShoot();
		}

		if (playerShootTime.isOver()) {
			playerShootTime.updateTime();
			playerShootTime.resetCount();
			{
				p1->shoot();
			}

		}

		if (listenMouseTime.ifOverTime()) {
			listenMouseTime.updateTime();
			//listenMouseTime.resetCount();
			{
				// 获取一条鼠标消息
				if (haveMessage) {
					haveMessage = false;
					if (message.message == WM_MOUSEMOVE)
					{
						p1->last_x = message.x;
						p1->last_y = message.y;
						p1->clearPlayer();
						int detX = p1->plane_x - message.x;
						int detY = p1->plane_y - message.y;
						p1->angle = -atan2(detY, detX);
					}
				}

			}
		}

		if (KEY_DOWN('H'))
			time_to_end = true;

		// 检测是否超过检测暂停按键的间隔时间
		if (pauseTime.ifOverTime()) {
			if (KEY_DOWN('P')) {
				isPause = !isPause;
				pauseTime.updateTime();
				startPause();
			}
		}

		// 检测否是暂停
		while (isPause) {
			if (pauseTime.ifOverTime()) {
				if (KEY_DOWN('P')) {
					isPause = !isPause;
					pauseTime.updateTime();
					endPause();
				}
			}
			Sleep(1);
		}

		// 检测是否超过检测 输出数据按键的间隔时间
		if (printParamTime.ifOverTime()) {
			if (KEY_DOWN(VK_F3)) {
				isPrintParam = !isPrintParam;
				printParamTime.updateTime();
			}
		}

		reDraw();
		addTimersCount();
		myClearKeyBoardState();
		if (isLoopEnd) {
			putBlackScreen();
			p1->~player();
			clearAllObj();
			SetWorkingImage();
			cleardevice();
			isListenEnd = true;
			break;
		}

		if (time_to_end)
		{
			// 直接对显示缓冲区赋值
			if (temp_color >= 255)
				break;
			if (temp_color >= 150)
				p1->isShoot = false;
			for (int i = 0; i < 1520 * 830; i++)
				pbImg[i] = BGR(RGB(temp_color, temp_color, temp_color, ));
			temp_color += 2.5;
			music.turn_down_volumn(10);
			myputimage(0, 0, &img, 0);
		}

		//输出测试数据
		{
			long loopTime3 = loopTime.getLengthBetweenPreviousAndNow();
			while (!loopTime.ifOverTime()) {
				Sleep(2);
			}
			long loopTime4 = loopTime.getLengthBetweenPreviousAndNow();

			if (isPrintParam) {
				int lastEnemyBlood = enemy::lastEnemy == nullptr ? 0 : enemy::lastEnemy->blood;

				printParam(loopTime3, loopTime4, lastEnemyBlood);
			}

		}
		loopTime.updateTime();// 计时器归零
	}

	// 退出其他线程
	{
		isMessageEnd = true;
		isListenEnd = true;

		listenT2.join();
		messageThread1.join();
	}
	
	Sleep(100);
	// 关闭图形窗口
	closegraph();
	return 0;
}

int nierPlane::endlessGameMain()
{
	clock_t onStageTime = clock();

	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	// 新建玩家
	//player* p1 = new player(true);
	player* p1;

	ExMessage message;		// 定义消息变量

	// 消息标记,提示主线程读取鼠标消息
	bool haveMessage = true;
	bool isMessageEnd = false;
	thread messageThread1([](ExMessage* _message, bool* _haveMessage, bool* _isMessageEnd) {
		while (true) {
			if (*_isMessageEnd) {
				Sleep(500);
				break;
			}
			Sleep(1);
			*_message = getmessage(EM_MOUSE);
			*_haveMessage = true;
		}
		}, &message, &haveMessage, &isMessageEnd);

	// 触发函数数量
#define handleNum 10
	// 触发函数列表,包含了需要触发的事件
	HANDLE_FUNCTION handleList[handleNum] = {
		[](enemyContainer* enemyVctorList,double a,int b)->int {
			enemyVctorList[0].createEnemy();
			enemyVctorList[1].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList,double a,int b)->int {
			enemyVctorList[2].createEnemy();
			enemyVctorList[3].createEnemy();
			enemyVctorList[4].createEnemy();
			enemyVctorList[5].createEnemy();
			enemyVctorList[6].createEnemy();
			enemyVctorList[7].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList,double a,int b)->int {
			enemyVctorList[8].createEnemy();
			enemyVctorList[9].createEnemy();
			enemyVctorList[10].createEnemy();
			enemyVctorList[11].createEnemy();

			return 0;
		},
		[](enemyContainer* enemyVctorList, double a, int b)->int {
			srand(clock());
			int i = rand() % 50;
			if (i < 10) {
				if (i < 1) {
					enemyVctorList[14].createEnemy(a);
				}
				else if (i < 3) {
					enemyVctorList[13].createEnemy(a);
				}
				else enemyVctorList[12].createEnemy(a);
			}
			return 0;
		},

	};

	// 一个暂停标记和一个终止标记
	bool isLoopEnd = false;


	IMAGE* imgPtr = new IMAGE(GRAPH_WIDTH, GRAPH_HEIGHT);
	DWORD* graphBuffer = GetImageBuffer();
	DWORD* imgBuffer = GetImageBuffer(imgPtr);

	// 设置背景色
	SetWorkingImage();
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	// 对子弹/粒子 进行预渲染
	// 对部分图片/效果预生成
	preRender();

	// 打开音乐文件
	openMusicFile();


	// 延时三秒后己方出现
	while (1) {
		if (clock() - onStageTime > 3000) break;
		Sleep(10);
	}
	p1 = new player(true);


	// 监听标记, 为true时停止监听
	bool isListenEnd = false;
	// 监听线程, 监听目前已击败的敌人数量, 当满足触发条件时触发相应的触发函数
	thread listenT1([](bool* isListenEnd, HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, player* p1) {
		bool handleStatus[handleNum];
		for (int i = 0; i < handleNum; i++) {
			handleStatus[i] = true;
		}
		int nowCount = enemy::totalCount;
		int count = enemy::enemyNum;
		int list = -1;
		
		int maxEnemyNum = 3;
		double nowDegreeOfDifficulty = 1;
		double stepDegreeOfDifficulty = 0.1;

		while (true) {

			list = -1;
			nowCount = enemy::totalCount;
			count = enemy::enemyNum;
			Sleep(100);
			if (*isListenEnd) {
				Sleep(500);
				break;
			}
			if (handleStatus[++list] && (nowCount == 0)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{
						handleList[list](enemyVctorList, 1, 1);
					}
				, handleList, enemyVctorList, list).join();
				p1->isShoot = true;
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 2)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 8)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 12) && count <= maxEnemyNum) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list, double degreeOfDifficulty)
					{handleList[list](enemyVctorList, degreeOfDifficulty, 1); }
				, handleList, enemyVctorList, list, nowDegreeOfDifficulty).join();

				//handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 20)) {
				maxEnemyNum = 5;
				nowDegreeOfDifficulty += stepDegreeOfDifficulty;
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 30)) {
				/*thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();*/
				maxEnemyNum = 8;
				nowDegreeOfDifficulty += stepDegreeOfDifficulty;
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 40)) {
				/*thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();*/
				maxEnemyNum = 12;
				nowDegreeOfDifficulty += stepDegreeOfDifficulty;
				handleStatus[list] = false;
			}
			/*if (handleStatus[++list] && (nowCount >= 26)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 36)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}
			if (handleStatus[++list] && (nowCount >= 39)) {
				thread([](HANDLE_FUNCTION* handleList, enemyContainer* enemyVctorList, int list)
					{handleList[list](enemyVctorList, 1, 1); }
				, handleList, enemyVctorList, list).detach();
				handleStatus[list] = false;
			}*/
		}
		}, &isListenEnd, handleList, enemyVctorList, p1);
		//}, &isListenEnd, handleList, endlessEnemyVctorList, p1);

	SetWorkingImage(imgPtr);
	setbkcolor(BACKGROUND_COLOR);


	while (true)
	{

		// 将上一帧渲染好的图片放到屏幕上
		memmove(graphBuffer, imgBuffer, GRAPH_HEIGHT * GRAPH_WIDTH * sizeof(DWORD));

		cleardevice();

		myGetKeyBoardState();

		if (playerBulletMoveTime.isOver()) {
			playerBulletMoveTime.updateTime();
			playerBulletMoveTime.resetCount();
			movePlayerBulletIfNotHitEnemyOrEnemyBullet();

		}

		if (particle_planeHit2::nowPlaneHit == nullptr) {
			p1->isCouldHit = true;
		}
		else {
			planeHitClearEnemyBulletAndEnemy();
		}

		if (enemyBulletMoveTime.isOver()) {
			enemyBulletMoveTime.updateTime();
			enemyBulletMoveTime.resetCount();
			isLoopEnd = moveEnemyBulletIfNotHitPlayer();
		}

		if (playerMoveTime.isOver()) {
			playerMoveTime.updateTime();
			playerMoveTime.resetCount();
			movePlayer();
		}

		if (enemyTime1.isOver()) {
			enemyTime1.updateTime();
			enemyTime1.resetCount();
			moveEnemyAndShoot();
		}

		if (playerShootTime.isOver()) {
			playerShootTime.updateTime();
			playerShootTime.resetCount();
			{
				p1->shoot();
			}

		}

		if (listenMouseTime.ifOverTime()) {
			listenMouseTime.updateTime();
			//listenMouseTime.resetCount();
			{
				// 获取一条鼠标消息
				if (haveMessage) {
					haveMessage = false;
					if (message.message == WM_MOUSEMOVE)
					{
						p1->last_x = message.x;
						p1->last_y = message.y;
						p1->clearPlayer();
						int detX = p1->plane_x - message.x;
						int detY = p1->plane_y - message.y;
						p1->angle = -atan2(detY, detX);
					}
				}

			}
		}


		// 检测是否超过检测暂停按键的间隔时间
		if (pauseTime.ifOverTime()) {
			if (KEY_DOWN('P')) {
				isPause = !isPause;
				pauseTime.updateTime();
				startPause();
			}
		}

		// 检测否是暂停
		while (isPause) {
			if (pauseTime.ifOverTime()) {
				if (KEY_DOWN('P')) {
					isPause = !isPause;
					pauseTime.updateTime();
					endPause();
				}
			}
			Sleep(1);
		}

		// 检测是否超过检测 输出数据按键的间隔时间
		if (printParamTime.ifOverTime()) {
			if (KEY_DOWN(VK_F3)) {
				isPrintParam = !isPrintParam;
				printParamTime.updateTime();
			}
		}

		reDraw();
		addTimersCount();
		myClearKeyBoardState();
		if (isLoopEnd) {
			putBlackScreen();
			p1->~player();
			clearAllObj();
			SetWorkingImage();
			cleardevice();
			isListenEnd = true;
			break;
		}

		//输出测试数据
		{
			long loopTime3 = loopTime.getLengthBetweenPreviousAndNow();
			while (!loopTime.ifOverTime()) {
				Sleep(2);
			}
			long loopTime4 = loopTime.getLengthBetweenPreviousAndNow();

			if (isPrintParam) {
				int lastEnemyBlood = enemy::lastEnemy == nullptr ? 0 : enemy::lastEnemy->blood;

				printParam(loopTime3, loopTime4, lastEnemyBlood);
			}

		}
		loopTime.updateTime();// 计时器归零
	}

	

	// 退出其他线程
	{
		isListenEnd = true;
		listenT1.join();
		isMessageEnd = true;
		isListenEnd = true;
		messageThread1.join();
	}

	Sleep(100);
	// 关闭图形窗口
	closegraph();
	return 0;
}

static void myGetKeyBoardState() {
	if (KEY_DOWN('A')) {
		isLeft = true;
	}
	if (KEY_DOWN('D')) {
		isRight = true;
	}
	if (KEY_DOWN('W')) {
		isUp = true;
	}
	if (KEY_DOWN('S')) {
		isDown = true;
	}
	if (KEY_DOWN('J')) {
		isCWRotate = true;
	}
	if (KEY_DOWN('K')) {
		isCCWRotate = true;
	}

	/*if (KEY_DOWN('P')) {
		isPause = true;
	}*/
	if (KEY_DOWN(VK_UP)) {
		music.turn_up_volumn();
	}
	if (KEY_DOWN(VK_DOWN)) {
		music.turn_down_volumn();
	}
}

static void myClearKeyBoardState() {
	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = false;
	isCWRotate = false;
	isCCWRotate = false;
}

/// <summary>
/// 放对话框
/// </summary>
static void putDialogBox() {
	IMAGE* img = new IMAGE(GRAPH_WIDTH, GRAPH_HEIGHT);
	SetWorkingImage(img);
	setbkcolor(0);
	dialogBox* dB = new dialogBox();
	dialogText* textList[4] = {
		new dialogText(13,(wchar_t*)(L"你承认自己已经战败了吗?")),
		new dialogText(8,(wchar_t*)(L"要在此放弃吗?")),
		new dialogText(28,(wchar_t*)(L"收到来自 开发组 的救援提议")),
		new dialogText(8,(wchar_t*)(L"要接受救援吗?"))
	};

	for (int i = 0; i < textList[0]->textNum; i++) {
		SetWorkingImage(img);
		cleardevice();
		textList[0]->darwText();
		textList[0]->addText();
		dB->drawDialogBox();
		SetWorkingImage();
		putimage(0, 0, img);
		Sleep(100);
	}
	char c = _getch(); // c无用, 只是消除warnning
	for (int i = 0; i < textList[1]->textNum; i++) {
		SetWorkingImage(img);
		cleardevice();
		textList[1]->darwText();
		textList[1]->addText();
		dB->drawDialogBox();
		SetWorkingImage();
		putimage(0, 0, img);
		Sleep(100);
	}
	c = _getch();
	for (int i = 0; i < textList[2]->textNum; i++) {
		SetWorkingImage(img);
		cleardevice();
		textList[2]->darwText();
		textList[2]->addText();
		dB->drawDialogBox();
		SetWorkingImage();
		putimage(0, 0, img);
		Sleep(100);
	}
	c = _getch();
	for (int i = 0; i < textList[3]->textNum; i++) {
		SetWorkingImage(img);
		cleardevice();
		textList[3]->darwText();
		textList[3]->addText();
		dB->drawDialogBox();
		SetWorkingImage();
		putimage(0, 0, img);
		Sleep(100);
	}


}

/// <summary>
/// 黑屏
/// </summary>
static void putBlackScreen() {
	SetWorkingImage();
	int step = 0xff / 16;
	for (int i = 0; i < 16; i++) {

		mycleardevice(step);
		Sleep(50);
	}
	setbkcolor(0);
	cleardevice();
}

/// <summary>
/// 清除所有画布上的对象 (敌人,敌人子弹, 粒子)
/// </summary>
static void clearAllObj() {
	for (int i = 0; i < 10; i++) {
		Sleep(10);
		particle* lastParticlePtr = particle::totalLastParticlePtr;
		while (lastParticlePtr != nullptr) {
			particle* swap = lastParticlePtr->nextParticlePtr;
			lastParticlePtr->~particle();
			lastParticlePtr = swap;
		}
	}

	int bulletNum = bullet::getBulletNum();
	{
		bullet* lastBulletPtr = bullet::theLastBullet;
		bullet* step;
		for (int i = 0; i < bulletNum; i++) {
			if (lastBulletPtr != nullptr) {
				//lastBulletPtr->drawBulletWithoutBorder();
				step = lastBulletPtr;
				lastBulletPtr->~bullet();
				lastBulletPtr = step->lastBullet;

			}
		}
	}

	{
		bulletNum = enemyBullet::getBulletNum();
		enemyBullet* lastEnemyBulletPtr = enemyBullet::theLastEnemyBullet;
		enemyBullet* step;
		for (; lastEnemyBulletPtr != nullptr;) {
			step = lastEnemyBulletPtr;
			lastEnemyBulletPtr->~enemyBullet();
			lastEnemyBulletPtr = step->lastBullet;
		}
	}
	{
		bulletNum = enemyBullet_2::getBulletNum();
		enemyBullet_2* lastEnemyBulletPtr = enemyBullet_2::theLastEnemyBullet;
		enemyBullet_2* step;
		for (; lastEnemyBulletPtr != nullptr;) {
			step = lastEnemyBulletPtr;
			lastEnemyBulletPtr->~enemyBullet_2();
			lastEnemyBulletPtr = step->lastBullet;
		}
	}
	{
		enemy* lastEnemyPtr = enemy::lastEnemy;
		enemy* step;
		for (int j = 0; lastEnemyPtr != nullptr;) {
			step = lastEnemyPtr;
			lastEnemyPtr->~enemy();
			lastEnemyPtr = step->last_enemy;
		}
	}
}

/// <summary>
/// 对一些粒子效果和图片预先生成
/// </summary>
static void preRender() {
	//bullet::preRenderStatic();
	bullet::preRenderStatic2();

	particle_enemyBoom::loadBoomImg();

	particle_hitHalo::preRenderHitImg();

	particle_enemyHit3::preRender();

	particle_planeHit2::preRender();
	particle_planeHit4::preRender();
	
	particle_onStageHalo::preRender();

	particle_onStagePoint::preRender();
	particle_onStagePoint2::preRender();

	enemyBullet::preRender();
	enemyBullet_2::preRender();

	enemy::mySetFontStyle();
}

/// <summary>
/// 打开音乐文件
/// </summary>
static void openMusicFile() {
	//mciSendString(TEXT("open sounds//shooting.wav"), NULL, NULL, NULL);// 打开音乐文件
	//mciSe
	// ndString(TEXT("open sounds//shooting3.mp3"), NULL, NULL, NULL);// 打开音乐文件
	//mciSendString(TEXT("open sounds//Weight_of_the_World.mp3"), NULL, NULL, NULL);// 打开音乐文件
	//mciSendString(TEXT("open sounds//ending_song.mp3"), NULL, NULL, NULL);// 打开音乐文件
	//mciSendString(TEXT("play sounds//Weight_of_the_World.mp3"), NULL, NULL, NULL);// 播放音乐文件
	//mciSendString(TEXT("play sounds//ending_song.mp3"), NULL, NULL, NULL);// 播放音乐文件
}

/// <summary>
/// 每一个循环的绘画部分, 可以调整绘画次序/是否绘画
/// </summary>
static void reDraw() {
	player* player1 = player::mainPlayer;
	player1->showPlayers();

	{
		particle* lastParticlePtr = particle::totalLastParticlePtr;
		while (lastParticlePtr != nullptr) {
			particle* swap = lastParticlePtr->nextParticlePtr;
			lastParticlePtr->showParticle();
			lastParticlePtr = swap;
		}
	}

	int bulletNum = bullet::getBulletNum();
	{
		bullet* lastBulletPtr = bullet::theLastBullet;
		for (int i = 0; i < bulletNum; i++) {
			if (lastBulletPtr != nullptr) {
				//lastBulletPtr->drawBulletWithoutBorder();

				lastBulletPtr->drawBullet();
				lastBulletPtr = lastBulletPtr->lastBullet;

			}
		}
	}

	{
		bulletNum = enemyBullet::getBulletNum();
		enemyBullet* lastEnemyBulletPtr = enemyBullet::theLastEnemyBullet;
		for (; lastEnemyBulletPtr != nullptr;) {

			lastEnemyBulletPtr->drawBullet();
			lastEnemyBulletPtr = lastEnemyBulletPtr->lastBullet;
		}
	}
	{
		bulletNum = enemyBullet_2::getBulletNum();
		enemyBullet_2* lastEnemyBulletPtr = enemyBullet_2::theLastEnemyBullet;
		for (; lastEnemyBulletPtr != nullptr;) {
			lastEnemyBulletPtr->drawBullet();
			lastEnemyBulletPtr = lastEnemyBulletPtr->lastBullet;
		}
	}
	{
		enemy* lastEnemyPtr = enemy::lastEnemy;
		for (int j = 0; lastEnemyPtr != nullptr;) {
			lastEnemyPtr->showEnemy();
			lastEnemyPtr = lastEnemyPtr->last_enemy;
		}
	}


}

static void addTimersCount() {
	playerShootTime.addCount();
	enemyTime1.addCount();
	playerMoveTime.addCount();
	listenMouseTime.addCount();
	playerBulletMoveTime.addCount();
	enemyBulletMoveTime.addCount();
}

/// <summary>
/// 遍历己方子弹, 移动并判断是否击中敌人/敌人的可击破子弹
/// </summary>
void movePlayerBulletIfNotHitEnemyOrEnemyBullet() {
	bullet* lastBulletPtr = bullet::theLastBullet;
	int bulletNum = bullet::getBulletNum();
	for (; lastBulletPtr != nullptr;) {
		int k1 = lastBulletPtr->move();
		enemy* lastEnemyPtr = enemy::lastEnemy;
		for (; lastEnemyPtr != nullptr; ) {
			if (lastBulletPtr != nullptr) {

				if (lastEnemyPtr->isHit) {
					int detX = static_cast<int>(abs(lastBulletPtr->x - lastEnemyPtr->nowPosition.x));
					int detY = static_cast<int>(abs(lastBulletPtr->y - lastEnemyPtr->nowPosition.y));
					if (detX < lastEnemyPtr->width / 2 && detY < lastEnemyPtr->height / 2) {
						lastEnemyPtr->hit(lastBulletPtr->x, lastBulletPtr->y);
						try {
							k1 = 1;
						}
						catch (exception e) {
							SetWorkingImage();
							outtextxy(GRAPH_WIDTH / 2, GRAPH_HEIGHT / 2, L"出现此BUG请通知程序组");
							Sleep(10000);
							system("pause");
						}
						break;
					}
				}
				lastEnemyPtr = lastEnemyPtr->last_enemy;
			}
		}
		{
#define hitBox 40
			enemyBullet_2* lastEnemyBulletPtr = enemyBullet_2::theLastEnemyBullet;
			for (; lastEnemyBulletPtr != nullptr;) {
				enemyBullet_2* swap = lastEnemyBulletPtr->lastBullet;
				if (abs(lastEnemyBulletPtr->x - lastBulletPtr->x) < hitBox && abs(lastEnemyBulletPtr->y - lastBulletPtr->y) < hitBox) {
					lastEnemyBulletPtr->~enemyBullet_2();
					k1 = 1;
					break;
				}
				lastEnemyBulletPtr = swap;
			}
		}

		bullet* swap = lastBulletPtr->lastBullet;
		if (k1 == 1) {
			lastBulletPtr->~bullet();
		}
		lastBulletPtr = swap;
	}
}

/// <summary>
/// 遍历地方子弹(两种), 移动并判断是否击中己方飞机
/// </summary>
/// <returns>己方飞机被击中返回true, 未被击中返回false</returns>
bool moveEnemyBulletIfNotHitPlayer() {
	player* p1 = player::mainPlayer;
	{
		int bulletNum = enemyBullet::getBulletNum();
		enemyBullet* lastEnemyBulletPtr = enemyBullet::theLastEnemyBullet;
		for (int i = 0; i < bulletNum; i++) {
			if (lastEnemyBulletPtr != nullptr) {
				int k = lastEnemyBulletPtr->move();
				int detX = static_cast<int>(abs(lastEnemyBulletPtr->x - p1->plane_x));
				int detY = static_cast<int>(abs(lastEnemyBulletPtr->y - p1->plane_y));
				if (detX < 20 && detY < 20) {
					if (p1->hit() == 1) {
						return true;
					}
					k = 1;
				}
				enemyBullet* swap = lastEnemyBulletPtr->lastBullet;
				if (k == 1) {
					lastEnemyBulletPtr->~enemyBullet();
				}
				lastEnemyBulletPtr = swap;
			}

		}
	}
	{
		int bulletNum = enemyBullet_2::getBulletNum();
		enemyBullet_2* lastEnemyBulletPtr = enemyBullet_2::theLastEnemyBullet;
		for (int i = 0; i < bulletNum; i++) {
			if (lastEnemyBulletPtr != nullptr) {
				int k = lastEnemyBulletPtr->move();
				int detX = static_cast<int>(abs(lastEnemyBulletPtr->x - p1->plane_x));
				int detY = static_cast<int>(abs(lastEnemyBulletPtr->y - p1->plane_y));
				if (detX < 20 && detY < 20) {
					if (p1->hit() == 1) {
						return true;
					}
					k = 1;
				}
				enemyBullet_2* swap = lastEnemyBulletPtr->lastBullet;
				if (k == 1) {
					lastEnemyBulletPtr->~enemyBullet_2();
				}
				lastEnemyBulletPtr = swap;
			}
		}
	}
	return false;
}

/// <summary>
/// 读取键盘, 移动/旋转己方
/// </summary>
void movePlayer(){
	int detX = 0;
	int detY = 0;
	player* p1 = player::mainPlayer;
	detX = p1->plane_x - p1->last_x;
	detY = p1->plane_y - p1->last_y;

	double stepangle = p1->angle;
	//stepangle = -atan2(detY, detX);

	if (p1->isMove) {

		if (isLeft) {
			p1->moveLeft();
		}
		if (isRight) {
			p1->moveRight();
		}
		if (isUp) {
			p1->moveUp();
		}
		if (isDown) {
			p1->moveDown();
		}
		if (isCWRotate) {
			stepangle += p1->angleSpeed;
		}
		if (isCCWRotate) {
			stepangle -= p1->angleSpeed;
		}
	}
	p1->setAngle(stepangle);
	
	//p1->showPlayers();
}

/// <summary>
/// 读取鼠标信息(有的话), 旋转己方飞机使其朝向鼠标所指位置(窗口内)
/// </summary>
/// <param name="haveMessage">是否有消息</param>
/// <param name="m">消息内容</param>
void rotatePlayer(bool haveMessage, ExMessage m) {
	player* p1 = player::mainPlayer;
	
}

/// <summary>
/// 移动敌人, 并在移动一定次数后射击
/// </summary>
void moveEnemyAndShoot() {
	enemy* lastEnemyPtr = enemy::lastEnemy;
	for (; lastEnemyPtr != nullptr;) {
		int enemyX = lastEnemyPtr->nowPosition.x;
		int enemyY = lastEnemyPtr->nowPosition.y;
		// 射击计数, 移动一定次数后射击一次
		if (lastEnemyPtr->shootNum++ % lastEnemyPtr->shootSleep == 0) {
			lastEnemyPtr->shoot();
		}
		enemy* swap = lastEnemyPtr;
		int k = lastEnemyPtr->move();
		lastEnemyPtr = lastEnemyPtr->last_enemy;
		if (k == 1) {
			swap->~enemy();
		}
	}
}

double getDistance(int sx, int sy, int dx, int dy) {
	return sqrt(pow(dx - sx, 2) + pow(dy - sy, 2));
};

void planeHitClearEnemyBulletAndEnemy() {
	particle_planeHit2* pHit2 = particle_planeHit2::nowPlaneHit;
	double r = pHit2->getNowR();
	int k = 0;
	{
		int bulletNum = enemyBullet::getBulletNum();
		enemyBullet* lastEnemyBulletPtr = enemyBullet::theLastEnemyBullet;
		for (int i = 0; i < bulletNum; i++) {
			if (lastEnemyBulletPtr != nullptr) {
				double d = getDistance(pHit2->x,pHit2->y,lastEnemyBulletPtr->x, lastEnemyBulletPtr->y);
				if (d <= r + 10) {
					k = 1;
				}
				enemyBullet* swap = lastEnemyBulletPtr->lastBullet;
				if (k == 1) {
					lastEnemyBulletPtr->~enemyBullet();
					k = 0;
				}
				lastEnemyBulletPtr = swap;
			}

		}
	}
	{
		int bulletNum = enemyBullet_2::getBulletNum();
		enemyBullet_2* lastEnemyBulletPtr = enemyBullet_2::theLastEnemyBullet;
		for (int i = 0; i < bulletNum; i++) {
			if (lastEnemyBulletPtr != nullptr) {
				double d = getDistance(pHit2->x, pHit2->y, lastEnemyBulletPtr->x, lastEnemyBulletPtr->y);
				if (d <= r + 10) {
					k = 1;
				}
				enemyBullet_2* swap = lastEnemyBulletPtr->lastBullet;
				if (k == 1) {
					lastEnemyBulletPtr->~enemyBullet_2();
					k = 0;
				}
				lastEnemyBulletPtr = swap;
			}
		}
	}

	/*enemy* lastEnemyPtr = enemy::lastEnemy;
	for (; lastEnemyPtr != nullptr; ) {
		if (lastEnemyPtr->isHit) {
			double d = getDistance(pHit2->x, pHit2->y, lastEnemyPtr->nowPosition.x, lastEnemyPtr->nowPosition.y);
			if (d < r + 10) {
					k = 1;
			}
			enemy* swap = lastEnemyPtr->last_enemy;
			if (k == 1) {
				lastEnemyPtr->~enemy();
				k = 0;
			}
			lastEnemyPtr = swap;
		}
	}*/
}

void printParam(long realLoopTime, long totalLoopTime, int lastEnemyBlood) {
	const int textHeight = 20;
	wchar_t s1[200];
	wchar_t s2[200];
	wsprintf(s1, L" bulletNum: %2d | enemyBlt1: %2d | enemyBlt2: %2d | enemyNum: %2d | particleNum: %2d | lastEnemyBlood %2d | loodtime1: %4ld | loodtime2: %4ld",
		bullet::getBulletNum(),
		enemyBullet::getBulletNum(),
		enemyBullet_2::getBulletNum(),
		enemy::enemyNum,
		particle::particleCount,
		lastEnemyBlood,
		realLoopTime,
		totalLoopTime
	);
	wsprintf(s2, L" enemyTime1: %4ld | playerMoveTime: %4ld | listenMouseTime: %4ld | playerBulletMoveTime: %4ld |  enemyBulletMoveTime: %4ld | loodtime: %4ld | printParamTime: %4ld | playerShootTime: %6ld",
		
		enemyTime1.getLengthBetweenPreviousAndNow(),
		playerMoveTime.getLengthBetweenPreviousAndNow(),
		listenMouseTime.getLengthBetweenPreviousAndNow(),
		playerBulletMoveTime.getLengthBetweenPreviousAndNow(),
		enemyBulletMoveTime.getLengthBetweenPreviousAndNow(),
		loopTime.getLengthBetweenPreviousAndNow(),
		printParamTime.getLengthBetweenPreviousAndNow(),
		playerShootTime.getLengthBetweenPreviousAndNow()
	);
	settextcolor(WHITE);		// 回复颜色设置
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
	f.lfWeight = FW_DONTCARE;			// 设置字符笔画粗细为最细
	settextstyle(&f);
	settextstyle(textHeight, 0, _T("微软雅黑"));
	setlinecolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(0, 0, s1);

	outtextxy(0, textHeight, s2);

}

void startPause() {
	playerShootTime.pauseTimer();
	enemyTime1.pauseTimer();
	playerMoveTime.pauseTimer();
	listenMouseTime.pauseTimer();
	playerBulletMoveTime.pauseTimer();
	enemyBulletMoveTime.pauseTimer();
	loopTime.pauseTimer();
	printParamTime.pauseTimer();
}

void endPause() {
	playerShootTime.endPauseTimer();
	enemyTime1.endPauseTimer();
	playerMoveTime.endPauseTimer();
	listenMouseTime.endPauseTimer();
	playerBulletMoveTime.endPauseTimer();
	enemyBulletMoveTime.endPauseTimer();
	loopTime.endPauseTimer();
	printParamTime.endPauseTimer();
}