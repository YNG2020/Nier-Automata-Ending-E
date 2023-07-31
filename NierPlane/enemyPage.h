#pragma once
#include "enemy.h"

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


//enum SHOOT_TYPE {
//	one_bullet,
//	four_bullet,
//	six_bullet,
//	double_four_bullet,
//	double_six_bullet
//};

int inti_pos_x = 0;
int inti_pos_y = 0;

int E_FontClass_1 = 25;
int E_FontClass_2 = 20;
int E_FontClass_3 = 15;

int C_FontClass_1 = 20;
int C_FontClass_2 = 18;
int C_FontClass_3 = 13;

int C_Font_wid = 80;

int BufferClass_1 = 10;
int BufferClass_2 = 10;
int BufferClass_3 = 3;

int Mid_x = GRAPH_WIDTH / 2;
int Mid_y = GRAPH_HEIGHT / 2;

// 原点出现波动范围
int Class_1_ori_x_range = GRAPH_WIDTH / 4;
int Class_1_ori_y_range = GRAPH_HEIGHT / 4;

int Class_2_ori_x_range = GRAPH_WIDTH / 2;
int Class_2_ori_y_range = GRAPH_HEIGHT / 2;

// 原点初始值
int Class_1_ori_x = GRAPH_WIDTH / 2;
int Class_1_ori_y = 3 * GRAPH_HEIGHT / 8;

int Class_2_ori_x = GRAPH_WIDTH / 2;
int Class_2_ori_y = 3 * GRAPH_HEIGHT / 8;

int ori_x = 0;
int ori_y = 0;

float Class_1_p = 0.01;
float Class_2_p = 0.05;

float Class_1_pv = 0;

double shootSpeedRatio_class1 = 1.0;
double shootSpeedRatio_class2 = 2.0;
int buffer_ratio = 2;

#define Class1_enemy(_enemy_name, _Font_Size, _Buffer, _Wid, _Hei, _bullet_type, _shootSpeedRatio) {{Class_1_ori_x + (2 * (rand() % 2) - 1) * (rand() % Class_1_ori_x_range), Class_1_ori_y + (2 * rand() % 2 - 1) * (rand() % Class_1_ori_y_range)}\
,_Wid,_Hei\
,_Buffer,_Font_Size,_enemy_name\
,Class_1_p,0.1\
,{100,100,GRAPH_WIDTH - 100,GRAPH_HEIGHT - 200}\
,_bullet_type,_shootSpeedRatio}

#define Class2_enemy(_enemy_name, _Font_Size, _Buffer, _Wid, _Hei, _bullet_type,_shootSpeedRatio) {{Class_2_ori_x + (2 * (rand() % 2) - 1) * (rand() % Class_2_ori_x_range), Class_2_ori_y + (2 * rand() % 2 - 1) * (rand() % Class_2_ori_y_range)}\
,_Wid,_Hei\
,_Buffer,_Font_Size,_enemy_name\
,Class_2_p,0.1\
,{100,100,GRAPH_WIDTH - 100,GRAPH_HEIGHT - 200}\
,_bullet_type,_shootSpeedRatio}


