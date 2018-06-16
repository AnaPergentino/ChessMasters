#include "includes/board.hpp"

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
	return boardArray[row][col];
}