#include "starting.h"

/**
* @brief 音乐对象创建函数
* @note <此处将原来的non-local static对象
* 变为local static对象，目的是为了免除“跨编
* 译单元之初始化次序”问题>
*/
MyMusic& music()
{
	static MyMusic music;	// 创建播放音乐对象
	return music;
}

static const int win_wid = GRAPH_WIDTH;	// 画布宽
static const int win_hei = GRAPH_HEIGHT;		// 画布高

static bool IS_QUIT_THREAD = false;	// 线程退出条件
static bool IS_QUIT_MUSIC = false;	// 音乐退出条件

static const float pi = 3.141592f;	// 圆周率常数

static float x_ratio = win_wid / 1344.0f;	// 横向比例调节
static float y_ratio = win_hei / 756.0f;	// 纵向比例调节

const float Particle::blink_frequency_max = 0.5f * pi;	// 粒子闪烁频率最大值
const float Particle::blink_frequency_min = 25.0f;		// 粒子闪烁频率最小值

int Menu::show_menu_count = 0;	// 菜单显示文字索引
int Menu::font_height = static_cast<int>(22 * x_ratio);	// 菜单文字高度（大小）
bool Menu::JUMP_FLAG = false;	// 菜单跳跃标志（不同级的跳跃）

int RandBlock::Mosaic_left = static_cast<int>(220 * x_ratio);		// 掩块区域左边界
int RandBlock::Mosaic_right = static_cast<int>(1010 * x_ratio);		// 掩块区域右边界
int RandBlock::Mosaic_top = static_cast<int>(330 * y_ratio);		// 掩块区域上边界
int RandBlock::Mosaic_bottom = static_cast<int>(380 * y_ratio);		// 掩块区域下边界
int RandBlock::Mosaic_width = Mosaic_right - Mosaic_left;	// 掩块区域宽度
int RandBlock::Mosaic_height = Mosaic_bottom - Mosaic_top;	// 掩块区域高度
int RandBlock::renew_block_count = 1;		// 掩块更新计数
int RandBlock::num_showing_block = 0;		// 当前显示掩块数目
vector<int> RandBlock::rand_index = {0};	// 掩块随机编号

/**
* @brief 粒子构造函数
*/
Particle::Particle()
{
	vX = 0;
	vY = 0;
	XAm = rand() % XAm_range + XAm_min;
	YAm = rand() % YAm_range + YAm_min;
	cur_x = ori_x = float(rand() % win_wid);
	cur_y = ori_y = float(rand() % win_hei);
	blink_count = 10000 * pi + rand() % 628 / 100;		// 应该是能够解决数值误差问题，详细原因还没找到
	blink_frequency = blink_frequency_max / (rand() % blink_frequency_level + blink_frequency_min);		// 设置闪烁频率
	show_frequency = rand() % show_frequency_range + show_frequency_min;
	show_count = 0;
	particle_light_offset = 0;

	if (rand() % 10 < 6)
		border = rand() % small_border_range + border_min;
	else
		border = rand() % border_range + border_min;
}

/**
* @brief 随机掩块构造函数
*/
RandBlock::RandBlock()
{
	block_left = rand() % Mosaic_width + Mosaic_left;		// 随机生成掩块左边界
	block_top = rand() % Mosaic_height + Mosaic_top;		// 随机生成掩块上边界
	width = rand() % block_wid_range + block_wid_min;		// 随机生成掩块宽度
	height = rand() % block_hei_range + block_hei_min;		// 随机生成掩块高度
	ratio = (rand() % 99) / 100.0;							// 随机生成黑白比例
	blink_count = rand() % 10;								// 随机生成初始值
	blink_period = rand() % block_blink_period_range + block_blink_period_min;

	for (int i = 1; i < RandBlock::NUM_ALL_RANDBLOCK; i++)	// 初始化index
		rand_index.push_back(i);
}

