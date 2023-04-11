#include "bullet.h"
int bullet::bulletNum = 0;

static IMAGE* renderImg;

bullet* bullet::theLastBullet = nullptr;

#define PRE_RENDER_BULLET_IMG (100)
#define PRE_RENDER_HOLOBULLET_IMG (160)

int bullet::width = 10;
int bullet::height = 40;

struct myPoint {
	myPoint() {}
	myPoint(double _x, double _y) { x = _x, y = _y; }
	double x = 0;
	double y = 0;
};


template<class T>
T convertor(T num, T(*fun)(T)) {
	return fun(num);
}

double convertorR(double n) {
	const double minN = 10;
	const double maxN = 220;
	if (n < minN / 255.) {
		return 0;
	}
	if (n > maxN / 255.) {
		return 1;
	}
	return maxN / 255 - maxN / (255 - minN) * (1. - n);
}
double convertorG(double n) {
	const double minN = 10;
	const double maxN = 192;
	if (n < minN / 255.) {
		return 0;
	}
	if (n > maxN / 255.) {
		return 1;
	}
	return maxN / 255 - maxN / (255 - minN) * (1. - n);
}
double convertorB(double n) {
	const double minN = 10;
	const double maxN = 143;
	if (n < minN / 255.) {
		return 0;
	}
	if (n > maxN / 255.) {
		return 1;
	}
	return maxN / 255 - maxN / (255 - minN) * (1. - n);
}

double rectLength(myPoint d, myPoint rectLT, myPoint rectRB) {
	myPoint length;
	if (d.x > rectRB.x) {
		length.x = d.x - rectRB.x;
	}
	else {
		if (d.x < rectLT.x) {
			length.x = rectLT.x - d.x;
		}
		else {
			length.x = 0;
		}
	}

	if (d.y > rectRB.y) {
		length.y = d.y - rectRB.y;
	}
	else {
		if (d.y < rectLT.y) {
			length.y = rectLT.y - d.y;
		}
		else {
			length.y = 0;
		}
	}


	return sqrt(pow(length.x, 2) + pow(length.y, 2));

}
COLORREF drawHoloRect1(int x, int y, myPoint LT, myPoint RB , int graph_wid = GRAPH_WIDTH,int graph_height = GRAPH_HEIGHT) {
	double u = static_cast<double> (x) / graph_wid;
	double v = static_cast<double> (y) / graph_height;

	myPoint lt((LT.x - graph_wid / 2) / graph_height, LT.y / graph_height - 0.5);
	myPoint rb((RB.x - graph_wid / 2) / graph_height, RB.y / graph_height - 0.5);

	u -= 0.5;
	v -= 0.5;
	u *= static_cast<double>(graph_wid) / graph_height;
	double r = 0, g = 0, b = 0;
	double d = rectLength({ u,v }, lt, rb);

	double glow = 0.01 / d * 1 / 3;
	glow = clamp(glow, 0., 1.);



	if (d <= 0) {
		r = g = b = 1;
	}

	r += convertor(glow, convertorR);
	g += convertor(glow, convertorG);
	b += convertor(glow, convertorB);

	r *= 255;
	g *= 255;
	b *= 255;


	/*r -= 10;
	g -= 10;
	b -= 10;*/
	r = clamp(r, 0.0, 255.0);
	g = clamp(g, 0.0, 255.0);
	b = clamp(b, 0.0, 255.0);
	//if (r < 6) r = 0;
	//if (g < 6) g = 0;
	//if (b < 6) b = 0;
	return RGB(static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b));
}

