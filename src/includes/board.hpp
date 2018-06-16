/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef BOARD
#define BOARD

const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const int pawn = 0;
const int rook = 1;
const int knight = 2;
const int bishop = 3;
const int queen = 4;
const int king = 5;
const int startArray[8][8] = {rook, knight, bishop, queen, king, bishop, knight, rook, pawn,
						  pawn,pawn,pawn,pawn,pawn,pawn, pawn, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -rook, -knight,
						  -bishop, -queen, -king, -bishop, -knight, -rook};

class Board
{
private:
	int boardArray[NUM_ROWS][NUM_COLS];
public:
	/**
	 * Função
	 *      Construtora da classe Board
	 * Interface implícita
	 *      boardArray
	 */
	Board();

	/**
	 * Função
	 *      retornar valor da posição no tabuleiro
	 * Valor retornado
	 *      valor da posição no tabuleiro
	 * Assertivas de entrada
	 *      row < NUM_ROWS
	 *		col < NUM_COLS
	 * Interfarce explícita
	 *      row
	 *      col
	 * Interface implícita
	 *      boardArray
	 */
	int getSquareValue(int row, int col);

	/**
	 * Função
	 *      popular com as peças e posições iniciais
	 * Interface implícita
	 *      boardArray
	 */
	void populate();
};

#endif