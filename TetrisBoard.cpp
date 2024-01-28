#include "TetrisBoard.h"
#include <iostream>
#include "point.h"
#include <Windows.h>
#include <conio.h> // for kbhit+getch
using namespace std;



//This function is for drawing both players boards
void TetrisBoard::drawBorder()
{
	for (int col = minX; col < minX + TetrisBoard::GAME_WIDTH; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, TetrisBoard::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::MIN_Y + TetrisBoard::GAME_HEIGHT; row++)
	{
		gotoxy(minX - 1, row);
		cout << "|";

		gotoxy(TetrisBoard::GAME_WIDTH + minX, row);
		cout << "|";
	}
}


//This function is creating a new shape 
shape TetrisBoard::giveMeShape()
{
	shape s;
	s.init(rand() % (TetrisBoard::NUM_OF_SHAPES)+1, '#', color);									//Updating random shape and the color
	s.setShape(minX);
	currShape = s;
	this->placePieceOnBoard();																		//Putting shape in the matrix
	if(color==GameConfig::BLACK)
		currShape.drawShape('#', color);																//Drawing the shape on screen
	else
	{
		int i = rand() % GameConfig::NUM_OF_COLORS;
		color = GameConfig::COLORS_ARRAY[(i % (GameConfig::NUM_OF_COLORS - 1)) + 1];
		currShape.drawShape('#', color);
	}
	Sleep(GameConfig::SLEEP_TIME);
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);					//Delete shape from screen
	this->deletePieceOnBoard(currShape);															//Delete shape from matrix

	return s;
}