/**
* @brief 菜单构造函数
* @param <text> <菜单文字>
* @param <text_y> <菜单文字高度>
* @note <菜单函数只是完成了转进转出特效，内容暂时还没有做>
*/
Menu::Menu(const TCHAR* text, int text_y) : text(text), text_y(text_y)
{
	// 设置文字样式
	settextstyle(font_height, 0, _T("Consolas"));
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfQuality = ANTIALIASED_QUALITY;			// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(TRANSPARENT);					// 设置文字背景为透明色

	text_x = (win_wid - textwidth(text)) / 2;
	line_lx = (win_wid) / 2 - (win_wid) / 9;
	line_rx = (win_wid) / 2 + (win_wid) / 9;

	cur_text[0] = '\0';
	cur_char_index = 0;
	num_of_char = (lstrlen(text) * sizeof(TCHAR)) / 2;
	cur_text_x = 0;

	text_loop_count = 0;
	underline_loop_count = 0;
	tot_loop = 6;
}

/**
* @brief 齿轮构造函数
* @param <gear_base_x> 齿轮中心x方向坐标
* @param <gear_base_y> 齿轮中心y方向坐标
* @param <ratio> 齿轮大小调节因子
* @param <gear_rotate_v> 转速
*/
Gear::Gear(float gear_base_x, float gear_base_y, float ratio, float gear_rotate_v)
	: gear_base_x(gear_base_x), gear_base_y(gear_base_y), ratio(ratio), gear_rotate_v(gear_rotate_v)
{
	exradius = static_cast<float>(10.0f * ratio);

	gear_tooth_upleft_x = -3.0f * ratio;
	gear_tooth_upleft_y = exradius;

	gear_tooth_upright_x = 3.0f * ratio;
	gear_tooth_upright_y = exradius;

	gear_tooth_downleft_x = -1.0f * ratio;
	gear_tooth_downleft_y = (exradius + 4 * ratio);

	gear_tooth_downright_x = 1.0f * ratio;
	gear_tooth_downright_y = (exradius + 4 * ratio);

	gear_heart_radius1 = 3.0f * ratio;

	gear_axis_in_x = 0;
	gear_axis_in_y = -gear_heart_radius1;

	gear_axis_out_x = 0;
	gear_axis_out_y = -exradius;

	gear_axis_width = 1 * ratio;
}

/**
* @brief 荧光粒子构造函数
* @param <imgBuffer> 内存缓冲区指针
* @param <img> 画布指针
* @param <win_wid> 画布宽
* @param <win_hei> 画布高
* @param <particles> 要显示的粒子数组
*/
void Particle::show_particle(DWORD* imgBuffer, IMAGE* img, const int& win_wid, const int& win_hei, Particle* particles)
{
	SetWorkingImage(img);
	cleardevice();
	setlinecolor(BLACK);
	// 显示粒子
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		if ((abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border) == 0)		// 控制出现
		{
			particles[i].show_count++;										// 当粒子光晕半径为0时，进行出现计数
			if ((particles[i].show_count % particles[i].show_frequency))	// 让粒子暂时不出现，并且这时候particles[i].blink_count不变化
				continue;
			else
				particles[i].show_count = 1;								// 出现计数归1，直接归零的话，会让粒子在暂时不出现的时候出现
		}

		particles[i].blink_count += particles[i].blink_frequency;
		int border = (abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border);	// 控制光晕半径，达到闪烁效果

		COLORREF nowColor = getlinecolor();

		int light = 40 + rand() % (4 * particles[i].border);	// 控制亮度闪烁
		particles[i].particle_light_offset = light - 40;
		COLORREF stepColor = RGB(light - 15, light - 17, light - 31);

		for (int j = 0; j < border; border--) {					// 画亮度渐变圆，让平滑好看一些
			setlinecolor(stepColor);
			fillcircle(static_cast<int>(particles[i].cur_x), static_cast<int>(particles[i].cur_y), border);
			min(light++, 255);
			stepColor = RGB(light - 15, light - 17, light - 31);
		}
		setlinecolor(nowColor);
	}

	thread t1(Blur_step_weight_25_float, imgBuffer, 3, win_wid, win_hei);
	thread t2(Blur_step_weight_25_float, imgBuffer, 3, win_wid, win_hei);
	thread t3(Blur_step_weight_25_float, imgBuffer, 3, win_wid, win_hei);

	t1.join();
	t2.join();
	t3.join();

	// 更新粒子的位置
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		float x = particles[i].cur_x;
		float y = particles[i].cur_y;

		float p_v = 1;

		float vX = (1 - p_v) * particles[i].vX + particles[i].XAm;
		float vY = (1 - p_v) * particles[i].vY + particles[i].YAm;

		float nextX = x - vX;
		float nextY = y - vY;

		if (Particle::Vx_min > vX || vX < Particle::Vx_max)
			vX = 0;
		if (Particle::Vy_min > vY || vY < Particle::Vy_max)
			vY = 0;

		particles[i].vX = vX;
		particles[i].vY = vY;

		if (nextX > win_wid) { nextX = 0; }
		else if (nextX < 0) { nextX = static_cast<float>(win_wid); }
		if (nextY > win_hei) { nextY = 0; }
		else if (nextY < 0) { nextY = static_cast<float>(win_hei); }

		if ((abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border) == 0)		// 控制粒子出现，如果光晕半径为0，则只更新粒子位置而不画出粒子
		{
			if ((particles[i].show_count % particles[i].show_frequency))			// 让粒子在暂时不该出现的时候仍然能更新位置
			{
				particles[i].cur_x = nextX;
				particles[i].cur_y = nextY;
				continue;
			}
		}

		int light = min(15 * (abs(static_cast<int>(10 * sin(particles[i].blink_count))) % 10) + 7 * particles[i].particle_light_offset, 254);
		COLORREF stepColor = RGB(light, light, light);
		setlinecolor(stepColor);
		setfillcolor(stepColor);
		int particle_wid = max(particles[i].border - 10, 1);
		particle_wid = min(particle_wid, 2);

		if (particle_wid < 2)
			fillrectangle(static_cast<int>(particles[i].cur_x), static_cast<int>(particles[i].cur_y), static_cast<int>(particles[i].cur_x) + particle_wid, static_cast<int>(particles[i].cur_y) + particle_wid);
		else
			fillrectangle(static_cast<int>(particles[i].cur_x) - 1, static_cast<int>(particles[i].cur_y) - 1, static_cast<int>(particles[i].cur_x) + 1, static_cast<int>(particles[i].cur_y) + 1);

		particles[i].cur_x = nextX;
		particles[i].cur_y = nextY;
	}

	SetWorkingImage();
	myputimage(0, 0, img, 0);	// 放置渲染粒子
}

