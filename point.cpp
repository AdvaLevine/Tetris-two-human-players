#include <iostream>
#include <Windows.h>

#include "point.h"
#include "gameConfig.h"
#include "TetrisBoard.h"


using namespace std;

//This function is initilising the point data members
void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;

}
//This function is drawing the point
void Point::draw(char ch, int backcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor); //remove backgroung color for point
	gotoxy(x, y);
	cout << ch;
}
//This function is moving the pointleft or right
void Point::movePointLeftfOrRight(char direction)
{
	int newX = this->getX();

	if(direction == GameConfig::eKeys_left::LEFT)//LEFT
		newX = newX - 1;
	else if(direction == GameConfig::eKeys_left::RIGHT) //RIGHT
		newX = newX + 1;

	this->set(newX, this->getY());
}
//This function is moving the point down
void Point::movePointDown() {
	int  newY = this->getY() + 1;
	this->set(this->getX(), newY);
}
