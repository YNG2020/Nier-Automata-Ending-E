#pragma once
#include "common.h"
struct dialogCircle
{
	dialogCircle(double _vX, RECT _moveRange, double _vR, double _maxR, double _minR) {
		moveRange = _moveRange;
		vX = abs(_vX);
		x = moveRange.left;
		y = moveRange.top;

		minR = _minR;
		maxR = _maxR;
		r = minR;
		vR = abs(_vR);
	}
	double x;
	double y;
	double vX = 0.5;
	double vY = 0;
	RECT moveRange = { 40,-25,45,-20 };
	double r;
	double vR = 0.4;
	int maxR;
	int minR;
	void drawCircle() {
		setlinestyle(SOLID_FILL, 2);
		setlinecolor(RGB(30, 30, 30));
		circle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(r));
		//circle(x, y, r+1);
		//circle(x, y, r+2);
		//circle(x, y, r-1);
		//circle(x, y, r-2);

	}
	void move() {
		if (vX != 0) {
			x += vX;
			if (x > moveRange.right || x < moveRange.left) {
				vY = -vX;
				vX = 0;
			}
		}
		else
		{
			y += vY;
			if (y > moveRange.bottom || y < moveRange.top) {
				vX = vY;
				vY = 0;
			}
		}
		r += vR;
		if (r<minR || r>maxR) {
			vR = -vR;
		}
	}
};
struct dialogText
{
	dialogText(int _textNum, wchar_t* _text, RECT _r = { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }) {
		textNum = _textNum;
		text = _text;
		textRect = _r;
	}
	wchar_t* text = nullptr;
	wchar_t nowOutput[50] = L"";
	int textNum;
	int textIndex = 0;
	int textStep = 0;
	RECT textRect;
	int addText() {
		if (textIndex >= textNum)return 1;
		if (textStep < 0) {
			textStep++;
			return 0;
		}
		textStep = 0;
		nowOutput[textIndex] = text[textIndex];
		textIndex++;
		return 0;
	}
	void darwText() {
		settextstyle(20, 0, _T("ËÎÌå"));
		drawtext(nowOutput, &textRect, DT_SINGLELINE | DT_END_ELLIPSIS);
		addText();
	}
};
struct dialogBox
{
#define DialogBoxHeight 180
	dialogBox() {
		dc1 = new dialogCircle(0.01, { 40,-20,42,-20 }, 0.15, 175, 165);
		dc2 = new dialogCircle(0, { 42,-20,42,-20 }, 0.20, 190, 185);
		dc3 = new dialogCircle(0, { GRAPH_WIDTH - 40,DialogBoxHeight + 20,GRAPH_WIDTH - 43,DialogBoxHeight + 20 }, 0.20, 175, 165);
		dc4 = new dialogCircle(0, { GRAPH_WIDTH - 42,DialogBoxHeight + 20,GRAPH_WIDTH - 42,DialogBoxHeight + 20 }, 0.20, 190, 185);

		p1 = { 310,155 };
		p2 = { 270,100 };
		p3 = { GRAPH_WIDTH - 310,DialogBoxHeight - 155 };
		p4 = { GRAPH_WIDTH - 270,DialogBoxHeight - 100 };

	}

	dialogCircle* dc1, * dc2, * dc3, * dc4;
	POINT p1, p2, p3, p4;
	double p_v = 0.5;
	double vX = 0;
	void movePoint() {
		double _vX = (double)((rand() % 100) / 50) - 1;
		vX = p_v * _vX + (1 - p_v) * vX;
		if (p1.x < 305) {
			vX = abs(vX);
		}
		else if (p1.x > 315) {
			vX = -abs(vX);
		}
		double vY = vX * 3 / 5;
		p1.x += static_cast<LONG>(vX);
		p2.x += static_cast<LONG>(vX);
		p3.x += static_cast<LONG>(vX);
		p4.x += static_cast<LONG>(vX);

		p1.y += static_cast<LONG>(vY);
		p2.y += static_cast<LONG>(vY);
		p3.y += static_cast<LONG>(vY);
		p4.y += static_cast<LONG>(vY);
	}
	void drawLine() {
		setlinestyle(SOLID_FILL, 2);
		setlinecolor(RGB(30, 30, 30));
		line(p1.x, p1.y, p1.x - 500, p1.y - 300);
		line(p2.x, p2.y, p2.x - 500, p2.y - 300);
		line(p3.x, p3.y, p3.x + 500, p3.y + 300);
		line(p4.x, p4.y, p4.x + 500, p4.y + 300);
		movePoint();
	}

	void drawDialogBox() {
		IMAGE* nowWorkingImg = GetWorkingImage();
		IMAGE* dialogBoxImg = new IMAGE(GRAPH_WIDTH, DialogBoxHeight);
		DWORD* imgBuffer = GetImageBuffer(dialogBoxImg);
		COLORREF bkColor = getbkcolor();
		COLORREF dialogBoxColor = RGB(10, 12, 10);
		SetWorkingImage(dialogBoxImg);
		setbkcolor(RGB(10, 12, 10));
		cleardevice();
		// »¨ÎÆ
		for (int j = 0; j < DialogBoxHeight; j++) {
			if (j % 8 == 0 || j % 8 == 4)continue;
			int k = 0;
			if (j % 4 == 2) {
				k = 1;
			}
			int iOffset = 0;
			if (j % 8 < 4) {
				iOffset = 4;
			}
			for (int i = 0; i < GRAPH_WIDTH - 4; i++) {
				if (k == 1) {
					if (i % 8 == 3 || i % 8 == 5) {
						imgBuffer[j * GRAPH_WIDTH + i + iOffset] = BGR(bkColor);
					}
				}
				if (i % 8 == 4) {
					imgBuffer[j * GRAPH_WIDTH + i + iOffset] = BGR(bkColor);
				}
			}
		}



		IMAGE* dialogBoxImg2 = new IMAGE(GRAPH_WIDTH, DialogBoxHeight);
		SetWorkingImage(dialogBoxImg2);

		dc1->move();
		dc2->move();
		dc1->drawCircle();
		dc2->drawCircle();
		dc3->move();
		dc4->move();
		dc3->drawCircle();
		dc4->drawCircle();
		drawLine();
		Blur_step_weight_25(GetImageBuffer(dialogBoxImg2), 1, GRAPH_WIDTH, DialogBoxHeight);
		//circle(40, -20, 170);
		//circle(40, -20, 180);
		SetWorkingImage(dialogBoxImg);
		myputimage(0, 0, dialogBoxImg2);
		SetWorkingImage(nowWorkingImg);
		myputimage(0, GRAPH_HEIGHT - DialogBoxHeight, dialogBoxImg);
		dialogBoxImg->~IMAGE();
		dialogBoxImg2->~IMAGE();
	}
};