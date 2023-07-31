#include "MyMusic.h"

MyMusic::MyMusic(int _volumn) {
	MUSIC_VOLUMN = _volumn;
}

bool MyMusic::turn_up_volumn(int step) {
	if (MUSIC_VOLUMN == 1000)return false;
	MUSIC_VOLUMN = clamp(MUSIC_VOLUMN + step, 0, 1000);
	musicmci.setVolume(MUSIC_VOLUMN);
	return true;
}

bool MyMusic::turn_down_volumn(int step) {
	if (MUSIC_VOLUMN == 0)return false;
	MUSIC_VOLUMN = clamp(MUSIC_VOLUMN - step, 0, 1000);
	musicmci.setVolume(MUSIC_VOLUMN);
	return true;
}

void MyMusic::open_music(LPCWSTR song_name)
{
	// ������
	musicmci.open(song_name);

	// ��������
	musicmci.setVolume(700);
}

void MyMusic::play_music()
{
	// ��������
	musicmci.play();
}

void MyMusic::pause_music()
{
	// ������ͣ��������
	for (int i = MUSIC_VOLUMN - 1; i >= 0; i--)
	{
		musicmci.setVolume(i);
		Sleep(1);
	}
	musicmci.pause();

	// �����������ָ�
	musicmci.setVolume(MUSIC_VOLUMN);
}

void MyMusic::quit_music()
{

	//// ֹͣ���Ų��ر�����
	//for (int i = MUSIC_VOLUMN - 1; i >= 0; i--)
	//{
	//	musicmci.setVolume(i);
	//	Sleep(2);
	//}

	musicmci.close();
}