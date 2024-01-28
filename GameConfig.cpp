#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>

using namespace std;

#include "gameConfig.h"


// Colors for the game pieces
const int GameConfig::COLORS_ARRAY[] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, 96, 176, 224, 95, 23, 111, 143, 48,120 };
const int GameConfig::NUM_OF_COLORS = sizeof(COLORS_ARRAY) / sizeof(int);

//This function gets the coord for x and y
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//This function cleans the screen
void clrscr()
{
	system("cls");
}

