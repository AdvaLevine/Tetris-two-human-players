#include <Windows.h> // for Sleep and colors

#include "TetrisBoard.h"
#include "shape.h"

//This function is converting the char to the left ekeys 
char shape::convert(char direction)
{
	if (direction == GameConfig::eKeys_right::LEFT)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::LEFT);
	if (direction == GameConfig::eKeys_right::RIGHT)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::RIGHT);
	if (direction == GameConfig::eKeys_right::ROTATE_clockwise)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::ROTATE_clockwise);
	if (direction == GameConfig::eKeys_right::ROTATE_counter)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::ROTATE_counter);
	if (direction == GameConfig::eKeys_right::DROP)
		GameConfig::assignFromEnum(direction, GameConfig::eKeys_left::DROP);

	return direction;
}
//This function is moving the shape
void shape::move(char direction)
{
	direction = convert(direction);								//Converting the left ekeys
	if (direction == GameConfig::eKeys_left::ROTATE_counter)
	{
		if (shapeNumber != 1)										//Not a square
			rotatePieceCounter();
	}
	if (direction == GameConfig::eKeys_left::ROTATE_clockwise)
	{
		if (shapeNumber != 1)										//Not a square
			rotatePieceClockwise();
	}
	if (direction == GameConfig::eKeys_left::LEFT || direction == GameConfig::eKeys_left::RIGHT)			//If its left or right then go to move in point
	{
		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			piece[i].movePointLeftfOrRight(direction);
		}
	}

	if (direction == GameConfig::eKeys_left::DROP)															//If drop then move down an extra time
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)
		{
			piece[i].movePointDown();
		}
	}
}
//This function is moving the shape conter clockwise
void shape::rotatePieceCounter()
{
	// Assuming the rotation is around the first point (piece[0])
	for (int i = 1; i < shape::NUM_OF_POINTS; ++i) {
		int relativeX = piece[i].getX() - piece[0].getX();
		int relativeY = piece[i].getY() - piece[0].getY();

		// Rotate the point relative to the first point
		piece[i].set(piece[0].getX() + relativeY, piece[0].getY() - relativeX);
	}
}
//This function is moving the shape clockwise
void shape::rotatePieceClockwise()
{
	for (int i = 1; i < shape::NUM_OF_POINTS; ++i) {
		int relativeX = piece[i].getX() - piece[0].getX();
		int relativeY = piece[i].getY() - piece[0].getY();

		piece[i].set(piece[0].getX() - relativeY, piece[0].getY() + relativeX);
	}
}
//This function is drawing the shape 
void shape::drawShape(char ch, int color)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		piece[i].draw(ch, color);
	}
}
//This function is initilising the shape 
void shape::init(int shapeNumber, char ch, int color)
{
	this->ch = ch;
	this->backgroundcolor = color;
	this->shapeNumber = shapeNumber;
}
//This function is the shape structure
void shape::setShape(int minX)
{
	switch (shapeNumber)
	{
	case 1: //Squrae
		piece[0].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX + 1, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX + 1, TetrisBoard::START_HEIGHT + 1);
		break;

	case 2: //Line 
		piece[0].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 3);
		break;

	case 3: //Half + upsidedown
		piece[0].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX + 1, TetrisBoard::START_HEIGHT);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		break;

	case 4: //Like hebrew ð
		piece[0].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT + 2);

		break;

	case 5: //Upposite hebrew ð
		piece[0].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT + 1);
		piece[2].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT + 2);
		piece[3].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 2);

		break;

	case 6: //Egypian hands right
		piece[0].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT + 1);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX + 1, TetrisBoard::START_HEIGHT);

		break;
	case 7: //Egypian hands left
		piece[0].set(TetrisBoard::MID_WIDTH + minX - 1, TetrisBoard::START_HEIGHT);
		piece[1].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT);
		piece[2].set(TetrisBoard::MID_WIDTH + minX, TetrisBoard::START_HEIGHT + 1);
		piece[3].set(TetrisBoard::MID_WIDTH + minX + 1, TetrisBoard::START_HEIGHT + 1);

		break;
	}
}
//This function is for getting the shape
Point* shape::getShape()
{
	return piece;
}


