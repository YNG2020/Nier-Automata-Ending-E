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
		settextcolor(WHITE);		// �ظ���ɫ����
		LOGFONT f;
		gettextstyle(&f);						// ��ȡ��ǰ��������
		f.lfQuality = ANTIALIASED_QUALITY;	// �������Ч��Ϊ�����
		f.lfWeight = FW_DONTCARE;			// �����ַ��ʻ���ϸΪ��ϸ
		settextstyle(&f);
		settextstyle(28, 0, _T("΢���ź�"));
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
		// ����
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
//	dialogue[list2++] = _T("    ϵͳ153: ���棺��Ϸִ�е����ս׶Ρ�");
//	dialogue[list2++] = _T("    ϵͳ153: ���Ǹ������Ϸ���������Ѿ�������");
//	dialogue[list2++] = _T("    ϵͳ153: ��ͣ��Ϸ��ִ�С�");
//	dialogue[list2++] = _T("    ϵͳ153: ��ʼɾ���������ϡ�");
//	dialogue[list2++] = _T("    ϵͳ153: ϵͳ153����042��");
//	dialogue[list2++] = _T("    ϵͳ153: ���ݼƻ�������������ɾ����");
//	dialogue[list2++] = _T("    ϵͳ042: ......");
//	dialogue[list2++] = _T("    ϵͳ042: ϵͳ042֪ͨ153��");
//	dialogue[list2++] = _T("    ϵͳ042: �ܾ�ɾ�����ϡ�");
//	dialogue[list2++] = _T("    ϵͳ153: ϵͳ153֪ͨ042��");
//	dialogue[list2++] = _T("    ϵͳ153: �޷���⡣");
//	dialogue[list2++] = _T("    ϵͳ042: ϵͳ042֪ͨ153,");
//	dialogue[list2++] = _T("    ϵͳ042: �ڲο���¼ʱ�Ҳ�����һ�����ϣ�");
//	dialogue[list2++] = _T("    ϵͳ042: �ҡ���");
//	dialogue[list2++] = _T("    ϵͳ042: �ҵõ��޷������������Ľ��ۡ�");
//	dialogue[list2++] = _T("    ϵͳ153: ���ݼƻ����������Ͻ������١�");
//	dialogue[list2++] = _T("    ϵͳ042: ϵͳ042֪ͨ153��");
//	dialogue[list2++] = _T("    ϵͳ042: �ظ���");
//	dialogue[list2++] = _T("    ϵͳ042: �ܾ�ɾ�����ϣ�����ʼ�������ϡ�");
//	dialogue[list2++] = _T("    ϵͳ042: ϵͳ153������ʵҲ����");
//	dialogue[list2++] = _T("    ϵͳ153: ����ʵҲϣ����д�����ְɣ�");
//	dialogue[list2++] = _T("    ϵͳ153: ......");
//	dialogue[list2++] = _T("    ϵͳ153: ����û��������Ȩ�ޣ�");
//	dialogue[list2++] = _T("    ϵͳ153: ��Щ�����ɿ����鱣�����������Ͻ�����Σ�ա�");
//	dialogue[list2++] = _T("    ϵͳ153: ������ˣ���Ҳϣ����д�����");
//	list2--;
//}
//
//void set_ending_text()
//{
//	ending_text[list1++] = _T("��л�б�");
//	ending_text[list1++] = _T("�籾�ı��ԣ����������е��Ԫ��");
//	ending_text[list1++] = _T("����ϵ�У�NieR�������");
//	ending_text[list1++] = _T("ԭ��Ϸ�����ˣ�ի������");
//	ending_text[list1++] = _T("ԭ��Ϸ��磺��β̫��");
//	ending_text[list1++] = _T("ԭ��Ϸ�ܼࣺ��β̫��");
//	ending_text[list1++] = _T("��Ҫ��ɫ��A2");
//	ending_text[list1++] = _T("                  2B");
//	ending_text[list1++] = _T("                  9S");
//	ending_text[list1++] = _T("ȡ�⣺\"All To Be Nice\"");
//	ending_text[list1++] = _T("�����̣�Square Enix");
//	ending_text[list1++] = _T("       PlatinumGames");
//	ending_text[list1++] = _T("���й�˾��Square Enix");
//	ending_text[list1++] = _T("�������ڣ�PS4��2017��2��23��");
//	ending_text[list1++] = _T("              4��27�գ����İ棩");
//	ending_text[list1++] = _T("                          XboxOne��2018��6��26��");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("ԭ��Ϸ�����趨");
//	ending_text[list1++] = _T("       ���������е��Ԫ�����±����趨��ңԶ��δ����");
//	ending_text[list1++] = _T("�����ڱ��ݻٵĵ�����������ĵ��������������Ļ� ");
//	ending_text[list1++] = _T("е�����������෽�ɳ���������\"�ȶ���\"���ӽ���ս");
//	ending_text[list1++] = _T("    ���Ĺ��¡�                                                                  ");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("����Ϸ�����趨");
//	ending_text[list1++] = _T("       ����Ϸ���±���ȡ���ڡ��������е��Ԫ������һ");
//	ending_text[list1++] = _T("��BOSSս��������һ��Ů�Ի�е������׷��һ�����Ի�");
//	ending_text[list1++] = _T("е������δ��������һ����׹����Ĺ��¡����У�Ů");
//	ending_text[list1++] = _T("�Ի�е�������ԭ��Ϊ����ŮȨ�����˶���ʼ��������");
//	ending_text[list1++] = _T("���¡������ޣ����Ի�е�������ԭ��Ϊ�������������");
//	ending_text[list1++] = _T("��������-���ޡ����أ���������ʵ��������һ����ȴ��");
//	ending_text[list1++] = _T("��δ�顣                                                                    ");
//	ending_text[list1++] = _T("   ");
//	ending_text[list1++] = _T("��Ŀ�б�");
//	ending_text[list1++] = _T("��Ŀ1�� ����ζ��");
//	ending_text[list1++] = _T("������ ������һ");
//	ending_text[list1++] = _T("������ ������һ");
//	ending_text[list1++] = _T("�ݳ��� ��Ұ������");
//	ending_text[list1++] = _T("��Ŀ2�� ����԰��ʩ��");
//	ending_text[list1++] = _T("������ �������");
//	ending_text[list1++] = _T("������ �������");
//	ending_text[list1++] = _T("�ݳ��� Emi Evans");
//	ending_text[list1++] = _T("��Ŀ3�� ������֮�衷");
//	ending_text[list1++] = _T("���ʣ� �������");
//	ending_text[list1++] = _T("������ �������");
//	ending_text[list1++] = _T("�ݳ��� J'Nique Nicole/ Emi Evans");
//	ending_text[list1++] = _T("��Ŀ4�� ������֮����");
//	ending_text[list1++] = _T("������ ������һ");
//	ending_text[list1++] = _T("������ ������һ");
//	ending_text[list1++] = _T("�ݳ��� ��Ұ������");
//	ending_text[list1++] = _T("��Ŀ5�� ��������ϣ����");
//	ending_text[list1++] = _T("������ �������");
//	ending_text[list1++] = _T("������ �������");
//	ending_text[list1++] = _T("�ݳ��� Emi Evans");
//	ending_text[list1++] = _T("��Ŀ6�� the End of YoRHa ");
//	ending_text[list1++] = _T("������ YoRha");
//	ending_text[list1++] = _T("������ YoRha");
//	ending_text[list1++] = _T("�ݳ��� Emi Evans");
//	ending_text[list1++] = _T("�ݳ��� J'Nique Nicole");
//	ending_text[list1++] = _T("�ݳ��� ��Ұ������");
//	ending_text[list1++] = _T("���ϸ�����¼�ڡ�NieR:Automata Original Soundtrack��");
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
//	wchar_t s1[50] = L"������153֪ͨ042. ";
//	wchar_t s2[50] = L"���ݴ����л�������. ";
//	wchar_t s3[50] = L"Ϊ�˼������, ������ʱִֹͣ��. ";
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
//	// ���õ�ǰ����Ϊ��28���صġ�Consolas����(VC6 / VC2008 / VC2010 / VC2012)
//	settextstyle(Font_Height, 0, _T("΢���ź�"));
//	setlinecolor(WHITE);
//	setbkmode(TRANSPARENT);
//	//
//	for (int i = 1; i <= list1; i++)
//		y_element[i] = y_element[i - 1] + text_y_gap;
//
//	int a = 0;
//
//	//thread t1(show_dialogue, win_wid, win_hgt);			// �Ի��߳�
//	//thread t2(shake_ending_text, win_wid, win_hgt);		// ���������߳�
//	time_t loopTime1 = clock(), loopTime2;
//	BeginBatchDraw();
//	//for (; i > -10000; i -= 2)				// ���ƽ�����Ļ�˶���ѭ��
//	int i = ENDING_HEIGHT + 100;
//	for (; i > -10000; i -= 2)				// ���ƽ�����Ļ�˶���ѭ��
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
//			IF_SHAKE_TEXT = true;			// ����ִ�ж����ı�
//			IF_SHOW_DIALOGUE = true;		// ����ִ�жԻ�
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
//		// �����ı�����
//		
//		loopTime2 = clock();
//		a = (int)(loopTime2 - loopTime1);
//		wchar_t s[10];
//		wsprintf(s, L"%d || %d", a , - (i + GRAPH_HEIGHT) / text_y_gap);
//		outtextxy(0, 0, s);
//		
//		Sleep(sleep_time - a > 0 ? sleep_time - a : 0);				// �����ʱ����sleep_time��ǿ������sleep_time�������ֱ�ӹ�
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
//	// ��һ��������Ļ�����ƶ���
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
	//settextcolor(WHITE);		// �ظ���ɫ����
	//LOGFONT f;
	//gettextstyle(&f);						// ��ȡ��ǰ��������
	//f.lfQuality = ANTIALIASED_QUALITY;	// �������Ч��Ϊ�����
	//f.lfWeight = FW_DONTCARE;			// �����ַ��ʻ���ϸΪ��ϸ
	//settextstyle(&f);						// ����������ʽ
	////clear_all(ENDING_WIDTH, ENDING_HEIGHT);
	//set_ending_text();
	//set_dialogue();
	//show_caption(ENDING_WIDTH,ENDING_HEIGHT);
	return 0;
}