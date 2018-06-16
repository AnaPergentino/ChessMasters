#include "includes/board.hpp"
#include <cassert>

// Board createBoard(void)
// {
// 	int **newBoard = new int*[NUM_ROWS];

// 	for(int row = 0; row < NUM_ROWS; row++)
// 	{
// 		newBoard[row] = new int[NUM_COLS];
// 	}

// 	return newBoard;
// }

Board::Board()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			boardArray[row][col] = 0;
		}
	}
}

int Board::getSquareValue(int row, int col)
{
	assert(row < NUM_ROWS);
	assert(col < NUM_COLS);
	return boardArray[row][col];
}

void Board::populate()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			boardArray[row][col] = startArray[row][col];
		}
	}
}