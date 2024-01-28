#ifndef __POINT_H
#define __POINT_H

#include "gameConfig.h"

class Point
{
	int x;
	int y;
public:
	void set(int x, int y);
	void draw(char ch, int backcolor);
	void movePointLeftfOrRight(char direction);
	int getX() { return x; };
	int getY() { return y; };
	void movePointDown();
};

#endif