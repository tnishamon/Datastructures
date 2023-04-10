/*
 * knightType.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Matthew Noojin
 *
 *      See the header file for more info
 */

#include "knightType.h"
// Our constructor that initializes the size of the board
knightType::knightType(int dim)
{
	// Also sets functions call to 0
	functionsCalled = 0;
	// Pushes vector onto vector for 2D vector
	for(int i = 0; i < dim; i++)
	{
		std::vector<int> temp;

		for(int j = 0; j < dim; j++)
		{
			temp.push_back(0);
		}
		board.push_back(temp);
	}

}
// Checks if the board is full, returns true if it is, false if it isn't
bool knightType::fullBoard()
{
	for(unsigned long int i = 0; i < board.size(); i++)
	{
		for(unsigned long int j = 0; j < board[i].size(); j++)
		{
			if(board[i][j] == 0)
				return false;
		}
	}

	return true;
}
/* Gets available moves the knight can jump to, and the total moves it can make after
 * Takes in our current position to determine where we can jump
 * Returns the potential knight moves in a vector
 */
std::vector<knightType::position> knightType::getAvailableMoves(int r, int c)
{
	// Our vector holding the potential positions of the knight (and total onward moves)
	std::vector<position> knightMoves;

	// The order in which the knight will move from the current position
	int rowMoveOrder[maxKnightMoves] = {-1, -2, -2, -1, 1, 2, 2, 1};
	int colMoveOrder[maxKnightMoves] = {-2, -1, 1, 2, 2, 1, -1, -2};

	// Size to check in bounds
	int rowColSize = board[0].size();

	// Index for knightMoves
	int knightMoveCount = 0;

	// We should only need to check how many moves there are for the knight 8 times
	for(int i = 0; i < maxKnightMoves; i++)
	{
		// Our temp "next" position
		int tempRow = r + rowMoveOrder[i];
		int tempCol = c + colMoveOrder[i];

		// Checks if temp position is valid and if it is an "empty" position
		if(tempRow >= 0 && tempCol >= 0 &&
		   tempRow < rowColSize && tempCol < rowColSize &&
		   board[tempRow][tempCol] == 0)
		{
			// Allocate new knightMove position
			knightMoves.push_back(position(0, 0, 0));

			knightMoves[knightMoveCount].row = tempRow;
			knightMoves[knightMoveCount].col = tempCol;
			// Checks onward positions for possible 8 moves
			for(int j = 0; j < maxKnightMoves; j++)
			{
				// Same temp row/col strategy as before
				int tempRow2 = tempRow + rowMoveOrder[j];
				int tempCol2 = tempCol + colMoveOrder[j];

				// Checks if onward move is possible, if so onward moves increments
				if(tempRow2 >= 0 && tempCol2 >= 0 &&
				   tempRow2 < rowColSize && tempCol2 < rowColSize
				   && board[tempRow2][tempCol2] == 0)
				{
					knightMoves[knightMoveCount].onwardMoves++;
				}

			}
			// Index in knightMoves++
			knightMoveCount++;
		}
	}
	// Return the knightMoves vector for recursive functions
	return knightMoves;

}
// Wrapper function to initiate recursive call
bool knightType::knightTour(int r, int c)
{
	functionsCalled++;
	return knightTour(r, c, 1);
}
/* The recursive function
 * Takes in the current row and column, and the present tour index
 * Only returns true if base case is satisfied
 */
bool knightType::knightTour(int r, int c, int tourIndex)
{
	// Sets our current, valid position to current index of tour
	board[r][c] = tourIndex;

	// Base case, in case the board is completely full
	if(fullBoard())
		return true;

	// Get the knightMoves vector to check for where to jump next
	std::vector<position> knightMoves = getAvailableMoves(r, c);

	// Index of the jump with least amount of onward jumps
	int leastMoves = 0;

	// Loops through knightMoves to find index with least amount of onward jumps
	for(unsigned long int i = 0; i < knightMoves.size(); i++)
	{
		// Only reassign in this case
		if(knightMoves[i].onwardMoves <= knightMoves[leastMoves].onwardMoves)
		{
			leastMoves = i;
		}

	}

	// Our new row and column (the position of knight)
	r = knightMoves[leastMoves].row;
	c = knightMoves[leastMoves].col;

	// Keep count of total functions called
	functionsCalled++;

	// Call the function again since base case is not satisfied
	knightTour(r, c, ++tourIndex);
	// Only will return true if we return true in base case
	return true;
}
/* Algorithm to output our board (with proper tourIndex at each spot)
 * No arguments, no return
 */
void knightType::outputTour() const
{
	// Alphabetical label for row/col
	char rowChar = 'A';
	char columnChar = 'A';

	// Column alphabet label
	std::cout << std::setw(4);
	for(unsigned long int k = 0; k < board[0].size(); k++)
	{
		std::cout << columnChar++ << std::setw(3);
	}
		std::cout << std::endl;

	// Output loop
	for(unsigned long int i = 0; i < board.size(); i++)
	{
		// Row alphabet label
		std::cout << std::setw(0) << rowChar++ << std::setw(2) << " ";
		// Loop for each element in subsequent column
		for(unsigned long int j = 0; j < board[i].size(); j++)
		{
			// This length will be used to determine how much we should setw
			int length = std::to_string(board[i][j]).length();
			// Setw based on number's total digits
			std::cout << board[i][j] << std::setw(3 - length)<< " ";
		}
		std::cout << std::endl;
	}
	// Total functions called
	std::cout << "\nFunctions called: " << functionsCalled << std::endl;
}