/**
* @brief 显示随机掩块
* @param <randblocks> 要显示的掩块数组
*/
void RandBlock::show_randblock(RandBlock* randblocks)
{
	if (!(renew_block_count % renew_block_period))			// 到点就更新一次随机数组
	{
		random_shuffle(rand_index.begin(), rand_index.end());  // 随机打乱顺序
		num_showing_block = rand() % 5 + 7;

		if (!(renew_block_count % (20 * renew_block_period)))
			num_showing_block = rand() % 20 + 60;
	}

	renew_block_count++;

	if (!(renew_block_count % 3))		// 强行把周期乘3，微调的作用
		for (int i = 0; i < num_showing_block; i++)
		{
			randblocks[rand_index[i]].blink_count++;

			if (!(randblocks[rand_index[i]].blink_count % randblocks[rand_index[i]].blink_period))		// 控制闪烁，count到点就不出现
				continue;

			int BW_border = int(randblocks[rand_index[i]].block_left + randblocks[rand_index[i]].ratio * randblocks[rand_index[i]].width);

			if (rand() % 2)
			{
				setfillcolor(RGB(20, 24, 40));
				setlinecolor(RGB(20, 24, 40));
				fillrectangle(randblocks[rand_index[i]].block_left, randblocks[rand_index[i]].block_top, BW_border, randblocks[rand_index[i]].block_top + randblocks[rand_index[i]].height);

				setfillcolor(RGB(230, 230, 218));
				setlinecolor(RGB(230, 230, 218));
				fillrectangle(BW_border, randblocks[rand_index[i]].block_top, randblocks[rand_index[i]].block_left + randblocks[rand_index[i]].width, randblocks[rand_index[i]].block_top + randblocks[rand_index[i]].height);
			}
			else
			{
				setfillcolor(RGB(230, 230, 218));
				setlinecolor(RGB(230, 230, 218));
				fillrectangle(randblocks[rand_index[i]].block_left, randblocks[rand_index[i]].block_top, BW_border, randblocks[rand_index[i]].block_top + randblocks[rand_index[i]].height);
				
				setfillcolor(RGB(20, 24, 40));
				setlinecolor(RGB(20, 24, 40));
				fillrectangle(BW_border, randblocks[rand_index[i]].block_top, randblocks[rand_index[i]].block_left + randblocks[rand_index[i]].width, randblocks[rand_index[i]].block_top + randblocks[rand_index[i]].height);
			}

		}

}

