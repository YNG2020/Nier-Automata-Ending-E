#pragma once
#include "MusicMCI.h"
#include "common.h"

class MyMusic
{

private:
	MusicMCI musicmci;

	int MUSIC_VOLUMN;
public:
	MyMusic(int _volumn = 500);

	bool turn_up_volumn(int step = 50);

	bool turn_down_volumn(int step = 50);

	void open_music(LPCWSTR song_name);

	void play_music();

	void pause_music();

	void quit_music();

};
