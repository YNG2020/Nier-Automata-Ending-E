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

// ���� Windows Multimedia API
#pragma comment(lib,"winmm.lib")

void starting();
void running();

/**
* @class <Particle> [starting.h]
* @brief ����ө�����ӵ���
*/
class Particle
{
public:
	Particle();
	static void show_particle(DWORD* imgBuffer, IMAGE* img, const int& win_wid, const int& win_hei, Particle* particles);
	static const int NUM_PARTICLE = 100;		// �����Ӹ���
private:
	float ori_x, ori_y;		// ԭʼ����
	float cur_x, cur_y;		// ��ǰ����
	float vX, vY;			// �����ٶ�
	int XAm;				// ����X�����ƶ�����
	int YAm;				// ����X�����ƶ�����
	float blink_frequency;	// ������˸Ƶ��
	float blink_count;		// ��˸���������ڿ���������˸
	int border;				// ���ڿ��ƹ��ΰ뾶,ͬʱҲ���ڿ���������˸
	int show_frequency;		// ���ڿ������ӳ���Ƶ��
	int show_count;			// ���ּ��������ڿ������ӳ���
	int particle_light_offset;		// �����������ƫ��

	static const int XAm_range = 2;		// ����x�����ʼ���ٶȷ�Χ
	static const int XAm_min = -2;		// ����x�����ʼ���ٶ���Сֵ

	static const int YAm_range = 3;		// ����y�����ʼ���ٶȷ�Χ
	static const int YAm_min = 0;		// ����y�����ʼ���ٶ���Сֵ

	static const int border_range = 15;	// ���Ӵ���γ�ʼ�뾶
	static const int small_border_range = 5;	// ����С���γ�ʼ�뾶
	static const int border_min = 1;	// ���Ӱ뾶��Сֵ

	static const float blink_frequency_max;	// ������˸Ƶ�����ֵ
	static const float blink_frequency_min;	// ������˸Ƶ����Сֵ
	static const int blink_frequency_level = 20;	// ������˸Ƶ�ʷּ�

	static const int show_frequency_min = 8;	// ���ӳ���Ƶ����Сֵ
	static const int show_frequency_range = 15;	// ���ӳ���Ƶ�����ֵ

	static const int Vx_max = 7;	// ����x��������ٶ�
	static const int Vy_max = 3;	// ����y��������ٶ�
	static const int Vx_min = -2;	// ����x������С�ٶ�
	static const int Vy_min = -3;	// ����y������С�ٶ�

};

/**
* @class <RandBlock> [starting.h]
* @brief ��������ڿ����
*/
class RandBlock
{
public:
	RandBlock();
	static void show_randblock(RandBlock* randblocks);
	static const int NUM_ALL_RANDBLOCK = 100;	// ���ڿ����
private:
	int block_left;		// �ڿ����߽�
	int block_top;		// �ڿ���ϱ߽�
	int width;			// �ڿ�Ŀ��
	int height;			// �ڿ�ĸ߶�
	double ratio;		// �ڿ�ĺڰױ������Ⱥں��
	int blink_period;	// �ڿ���˸Ƶ��
	int blink_count;	// ��˸���������ڿ����ڿ���˸

	static int Mosaic_left;			// �ڿ�������߽�
	static int Mosaic_right;		// �ڿ������ұ߽�
	static int Mosaic_top;			// �ڿ������ϱ߽�
	static int Mosaic_bottom;		// �ڿ������±߽�

	static int Mosaic_width;		// �ڿ�������
	static int Mosaic_height;		// �ڿ�����߶�

	static const int block_wid_range = 150;		// �ڿ��ȷ�Χ
	static const int block_wid_min = 10;		// �ڿ�����Сֵ

	static const int block_hei_range = 8;		// �ڿ�߶ȷ�Χ
	static const int block_hei_min = 5;			// �ڿ�߶���Сֵ

	static const int block_blink_period_min = 1;	// �ڿ���˸������Сֵ
	static const int block_blink_period_range = 3;	// �ڿ���˸���ڷ�Χ

	static int num_showing_block;		// ��ǰ��ʾ�ڿ���Ŀ
	static int renew_block_count;		// �ڿ���¼���
	static const int renew_block_period = 4;	// �ڿ��������

	static vector<int> rand_index;		// �ڿ�������
};

/**
* @class <Menu> [starting.h]
* @brief ����˵�����
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

	static bool JUMP_FLAG;		// �˵���Ծ��־����ͬ������Ծ��

private:
	static int font_height;		// �˵����ָ߶ȣ���С��
	static int show_menu_count;	// �˵���ʾ��������
	int text_x;			// �˵�����ԭʼx����
	int text_y;			// �˵�����ԭʼy����
	int line_rx;		// �˵��»����Ҷ�x����
	int line_lx;		// �˵��»������x����
	const TCHAR* text;	// �˵�����
	TCHAR cur_text[50] = { '\0' };	// �˵���ǰ������֣���Ч�ã�

	int cur_char_index;	// �˵���ǰ���������������Ч�ã�
	int cur_text_x;		// �˵���ǰ�������x���꣨��Ч�ã�
	int num_of_char;	// �˵�����������Ч�ã�

	int text_loop_count;		// �˵�������Ч���ڼ�������Ч�ã�
	int underline_loop_count;	// �˵��»�����Ч���ڼ�������Ч�ã�
	int tot_loop;		// �˵���Ч�����ڣ���Ч�ã�
};

/**
* @class <Gear> [starting.h]
* @brief ������ֵ���
*/
class Gear {
private:
	float ratio;	// ���ű���
	float exradius;	// ���ְ뾶

	float gear_base_x;	// ��������x����
	float gear_base_y;	// ��������y����

	float gear_tooth_upleft_x;	// ��������x����
	float gear_tooth_upleft_y;	// ��������y����
	float gear_tooth_upright_x;	// ��������x����
	float gear_tooth_upright_y;	// ��������y����
	float gear_tooth_downleft_x;// ��������x����
	float gear_tooth_downleft_y;// ��������y����
	float gear_tooth_downright_x;// ��������x����
	float gear_tooth_downright_y;// ��������y����

	float gear_heart_radius1;	// ���İ뾶1

	float gear_axis_in_x;	// �����ڶ˵�x����
	float gear_axis_in_y;	// �����ڶ˵�y����
	float gear_axis_out_x;	// ������˵�x����
	float gear_axis_out_y;	// ������˵�y����
	float gear_axis_width;	// ������

	float gear_rotate_v;	// ת��
public:
	void show_gear() const;
	Gear(float ori_point_x, float ori_point_y, float ratio = 0.9f, float gear_rotate_v = 3.1415926f / 60);
};