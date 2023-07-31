#pragma once
#include "starting.h"
#include "surprise.h"
#include "common.h"

int main()
{
	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);

	/// 设置窗口位置
	SetWindowPos(GetHWnd(), NULL, 0, 0, GRAPH_WIDTH, GRAPH_HEIGHT, 0);
	while (true) {
		// 开始界面的实现
		starting();

		// 结尾小飞机的实现
		surprise();

	}
	closegraph(); 
	exit(1);
	return 0;
}