/**
* @brief 显示菜单文字
* @param <win_wid> 画布宽
* @param <win_hei> 画布高
*/
void Menu::show_text(const int& win_wid, const int& win_hei) const
{	
	int light = 255 * text_loop_count / tot_loop;
	settextcolor(RGB(light, light, light));
	outtextxy(cur_text_x, text_y, cur_text);
}

/**
* @brief 显示菜单雪花噪声
*/
void Menu::show_snowflake() const
{
	for (int i = 4; i < 22; i += 1)
	{
		int count_step = 15;
		int start_x = 0;
		int len = 0;

		for (int j = 0; j <= 3; j++)
		{
			line_sty_gen();
			start_x = rand_start_x_gen(count_step);
			len = rand_len_gen(count_step);
			line(start_x, text_y + i, start_x + len, text_y + i);
		}
	}
}

/**
* @brief 显示菜单文字下划线
*/
void Menu::show_underline() const
{
	int light = 255 * underline_loop_count / tot_loop;
	int line_cur_lx;
	int line_cur_rx;
	setlinecolor(RGB(light, light, light));
	setlinestyle(PS_SOLID, 2);

	if (Menu::JUMP_FLAG == false)
	{
		line_cur_lx = (win_wid) / 2 - (win_wid) / 9 * underline_loop_count / tot_loop;
		line_cur_rx = (win_wid) / 2 + (win_wid) / 9 * underline_loop_count / tot_loop;
	}
	else
	{
		line_cur_lx = (win_wid) / 2 - (win_wid) / 9 * (2 * tot_loop - underline_loop_count) / tot_loop;
		line_cur_rx = (win_wid) / 2 + (win_wid) / 9 * (2 * tot_loop - underline_loop_count) / tot_loop;
	}

	for (int i = 0; i < 6; i++)
	{
		int count_step = 30;
		int init_offset = 20;
		line_sty_gen();
		line((line_cur_lx - offset_gen(count_step, init_offset)), text_y + font_height + 3, (line_cur_rx + offset_gen(count_step, init_offset)), text_y + font_height + 3);
		line_sty_gen();
		line((line_cur_lx - offset_gen(count_step, init_offset)), text_y + font_height + 2, (line_cur_rx + offset_gen(count_step, init_offset)), text_y + font_height + 2);
	}

	setlinecolor(RGB(light, light, light));
	setlinestyle(PS_SOLID, 2);
	line(line_cur_lx, text_y + font_height + 3, line_cur_rx, text_y + font_height + 3);
	fillcircle(line_cur_lx - 5, text_y + font_height + 3, 1);
	fillcircle(line_cur_rx + 5, text_y + font_height + 3, 1);
}

/**
* @brief 文字转进特效处理函数
*/
void Menu::text_transfer_in()
{
	if (this->cur_char_index <= this->num_of_char + 1)	// 是否更新文字
	{
		this->cur_text[this->cur_char_index + 1] = '\0';
		for (int i = 0; i <= this->cur_char_index; i++)
		{
			this->cur_text[i] = this->text[i];
			this->cur_text_x = (win_wid - textwidth(this->cur_text)) / 2;
		}
		this->cur_char_index++;
	}
	if (this->text_loop_count < this->tot_loop)	// 是否更新文字loop_count
		this->text_loop_count++;
}

/**
* @brief 文字转出特效处理函数
*/
void Menu::text_transfer_out()
{
	if (this->text_loop_count > 0)
		this->text_loop_count--;
}

/**
* @brief 下划线转进特效处理函数
*/
void Menu::underline_transfer_in()
{
	if (this->underline_loop_count < this->tot_loop)	// 是否更新文字loop_count
		this->underline_loop_count++;
}

/**
* @brief 下划线转出特效处理函数
*/
void Menu::underline_transfer_out()
{
	if (this->underline_loop_count > 0)
		this->underline_loop_count--;
}

