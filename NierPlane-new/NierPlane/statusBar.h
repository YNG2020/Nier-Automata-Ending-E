#pragma once

class statusBar
{
public:
	statusBar();
	statusBar(int _x, int _y);
	~statusBar();
	void setXlen(int _xlen) { xlen = _xlen; }
	void setYlen(int _ylen) { ylen = _ylen; }
	int getXlen() { return xlen; }
	int getYlen() { return ylen; }

private:
	int xlen = 0;
	int ylen = 0;
	
};

