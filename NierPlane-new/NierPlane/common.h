#pragma once
#include <graphics.h>
#include <math.h>
#include <mutex>
#include <thread>

// 窗口大小, 全局共享, 所有锚定位置的函数都需以此大小为参考
#define GRAPH_WIDTH 1520
#define GRAPH_HEIGHT 830

#define MainLoopTime 30

// 背景颜色
#define BACKGROUND_COLOR (RGB(18, 16, 12))


#define draw_Sleep 10


static std::mutex drawMtx;

//control_workStatus 0 留空,待后续使用
//control_workStatus 1 是否暂停
static bool control_workStatus[2] = { false, false };

static bool graph_isDraw = false;

template<class T>
static T clamp(T x, T min, T max) {
	if (x > max) {
		return max;
	}
	if (x < min) {
		return min;
	}
	return x;
}

static void myputimage(int x, int y, IMAGE* img, float alpha = 1, int type = 0) {
	IMAGE* workingImg = GetWorkingImage();
	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);
	DWORD* imgBuffer = GetImageBuffer(img);


	int imgWidth = img->getwidth();
	int imgHeight = img->getheight();

	int Height = imgHeight;
	int Width = imgWidth;
	int offsetX = 0;
	int offsetY = 0;
	// 边缘处理
	if (x < 0) {
		offsetX = -x;
		imgWidth += x;
		x = 0;
	}
	else if (x + imgWidth > bkWidth) {
		imgWidth = bkWidth - x;
	}
	if (y < 0) {
		offsetY = -y;
		imgHeight += y;
		y = 0;
	}
	else if (y + imgHeight > bkHeight) {
		imgHeight = bkHeight - y;
	}
	BYTE* sp, * dp;

	// 按位移入显示缓存区
	for (int i = 0; i < imgHeight; i++) {
		// 源指针
		sp = (BYTE*)(imgBuffer + ((i + offsetY) * Width) + offsetX);
		// 目标指针
		dp = (BYTE*)(bkBuffer + ((y + i) * bkWidth + x));
		for (int j = 0; j < imgWidth; j++) {
			*(dp + 0) += *(sp + 0);
			if (*(dp + 0) < *(sp + 0))*(dp + 0) = 0xff;
			*(dp + 1) += *(sp + 1);
			if (*(dp + 1) < *(sp + 1))*(dp + 1) = 0xff;
			*(dp + 2) += *(sp + 2);
			if (*(dp + 2) < *(sp + 2))*(dp + 2) = 0xff;
			sp += 4;
			dp += 4;
		}
	}

}

static void myputimage2(int x, int y, IMAGE* img, float alpha = 1, int type = 0) {
	IMAGE* workingImg = GetWorkingImage();
	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);
	DWORD* imgBuffer = GetImageBuffer(img);


	int imgWidth = img->getwidth();
	int imgHeight = img->getheight();

	int Height = imgHeight;
	int Width = imgWidth;
	int offsetX = 0;
	int offsetY = 0;
	// 边缘处理
	if (x < 0) {
		offsetX = -x;
		imgWidth += x;
		x = 0;
	}
	else if (x + imgWidth > bkWidth) {
		imgWidth = bkWidth - x;
	}
	if (y < 0) {
		offsetY = -y;
		imgHeight += y;
		y = 0;
	}
	else if (y + imgHeight > bkHeight) {
		imgHeight = bkHeight - y;
	}
	BYTE* sp, * dp;

	// 按位移入显示缓存区
	for (int i = 0; i < imgHeight; i++) {
		// 源指针
		sp = (BYTE*)(imgBuffer + ((i + offsetY) * Width) + offsetX);
		// 目标指针
		dp = (BYTE*)(bkBuffer + ((y + i) * bkWidth + x));
		for (int j = 0; j < imgWidth; j++) {
			if (*(dp + 0) < *(sp + 0))
				*(dp + 0) = *(sp + 0);
			if (*(dp + 1) < *(sp + 1))
				*(dp + 1) = *(sp + 1);
			if (*(dp + 2) < *(sp + 2))
				*(dp + 2) = *(sp + 2);
			sp += 4;
			dp += 4;
		}
	}

}