void Blur_step_addV(DWORD* pMem, int size, float v_mul, int width, int height, int type)
{

	DWORD* buffer = (DWORD*)calloc(static_cast<long long>(height) * width, sizeof(DWORD));
	if (buffer == nullptr)return;
	int matrix[25] =
	{
		-2 * size - 2 * size * width,-1 * size - 2 * size * width,0 - 2 * size * width,1 * size - 2 * size * width,2 * size - 2 * size * width,
		-2 * size - 1 * size * width,-1 * size - 1 * size * width,0 - 1 * size * width,1 * size - 1 * size * width,2 * size - 1 * size * width,
		-2 * size,-1 * size,0,1 * size,2 * size,
		-2 * size + 1 * size * width,-1 * size + 1 * size * width,0 + 1 * size * width,1 * size + 1 * size * width,2 * size + 1 * size * width,
		-2 * size + 2 * size * width,-1 * size + 2 * size * width,0 + 2 * size * width,1 * size + 2 * size * width,2 * size + 2 * size * width
	};
	for (int i = 2 * size * width + 2 * size; i < width * (height - 2 * size) - 2 * size; i++)
	{
		int r = 0, g = 0, b = 0;
		for (int j = 0; j < 25; j++) {
			r += GetRValue(pMem[i + matrix[j]]);
			g += GetGValue(pMem[i + matrix[j]]);
			b += GetBValue(pMem[i + matrix[j]]);
		}
		float h, s, v;
		if (RGB(r / 25, g / 25, b / 25) != getbkcolor()) {
			RGBtoHSV(RGB(r / 25, g / 25, b / 25), &h, &s, &v);
			v *= v_mul;
			v = v > 1 ? 1 : v;
			buffer[i] = HSVtoRGB(h, s, v);
		}
	}
	memmove(pMem, buffer, sizeof(DWORD) * height * width);
	free(buffer);
}

bullet::bullet(int _x, int _y, double _angle)
{
	bulletNum++;

	x = _x;
	y = _y;
	angle = -_angle;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	xSpeed = speed * cos_angle;
	ySpeed = speed * sin_angle;
	
	lastBullet = theLastBullet;
	nextBullet = nullptr;
	if (lastBullet != nullptr) {
		lastBullet->nextBullet = this;
	}
	theLastBullet = this;

	int step_height_x = static_cast<int>(cos_angle * height / 2);
	int step_height_y = static_cast<int>(sin_angle * height / 2);
	int step_width_x = -static_cast<int>(sin_angle * width / 2);
	int step_width_y = static_cast<int>(cos_angle * width / 2);
	
	offsetPoint[0] = { step_height_x + step_width_x,step_height_y + step_width_y };
	offsetPoint[1] = { step_height_x - step_width_x,step_height_y - step_width_y };
	offsetPoint[2] = { - step_height_x - step_width_x,- step_height_y - step_width_y };
	offsetPoint[3] = { - step_height_x + step_width_x,- step_height_y + step_width_y };
	
	step_height_x = static_cast<int>(cos_angle * (height) / 2);
	step_height_y = static_cast<int>(sin_angle * (height) / 2);
	step_width_x = -static_cast<int>(sin_angle * (static_cast<long long>(width) + (static_cast<long long>(border))) / 2);
	step_width_y = static_cast<int>(cos_angle * (static_cast<long long>(width) + (static_cast<long long>(border))) / 2);
	borderOffset[0] = { step_height_x + step_width_x,step_height_y + step_width_y };
	borderOffset[1] = { step_height_x - step_width_x,step_height_y - step_width_y };
	borderOffset[2] = { -step_height_x - step_width_x,-step_height_y - step_width_y };
	borderOffset[3] = { -step_height_x + step_width_x,-step_height_y + step_width_y };

	for (int i = 0; i < 4; i++) {
		pts[i].x = offsetPoint[i].x + static_cast<LONG>(x);
		pts[i].y = offsetPoint[i].y + static_cast<LONG>(y);
	}
	preRender();
	//drawBulletWithoutBorder();
}

