#include "TetrisGame.h"
//This function initilizes the boards for the two players and initilises the boolian for if the game has already started
void TetrisGame::initNewGame()
{
	boardOne.init(GameConfig::MIN_X_BOARD1, gameColor);
	boardTwo.init(GameConfig::MIN_X_BOARD2, gameColor);
	newGame = true;
}
//This function is running the game
void TetrisGame::start()
{
	newGame = true;															//A new game in the beginning
	gameColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;		//default is black background
	int choice = 0;															//Choice is getting the player's choice of display 
	while (choice != GameConfig::EXIT)										//Checking if the user chose to exit the game
	{
		displayMenu();														//Prints the menu
		cin >> choice;														//Get the user choice
		clrscr();															//Clean screen	
		handleMenuChoice(choice);											//Checking the players choice
	}
}
//This function is printing the menu on screen
void TetrisGame::displayMenu()
{
	cout << "===== Menu =====" << endl;
	cout << "(1) Start a new game" << endl;
	if (!newGame)															//Prints option 2 onlt if the game already started and been paused
	{
		cout << "(2) Continue a paused game" << endl;
	}
	cout << "(3) Game color options";
	if (gameColor == GameConfig::BLACK) {
		cout << " (Current game color: Black)" << endl;
	}
	else {
		cout << " (Current game color: ColorFul)" << endl;
	}
	cout << "(8) Display instructions and keys" << endl;
	cout << "(9) Exit" << endl;
	cout << "================" << endl;
}
//This function gets the choice of the user and plays accordingly
void TetrisGame::handleMenuChoice(int choice)
{
	switch (choice) {
	case GameConfig::START_NEW_GAME:
		// Start a new game
		clrscr();
		initNewGame();
		runGame();
		break;

	case GameConfig::CONTINUE:
		// Continue a paused game 
		clrscr();
		boardOne.drawBorder();
		boardTwo.drawBorder();
		boardOne.PrintNewBoard();
		boardTwo.PrintNewBoard();
		runGame();
		break;

	case GameConfig::COLORS:
		int choice;
		cout << "Press 1 for colors and 2 for non-colored game: ";
		cin >> choice;
		if (choice == WITH_COLORS)
		{
			gameColor = COLORFUL;
			boardOne.setColor(COLORFUL);
			boardTwo.setColor(COLORFUL);
		}
		else //chose 2
		{
			gameColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;			//Black background
			boardOne.setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			boardTwo.setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		clrscr();
		break;

	case GameConfig::INSTRUCTIONS:
		// Display instructions and keys
		displayInstructions();
		clrscr();
		break;

	case GameConfig::EXIT:
		// Exit
		cout << "Goodbye" << endl;
		break;
	}
}

//This function is printing the instruction of the game and the keys for each player
void TetrisGame::displayInstructions() {
	cout << "=== Tetris Instructions ===" << endl;
	cout << "Right Player Controls:" << endl;
	cout << "-----------------" << endl;
	cout << "LEFT\t\t\t\tj or J" << endl;
	cout << "RIGHT\t\t\t\tl (small L) or L" << endl;
	cout << "ROTATE clockwise\t\tk or K" << endl;
	cout << "ROTATE counterclockwise\t\ti or I (uppercase i)" << endl;
	cout << "DROP\t\t\t\tm or M" << endl;
	cout << "-----------------" << endl;
	cout << "Left Player Controls:" << endl;
	cout << "-----------------" << endl;
	cout << "LEFT\t\t\t\ta or A" << endl;
	cout << "RIGHT\t\t\t\td or D" << endl;
	cout << "ROTATE clockwise\t\ts or S" << endl;
	cout << "ROTATE counterclockwise\t\tw or W" << endl;
	cout << "DROP\t\t\t\tx or X" << endl;
	cout << "-----------------" << endl;

	//to exit instruction 
	cout << "PRESS ANY KEY TO GO BACK TO MENU";

	_getch();
}

//This function is managing the game
void TetrisGame::runGame()
{
	newGame = false;															 //Because game has started now
	while (boardOne.getDidLose() == FALSE && boardTwo.getDidLose() == FALSE)
	{
		for (int i = 0; i < NUM_OF_ITERATIONS; i++)
		{
			char keyPressed = shape::MOVE_DOWN;									//Initialize direction, move down by default
			if (_kbhit())														//Check if key is pressed
			{
				keyPressed = _getch();
				if (keyPressed == GameConfig::ESC)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //Remove background color for point and turn to black
					clrscr();
					return;
				}
				keyPressed = toupper(keyPressed);																					//Change to uppercase letters the keypressed
			}
			//Checking if the first player pressed any of his keys and if so moving curr piece
			if (keyPressed == GameConfig::eKeys_left::LEFT || keyPressed == GameConfig::eKeys_left::RIGHT ||
				keyPressed == GameConfig::eKeys_left::ROTATE_clockwise || keyPressed == GameConfig::eKeys_left::ROTATE_counter ||
				keyPressed == GameConfig::eKeys_left::DROP)
			{
				boardOne.move(keyPressed);
				boardTwo.move(shape::MOVE_DOWN);									//The other board just moving piece down
			}
			//Checking if the second player pressed any of his keys and if so moving curr piece 
			else if (keyPressed == GameConfig::eKeys_right::LEFT || keyPressed == GameConfig::eKeys_right::RIGHT ||
				keyPressed == GameConfig::eKeys_right::ROTATE_clockwise || keyPressed == GameConfig::eKeys_right::ROTATE_counter ||
				keyPressed == GameConfig::eKeys_right::DROP)
			{
				boardTwo.move(keyPressed);
				boardOne.move(shape::MOVE_DOWN);									//The other board just moving piece down
			}
			else
			{
				//Move both board pieces down in every round
				boardOne.move(shape::MOVE_DOWN);
				boardTwo.move(shape::MOVE_DOWN);
			}
			Sleep(GameConfig::SLEEP_TIME);
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		Sleep(GameConfig::SLEEP_TIME);

	}
	//The game is over
	clrscr();
	if (boardOne.getDidLose())									//Player 1 lost
		cout << "PLAYER " << PLAYER2 << " WON!" << endl;
	else														//Player 2 lost
		cout << "PLAYER " << PLAYER1 << " WON!" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);		//Remove background color for point

	cout << "GAME OVER!" << endl;
	Sleep(GameConfig::LONG_SLEEP_TIME);
	clrscr();

	//Getting all the leftover chars 
	while (_kbhit()) {
		_getch();
	}
	newGame = true;								//Initilises the indicator, the current game has ended
}
