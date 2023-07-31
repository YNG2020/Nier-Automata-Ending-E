#include "starting.h"

/**
* @brief ���ֶ��󴴽�����
* @note <�˴���ԭ����non-local static����
* ��Ϊlocal static����Ŀ����Ϊ����������
* �뵥Ԫ֮��ʼ����������>
*/
MyMusic& music()
{
	static MyMusic music;	// �����������ֶ���
	return music;
}

static const int win_wid = GRAPH_WIDTH;	// ������
static const int win_hei = GRAPH_HEIGHT;		// ������

static bool IS_QUIT_THREAD = false;	// �߳��˳�����
static bool IS_QUIT_MUSIC = false;	// �����˳�����

static const float pi = 3.141592f;	// Բ���ʳ���

static float x_ratio = win_wid / 1344.0f;	// �����������
static float y_ratio = win_hei / 756.0f;	// �����������

const float Particle::blink_frequency_max = 0.5f * pi;	// ������˸Ƶ�����ֵ
const float Particle::blink_frequency_min = 25.0f;		// ������˸Ƶ����Сֵ

int Menu::show_menu_count = 0;	// �˵���ʾ��������
int Menu::font_height = static_cast<int>(22 * x_ratio);	// �˵����ָ߶ȣ���С��
bool Menu::JUMP_FLAG = false;	// �˵���Ծ��־����ͬ������Ծ��

int RandBlock::Mosaic_left = static_cast<int>(220 * x_ratio);		// �ڿ�������߽�
int RandBlock::Mosaic_right = static_cast<int>(1010 * x_ratio);		// �ڿ������ұ߽�
int RandBlock::Mosaic_top = static_cast<int>(330 * y_ratio);		// �ڿ������ϱ߽�
int RandBlock::Mosaic_bottom = static_cast<int>(380 * y_ratio);		// �ڿ������±߽�
int RandBlock::Mosaic_width = Mosaic_right - Mosaic_left;	// �ڿ�������
int RandBlock::Mosaic_height = Mosaic_bottom - Mosaic_top;	// �ڿ�����߶�
int RandBlock::renew_block_count = 1;		// �ڿ���¼���
int RandBlock::num_showing_block = 0;		// ��ǰ��ʾ�ڿ���Ŀ
vector<int> RandBlock::rand_index = {0};	// �ڿ�������

/**
* @brief ���ӹ��캯��
*/
Particle::Particle()
{
	vX = 0;
	vY = 0;
	XAm = rand() % XAm_range + XAm_min;
	YAm = rand() % YAm_range + YAm_min;
	cur_x = ori_x = float(rand() % win_wid);
	cur_y = ori_y = float(rand() % win_hei);
	blink_count = 10000 * pi + rand() % 628 / 100;		// Ӧ�����ܹ������ֵ������⣬��ϸԭ��û�ҵ�
	blink_frequency = blink_frequency_max / (rand() % blink_frequency_level + blink_frequency_min);		// ������˸Ƶ��
	show_frequency = rand() % show_frequency_range + show_frequency_min;
	show_count = 0;
	particle_light_offset = 0;

	if (rand() % 10 < 6)
		border = rand() % small_border_range + border_min;
	else
		border = rand() % border_range + border_min;
}

/**
* @brief ����ڿ鹹�캯��
*/
RandBlock::RandBlock()
{
	block_left = rand() % Mosaic_width + Mosaic_left;		// ��������ڿ���߽�
	block_top = rand() % Mosaic_height + Mosaic_top;		// ��������ڿ��ϱ߽�
	width = rand() % block_wid_range + block_wid_min;		// ��������ڿ���
	height = rand() % block_hei_range + block_hei_min;		// ��������ڿ�߶�
	ratio = (rand() % 99) / 100.0;							// ������ɺڰױ���
	blink_count = rand() % 10;								// ������ɳ�ʼֵ
	blink_period = rand() % block_blink_period_range + block_blink_period_min;

	for (int i = 1; i < RandBlock::NUM_ALL_RANDBLOCK; i++)	// ��ʼ��index
		rand_index.push_back(i);
}