bullet::~bullet()
{
	bulletImg->~IMAGE();
	if (this == nullptr)return;
	if (this->lastBullet != nullptr) {
		this->lastBullet->nextBullet = this->nextBullet;
	}
	if (this->nextBullet != nullptr) {
		this->nextBullet->lastBullet = this->lastBullet;
	}
	else {
		theLastBullet = this->lastBullet;
	}
	//clearpolygon(pts, 4);
	clearBullet();
	
	bulletNum--;
}
int bullet::move() {

	/*int x1 = min(min(pts[0].x, pts[1].x), min(pts[2].x, pts[3].x));
	int y1 = min(min(pts[0].y, pts[1].y), min(pts[2].y, pts[3].y));
	int x2 = max(max(pts[0].x, pts[1].x), max(pts[2].x, pts[3].x));
	int y2 = max(max(pts[0].y, pts[1].y), max(pts[2].y, pts[3].y));

	clearrectangle(x1, y1, x2, y2);*/


	//clearpolygon(pts, 4);
	clearBullet();
	x -= xSpeed;
	y -= ySpeed;
	for (int i = 0; i < 4; i++) {
		pts[i].x = offsetPoint[i].x + static_cast<LONG>(x);
		pts[i].y = offsetPoint[i].y + static_cast<LONG>(y);
		if (pts[i].x < 0 || pts[i].y < 0) {
			return 1;
		}
		if (pts[i].x >=  GRAPH_WIDTH|| pts[i].y >= GRAPH_HEIGHT) {
			return 1;
		}
	}
	//solidpolygon(pts, 4);
	//drawBullet();
	return 0;
}

void bullet::clearBullet() {
}
void bullet::drawBulletRect() {
	POINT stepPts[4];

	int r, g, b;
	COLORREF baseColor = RGB(200, 175, 130);

	COLORREF stepColor = RGB((GetRValue(baseColor) - GetRValue(getbkcolor())) / border, (GetGValue(baseColor) - GetGValue(getbkcolor())) / border, (GetBValue(baseColor) - GetBValue(getbkcolor())) / border);
	r = static_cast<int>GetRValue(baseColor) - static_cast<int>GetRValue(stepColor) * border;
	g = static_cast<int>GetGValue(baseColor) - static_cast<int>GetGValue(stepColor) * border;
	b = static_cast<int>GetBValue(baseColor) - static_cast<int>GetBValue(stepColor) * border;
	COLORREF fillColor = RGB(
		r < 0 ? 0 : r,
		g < 0 ? 0 : g,
		b < 0 ? 0 : b);

	int _width = (width + border);
	int _height = (height + border);

	for (int i = 0; i < border; i++) {
		{
			/*color += stepColor;
			setfillcolor(color);
			solidcircle(x, y, border - i);
			solidcircle((pts[0].x + pts[1].x) / 2, (pts[0].y + pts[1].y) / 2, border - i);
			solidcircle((pts[2].x + pts[3].x) / 2, (pts[2].y + pts[3].y) / 2, border - i);
			int step = (border - i);
			stepPts[0] = { (pts[0].x + pts[1].x) / 2 - (long)(sin_angle * step), (pts[0].y + pts[1].y) / 2 + (long)(cos_angle * step) };
			stepPts[1] = { (pts[0].x + pts[1].x) / 2 + (long)(sin_angle * step), (pts[0].y + pts[1].y) / 2 - (long)(cos_angle * step) };
			stepPts[2] = { (pts[2].x + pts[3].x) / 2 + (long)(sin_angle * step), (pts[2].y + pts[3].y) / 2 - (long)(cos_angle * step) };
			stepPts[3] = { (pts[2].x + pts[3].x) / 2 - (long)(sin_angle * step), (pts[2].y + pts[3].y) / 2 + (long)(cos_angle * step) };*/
		}
		{
			setfillcolor(fillColor);
			r = static_cast<int>GetRValue(stepColor) + static_cast<int>GetRValue(fillColor);
			g = static_cast<int>GetGValue(stepColor) + static_cast<int>GetGValue(fillColor);
			b = static_cast<int>GetBValue(stepColor) + static_cast<int>GetBValue(fillColor);
			fillColor = RGB(
				r > GetRValue(baseColor) ? GetRValue(baseColor) : r,
				g > GetGValue(baseColor) ? GetGValue(baseColor) : g,
				b > GetBValue(baseColor) ? GetBValue(baseColor) : b
			);
		}
		//solidpolygon(stepPts,4);
		for (int j = 0; j < 4; j++) {
			stepPts[j].x = pts[j].x + offsetPoint[j].x - (i * offsetPoint[j].x / border);
			stepPts[j].y = pts[j].y + offsetPoint[j].y - (i * offsetPoint[j].y / border);
		}
		
		solidpolygon(stepPts, 4);
	}
	setfillcolor(0xffffff);
	//drawBulletWithoutBorder();
}

