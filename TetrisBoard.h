#ifndef __TETRISBOARD_H
#define __TETRISBOARD

#include "shape.h"

class shape;
class TetrisBoard
{
public:
	static constexpr int GAME_WIDTH = 12;									//12 for the frame
	static constexpr int GAME_HEIGHT = 18;									//18 for the frame
	static constexpr int NUM_OF_SHAPES = 7;									//There are 7 possible shapes 
	static constexpr int MID_WIDTH = 6;										//The middle of the board 
	static constexpr int START_HEIGHT = 1;									//The beginning height of every piece



	void drawBorder();														//Drawing the board
	void placePieceOnBoard();												//Putting the coords in the matrix
	void deletePieceOnBoard(shape s);										//Removing the points from the matrix
	int getCoordInBoard(Point p);											//Getting the coords
	bool isPointOnBoard(Point p);											//Checking if point on board
	bool checkMovePieceDown(shape s);										//Checking if can move down
	bool checkMovePieceRightAndLeft(shape s);								//Checking if can move left right
	void checkFullLinesOnBoard();											//Checking if line is full
	bool getDidLose();														//Getting the player status in game
	bool checkIfDidLose();													//Checking if a player lost
	void removeLine(int line);												//Remving the line from board and screen
	void moveLinesDown(int line);											//Moving boards lines down
	void deleteLineFromScreen(int line);									//Delete the line from the screen
	void PrintNewBoard();													//Print the new board updated
	shape giveMeShape();													//Get new shape
	bool isPieceMovedDown();												//Check if piece moved down
	void movePieceLeftRight(char keyPressed);								//Moving the shape left or right
	void move(char keyPressed);												//Moving the shape
	void init(int minX, int color);											//Initilising the board
	void clearBoard();														//Clear the matrix
	void setColor(int color);												//Set a color for the pieces



private:
	int board[GAME_HEIGHT][GAME_WIDTH];										//The matrix
	int color;
	int minX;																//Where the board begins
	shape currShape;														//Current shape on board
	bool didLose;															//Chcek for if player lost if shapes reach the top
	int playerNum;															// 1 or 2
};

#endif

