#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:

	enum { ESC = 27, EXIT = 9, START_NEW_GAME = 1, CONTINUE = 2, COLORS = 3, INSTRUCTIONS = 8, BLACK=7};			//The keys for escape, start, instuctions and colors
	enum class eKeys_left { LEFT = 'A', RIGHT = 'D', ROTATE_clockwise = 'S', ROTATE_counter = 'W', DROP = 'X' };	//The left player key
	enum class eKeys_right { LEFT = 'J', RIGHT = 'L', ROTATE_clockwise = 'K', ROTATE_counter = 'I', DROP = 'M' };	//The right player key
	enum{SLEEP_TIME=50, LONG_SLEEP_TIME=1500,AVG_SLEEP =200};														//Sleep time

	// Static member function to assign a character from eKeys_left to a char
	static char& assignFromEnum(char& dest, const eKeys_left& src)
	{
		dest = static_cast<char>(src);
		return dest;
	}
	//Overloading two functions for the comparison of the keypressed 
	friend bool operator==(const char key, const eKeys_left& rhs) {				//Left ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}
	friend bool operator==(const char key, const eKeys_right& rhs) {			//Right ekeys
		return static_cast<int>(key) == static_cast<int>(rhs);
	}

	//The proportions where the boards start
	static constexpr int MIN_X_BOARD2 = 31;					//The second board beginning x point
	static constexpr int MIN_X_BOARD1 = 1;					//The first board beginning x point
	static constexpr int MIN_Y = 1;							//Both boards beginning y point

	// Colors for the game pieces
	static const int COLORS_ARRAY[];
	static const int NUM_OF_COLORS;
};

void gotoxy(int, int);
void clrscr();

#endif
