#pragma once
#include<graphics.h>
#include<thread>
#include"common.h"
#include"UI.h"

using namespace std;
static const int num_dialogue = 100;
static const TCHAR* dialogue[num_dialogue];
static int list2 = 0;
static const int num_text = 100;
static const TCHAR* ending_text[num_text];
static int list1 = 0;
static int y_element[num_text] = { 0 };


class ending {
public:
	static int gameMain();
};