enemyContainer enemyVctorList[] = {
	//初始点, 宽度, 高度, 血量, 字号，显示的文本, 比例, 动量, 运动范围
	// #5 5
	{{GRAPH_WIDTH / 2,max(GRAPH_HEIGHT / 2 - 100,0) },160,40,BufferClass_1,E_FontClass_1,_T("Programmer"),Class_1_p,0.1,{400,200,GRAPH_WIDTH - 400,GRAPH_HEIGHT - 200},four_bullet,shootSpeedRatio_class1},
	Class2_enemy(_T("Programmer"),E_FontClass_2,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Programmer"),E_FontClass_2,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("殷JS"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("叶NG"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #2 7
	Class1_enemy(_T("Framework"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("殷JS"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #2 9
	Class1_enemy(_T("Adaptor"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("叶NG"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #5 14
	Class1_enemy(_T("Planner"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("陈ZQ"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("成SY"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("叶NG"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("殷JS"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	//  #7 21 $
	Class1_enemy(_T("KeyWord"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("char"),E_FontClass_3,BufferClass_3,80,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned char"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("short"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned short"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("int"),E_FontClass_3,BufferClass_3,80,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned int"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),

	// #8 29 $
	Class2_enemy(_T("long"),E_FontClass_3,BufferClass_3,80,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned long"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("float"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned float"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("double"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned double"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("long double"),E_FontClass_3,BufferClass_3,140,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("unsigned long double"),E_FontClass_3,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),

	// #7 36 $
	Class2_enemy(_T("Public"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Private"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Protected"),E_FontClass_3,BufferClass_3,100,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Abstraction"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Inheritance"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Capsulation"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Polymorphism"),E_FontClass_3,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),

	// #3 39
	Class1_enemy(_T("Illustrator"), E_FontClass_1, BufferClass_1, 180, 40, six_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("利JW"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("陈ZQ"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #4 43
	Class1_enemy(_T("Sound Effect"), E_FontClass_1, BufferClass_1, 180, 40, double_four_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("成SY"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("陈ZQ"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("余MY"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #8 51 $
	Class1_enemy(_T("Musician"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Marina"),E_FontClass_2,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Emi Evans"),E_FontClass_2,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("J'Nique Nicole"),E_FontClass_2,BufferClass_3,160,40,one_bullet,shootSpeedRatio_class1),
	Class1_enemy(_T("Music"), E_FontClass_1, BufferClass_1, 160, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Significance"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Amusement Park"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("A Beautiful Song"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),

	// #9 60 $
	Class2_enemy(_T("Blissful Death"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Vague Hope"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Weight of the World"),E_FontClass_2,BufferClass_3,210,40,one_bullet,shootSpeedRatio_class1),
	Class1_enemy(_T("Recommended"), E_FontClass_1, BufferClass_1, 180, 40, six_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("Song of the Ancients"),E_FontClass_2,BufferClass_3,220,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("City Ruins"),E_FontClass_2,BufferClass_3,180,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Memories of Dust"),E_FontClass_2,BufferClass_3,210,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Kainé / Salvation"),E_FontClass_2,BufferClass_3,210,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("This silence is mine"),E_FontClass_2,BufferClass_3,220,40,one_bullet,shootSpeedRatio_class1),

	// #3 63 
	Class1_enemy(_T("Visual Effect"), E_FontClass_1, BufferClass_1, 200, 40, double_four_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("殷JS"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("陈ZQ"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #3 66
	Class1_enemy(_T("Voice Actor"), E_FontClass_1, BufferClass_1, 180, 40, six_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("成SY"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("叶NG"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),

	// #25 91
	Class1_enemy(_T("File"), E_FontClass_1, BufferClass_1, 120, 40, six_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("File"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("王Z"),C_FontClass_1,BufferClass_3,C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("File"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("张BY"),C_FontClass_1,BufferClass_3, C_Font_wid,40,one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("File"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("File"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("File"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),

	Class1_enemy(_T("Tester"), E_FontClass_1, BufferClass_1, 140, 40, six_bullet, shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("陈H"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("利JW"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),

	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, four_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("蔡XK"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("向LX"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("曹XC"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("余MY"), C_FontClass_1, BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class1),
	Class2_enemy(_T("Tester"), E_FontClass_3, BufferClass_3, 100, 40, one_bullet,shootSpeedRatio_class1),

	// #12 103
	Class1_enemy(_T("Dev.'s words"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, four_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("We're here."), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, four_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Come on!"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, four_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Don't give up!"), E_FontClass_2, buffer_ratio * BufferClass_3, 210, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("God bless."), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Keep going!"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Work hard!"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Stay young!"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Never old!"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("We're the same."), E_FontClass_2, buffer_ratio * BufferClass_3, 210, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Be yourself!"), E_FontClass_2, buffer_ratio * BufferClass_3, 200, 40, one_bullet, 0.6 * shootSpeedRatio_class2),
	Class2_enemy(_T("Keep dreaming!"), E_FontClass_2, buffer_ratio * BufferClass_3, 200, 40, one_bullet, 0.6 * shootSpeedRatio_class2),

	// #11 114
	Class1_enemy(_T("Appreciation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, four_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("Nier：Automata"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, four_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("横尾太郎"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid + 10, 40, four_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("岡部啓一"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid + 10, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("Yuya Nagai"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("YoRHa"), E_FontClass_2, buffer_ratio * BufferClass_3, 120, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("Square Enix"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("PlatinumGames"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("A2"), E_FontClass_2, buffer_ratio * BufferClass_3, 40, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("2B"), E_FontClass_2, buffer_ratio * BufferClass_3, 40, 40, one_bullet, 0.7 * shootSpeedRatio_class2),
	Class2_enemy(_T("9S"), E_FontClass_2, buffer_ratio * BufferClass_3, 40, 40, one_bullet, 0.7 * shootSpeedRatio_class2),

	// #11 125
	Class1_enemy(_T("Appreciation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, four_bullet,0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("James Maxwell"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, six_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Nikola Tesla"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, six_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Alan Turing"), E_FontClass_2, buffer_ratio * BufferClass_3, 150, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("John von Neumann"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Dennis Ritchie"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Kenneth Thompson"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Bjarne Stroustrup"), E_FontClass_2, buffer_ratio * BufferClass_3, 190, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Alexey Pazhitnov"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("Bill Gates"), E_FontClass_2, buffer_ratio * BufferClass_3, 150, 40, one_bullet, 0.8 * shootSpeedRatio_class2),
	Class2_enemy(_T("BangBangTang"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.8 * shootSpeedRatio_class2),

	// #11 136
	Class1_enemy(_T("Appreciation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, six_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Stackoverflow"), E_FontClass_2, buffer_ratio * BufferClass_3, 180, 40, six_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Github"), E_FontClass_2, buffer_ratio * BufferClass_3, 120, 40, six_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("CSDN"), E_FontClass_2, buffer_ratio * BufferClass_3, 120, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Google"), E_FontClass_2, buffer_ratio * BufferClass_3, 120, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Baidu"), E_FontClass_2, buffer_ratio * BufferClass_3, 120, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("toSound.com"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Bilibili"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Wikipedia"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Stream"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet, 0.9 * shootSpeedRatio_class2),
	Class2_enemy(_T("Youtube"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet, 0.9 * shootSpeedRatio_class2),

	// #11 147
	Class1_enemy(_T("Appreciation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, double_four_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("C++"), E_FontClass_2, buffer_ratio * BufferClass_3, 100, 40, double_four_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("Photoshop"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, six_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("Netease"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Visual Studio"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("QQ music"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("VS code"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Adobe Premiere"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("WPS Office"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Microsoft"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("EasyX"), E_FontClass_2, buffer_ratio * BufferClass_3, 140, 40, one_bullet,shootSpeedRatio_class2),

	// #11 158
	Class1_enemy(_T("Appreciation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, double_six_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("Kato megumi"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, double_six_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("Aki Tomoya"), E_FontClass_2, buffer_ratio * BufferClass_3, 160, 40, six_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("Eriri Spencer Sawamura"), E_FontClass_2, buffer_ratio * BufferClass_3, 250, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Kasumigaoka Utaha"), E_FontClass_2, buffer_ratio * BufferClass_3, 200, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Hyodo Michiru"), E_FontClass_2, buffer_ratio * BufferClass_3, 170, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("Hashima Izumi"), E_FontClass_2, buffer_ratio * BufferClass_3, 170, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("blessing software"), E_FontClass_2, buffer_ratio * BufferClass_3, 200, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("深崎暮人"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid + 10, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("丸户史明"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid + 10, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("叶 巡璃"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),


	// #13 171
	Class1_enemy(_T("G7: Salvation"), E_FontClass_1, buffer_ratio * BufferClass_1, 200, 40, double_six_bullet, shootSpeedRatio_class2),
	Class2_enemy(_T("殷JS"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("叶NG"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("陈ZQ"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("成SY"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("利JW"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("余MY"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("张BY"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("王Z"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("陈H"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("向LX"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("曹XC"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2),
	Class2_enemy(_T("蔡XK"), C_FontClass_1, buffer_ratio * BufferClass_3, C_Font_wid, 40, one_bullet,shootSpeedRatio_class2)


};