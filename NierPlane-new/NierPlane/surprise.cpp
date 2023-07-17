#include "surprise.h"

void showTitle();
void setTitleFontStyle();
void outTitle(int x, int y, const wchar_t*, COLORREF, COLORREF);

void surprise()
{
	SetWorkingImage();
	//initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);		// 设置画布大小, 如果只运行surprise，不要注释该行
	setbkcolor(BACKGROUND_COLOR);
	cleardevice(); // 初始化画布后先清除画面, 避免分配的内存未清空

	Sleep(1000);

	music.open_music(_T("Weight_of_the_World.mp3"));
	music.play_music();

	// 显示标题, 延时11s(为卡音乐的点)
	showTitle();
	
	// 小飞机主程序
	nierPlane::gameMain();
	
	music.pause_music();
	music.quit_music();
	
	Sleep(1000);
}

/// <summary>
/// 该函数执行11000ms
/// </summary>
void showTitle() {


	COLORREF color;

	clock_t onStageTime = clock();

	const wchar_t* title1 = _T("G7: Salvation");
	const wchar_t* title2 = _T("the  [E]nd  of  Dev.  Team");

	// 设置标题字体样式
	LOGFONT f;
	gettextstyle(&f);					// 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
	f.lfWeight = FW_DONTCARE;			// 设置字符笔画粗细为最细
	settextstyle(&f);					// 设置字体样式
	settextstyle(48, 0, _T("Calibri"));
	//setTitleFontStyle();

	// 睡眠至距离onStageTime 1000ms
	while (1) {
		if (clock() - onStageTime > 1000) break;
		Sleep(10);
	}
	// 标题淡入
	outTitle((GRAPH_WIDTH - textwidth(title1)) / 2, (GRAPH_HEIGHT - textheight(title1)) / 2 - 40, title1, BACKGROUND_COLOR, WHITE);

	settextstyle(32, 0, _T("Calibri"));

	// 睡眠至距离onStageTime 4100ms
	while (1) {
		if (clock() - onStageTime > 4100) break;
		Sleep(10);
	}
	//标题淡入
	outTitle((GRAPH_WIDTH - textwidth(title2)) / 2, (GRAPH_HEIGHT - textheight(title2)) / 2, title2, BACKGROUND_COLOR, WHITE);

	Sleep(3000);
	// 淡出效果
	for (int i = 255; i >= 0; i--)
	{
		mycleardevice(0x01);
		Sleep(4);
	}

	while (1) {
		if (clock() - onStageTime > 11000) break;
		Sleep(10);
	}
}
void setTitleFontStyle() {
	LOGFONT f;
	gettextstyle(&f);					// 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
	f.lfWeight = FW_DONTCARE;			// 设置字符笔画粗细为最细
	settextstyle(&f);						// 设置字体样式
}
void outTitle(int x,int y,const wchar_t* title, COLORREF startColor, COLORREF endColor){
	int startColorR = GetRValue(startColor);
	int startColorG = GetGValue(startColor);
	int startColorB = GetBValue(startColor);

	double stepR = (GetRValue(endColor) - GetRValue(startColor))/256.0;
	double stepG = (GetGValue(endColor) - GetGValue(startColor))/256.0;
	double stepB = (GetBValue(endColor) - GetBValue(startColor))/256.0;
	
	for (int i = 0; i <= 254; i++)
	{
		settextcolor(RGB(startColorR + (int)(stepR * i), startColorG + (int)(stepG * i), startColorB + (int)(stepB * i)));
		outtextxy(x, y, title);
		Sleep(4);
	}
	settextcolor(RGB(min(0xff,startColorR + (int)(stepR * 255)), min(0xff,startColorG + (int)(stepG * 255)), min(0xff,startColorB + (int)(stepB * 255))));
	outtextxy(x, y, title);
}