/**
* @brief �˵����캯��
* @param <text> <�˵�����>
* @param <text_y> <�˵����ָ߶�>
* @note <�˵�����ֻ�������ת��ת����Ч��������ʱ��û����>
*/
Menu::Menu(const TCHAR* text, int text_y) : text(text), text_y(text_y)
{
	// ����������ʽ
	settextstyle(font_height, 0, _T("Consolas"));
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfQuality = ANTIALIASED_QUALITY;			// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(TRANSPARENT);					// �������ֱ���Ϊ͸��ɫ

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
* @brief ���ֹ��캯��
* @param <gear_base_x> ��������x��������
* @param <gear_base_y> ��������y��������
* @param <ratio> ���ִ�С��������
* @param <gear_rotate_v> ת��
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
* @brief ӫ�����ӹ��캯��
* @param <imgBuffer> �ڴ滺����ָ��
* @param <img> ����ָ��
* @param <win_wid> ������
* @param <win_hei> ������
* @param <particles> Ҫ��ʾ����������
*/
void Particle::show_particle(DWORD* imgBuffer, IMAGE* img, const int& win_wid, const int& win_hei, Particle* particles)
{
	SetWorkingImage(img);
	cleardevice();
	setlinecolor(BLACK);
	// ��ʾ����
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		if ((abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border) == 0)		// ���Ƴ���
		{
			particles[i].show_count++;										// �����ӹ��ΰ뾶Ϊ0ʱ�����г��ּ���
			if ((particles[i].show_count % particles[i].show_frequency))	// ��������ʱ�����֣�������ʱ��particles[i].blink_count���仯
				continue;
			else
				particles[i].show_count = 1;								// ���ּ�����1��ֱ�ӹ���Ļ���������������ʱ�����ֵ�ʱ�����
		}

		particles[i].blink_count += particles[i].blink_frequency;
		int border = (abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border);	// ���ƹ��ΰ뾶���ﵽ��˸Ч��

		COLORREF nowColor = getlinecolor();

		int light = 40 + rand() % (4 * particles[i].border);	// ����������˸
		particles[i].particle_light_offset = light - 40;
		COLORREF stepColor = RGB(light - 15, light - 17, light - 31);

		for (int j = 0; j < border; border--) {					// �����Ƚ���Բ����ƽ���ÿ�һЩ
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

	// �������ӵ�λ��
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

		if ((abs(static_cast<int>(particles[i].border * sin(particles[i].blink_count))) % particles[i].border) == 0)		// �������ӳ��֣�������ΰ뾶Ϊ0����ֻ��������λ�ö�����������
		{
			if ((particles[i].show_count % particles[i].show_frequency))			// ����������ʱ���ó��ֵ�ʱ����Ȼ�ܸ���λ��
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
	myputimage(0, 0, img, 0);	// ������Ⱦ����
}

/**
* @brief ��ʾ����ڿ�
* @param <randblocks> Ҫ��ʾ���ڿ�����
*/
void RandBlock::show_randblock(RandBlock* randblocks)
{
	if (!(renew_block_count % renew_block_period))			// ����͸���һ���������
	{
		random_shuffle(rand_index.begin(), rand_index.end());  // �������˳��
		num_showing_block = rand() % 5 + 7;

		if (!(renew_block_count % (20 * renew_block_period)))
			num_showing_block = rand() % 20 + 60;
	}

	renew_block_count++;

	if (!(renew_block_count % 3))		// ǿ�а����ڳ�3��΢��������
		for (int i = 0; i < num_showing_block; i++)
		{
			randblocks[rand_index[i]].blink_count++;

			if (!(randblocks[rand_index[i]].blink_count % randblocks[rand_index[i]].blink_period))		// ������˸��count����Ͳ�����
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
* @brief ��ʾ�˵�����
* @param <win_wid> ������
* @param <win_hei> ������
*/
void Menu::show_text(const int& win_wid, const int& win_hei) const
{	
	int light = 255 * text_loop_count / tot_loop;
	settextcolor(RGB(light, light, light));
	outtextxy(cur_text_x, text_y, cur_text);
}

/**
* @brief ��ʾ�˵�ѩ������
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
* @brief ��ʾ�˵������»���
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
* @brief ����ת����Ч������
*/
void Menu::text_transfer_in()
{
	if (this->cur_char_index <= this->num_of_char + 1)	// �Ƿ��������
	{
		this->cur_text[this->cur_char_index + 1] = '\0';
		for (int i = 0; i <= this->cur_char_index; i++)
		{
			this->cur_text[i] = this->text[i];
			this->cur_text_x = (win_wid - textwidth(this->cur_text)) / 2;
		}
		this->cur_char_index++;
	}
	if (this->text_loop_count < this->tot_loop)	// �Ƿ��������loop_count
		this->text_loop_count++;
}

/**
* @brief ����ת����Ч������
*/
void Menu::text_transfer_out()
{
	if (this->text_loop_count > 0)
		this->text_loop_count--;
}

/**
* @brief �»���ת����Ч������
*/
void Menu::underline_transfer_in()
{
	if (this->underline_loop_count < this->tot_loop)	// �Ƿ��������loop_count
		this->underline_loop_count++;
}

/**
* @brief �»���ת����Ч������
*/
void Menu::underline_transfer_out()
{
	if (this->underline_loop_count > 0)
		this->underline_loop_count--;
}

/**
* @brief �˵�ת����Ч�ӿ�
*/
void Menu::transfer_interface(Menu* menu, const int& win_wid, const int& win_hei, char ch)
{
	if (ch == 0x0D || (Menu::show_menu_count == 0 && ch))
		Menu::JUMP_FLAG = true;
		
	Menu* text_obj_ptr;
	
	if (Menu::show_menu_count == 0)
	{
		text_obj_ptr = &menu[0];
		if (!Menu::JUMP_FLAG)				// ��û���յ���ת����
		{
			text_obj_ptr->text_transfer_in();
			text_obj_ptr->underline_transfer_in();
			text_obj_ptr->show_snowflake();	// ����ѩ��
			text_obj_ptr->show_text(win_wid, win_hei);	// �����ı�
			text_obj_ptr->show_underline();	// �����»���
		}
		else
		{
			text_obj_ptr->text_transfer_out();
			text_obj_ptr->underline_transfer_out();
			text_obj_ptr->show_snowflake();	// ����ѩ��
			text_obj_ptr->show_text(win_wid, win_hei);	// �����ı�
			text_obj_ptr->show_underline();	// �����»���

			if (text_obj_ptr->underline_loop_count == 0)
			{
				Menu::show_menu_count++;	// ��ת����Ч��ɺ�ת����һ�˵�
				Menu::JUMP_FLAG = false;	// ��ת����Ч��ɺ���ת��־��0
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
				text_obj_ptr->show_text(win_wid, win_hei);	// �����ı�

				if (i == now_pointed)		// �Ե�ǰѡ����������ѩ�����»���
				{
					if (now_pointed != ever_pointed)	// ���ѡ������Ҫ�����仯
					{
						text_obj_ptr = &menu[ever_pointed];
						text_obj_ptr->underline_transfer_out();
						text_obj_ptr->show_snowflake();	// ����ѩ��
						text_obj_ptr->show_underline();	// �����»���
						if (text_obj_ptr->underline_loop_count == 0)
							ever_pointed = now_pointed;
					}
					else
					{
						text_obj_ptr->underline_transfer_in();
						text_obj_ptr->show_snowflake();	// ����ѩ��
						text_obj_ptr->show_underline();	// �����»���
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
				text_obj_ptr->show_text(win_wid, win_hei);	// �����ı�

				if (i == now_pointed)
				{
					text_obj_ptr->underline_transfer_out();
					text_obj_ptr->show_snowflake();	// ����ѩ��
					text_obj_ptr->show_underline();	// �����»���
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
			text_obj_ptr->show_snowflake();	// ����ѩ��
			text_obj_ptr->show_text(win_wid, win_hei);	// �����ı�
			text_obj_ptr->show_underline();	// �����»���
		
		if (text_obj_ptr->underline_loop_count == text_obj_ptr->tot_loop &&
			text_obj_ptr->cur_char_index == text_obj_ptr->num_of_char + 1)
			IS_QUIT_MUSIC = true;	// �����˳�����
	}
}

/**
* @brief ��ʾ����
*/
void Gear::show_gear() const
{
	static float delta_angle = 0;

	setfillcolor(RGB(190, 190, 172));
	setlinecolor(RGB(190, 190, 172));

	// ������
	circle(static_cast<int>(gear_base_x), static_cast<int>(gear_base_y), static_cast<int>(gear_heart_radius1));

	// ������
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

	// ������
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
* @brief �˵�ѩ������������ɺ���
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
* @brief �»�������ѩ�����ƫ�����ɺ���
* @param <count_step> <���β��������������ڿ���>
* @param <init_offset> <�»�������ѩ�����ƫ�ƻ�����>
*/
int Menu::offset_gen(int count_step, int init_offset) const
{
	static unsigned int count = 0;
	count += count_step;
	return int((rand() % 100) * sin(count / 100)) + init_offset;
}

/**
* @brief �˵�ѩ���������ɺ���
* @param <count_step> <���β��������������ڿ���>
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
* @brief �˵�ѩ��������ɺ���
* @param <count_step> <���β��������������ڿ���>
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
* @brief ��ʼ�����ܿ��ƺ���
*/
void starting()
{
	initgraph(GRAPH_WIDTH,GRAPH_HEIGHT);

	music().open_music(_T("sounds/nonsense.mp3"));
	music().play_music();

	thread t1(running);	// ������Ч���ŵ����߳���

	while (true)
	{
		Sleep(100);
		if (IS_QUIT_MUSIC)
		{
			music().pause_music();
			music().quit_music();	// �˳�����
			IS_QUIT_THREAD = true;	// �˳�����Ч���߳�
			t1.join();
			setrop2(R2_COPYPEN);
			EndBatchDraw();			// ������������
			break;
		}
	}
}

/**
* @brief ��ʼ������Ч���ƺ���
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
		
		putimage(0, 0, &bk_img);						// ���ñ���ͼ
		Menu::transfer_interface(menu, win_wid, win_hei, ch);	// �˵�ת���ӿ�
		Particle::show_particle(imgBuffer, &img, win_wid, win_hei, particles);	// ������Ⱦ����
		RandBlock::show_randblock(randblocks);	// �������������	
		gear.show_gear();				// ���ó���

		loopTime2 = clock();
		time_count = static_cast<int>(loopTime2 - loopTime1);
		Sleep(sleep_time - time_count > 0 ? sleep_time - time_count : 0);	// �����ʱ����sleep_time��ǿ������sleep_time�������ֱ�ӹ�

		FlushBatchDraw();

		ch = '\0';

		if (IS_QUIT_THREAD)
			break;
	}
}