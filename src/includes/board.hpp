/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef BOARD
#define BOARD

const int NUM_ROWS = 8;
const int NUM_COLS = 8;

class Board
{
private:
	int boardArray[NUM_ROWS][NUM_COLS];
public:
	Board();
	int getSquareValue(int row, int col);
};

#endif