/**
* @brief 菜单转换特效接口
*/
void Menu::transfer_interface(Menu* menu, const int& win_wid, const int& win_hei, char ch)
{
	if (ch == 0x0D || (Menu::show_menu_count == 0 && ch))
		Menu::JUMP_FLAG = true;
		
	Menu* text_obj_ptr;
	
	if (Menu::show_menu_count == 0)
	{
		text_obj_ptr = &menu[0];
		if (!Menu::JUMP_FLAG)				// 若没有收到跳转命令
		{
			text_obj_ptr->text_transfer_in();
			text_obj_ptr->underline_transfer_in();
			text_obj_ptr->show_snowflake();	// 放置雪花
			text_obj_ptr->show_text(win_wid, win_hei);	// 放置文本
			text_obj_ptr->show_underline();	// 放置下划线
		}
		else
		{
			text_obj_ptr->text_transfer_out();
			text_obj_ptr->underline_transfer_out();
			text_obj_ptr->show_snowflake();	// 放置雪花
			text_obj_ptr->show_text(win_wid, win_hei);	// 放置文本
			text_obj_ptr->show_underline();	// 放置下划线

			if (text_obj_ptr->underline_loop_count == 0)
			{
				Menu::show_menu_count++;	// 待转出特效完成后，转到下一菜单
				Menu::JUMP_FLAG = false;	// 待转出特效完成后，跳转标志置0
			}
		}
	}
	else if (Menu::show_menu_count == 1)
	{
		static int now_pointed = 1;
		if (!Menu::JUMP_FLAG)
		{
			
			if ((ch == 'W' || ch == 'w') && now_pointed > 1)
				now_pointed--;
			else if ((ch == 'S' || ch == 's') && now_pointed < 3)
				now_pointed++;

			static int ever_pointed = 1;
			
			for (int i = 1; i <= 3; i++)
			{
				text_obj_ptr = &menu[i];
				text_obj_ptr->text_transfer_in();
				text_obj_ptr->show_text(win_wid, win_hei);	// 放置文本

				if (i == now_pointed)		// 对当前选定的栏放置雪花与下划线
				{
					if (now_pointed != ever_pointed)	// 如果选定的栏要发生变化
					{
						text_obj_ptr = &menu[ever_pointed];
						text_obj_ptr->underline_transfer_out();
						text_obj_ptr->show_snowflake();	// 放置雪花
						text_obj_ptr->show_underline();	// 放置下划线
						if (text_obj_ptr->underline_loop_count == 0)
							ever_pointed = now_pointed;
					}
					else
					{
						text_obj_ptr->underline_transfer_in();
						text_obj_ptr->show_snowflake();	// 放置雪花
						text_obj_ptr->show_underline();	// 放置下划线
						ever_pointed = now_pointed;
					}
				}
			}
		}
		else
		{
			for (int i = 1; i <= 3; i++)
			{
				text_obj_ptr = &menu[i];
				text_obj_ptr->text_transfer_out();
				text_obj_ptr->show_text(win_wid, win_hei);	// 放置文本

				if (i == now_pointed)
				{
					text_obj_ptr->underline_transfer_out();
					text_obj_ptr->show_snowflake();	// 放置雪花
					text_obj_ptr->show_underline();	// 放置下划线
				}
			}
			if (
				menu[1].underline_loop_count +
				menu[2].underline_loop_count +
				menu[3].underline_loop_count == 0)
			{
				Menu::show_menu_count++;
				Menu::JUMP_FLAG = false;
			}
		}	
	}
	else if (Menu::show_menu_count == 2)
	{
			text_obj_ptr = &menu[4];

			text_obj_ptr->text_transfer_in();
			text_obj_ptr->underline_transfer_in();
			text_obj_ptr->show_snowflake();	// 放置雪花
			text_obj_ptr->show_text(win_wid, win_hei);	// 放置文本
			text_obj_ptr->show_underline();	// 放置下划线
		
		if (text_obj_ptr->underline_loop_count == text_obj_ptr->tot_loop &&
			text_obj_ptr->cur_char_index == text_obj_ptr->num_of_char + 1)
			IS_QUIT_MUSIC = true;	// 音乐退出条件
	}
}

