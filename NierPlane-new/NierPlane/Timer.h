#pragma once
#include <time.h>
#include <iostream>
#include "common.h"

class Timer {
	long time_length = 0;
	long pause_time_length = 0;
	clock_t previous_time;
	clock_t pause_start_time;
	bool isPause = false;
	int count = 0;
	int maxCount;
public:

	Timer(long _timeLength) {
		time_length = _timeLength;
		previous_time = clock();
		pause_start_time = clock();
		maxCount = (time_length / MainLoopTime) + (time_length % MainLoopTime == 0 ? 0 : 1);
	}
	bool ifOverTime() {
		if ((clock() - previous_time) - pause_time_length > time_length) {
			return true;
		}
		else return false;
	}
	void updateTime() {
		previous_time = clock();
		pause_time_length = 0;
	}
	void pauseTimer() {

		isPause = true;
		pause_start_time = clock();
	}
	void endPauseTimer() {
		if (!isPause) {
			std::cerr << "Timer _ endPauseTimer ERROR: There is no pause" << std::endl;
			throw isPause;
		}
		isPause = false;
		pause_time_length += static_cast<long>(clock() - pause_start_time);
	}
	long getLengthBetweenPreviousAndNow() {
		return static_cast<long>(clock() - previous_time) - pause_time_length;
	}
	int getCount() {
		return count;
	}
	bool isOverMaxCount() {
		if (count >= maxCount)return true;
		else return false;
	}
	void addCount() {
		count++;
	}
	void resetCount() {
		count = 0;
	}
	bool isOver() {
		return isOverMaxCount() && ifOverTime();
	}
};