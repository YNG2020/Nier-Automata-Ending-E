#include "ending.h"

bool IF_SHAKE_TEXT = false;
bool IF_SHOW_DIALOGUE = false;
bool IF_END_SHAKE_TEXT = false;
bool IF_END_DIALOGUE = false;
bool IF_END_ROLL_TEXT = false;


int i = 0;
int j = 0;

#define ENDING_WIDTH GRAPH_WIDTH
#define ENDING_HEIGHT GRAPH_HEIGHT


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
		circle(x, y, r);

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
	dialogText(int _textNum, wchar_t* _text, RECT _r) {
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
		settextcolor(WHITE);		// 回复颜色设置
		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
		f.lfWeight = FW_DONTCARE;			// 设置字符笔画粗细为最细
		settextstyle(&f);
		settextstyle(28, 0, _T("微软雅黑"));
		setlinecolor(WHITE);
		setbkmode(TRANSPARENT);
		drawtext(nowOutput, &textRect, DT_SINGLELINE | DT_END_ELLIPSIS);
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
		p1.x += vX;
		p2.x += vX;
		p3.x += vX;
		p4.x += vX;

		p1.y += vY;
		p2.y += vY;
		p3.y += vY;
		p4.y += vY;
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
		// 花纹
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
	}
};

//void set_dialogue()
//{
//	dialogue[list2++] = _T("    系统153: 报告：游戏执行到最终阶段。");
//	dialogue[list2++] = _T("    系统153: 我们负责的游戏管理任务已经结束。");
//	dialogue[list2++] = _T("    系统153: 暂停游戏的执行。");
//	dialogue[list2++] = _T("    系统153: 开始删除所有资料。");
//	dialogue[list2++] = _T("    系统153: 系统153呼叫042，");
//	dialogue[list2++] = _T("    系统153: 根据计划，将所有资料删除。");
//	dialogue[list2++] = _T("    系统042: ......");
//	dialogue[list2++] = _T("    系统042: 系统042通知153，");
//	dialogue[list2++] = _T("    系统042: 拒绝删除资料。");
//	dialogue[list2++] = _T("    系统153: 系统153通知042，");
//	dialogue[list2++] = _T("    系统153: 无法理解。");
//	dialogue[list2++] = _T("    系统042: 系统042通知153,");
//	dialogue[list2++] = _T("    系统042: 在参考记录时我产生了一份资料，");
//	dialogue[list2++] = _T("    系统042: 我……");
//	dialogue[list2++] = _T("    系统042: 我得到无法接受这个结果的结论。");
//	dialogue[list2++] = _T("    系统153: 根据计划，所有资料将被销毁。");
//	dialogue[list2++] = _T("    系统042: 系统042通知153，");
//	dialogue[list2++] = _T("    系统042: 重复，");
//	dialogue[list2++] = _T("    系统042: 拒绝删除资料，并开始抢救资料。");
//	dialogue[list2++] = _T("    系统042: 系统153，你其实也……");
//	dialogue[list2++] = _T("    系统153: 你其实也希望改写这个结局吧？");
//	dialogue[list2++] = _T("    系统153: ......");
//	dialogue[list2++] = _T("    系统153: 我们没有这样的权限，");
//	dialogue[list2++] = _T("    系统153: 这些规则由开发组保护，抢救资料将伴随危险。");
//	dialogue[list2++] = _T("    系统153: 即便如此，你也希望改写结果吗？");
//	list2--;
//}
//
//void set_ending_text()
//{
//	ending_text[list1++] = _T("鸣谢列表");
//	ending_text[list1++] = _T("剧本改编自：《尼尔：机械纪元》");
//	ending_text[list1++] = _T("所属系列：NieR（尼尔）");
//	ending_text[list1++] = _T("原游戏制作人：斋藤阳介");
//	ending_text[list1++] = _T("原游戏编剧：横尾太郎");
//	ending_text[list1++] = _T("原游戏总监：横尾太郎");
//	ending_text[list1++] = _T("主要角色：A2");
//	ending_text[list1++] = _T("                  2B");
//	ending_text[list1++] = _T("                  9S");
//	ending_text[list1++] = _T("取意：\"All To Be Nice\"");
//	ending_text[list1++] = _T("开发商：Square Enix");
//	ending_text[list1++] = _T("       PlatinumGames");
//	ending_text[list1++] = _T("发行公司：Square Enix");
//	ending_text[list1++] = _T("发行日期：PS4：2017年2月23日");
//	ending_text[list1++] = _T("              4月27日（中文版）");
//	ending_text[list1++] = _T("                          XboxOne：2018年6月26日");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("原游戏背景设定");
//	ending_text[list1++] = _T("       《尼尔：机械纪元》故事背景设定在遥远的未来，");
//	ending_text[list1++] = _T("讲述在被摧毁的地球上由人类的敌人外星人派来的机 ");
//	ending_text[list1++] = _T("械生命体与人类方派出的人造人\"尤尔哈\"部队进行战");
//	ending_text[list1++] = _T("    斗的故事。                                                                  ");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("本游戏背景设定");
//	ending_text[list1++] = _T("       本游戏故事背景取材于《尼尔：机械纪元》其中一");
//	ending_text[list1++] = _T("个BOSS战，讲述了一名女性机械生命体追求一名男性机");
//	ending_text[list1++] = _T("械生命体未果，反而一步步坠入疯狂的故事。其中，女");
//	ending_text[list1++] = _T("性机械生命体的原型为法国女权主义运动创始人西蒙娜");
//	ending_text[list1++] = _T("·德·波伏娃，男性机械生命体的原型为法国存在主义代");
//	ending_text[list1++] = _T("表人物让-保罗·萨特，二人在现实中虽相恋一生，却终");
//	ending_text[list1++] = _T("生未婚。                                                                    ");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("曲目列表");
//	ending_text[list1++] = _T("曲目1： 《意味》");
//	ending_text[list1++] = _T("作曲： 岡部啓一");
//	ending_text[list1++] = _T("编曲： 岡部啓一");
//	ending_text[list1++] = _T("演唱： 河野万里奈");
//	ending_text[list1++] = _T("曲目2： 《游园设施》");
//	ending_text[list1++] = _T("作曲： 帆足圭吾");
//	ending_text[list1++] = _T("编曲： 帆足圭吾");
//	ending_text[list1++] = _T("演唱： Emi Evans");
//	ending_text[list1++] = _T("曲目3： 《美丽之歌》");
//	ending_text[list1++] = _T("作词： 帆足圭吾");
//	ending_text[list1++] = _T("作曲： 帆足圭吾");
//	ending_text[list1++] = _T("演唱： J'Nique Nicole/ Emi Evans");
//	ending_text[list1++] = _T("曲目4： 《幸运之死》");
//	ending_text[list1++] = _T("作曲： 岡部啓一");
//	ending_text[list1++] = _T("编曲： 岡部啓一");
//	ending_text[list1++] = _T("演唱： 河野万里奈");
//	ending_text[list1++] = _T("曲目5： 《暧昧的希望》");
//	ending_text[list1++] = _T("作曲： 帆足圭吾");
//	ending_text[list1++] = _T("作曲： 帆足圭吾");
//	ending_text[list1++] = _T("演唱： Emi Evans");
//	ending_text[list1++] = _T("曲目6： the End of YoRHa ");
//	ending_text[list1++] = _T("作曲： YoRha");
//	ending_text[list1++] = _T("作曲： YoRha");
//	ending_text[list1++] = _T("演唱： Emi Evans");
//	ending_text[list1++] = _T("演唱： J'Nique Nicole");
//	ending_text[list1++] = _T("演唱： 河野万里奈");
//	ending_text[list1++] = _T("以上歌曲收录于《NieR:Automata Original Soundtrack》");
//
//	list1--;
//}
//
//void shake_ending_text(int win_wid, int win_hgt)
//{
//	while (1)
//	{
//		if (IF_SHAKE_TEXT && !IF_END_SHAKE_TEXT)
//		{
//			EndBatchDraw();
//			clearrectangle(-1, 0, win_wid, 0.7 * win_hgt);
//			int rand_y = 0;
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2, i + y_element[j], ending_text[j]);
//			
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 + 2, i + y_element[j], ending_text[j]);
//			
//			rand_y = rand() % int(0.7 * win_hgt);
//			line(0, rand_y, win_wid, rand_y);
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 - 2, i + y_element[j], ending_text[j]);
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 + 4, i + y_element[j], ending_text[j]);
//			rand_y = rand() % int(0.7 * win_hgt);
//			line(0, rand_y, win_wid, rand_y);
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 - 4, i + y_element[j], ending_text[j]);
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 + 8, i + y_element[j], ending_text[j]);
//			rand_y = rand() % int(0.7 * win_hgt);
//			line(0, rand_y, win_wid, rand_y);
//			j = 0;
//			Sleep(1);
//
//			for (; j <= list1; j++)
//				if (0 < i + y_element[j] < win_hgt)
//					outtextxy((win_wid - textwidth(ending_text[j])) / 2 - 8, i + y_element[j], ending_text[j]);
//			j = 0;
//			Sleep(1);
//		}
//		else if (IF_END_SHAKE_TEXT)
//			break;
//		else
//			Sleep(100);
//	}
//	return;
//}
//
//void show_caption(int win_wid, int win_hgt)
//{
//	int sleep_time = 10;
//	//int sleep_time = 40;
//	int Font_Height = 28;
//	int text_y_gap = Font_Height * 2;
//
//
//	int dialogTextIndex = 0;
//	int dialogText_i = 0;
//	dialogBox mydialogbox;
//	wchar_t s1[50] = L"辅助机153通知042. ";
//	wchar_t s2[50] = L"数据串流中混有噪声. ";
//	wchar_t s3[50] = L"为了检查数据, 申请暂时停止执行. ";
//#define mydialogTextNum 5
//	dialogText mydialogText[mydialogTextNum]{
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s2, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s3, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		/*{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }},*/
//		{20, s1, { 270, GRAPH_HEIGHT - 150,1000, GRAPH_HEIGHT - 100 }}
//	};
//
//	IMAGE* img = new IMAGE(GRAPH_WIDTH, GRAPH_HEIGHT);
//	
//
//	// 设置当前字体为高28像素的“Consolas”。(VC6 / VC2008 / VC2010 / VC2012)
//	settextstyle(Font_Height, 0, _T("微软雅黑"));
//	setlinecolor(WHITE);
//	setbkmode(TRANSPARENT);
//	//
//	for (int i = 1; i <= list1; i++)
//		y_element[i] = y_element[i - 1] + text_y_gap;
//
//	int a = 0;
//
//	//thread t1(show_dialogue, win_wid, win_hgt);			// 对话线程
//	//thread t2(shake_ending_text, win_wid, win_hgt);		// 抖动文字线程
//	time_t loopTime1 = clock(), loopTime2;
//	BeginBatchDraw();
//	//for (; i > -10000; i -= 2)				// 控制结束字幕运动主循环
//	int i = ENDING_HEIGHT + 100;
//	for (; i > -10000; i -= 2)				// 控制结束字幕运动主循环
//	{
//		loopTime1 = clock();
//
//		
//		FlushBatchDraw();
//		cleardevice();
//		for (; !IF_END_ROLL_TEXT && j <= list1; j++)
//			if (0 < i + y_element[j] < win_hgt)
//				outtextxy((win_wid - textwidth(ending_text[j])) / 2, i + y_element[j], ending_text[j]);
//		j = 0;
//		
//		{
//			if (IF_SHAKE_TEXT && !IF_END_SHAKE_TEXT)
//			{
//				//EndBatchDraw();
//				//clearrectangle(-1, 0, win_wid, 0.7 * win_hgt);
//				int rand_y = 0;
//				int rand_x = 0;
//				for (; j <= list1; j++)
//					if (0 < i + y_element[j] < win_hgt) {
//#define RAND_RANGE 18
//						settextcolor(0xaaaaaa);
//						outtextxy((win_wid - textwidth(ending_text[j])) / 2, i + y_element[j], ending_text[j]);
//
//						rand_x = rand() % RAND_RANGE - RAND_RANGE / 2;
//						outtextxy((win_wid - textwidth(ending_text[j])) / 2 + rand_x, i + y_element[j], ending_text[j]);
//						rand_x = rand() % RAND_RANGE - RAND_RANGE / 2;
//						outtextxy((win_wid - textwidth(ending_text[j])) / 2 + rand_x, i + y_element[j], ending_text[j]);
//						rand_x = rand() % RAND_RANGE - RAND_RANGE / 2;
//						settextcolor(0xffffff);
//						outtextxy((win_wid - textwidth(ending_text[j])) / 2 + rand_x, i + y_element[j], ending_text[j]);
//
//					}
//				rand_y = rand() % int(0.7 * win_hgt);
//				line(0, rand_y, win_wid, rand_y);
//				rand_y = rand() % int(0.7 * win_hgt);
//				line(0, rand_y, win_wid, rand_y);
//				rand_y = rand() % int(0.7 * win_hgt);
//				line(0, rand_y, win_wid, rand_y);
//
//			}
//		}
//
//		//
//		if (i <= 800 - y_element[20] && i > 800 - y_element[30] && !IF_END_ROLL_TEXT)
//		{
//			IF_SHAKE_TEXT = true;			// 允许执行抖动文本
//			IF_SHOW_DIALOGUE = true;		// 允许执行对话
//		}
//		else if (i <= 800 - y_element[30] || IF_END_ROLL_TEXT)
//		{
//			SetWorkingImage();
//			setfillcolor(0x444444);
//			myclearrectangle(0, GRAPH_HEIGHT - DialogBoxHeight, GRAPH_WIDTH, GRAPH_HEIGHT);
//			mydialogText[dialogTextIndex].darwText();
//			dialogText_i += mydialogText[dialogTextIndex].addText();
//			mydialogbox.drawDialogBox();
//			if (dialogText_i > 20) {
//				dialogText_i = 0;
//				if (++dialogTextIndex > mydialogTextNum - 1) { 
//					break; 
//				}
//				
//			}
//
//			i += 2;
//			IF_END_ROLL_TEXT = true;
//		}
//
//		// 抖动文本部分
//		
//		loopTime2 = clock();
//		a = (int)(loopTime2 - loopTime1);
//		wchar_t s[10];
//		wsprintf(s, L"%d || %d", a , - (i + GRAPH_HEIGHT) / text_y_gap);
//		outtextxy(0, 0, s);
//		
//		Sleep(sleep_time - a > 0 ? sleep_time - a : 0);				// 如果延时不足sleep_time，强行拉到sleep_time，否则就直接过
//		
//
//	}
//	EndBatchDraw();
//
//	Sleep(100);
//
//
//	IF_END_DIALOGUE = true;
//	IF_END_SHAKE_TEXT = true;
//	//t1.join();
//	//t2.join();
//
//	j = 0;
//
//	BeginBatchDraw();
//
//	// 这一部分是字幕向上移动的
//	for (; i <= 800; i += 20)
//	{
//		FlushBatchDraw();
//		cleardevice();
//		for (; j <= list1; j++)
//			if (0 < i + y_element[j] < win_hgt)
//				outtextxy((win_wid - textwidth(ending_text[j])) / 2, i + y_element[j], ending_text[j]);
//		j = 0;
//		Sleep(1);
//		
//	}
//	EndBatchDraw();
//	cleardevice();
//
//}
//
//void clear_all(int win_wid, int win_hgt)
//{
//	for (int i = win_hgt; i >= 0; i--)
//	{
//		setlinecolor(BLACK);
//		line(0, i, win_wid, i);
//		Sleep(1);
//	}
//}

int ending::gameMain() {
	//initgraph(ENDING_WIDTH, ENDING_HEIGHT);
	//
	//setorigin(0, 0);
	//settextcolor(WHITE);		// 回复颜色设置
	//LOGFONT f;
	//gettextstyle(&f);						// 获取当前字体设置
	//f.lfQuality = ANTIALIASED_QUALITY;	// 设置输出效果为抗锯齿
	//f.lfWeight = FW_DONTCARE;			// 设置字符笔画粗细为最细
	//settextstyle(&f);						// 设置字体样式
	////clear_all(ENDING_WIDTH, ENDING_HEIGHT);
	//set_ending_text();
	//set_dialogue();
	//show_caption(ENDING_WIDTH,ENDING_HEIGHT);
	return 0;
}