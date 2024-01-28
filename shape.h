#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"

class shape
{
public:
	void setShape(int minX);
	void init(int shapeNumber, char ch, int color);
	void move(char direction);
	void drawShape(char ch, int color);
	char convert(char direction);
	void rotatePieceClockwise();
	void rotatePieceCounter();
	Point* getShape();

	static constexpr int NUM_OF_POINTS = 4;
	static constexpr int MOVE_DOWN = 0;
private:
	int backgroundcolor;		//Gray or Black
	int shapeNumber;			//between 1-7 
	char ch;					//The shape char
	Point piece[NUM_OF_POINTS];	//Shape is an array or 4 point

};
#endif

