#pragma once
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>
#include <math.h>
#include <thread>
#include <iostream>
#include "MyMusic.h"
#include "common.h"
using namespace std;

// 引用 Windows Multimedia API
#pragma comment(lib,"winmm.lib")

void starting();
void running();

/**
* @class <Particle> [starting.h]
* @brief 管理萤光粒子的类
*/
class Particle
{
public:
	Particle();
	static void show_particle(DWORD* imgBuffer, IMAGE* img, const int& win_wid, const int& win_hei, Particle* particles);
	static const int NUM_PARTICLE = 100;		// 总粒子个数
private:
	float ori_x, ori_y;		// 原始坐标
	float cur_x, cur_y;		// 当前坐标
	float vX, vY;			// 粒子速度
	int XAm;				// 粒子X方向移动幅度
	int YAm;				// 粒子X方向移动幅度
	float blink_frequency;	// 粒子闪烁频率
	float blink_count;		// 闪烁计数，用于控制粒子闪烁
	int border;				// 用于控制光晕半径,同时也用于控制亮度闪烁
	int show_frequency;		// 用于控制粒子出现频率
	int show_count;			// 出现计数，用于控制粒子出现
	int particle_light_offset;		// 粒子亮度随机偏移

	static const int XAm_range = 2;		// 粒子x方向初始化速度范围
	static const int XAm_min = -2;		// 粒子x方向初始化速度最小值

	static const int YAm_range = 3;		// 粒子y方向初始化速度范围
	static const int YAm_min = 0;		// 粒子y方向初始化速度最小值

	static const int border_range = 15;	// 粒子大光晕初始半径
	static const int small_border_range = 5;	// 粒子小光晕初始半径
	static const int border_min = 1;	// 粒子半径最小值

	static const float blink_frequency_max;	// 粒子闪烁频率最大值
	static const float blink_frequency_min;	// 粒子闪烁频率最小值
	static const int blink_frequency_level = 20;	// 粒子闪烁频率分级

	static const int show_frequency_min = 8;	// 粒子出现频率最小值
	static const int show_frequency_range = 15;	// 粒子出现频率最大值

	static const int Vx_max = 7;	// 粒子x方向最大速度
	static const int Vy_max = 3;	// 粒子y方向最大速度
	static const int Vx_min = -2;	// 粒子x方向最小速度
	static const int Vy_min = -3;	// 粒子y方向最小速度

};

/**
* @class <RandBlock> [starting.h]
* @brief 管理随机掩块的类
*/
class RandBlock
{
public:
	RandBlock();
	static void show_randblock(RandBlock* randblocks);
	static const int NUM_ALL_RANDBLOCK = 100;	// 总掩块个数
private:
	int block_left;		// 掩块的左边界
	int block_top;		// 掩块的上边界
	int width;			// 掩块的宽度
	int height;			// 掩块的高度
	double ratio;		// 掩块的黑白比例，先黑后白
	int blink_period;	// 掩块闪烁频率
	int blink_count;	// 闪烁计数，用于控制掩块闪烁

	static int Mosaic_left;			// 掩块区域左边界
	static int Mosaic_right;		// 掩块区域右边界
	static int Mosaic_top;			// 掩块区域上边界
	static int Mosaic_bottom;		// 掩块区域下边界

	static int Mosaic_width;		// 掩块区域宽度
	static int Mosaic_height;		// 掩块区域高度

	static const int block_wid_range = 150;		// 掩块宽度范围
	static const int block_wid_min = 10;		// 掩块宽度最小值

	static const int block_hei_range = 8;		// 掩块高度范围
	static const int block_hei_min = 5;			// 掩块高度最小值

	static const int block_blink_period_min = 1;	// 掩块闪烁周期最小值
	static const int block_blink_period_range = 3;	// 掩块闪烁周期范围

	static int num_showing_block;		// 当前显示掩块数目
	static int renew_block_count;		// 掩块更新计数
	static const int renew_block_period = 4;	// 掩块更新周期

	static vector<int> rand_index;		// 掩块随机编号
};

/**
* @class <Menu> [starting.h]
* @brief 管理菜单的类
*/
class Menu
{
public:
	Menu(const TCHAR* text, int text_y);
	Menu() {};
	static void transfer_interface(Menu* menu, const int& win_wid, const int& win_hei, char ch);
	void text_transfer_in();
	void text_transfer_out();
	void underline_transfer_in();
	void underline_transfer_out();

	void show_text(const int& win_wid, const int& win_hei) const;
	void show_snowflake() const;
	void show_underline() const;

	int rand_len_gen(int count_step) const;
	int rand_start_x_gen(int count_step) const;
	int offset_gen(int count_step, int init_offset) const;
	void line_sty_gen() const;

	static bool JUMP_FLAG;		// 菜单跳跃标志（不同级的跳跃）

private:
	static int font_height;		// 菜单文字高度（大小）
	static int show_menu_count;	// 菜单显示文字索引
	int text_x;			// 菜单文字原始x坐标
	int text_y;			// 菜单文字原始y坐标
	int line_rx;		// 菜单下划线右端x坐标
	int line_lx;		// 菜单下划线左端x坐标
	const TCHAR* text;	// 菜单文字
	TCHAR cur_text[50] = { '\0' };	// 菜单当前输出文字（特效用）

	int cur_char_index;	// 菜单当前输出文字索引（特效用）
	int cur_text_x;		// 菜单当前输出文字x坐标（特效用）
	int num_of_char;	// 菜单文字数（特效用）

	int text_loop_count;		// 菜单文字特效周期计数（特效用）
	int underline_loop_count;	// 菜单下划线特效周期计数（特效用）
	int tot_loop;		// 菜单特效总周期（特效用）
};

/**
* @class <Gear> [starting.h]
* @brief 管理齿轮的类
*/
class Gear {
private:
	float ratio;	// 缩放比例
	float exradius;	// 齿轮半径

	float gear_base_x;	// 齿轮中心x坐标
	float gear_base_y;	// 齿轮中心y坐标

	float gear_tooth_upleft_x;	// 齿牙左上x坐标
	float gear_tooth_upleft_y;	// 齿牙左上y坐标
	float gear_tooth_upright_x;	// 齿牙右上x坐标
	float gear_tooth_upright_y;	// 齿牙右上y坐标
	float gear_tooth_downleft_x;// 齿牙左下x坐标
	float gear_tooth_downleft_y;// 齿牙左下y坐标
	float gear_tooth_downright_x;// 齿牙右下x坐标
	float gear_tooth_downright_y;// 齿牙右下y坐标

	float gear_heart_radius1;	// 齿心半径1

	float gear_axis_in_x;	// 齿轴内端点x坐标
	float gear_axis_in_y;	// 齿轴内端点y坐标
	float gear_axis_out_x;	// 齿轴外端点x坐标
	float gear_axis_out_y;	// 齿轴外端点y坐标
	float gear_axis_width;	// 齿轴宽度

	float gear_rotate_v;	// 转速
public:
	void show_gear() const;
	Gear(float ori_point_x, float ori_point_y, float ratio = 0.9f, float gear_rotate_v = 3.1415926f / 60);
};