static void mycleardevice(BYTE stepColor = 0x10) {
	IMAGE* workingImg = GetWorkingImage();
	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	COLORREF bkColor = getbkcolor();
	int r = GetRValue(bkColor);
	int g = GetGValue(bkColor);
	int b = GetBValue(bkColor);

	DWORD* bkBuffer = GetImageBuffer(workingImg);

	BYTE * dp = (BYTE*) bkBuffer;

	// 按位移入显示缓存区
	for (int i = 0; i < bkHeight; i++) {
		for (int j = 0; j < bkWidth; j++) {
			if (b > (*(dp + 0) - stepColor) || ((*(dp + 0)) < (*(dp + 0) - 0x11)))*(dp + 0) = b;
			else *(dp + 0) -= stepColor;
			if (g > (*(dp + 1) - stepColor) || ((*(dp + 1)) < (*(dp + 1) - 0x11)))*(dp + 1) = g;
			else *(dp + 1) -= stepColor;
			if (r > (*(dp + 2) - stepColor) || ((*(dp + 2)) < (*(dp + 2) - 0x11)))*(dp + 2) = r;
			else *(dp + 2) -= stepColor;
			dp += 4;
		}
	}
}

static void myclearrectangle(int left, int top, int right, int down) {
	if (left > right || top > down)return;
	IMAGE* workingImg = GetWorkingImage();
	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);

	COLORREF fillColor = getfillcolor();

	int r = GetRValue(fillColor), g = GetGValue(fillColor), b = GetBValue(fillColor);

	int imgWidth = right - left;
	int imgHeight = down - top;

	int Height = imgHeight;
	int Width = imgWidth;
	int offsetX = 0;
	int offsetY = 0;
	// 边缘处理
	if (left < 0) {
		offsetX = -left;
		imgWidth += left;
		left = 0;
	}
	else if (left + imgWidth > bkWidth) {
		imgWidth = bkWidth - left;
	}
	if (top < 0) {
		offsetY = -top;
		imgHeight += top;
		top = 0;
	}
	else if (top + imgHeight > bkHeight) {
		imgHeight = bkHeight - top;
	}
	BYTE* dp;

	// 按位移入显示缓存区
	for (int i = 0; i < imgHeight; i++) {
		// 目标指针
		dp = (BYTE*)(bkBuffer + ((top + i) * bkWidth + left));
		for (int j = 0; j < imgWidth; j++) {
			if (*(dp + 0) > b)*(dp + 0) = b;
			if (*(dp + 1) > g)*(dp + 1) = g;
			if (*(dp + 2) > r)*(dp + 2) = r;
			dp += 4;
		}
	}
}

static void mysolidrectangle(int left, int top, int right, int down) {
	if (left > right || top > down)return;
	IMAGE* workingImg = GetWorkingImage();
	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);

	COLORREF fillColor = getfillcolor();

	int r = GetRValue(fillColor), g = GetGValue(fillColor), b = GetBValue(fillColor);

	int imgWidth = right - left;
	int imgHeight = down - top;

	int Height = imgHeight;
	int Width = imgWidth;
	int offsetX = 0;
	int offsetY = 0;
	// 边缘处理
	if (left < 0) {
		offsetX = -left;
		imgWidth += left;
		left = 0;
	}
	else if (left + imgWidth > bkWidth) {
		imgWidth = bkWidth - left;
	}
	if (top < 0) {
		offsetY = -top;
		imgHeight += top;
		top = 0;
	}
	else if (top + imgHeight > bkHeight) {
		imgHeight = bkHeight - top;
	}
	BYTE* dp;

	// 按位移入显示缓存区
	for (int i = 0; i < imgHeight; i++) {
		// 目标指针
		dp = (BYTE*)(bkBuffer + ((top + i) * bkWidth + left));
		for (int j = 0; j < imgWidth; j++) {
			*(dp + 0) += b;
			if (*(dp + 0) < b)*(dp + 0) = 0xff;
			*(dp + 1) += g;
			if (*(dp + 1) < g)*(dp + 1) = 0xff;
			*(dp + 2) += r;
			if (*(dp + 2) < r)*(dp + 2) = 0xff;
			dp += 4;
		}
	}
}

