#pragma once
#include <easyx.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

class ShowingImage {
private:
	float _ratio;		// ͼƬ�������
	int _img_Height;	// ͼƬ������߶�
	int _img_Width;		// ͼƬ��������
	int _image_pos_x;	// ͼƬ���Ͻ�x
	int _image_pos_y;	// ͼƬ���Ͻ�y
	IMAGE _img;			// ͼƬָ��

	// ����ͼ�����
	int _clear_unit;
	int _clear_x_time;
	int _clear_y_time;
	int _sleep_time_show;
	int _sleep_time_clear;
	static int count;

	vector<int> rand_value;

public:
	ShowingImage(const float ratio, const int img_Height, const int image_pos_x, const int image_pos_y, int clear_unit, const IMAGE img);
	ShowingImage() {};
	void inti_image() const;
	void clear_image(bool isend) const;
};