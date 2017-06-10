#include <iostream>
#include <string>
#include <array>
#include <ctime> // Used for pseudo random number generation

using namespace std;

void StartGame(char playerChar, char computerChar);
bool CheckForWin(char playerChar, char computerChar);
void DrawBoard();
void PromptPlayerChoice(char playerChar);
void DoComputerChoice(char playerChar, char computerChar);
bool WinnerExists();
char FindWinner();
bool IsBoardSpotTaken(int r, int c);
bool IsBoardFull();

char board[3][3];
int totalPlayerWins = 0;
int totalTies = 0;
int totalComputerWins = 0;

int main()
{
	// Seed the random number generator with the current time.
	// If the random number generator is not seeded, the rand()
	// function will always use a default seed of 1.
	srand(time(0));

	// Random value between 1 and 2. X will be 1, O will be 2.
	int randNum = (rand() % 2) + 1;

	char playerChar = (randNum == 1) ? 'X' : 'O';
	char computerChar = (randNum == 1) ? 'O' : 'X';

	StartGame(playerChar, computerChar);
	return 0;
}

// Starts a new Tic-Tac-Toe game.
void StartGame(char playerChar, char computerChar)
{
	srand(time(0)); // Change the random seed, so the last game doesn't end up like the next one.
	cout << endl;
	cout << "Stats: " << endl;
	cout << "\tTotal player wins: " << totalPlayerWins << endl;
	cout << "\tTotal ties: " << totalTies << endl;
	cout << "\tTotal computer wins: " << totalComputerWins << endl;
	cout << endl;
	cout << "The computer is " << computerChar << "." << endl;
	cout << "You are " << playerChar << "." << endl;
	cout << endl; // Write a new line just to clean up the screen.

				  // Reset the board each game.
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			board[r][c] = 0;
		}
	}

	while (true)
	{
		DrawBoard();
		cout << endl; // Separate board from choice prompt
		PromptPlayerChoice(playerChar);
		if (CheckForWin(playerChar, computerChar)) break;
		cout << endl; // Separate player choice from computer choice
		DoComputerChoice(playerChar, computerChar);
		if (CheckForWin(playerChar, computerChar)) break;
		cout << endl;
	}
}

// Returns true if user needs to exit
bool CheckForWin(char playerChar, char computerChar)
{
	if (WinnerExists())
	{
		DrawBoard();
		char winner = FindWinner();
		if (winner == 'T')
		{
			cout << "The game was a tie!" << endl;
			totalTies++;
		}
		else if (winner == playerChar)
		{
			cout << "You won the game!" << endl;
			totalPlayerWins++;
		}
		else if (winner == computerChar)
		{
			cout << "The computer won the game!" << endl;
			totalComputerWins++;
		}
		cout << "Play again? (y/n): ";
		string input;
		getline(cin, input);
		if (tolower(input[0]) == 'y')
		{
			StartGame(playerChar, computerChar);
			return true;
		}
		else if (tolower(input[0]) == 'n')
		{
			return true;
		}
	}
	return false;
}

// Prints out the board
void DrawBoard()
{
	// Write columns helper
	cout << "  1 2 3" << endl;
	cout << endl;
	cout << "1 " << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
	cout << "  -----" << endl;
	cout << "2 " << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
	cout << "  -----" << endl;
	cout << "3 " << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
}

// Prompts the player to choose a spot on the board
void PromptPlayerChoice(char playerChar)
{
	bool turnComplete = false;

	cout << "It is your turn." << endl;
	while (!turnComplete)
	{
		cout << "Row: ";
		string sRow;
		getline(cin, sRow);
		int row = stoi(sRow) - 1; // Subtract 1 because a user will choose 1 as the first row instead of 0.

		cout << "Column: ";
		string sCol;
		getline(cin, sCol);
		int col = stoi(sCol) - 1; // Subtract 1 because a user will choose 1 as the first col instead of 0.

		if (row > 2 || row < 0 || (col > 2 || col < 0))
		{
			cout << "The row or column you specified was out of the board range." << endl;
			cout << "Try a choosing a number from 1-3." << endl;
		}
		else if (IsBoardSpotTaken(row, col))
		{
			cout << "That board spot is taken. Try another one." << endl;;
		}
		else
		{
			board[row][col] = playerChar;
			turnComplete = true;
		}
	}
}

// The computer performs the best move.
void DoComputerChoice(char playerChar, char computerChar)
{
	bool hasFinishedTurn = false;
	while (!hasFinishedTurn)
	{
		int row = rand() % 3;
		int col = rand() % 3;

		if (!IsBoardSpotTaken(row, col))
		{
			hasFinishedTurn = true;
			board[row][col] = computerChar;
			// Add one to the row and column because the player
			// most likely does not understand how arrays work
			cout << "The computer chose:" << endl;
			cout << "Row: " << row + 1 << endl;
			cout << "Column: " << col + 1 << endl;
		}
	}
}

// Checks whether a winner exists.
bool WinnerExists()
{
	// N is the default value returned from FindWinner if no winner is found.
	// T(Tie) can be returned from FindWinner
	// X or O can also be returned from FindWinner
	return FindWinner() != 'N';
}

// Finds the winner on the board.
// If no winner exists, returns N.
char FindWinner()
{
	//      0   1   2
	//
	//	0	X | O | O
	//		---------
	//	1	X | X | O
	//		---------
	//	2	O | X | O
	//

	// Check X, then O
	for (int i = 0; i < 2; i++)
	{
		char charToCheck = (i == 0) ? 'X' : 'O';

		// Check rows and columns
		for (int j = 0; j < 3; j++)
		{
			// Check rows
			if (board[j][0] == charToCheck && board[j][1] == charToCheck && board[j][2] == charToCheck)
			{
				return charToCheck;
			}
			// Check columns
			if (board[0][j] == charToCheck && board[1][j] == charToCheck && board[2][j] == charToCheck)
			{
				return charToCheck;
			}
		}

		// Check diagonals
		if (board[0][0] == charToCheck && board[1][1] == charToCheck && board[2][2] == charToCheck)
		{
			return charToCheck;
		}
		else if (board[0][2] == charToCheck && board[1][1] == charToCheck && board[2][0] == charToCheck)
		{
			return charToCheck;
		}
	}
	if (IsBoardFull()) // It must be a tie
	{
		return 'T'; // T for tie
	}

	return 'N'; // N for no winner
}

// Checks whether a spot on the board is taken.
bool IsBoardSpotTaken(int r, int c)
{
	char spot = board[r][c];
	return spot == 'X' || spot == 'O';
}

// Checks whether the whole board has spots filled.
bool IsBoardFull()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (!IsBoardSpotTaken(r, c))
			{
				return false;
			}
		}
	}
	return true;
}