static void mysolidcircle(int x, int y, int radius) {
	IMAGE* workingImg = GetWorkingImage();
	IMAGE* img = new IMAGE(2 * radius, 2 * radius);
	COLORREF fillColor = getfillcolor();
	x -= radius;
	y -= radius;
	SetWorkingImage(img);

	setfillcolor(BLACK);
	cleardevice();
	setfillcolor(fillColor);
	solidcircle(radius, radius, radius);
	SetWorkingImage(workingImg);

	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);
	DWORD* imgBuffer = GetImageBuffer(img);


	int imgWidth = img->getwidth();
	int imgHeight = img->getheight();

	int Height = imgHeight;
	int Width = imgWidth;
	int offsetX = 0;
	int offsetY = 0;
	// 边缘处理
	if (x < 0) {
		offsetX = -x;
		imgWidth += x;
		x = 0;
	}
	else if (x + imgWidth > bkWidth) {
		imgWidth = bkWidth - x;
	}
	if (y < 0) {
		offsetY = -y;
		imgHeight += y;
		y = 0;
	}
	else if (y + imgHeight > bkHeight) {
		imgHeight = bkHeight - y;
	}
	BYTE* sp, * dp;

	// 按位移入显示缓存区
	for (int i = 0; i < imgHeight; i++) {
		// 源指针
		sp = (BYTE*)(imgBuffer + ((i + offsetY) * Width) + offsetX);
		// 目标指针
		dp = (BYTE*)(bkBuffer + ((y + i) * bkWidth + x));
		for (int j = 0; j < imgWidth; j++) {
			*(dp + 0) = max(*(dp + 0), *(sp + 0));
			*(dp + 1) = max(*(dp + 1), *(sp + 1));
			*(dp + 2) = max(*(dp + 2), *(sp + 2));
			/*if (*(dp + 0) < *(sp + 0))*(dp + 0) = *(sp + 0);
			if (*(dp + 1) < *(sp + 1))*(dp + 1) = *(sp + 1);
			if (*(dp + 2) < *(sp + 2))*(dp + 2) = *(sp + 2);*/
			sp += 4;
			dp += 4;
		}
	}
	delete(img);
}
static void myline(int x, int y, int length) {
	if (length < 0)return;
	IMAGE* workingImg = GetWorkingImage();
	COLORREF lineColor = getlinecolor();

	int r = GetRValue(lineColor);
	int g = GetGValue(lineColor);
	int b = GetBValue(lineColor);

	int bkWidth;
	int bkHeight;
	if (workingImg == nullptr) {
		bkWidth = getwidth();
		bkHeight = getheight();
	}
	else
	{
		bkWidth = workingImg->getwidth();
		bkHeight = workingImg->getheight();
	}
	DWORD* bkBuffer = GetImageBuffer(workingImg);

	// 边缘处理
	if (x < 0) {
		x = 0;
	}
	else if (x + length > bkWidth) {
		length = bkWidth - x;
	}
	if (y < 0) {
		return;
	}
	else if (y > bkHeight) {
		return;
	}
	BYTE* dp = (BYTE*)(bkBuffer + x + y * bkWidth);

	// 按位移入显示缓存区
	for (int i = 0; i < length; i++) {
		*(dp + 0) += b;
		if (*(dp + 0) < b)*(dp + 0) = 0xff;
		*(dp + 1) += g;
		if (*(dp + 1) < g)*(dp + 1) = 0xff;
		*(dp + 2) += r;
		if (*(dp + 2) < r)*(dp + 2) = 0xff;
		/*if (*(dp + 0) < *(sp + 0))*(dp + 0) = *(sp + 0);
		if (*(dp + 1) < *(sp + 1))*(dp + 1) = *(sp + 1);
		if (*(dp + 2) < *(sp + 2))*(dp + 2) = *(sp + 2);*/
		dp += 4;
	}
}
static void Blur_step_weight_25(DWORD* pMem, int size, int width, int height)
{
	DWORD* buffer = (DWORD*)calloc(height * width, sizeof(DWORD));
	if (buffer == nullptr)return;
	int matrix[25] =
	{
		-2 * size - 2 * size * width,-1 * size - 2 * size * width,0 - 2 * size * width,1 * size - 2 * size * width,2 * size - 2 * size * width,
		-2 * size - 1 * size * width,-1 * size - 1 * size * width,0 - 1 * size * width,1 * size - 1 * size * width,2 * size - 1 * size * width,
		-2 * size,-1 * size,0,1 * size,2 * size,
		-2 * size + 1 * size * width,-1 * size + 1 * size * width,0 + 1 * size * width,1 * size + 1 * size * width,2 * size + 1 * size * width,
		-2 * size + 2 * size * width,-1 * size + 2 * size * width,0 + 2 * size * width,1 * size + 2 * size * width,2 * size + 2 * size * width
	};
	int weight[25] = {
		1,2,5,2,1,
		2,8,16,8,2,
		5,16,24,16,5,
		2,8,16,8,2,
		1,2,5,2,1
	};
#define allWeight 150//权重矩阵的总和
	for (int i = 2 * size * width + 2 * size; i < width * (height - 2 * size) - 2 * size; i++)
	{
		int r = 0, g = 0, b = 0;
		for (int j = 0; j < 25; j++) {
			r += GetRValue(pMem[i + matrix[j]]) * weight[j];
			g += GetGValue(pMem[i + matrix[j]]) * weight[j];
			b += GetBValue(pMem[i + matrix[j]]) * weight[j];
		}
		buffer[i] = RGB(min(r / allWeight, 0xff), min(g / allWeight, 0xff), min(b / allWeight, 0xff));
		/*pMem[i] = RGB(
			(GetRValue(pMem[i]) + GetRValue(pMem[i - width]) + GetRValue(pMem[i - 1]) + GetRValue(pMem[i + 1]) + GetRValue(pMem[i + width])) / 5,
			(GetGValue(pMem[i]) + GetGValue(pMem[i - width]) + GetGValue(pMem[i - 1]) + GetGValue(pMem[i + 1]) + GetGValue(pMem[i + width])) / 5,
			(GetBValue(pMem[i]) + GetBValue(pMem[i - width]) + GetBValue(pMem[i - 1]) + GetBValue(pMem[i + 1]) + GetBValue(pMem[i + width])) / 5);*/
	}

	memmove(pMem, buffer, sizeof(DWORD) * height * width);
	free(buffer);
}

