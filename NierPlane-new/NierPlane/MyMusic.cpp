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
	// ´ò¿ªÒôÀÖ
	musicmci.open(song_name);

	// ÉèÖÃÒôÁ¿
	musicmci.setVolume(700);
}

void MyMusic::play_music()
{
	// ²¥·ÅÒôÀÖ
	musicmci.play();
}

void MyMusic::pause_music()
{
	// »ºÂýÔÝÍ£²¥·ÅÒôÀÖ
	for (int i = MUSIC_VOLUMN - 1; i >= 0; i--)
	{
		musicmci.setVolume(i);
		Sleep(1);
	}
	musicmci.pause();

	// °ÑÒôÀÖÒôÁ¿»Ö¸´
	musicmci.setVolume(MUSIC_VOLUMN);
}

void MyMusic::quit_music()
{

	//// Í£Ö¹²¥·Å²¢¹Ø±ÕÒôÀÖ
	//for (int i = MUSIC_VOLUMN - 1; i >= 0; i--)
	//{
	//	musicmci.setVolume(i);
	//	Sleep(2);
	//}

	musicmci.close();
}