void bullet::drawBulletImg() {
	//putimage(x - PRE_RENDER_BULLET_IMG / 2, y - PRE_RENDER_BULLET_IMG / 2, bulletImg, SRCPAINT);
	//myputimage(x - PRE_RENDER_BULLET_IMG / 2, y - PRE_RENDER_BULLET_IMG / 2, bulletImg);
	myputimage(static_cast<int>(x) - PRE_RENDER_HOLOBULLET_IMG / 2, 
		static_cast<int>(y) - PRE_RENDER_HOLOBULLET_IMG / 2, bulletImg);
}

void bullet::drawBullet() {
	drawBulletImg();
	//drawBulletRect();
}

void bullet::drawBulletWithoutBorder() {
	setfillcolor(0xffffff);
	solidpolygon(pts, 4);
}
void bullet::preRender() {
	bulletImg = new IMAGE(PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG);
	rotateimage(bulletImg, renderImg, -angle);
	setfillcolor(0xffffff);
}

int bullet::preRenderStatic() {
	renderImg = new IMAGE(PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG);
	IMAGE* nowWorkingImg = GetWorkingImage();
	SetWorkingImage(renderImg);

	int preBorder = 28;
	int width = 15;
	int height = 50;


	int r, g, b;
	//子弹中心纯白(0xffffff)与光晕边缘的交界处的rgb值, 光晕的最高rgb值
	COLORREF baseColor = RGB(200, 175, 130);
	//COLORREF baseColor = RGB(100, 100, 100);
	//COLORREF baseColor = RGB(160, 140, 104);

	//从0到baseColor,步长颜色stepColor = baseColor / preBorder
	COLORREF stepColor = RGB((GetRValue(baseColor) - GetRValue(getbkcolor())) / preBorder, (GetGValue(baseColor) - GetGValue(getbkcolor())) / preBorder, (GetBValue(baseColor) - GetBValue(getbkcolor())) / preBorder);
	r = static_cast<int>GetRValue(baseColor) - static_cast<int>GetRValue(stepColor) * preBorder;
	g = static_cast<int>GetGValue(baseColor) - static_cast<int>GetGValue(stepColor) * preBorder;
	b = static_cast<int>GetBValue(baseColor) - static_cast<int>GetBValue(stepColor) * preBorder;

	/*outtextxy(100, 100, L"test");*/
	COLORREF fillColor = RGB(
		r < 0 ? 0 : r,
		g < 0 ? 0 : g,
		b < 0 ? 0 : b);

	int _width = (width + preBorder);
	int _height = (height + preBorder);
	for (int i = 0; i < preBorder; i++) {
		{
			setfillcolor(fillColor);
			r = static_cast<int>GetRValue(stepColor) + static_cast<int>GetRValue(fillColor);
			g = static_cast<int>GetGValue(stepColor) + static_cast<int>GetGValue(fillColor);
			b = static_cast<int>GetBValue(stepColor) + static_cast<int>GetBValue(fillColor);
			fillColor = RGB(
				r > GetRValue(baseColor) ? GetRValue(baseColor) : r,
				g > GetGValue(baseColor) ? GetGValue(baseColor) : g,
				b > GetBValue(baseColor) ? GetBValue(baseColor) : b
			);
		}
		solidrectangle((PRE_RENDER_BULLET_IMG - _height) / 2, (PRE_RENDER_BULLET_IMG - _width) / 2,
			(PRE_RENDER_BULLET_IMG + _height) / 2, (PRE_RENDER_BULLET_IMG + _width) / 2);
		_width--;
		_height--;
	}

	Blur_step_weight_25(GetImageBuffer(renderImg), 4, PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG);
	Blur_step_weight_25(GetImageBuffer(renderImg), 4, PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG);
	//Blur_step_addV(GetImageBuffer(renderImg), 2, 1.3, PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG, 0);
	setfillcolor(0xffffff);
	solidrectangle((PRE_RENDER_BULLET_IMG - height) / 2, (PRE_RENDER_BULLET_IMG - width) / 2,
		(PRE_RENDER_BULLET_IMG + height) / 2, (PRE_RENDER_BULLET_IMG + width) / 2);
	Blur_step_weight_25(GetImageBuffer(renderImg), 1, PRE_RENDER_BULLET_IMG, PRE_RENDER_BULLET_IMG);
	SetWorkingImage(nowWorkingImg);
	return 0;
}
int bullet::preRenderStatic2() {
	renderImg = new IMAGE(PRE_RENDER_HOLOBULLET_IMG, PRE_RENDER_HOLOBULLET_IMG);
	DWORD* renderImgBuffer = GetImageBuffer(renderImg);

	POINT pts[6]{
		{height / 2 + 5 + PRE_RENDER_HOLOBULLET_IMG / 2,-width / 2 - 5 + PRE_RENDER_HOLOBULLET_IMG / 2},
		{height / 2 + 5 + 3 + PRE_RENDER_HOLOBULLET_IMG / 2,0 + PRE_RENDER_HOLOBULLET_IMG / 2},
		{height / 2 + 5 + PRE_RENDER_HOLOBULLET_IMG / 2,width / 2 + 5 + PRE_RENDER_HOLOBULLET_IMG / 2},
		{-height / 2 - 5 + PRE_RENDER_HOLOBULLET_IMG / 2,width / 2 + 5 + PRE_RENDER_HOLOBULLET_IMG / 2},
		{-height / 2 - 5 - 3 + PRE_RENDER_HOLOBULLET_IMG / 2,0 + PRE_RENDER_HOLOBULLET_IMG / 2},
		{-height / 2 - 5 + PRE_RENDER_HOLOBULLET_IMG / 2,-width / 2 - 5 + PRE_RENDER_HOLOBULLET_IMG / 2}
	};
	

	for (int y = 0; y < PRE_RENDER_HOLOBULLET_IMG; y++) {
		for (int x = 0; x < PRE_RENDER_HOLOBULLET_IMG; x++) {
			COLORREF holoColor = drawHoloRect1(x, y, { static_cast<double>(PRE_RENDER_HOLOBULLET_IMG) / 2 - static_cast<double>(height)/2, static_cast<double>(PRE_RENDER_HOLOBULLET_IMG) / 2 - static_cast<double>(width) / 2 },
				{ static_cast<double>(PRE_RENDER_HOLOBULLET_IMG) / 2 + static_cast<double>(height) / 2, static_cast<double>(PRE_RENDER_HOLOBULLET_IMG) / 2 + static_cast<double>(width) / 2 });
			renderImgBuffer[y * PRE_RENDER_HOLOBULLET_IMG + x] = BGR(
				RGB(
					min(0xff, GetRValue(renderImgBuffer[y * PRE_RENDER_HOLOBULLET_IMG + x]) + GetRValue(holoColor)),
					min(0xff, GetGValue(renderImgBuffer[y * PRE_RENDER_HOLOBULLET_IMG + x]) + GetGValue(holoColor)),
					min(0xff, GetBValue(renderImgBuffer[y * PRE_RENDER_HOLOBULLET_IMG + x]) + GetBValue(holoColor))
				)
			);
		}
	}
	IMAGE* nowWorkingImg = GetWorkingImage();
	SetWorkingImage(renderImg);
	setfillcolor(WHITE);
	solidpolygon(pts, 6);
	SetWorkingImage(nowWorkingImg);

	return 0;
}
//int bullet::
//int bullet::
//int bullet::
//int bullet::
//int bullet::
//int bullet::
//int bullet::