/**
* @brief 显示齿轮
*/
void Gear::show_gear() const
{
	static float delta_angle = 0;

	setfillcolor(RGB(190, 190, 172));
	setlinecolor(RGB(190, 190, 172));

	// 画齿心
	circle(static_cast<int>(gear_base_x), static_cast<int>(gear_base_y), static_cast<int>(gear_heart_radius1));

	// 画齿牙
	for (int i = 0; i < 16; i++)
	{
		float angle = (2.0f * pi / 16) * i + delta_angle;
		float cos_angle = -cos(angle);
		float sin_angle = -sin(angle);

		int rotate_gear_tooth_upleft_x = static_cast<int>(gear_base_x + gear_tooth_upleft_x * sin_angle - gear_tooth_upleft_y * cos_angle);
		int rotate_gear_tooth_upleft_y = static_cast<int>(gear_base_y + gear_tooth_upleft_x * cos_angle + gear_tooth_upleft_y * sin_angle);

		int rotate_gear_tooth_upright_x = static_cast<int>(gear_base_x + gear_tooth_upright_x * sin_angle - gear_tooth_upright_y * cos_angle);
		int rotate_gear_tooth_upright_y = static_cast<int>(gear_base_y + gear_tooth_upright_x * cos_angle + gear_tooth_upright_y * sin_angle);

		int rotate_gear_tooth_downleft_x = static_cast<int>(gear_base_x + gear_tooth_downleft_x * sin_angle - gear_tooth_downleft_y * cos_angle);
		int rotate_gear_tooth_downleft_y = static_cast<int>(gear_base_y + gear_tooth_downleft_x * cos_angle + gear_tooth_downleft_y * sin_angle);

		int rotate_gear_tooth_downright_x = static_cast<int>(gear_base_x + gear_tooth_downright_x * sin_angle - gear_tooth_downright_y * cos_angle);
		int rotate_gear_tooth_downright_y = static_cast<int>(gear_base_y + gear_tooth_downright_x * cos_angle + gear_tooth_downright_y * sin_angle);

		POINT pts[] = {
						{rotate_gear_tooth_upleft_x, rotate_gear_tooth_upleft_y},
						{rotate_gear_tooth_upright_x, rotate_gear_tooth_upright_y},
						{rotate_gear_tooth_downright_x, rotate_gear_tooth_downright_y},
						{rotate_gear_tooth_downleft_x, rotate_gear_tooth_downleft_y}
		};
		solidpolygon(pts, 4);
	}

	// 画齿轴
	setlinestyle(PS_SOLID, static_cast<int>(gear_axis_width));
	for (int i = 0; i < 3; i++)
	{
		float angle = (2 * pi / 3) * i + delta_angle;
		float cos_angle = -cos(angle);
		float sin_angle = -sin(angle);

		int rotate_gear_axis_in_x = static_cast<int>(gear_base_x + gear_axis_in_x * sin_angle - gear_axis_in_y * cos_angle);
		int rotate_gear_axis_in_y = static_cast<int>(gear_base_y + gear_axis_in_x * cos_angle + gear_axis_in_y * sin_angle);

		int rotate_gear_axis_out_x = static_cast<int>(gear_base_x + gear_axis_out_x * sin_angle - gear_axis_out_y * cos_angle);
		int rotate_gear_axis_out_y = static_cast<int>(gear_base_y + gear_axis_out_x * cos_angle + gear_axis_out_y * sin_angle);

		line(rotate_gear_axis_in_x, rotate_gear_axis_in_y, rotate_gear_axis_out_x, rotate_gear_axis_out_y);
	}
	delta_angle += gear_rotate_v;
}

/**
* @brief 菜单雪花随机线型生成函数
*/
void Menu::line_sty_gen() const
{
	int num_of_dash_line = 10;
	DWORD* a = new DWORD[num_of_dash_line];
	int line_light = 150;
	setlinecolor(RGB(line_light, line_light, line_light));
	for (int i = 0; i < num_of_dash_line; i++)
	{
		if (i % 2)
			a[i] = rand() % 40 + 5;
		else
			a[i] = rand() % 5;
	}

	setlinestyle(PS_USERSTYLE | PS_ENDCAP_FLAT, 1, a, num_of_dash_line);
	delete[] a;
}

/**
* @brief 下划线两端雪花随机偏移生成函数
* @param <count_step> <单次步进数，用于周期控制>
* @param <init_offset> <下划线两端雪花随机偏移基本量>
*/
int Menu::offset_gen(int count_step, int init_offset) const
{
	static unsigned int count = 0;
	count += count_step;
	return int((rand() % 100) * sin(count / 100)) + init_offset;
}

