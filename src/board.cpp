#include "includes/board.hpp"
#include <iostream>
#include <cassert>

using namespace std;

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
	if ((row >= NUM_ROWS && row < 0) || (col >= NUM_COLS && col < 0))
	{
		cout << "Coordenadas inválidas\n";
		return ERROR;
	}

	assert(boardArray[row][col] >= -KING && boardArray[row][col] <= KING);

	return boardArray[row][col];
}

void Board::populate()
{
	for(int row = 0; row < NUM_ROWS; row++)
	{
		for(int col = 0; col < NUM_COLS; col++)
		{
			boardArray[row][col] = START_ARRAY[row][col];
		}
	}
}

int Board::putPiece(int piece, int row, int col)
{
	if ((row >= NUM_ROWS || row < 0) || (col >= NUM_COLS || col < 0))
	{
		cout << "Coordenadas("<< row << ", " << col <<  ") inválidas\n";
		return ERROR;
	}

	if (boardArray[row][col] != 0)
	{
		cout << "Posição ("<< row << ", " << col <<  ") ocupada\n";
		return ERROR;
	}

	if (piece < -KING || piece > KING)
	{
		cout << "Peça " << piece << " inválida\n";
		return ERROR;
	}

	boardArray[row][col] = piece;
	return 0;
}

int Board::removePiece(int row, int col)
{
	int piece;

	if ((row >= NUM_ROWS || row < 0) || (col >= NUM_COLS || col < 0))
	{
		cout << "Coordenadas("<< row << ", " << col <<  ") inválidas\n";
		return ERROR;
	}

	if (boardArray[row][col] == 0)
	{
		cout << "Posição ("<< row << ", " << col <<  ") deocupada\n";
		return ERROR;
	}

	piece = boardArray[row][col];

	assert(piece >= -KING && piece <= KING);

	return piece;
}