static void Blur_step_weight_25_float(DWORD* pMem, int size, int width = GRAPH_WIDTH, int height = GRAPH_HEIGHT)
{
	DWORD* buffer = (DWORD*)calloc(height * width, sizeof(DWORD));
	if (buffer == nullptr)return;
	int matrix[25] =
	{
		-2 * size - 2 * size * width,-1 * size - 2 * size * width,0 - 2 * size * width,1 * size - 2 * size * width,2 * size - 2 * size * width,
		-2 * size - 1 * size * width,-1 * size - 1 * size * width,0 - 1 * size * width,1 * size - 1 * size * width,2 * size - 1 * size * width,
		-2 * size,-1 * size,0,1 * size,2 * size,
		-2 * size + 1 * size * width,-1 * size + 1 * size * width,0 + 1 * size * width,1 * size + 1 * size * width,2 * size + 1 * size * width,
		-2 * size + 2 * size * width,-1 * size + 2 * size * width,0 + 2 * size * width,1 * size + 2 * size * width,2 * size + 2 * size * width
	};
	float weight[25] = {
		1,2,5,2,1,
		2,8,16,8,2,
		5,16,24,16,5,
		2,8,16,8,2,
		1,2,5,2,1
	};
#define allWeight 150 //权重矩阵的总和
	float* rBuffer = (float*)calloc(height * width, sizeof(float));
	float* gBuffer = (float*)calloc(height * width, sizeof(float));
	float* bBuffer = (float*)calloc(height * width, sizeof(float));
	if (rBuffer == nullptr || gBuffer == nullptr || bBuffer == nullptr) { return; }
	COLORREF bkColor = getbkcolor();
	COLORREF color = pMem[1];
	float r, g, b;
	for (int i = 2 * size * width + 2 * size; i < width * (height - 2 * size) - 2 * size; i++) {
		if (pMem[i] != bkColor) {
			r = ((float)((int)GetRValue(pMem[i]))) / allWeight;
			g = ((float)((int)GetGValue(pMem[i]))) / allWeight;
			b = ((float)((int)GetBValue(pMem[i]))) / allWeight;
			for (int j = 0; j < 25; j++) {
				rBuffer[i + matrix[j]] += r * weight[j];
				gBuffer[i + matrix[j]] += g * weight[j];
				bBuffer[i + matrix[j]] += b * weight[j];//todo 
				buffer[i + matrix[j]] = RGB(
					min((int)rBuffer[i + matrix[j]], 0xff),
					min((int)gBuffer[i + matrix[j]], 0xff),
					min((int)bBuffer[i + matrix[j]], 0xff));
			}
		}
	}

	memmove(pMem, buffer, sizeof(DWORD) * height * width);
	/*for (int i = 0; i < width * height; i++) {
		pMem[i] = RGB((int)rBuffer[i], (int)gBuffer[i], (int)bBuffer[i]);
	}*/
	std::free(rBuffer);
	std::free(gBuffer);
	std::free(bBuffer);
	std::free(buffer);
}