/**
* @brief 菜单雪花长度生成函数
* @param <count_step> <单次步进数，用于周期控制>
*/
int Menu::rand_len_gen(int count_step) const
{
	static float count1 = 0;
	static int rand_len = 0;
	count1 += count_step;
	float ratio = 0.9f;
	rand_len = static_cast<int>((textwidth(cur_text) / 4 * sin(count1 / 100) + ratio * (rand() % 1) + (1 - ratio) * rand_len) + textwidth(cur_text) / 4);
	return rand_len;
}

/**
* @brief 菜单雪花起点生成函数
* @param <count_step> <单次步进数，用于周期控制>
*/
int Menu::rand_start_x_gen(int count_step) const
{
	static float count2 = 0;
	static int rand_start_x_offset = 0;
	int rand_start_x = cur_text_x + textwidth(cur_text) / 4;
	count2 += count_step;
	float ratio = 0.9f;
	if (textwidth(cur_text) != 0)
		rand_start_x_offset = static_cast<int>((2 * (rand() % 2) - 1) * (textwidth(cur_text) / 4 * sin(count2 / 100) + ratio * (rand() % textwidth(cur_text) / 4) + (1 - ratio) * rand_start_x_offset));
	rand_start_x += rand_start_x_offset;
	return rand_start_x;
}

/**
* @brief 开始界面总控制函数
*/
void starting()
{
	initgraph(GRAPH_WIDTH,GRAPH_HEIGHT);

	music().open_music(_T("sounds/nonsense.mp3"));
	music().play_music();

	thread t1(running);	// 将粒子效果放到多线程中

	while (true)
	{
		Sleep(100);
		if (IS_QUIT_MUSIC)
		{
			music().pause_music();
			music().quit_music();	// 退出音乐
			IS_QUIT_THREAD = true;	// 退出粒子效果线程
			t1.join();
			setrop2(R2_COPYPEN);
			EndBatchDraw();			// 结束批量绘制
			break;
		}
	}
}

/**
* @brief 开始界面特效控制函数
*/
void running()
{
	IMAGE bk_img;
	IMAGE img(win_wid, win_hei);
	DWORD* imgBuffer = GetImageBuffer(&img);
	int sleep_time = 50;
	int time_count = 0;
	const TCHAR* bk_name = _T("picture/mynierbk.jpg");
	loadimage(&bk_img, bk_name, win_wid, win_hei);
	time_t loopTime1, loopTime2;
	char ch = '\0';
	ExMessage m;

	BeginBatchDraw();

	Particle particles[Particle::NUM_PARTICLE];
	RandBlock randblocks[RandBlock::NUM_ALL_RANDBLOCK];
	Menu menu[5] = { 
		Menu(_T("Press Any Button"), static_cast<int>((win_hei - 24) * 0.68f)),
		Menu(_T("New Game"), static_cast<int>((win_hei - 24) * 0.68f)),
		Menu(_T("Setting"), static_cast<int>((win_hei - 24) * 0.68f + 42)),
		Menu(_T("Exit Game"), static_cast<int>((win_hei - 24) * 0.68f + 84)),
		Menu(_T("Loading..."), static_cast<int>((win_hei - 24) * 0.68f))
	};
	Gear gear = Gear(static_cast<float>(466 * x_ratio), static_cast<float>(333 * y_ratio), 0.75f * x_ratio);

	while (true)
	{
		loopTime1 = clock();

		if (peekmessage(&m, EX_KEY))
			if (m.message == WM_KEYDOWN)
				ch = m.ch;
		
		putimage(0, 0, &bk_img);						// 放置背景图
		Menu::transfer_interface(menu, win_wid, win_hei, ch);	// 菜单转换接口
		Particle::show_particle(imgBuffer, &img, win_wid, win_hei, particles);	// 放置渲染粒子
		RandBlock::show_randblock(randblocks);	// 放置随机马赛克	
		gear.show_gear();				// 放置齿轮

		loopTime2 = clock();
		time_count = static_cast<int>(loopTime2 - loopTime1);
		Sleep(sleep_time - time_count > 0 ? sleep_time - time_count : 0);	// 如果延时不足sleep_time，强行拉到sleep_time，否则就直接过

		FlushBatchDraw();

		ch = '\0';

		if (IS_QUIT_THREAD)
			break;
	}
}