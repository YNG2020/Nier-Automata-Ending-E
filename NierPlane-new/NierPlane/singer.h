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
	float _ratio;		// 图片拉伸比例
	int _img_Height;	// 图片的拉伸高度
	int _img_Width;		// 图片的拉伸宽度
	int _image_pos_x;	// 图片左上角x
	int _image_pos_y;	// 图片右上角y
	IMAGE _img;			// 图片指针

	// 擦除图像相关
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