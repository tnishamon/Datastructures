//============================================================================
// Name        : knightType.h (Assignment02)
// Author      : Matthew Noojin
// Date		   : 01/30/22
// Class	   : CS302
// Section	   : 1001
// Professor   : Andro Vasko
// Description : Create a recursive algorithm to have a knight jump across a
//				 board and then output the indexes of where it jumped
//			     and total recursive calls
//============================================================================
#ifndef KNIGHTTYPE_H_
#define KNIGHTTYPE_H_

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>

class knightType
{
public:
	struct position
	{
		position(int r = 0, int c = 0, int o = 0)
		{
			row = r;
			col = c;
			onwardMoves = o;
		}

		int row;
		int col;
		int onwardMoves;
	};
	knightType(int = 8);
	bool knightTour(int , int);
	void outputTour () const;

private:
	bool knightTour(int , int , int);
	std::vector<position> getAvailableMoves(int , int);
	bool fullBoard ();
	std::vector<std::vector<int>> board;
	int functionsCalled;
	// Added this private constant since a knight can only move to a max of 8 spaces
	const int maxKnightMoves = 8;
};

#endif /* KNIGHTTYPE_H_ */