//This function gets a shape, checks if its possible to move it down on the screen and on the matrix and if so it moves it
bool TetrisBoard::isPieceMovedDown()
{
	currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);					//Delete shape from screen
	this->deletePieceOnBoard(currShape);															//Delete shape from matrix
	bool isShapeCanMove = true;
	shape tempShapeDown = currShape;																//Temp shape to check if shape can move
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)													//Moving the temp shape 
	{
		tempShapeDown.getShape()[i].movePointDown();
	}
	if (this->checkMovePieceDown(tempShapeDown))													//Checking if temp shape is in an approved place if so we move the curr shape
	{
		for (int i = 0; i < shape::NUM_OF_POINTS; i++)												//Moving curr shape
		{
			currShape.getShape()[i].movePointDown();
		}
		this->placePieceOnBoard();																	//Putting shape in the matrix
		currShape.drawShape('#', color);															//Drawing the shape on screen
		Sleep(GameConfig::AVG_SLEEP);

	}
	else
	{
		currShape.drawShape('#', color);															//Keep the shape where it was before trying to move
		this->placePieceOnBoard();																	//Putting shape in the matrix
		isShapeCanMove = false;																		//Cant move anymore
		this->checkFullLinesOnBoard();																//checking if line is full to delete
		if (checkIfDidLose() == TRUE)																//Checking if one player got to the last line
			didLose = true;
	}
	return isShapeCanMove;
}
//This function is returning the data member did lose
bool TetrisBoard::getDidLose()
{
	return didLose;
}
//This function is checking if a player has any pieces in the first line of the board meaning if he lost
bool TetrisBoard::checkIfDidLose()
{
	for (int col = 0; col < GAME_WIDTH; col++)
	{
		if (board[0][col] == 1)
			return true;
	}
	return false;
}
//This function is checking if the shape can move left, right or rotate if so it moves it
void TetrisBoard::movePieceLeftRight(char keyPressed) {

	shape tempShapeLeftRight;
	tempShapeLeftRight = currShape;														//Creating a temp shape for checking if curr shape can move
	tempShapeLeftRight.move(keyPressed);												//right or left or rotate
	if (this->checkMovePieceRightAndLeft(tempShapeLeftRight))
	{
		currShape.drawShape(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);	//Delete shape from screen
		this->deletePieceOnBoard(currShape);											//Remove shape from matrix
		Sleep(GameConfig::AVG_SLEEP);
		currShape.move(keyPressed);														//Moving the curr shape
		currShape.drawShape('#', color);												//Drawing currshape on screen
		this->placePieceOnBoard();														//putting the coordinates in matrix
	}
}
//This function is for moving the pieces on the board
void TetrisBoard::move(char keyPressed)
{
	if (this->isPieceMovedDown())																		//Moving down
	{
		if (keyPressed == GameConfig::eKeys_right::DROP || keyPressed == GameConfig::eKeys_left::DROP)	//If the key pressed is drop
			this->isPieceMovedDown();
		else if (keyPressed != 0)																		//Any other key pressed
			movePieceLeftRight(keyPressed);
	}
	else
		this->giveMeShape();																			//New shape

}
//This function is for checking if the shape can move down
bool TetrisBoard::checkMovePieceDown(shape s)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if ((this->getCoordInBoard(tmp) != 0) || (tmp.getY() >= GAME_HEIGHT + 1))
			return false;
	}
	return true;
}
//This function is for checking if the shape can move right or left or rotate
bool TetrisBoard::checkMovePieceRightAndLeft(shape s)
{
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		Point tmp = s.getShape()[i];
		if (this->isPointOnBoard(tmp) == false)
			return false;
	}
	return true;
}
//This function is for updating the matrix (add piece)
void TetrisBoard::placePieceOnBoard()
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = currShape.getShape()[i].getX() - minX;					//The shapes are printed 1 forward becuase of the boarder, so we update the board matrix correctly
		tempY = currShape.getShape()[i].getY() - START_HEIGHT;
		this->board[tempY][tempX] = 1;
	}
}
//This function is for is for updating the matrix (remove piece)
void TetrisBoard::deletePieceOnBoard(shape s)
{
	int tempX, tempY;
	for (int i = 0; i < shape::NUM_OF_POINTS; i++)
	{
		tempX = s.getShape()[i].getX() - minX;
		tempY = s.getShape()[i].getY() - START_HEIGHT;
		this->board[tempY][tempX] = 0;
	}
}
//This function is for is for getting the shape coordinates
int TetrisBoard::getCoordInBoard(Point p)
{
	int tempX, tempY;
	tempX = p.getX() - minX;
	tempY = p.getY() - START_HEIGHT;
	return this->board[tempY][tempX];
}
//This function is for checking if the point is on the board
bool TetrisBoard::isPointOnBoard(Point p)
{
	if ((p.getX() >= GAME_WIDTH + minX) || (p.getX() <= minX - 1) || (p.getY() >= GAME_HEIGHT))
		return false;
	return true;
}
//This function is for is for checking if theres a full line to be removed
void TetrisBoard::checkFullLinesOnBoard()
{
	for (int rows = TetrisBoard::GAME_HEIGHT - 1; rows >= 0; rows--)	//Here we look for a full line
	{
		bool isFull = true;
		for (int cols = 0; cols < (TetrisBoard::GAME_WIDTH) && (isFull); cols++)
		{
			if (this->board[rows][cols] == 0)
				isFull = false;
		}

		if (isFull)
		{
			removeLine(rows);											//Remove line
			this->deleteLineFromScreen(rows);							//Remove line from the screen
			moveLinesDown(rows);										//Moving all lines down
			PrintNewBoard();											//Prints the updated board
			rows++;														//To check for maybe if the same row is full again
		}
	}
}
//This function is for deleteing the line from the screen
void TetrisBoard::deleteLineFromScreen(int line)
{
	for (int x = minX; x < TetrisBoard::GAME_WIDTH + minX; x++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		gotoxy(x, line + 1);
		cout << ' ';
	}
}
//This function is for is for updating the matrix (moving pieces down)
void TetrisBoard::moveLinesDown(int line)
{
	for (int row = line; row >= 1; row--)
	{
		for (int col = 0; col < TetrisBoard::GAME_WIDTH; col++)
		{
			this->board[row][col] = this->board[row - 1][col];
		}
	}
}
//This function is for is for updating the matrix (remove line)
void TetrisBoard::removeLine(int line)
{

	for (int row = 0; row < TetrisBoard::GAME_WIDTH; row++)
	{
		board[line][row] = 0;
	}
}
//This function is printing the new board on the screen
void TetrisBoard::PrintNewBoard()
{
	for (int row = 0; row < TetrisBoard::GAME_HEIGHT; row++)										//Starts from 0 because we go over the matrix
	{
		for (int col = 0; col < (TetrisBoard::GAME_WIDTH); col++)
		{
			if (this->board[row][col] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);					//Change the background of the shape
				gotoxy(col + minX, row + START_HEIGHT);												//Because we print the board from 1,1
				cout << '#';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				gotoxy(col + minX, row + START_HEIGHT);												//Because we print the board from 1,1
				cout << ' ';
			}
		}
	}
}
//This function is initilising the board for each player
void TetrisBoard::init(int minX, int color)
{
	this->clearBoard();
	this->color = color;
	this->minX = minX;
	this->drawBorder();
	this->currShape = giveMeShape();
	this->didLose = false;
	this->playerNum = playerNum;
}
//This function clears the matrix
void TetrisBoard::clearBoard() {
	std::memset(board, 0, sizeof(board));
}
//This function updates the new color for the pieces
void TetrisBoard::setColor(int color)
{
	this->color = color;
}
