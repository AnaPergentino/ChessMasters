/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef BOARD
#define BOARD

const int ERROR = 10;
const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const int PAWN = 1;
const int ROOK = 2;
const int KNIGHT = 3;
const int BISHOP = 4;
const int QUEEN = 5;
const int KING = 6;
const int START_ARRAY[8][8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK, PAWN,
						  PAWN,PAWN,PAWN,PAWN,PAWN,PAWN, PAWN, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -ROOK, -KNIGHT,
						  -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK};

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
	 *      0 <= row < NUM_ROWS
	 *		0 <= col < NUM_COLS
	 * Interfarce explícita
	 *      row
	 *      col
	 * Interface implícita
	 *      boardArray
	 * Valor de Retorno
	 *		int indicador da peça caso sucesso ou 
	 *      de erro caso valor de entrada fora do intervalo
	 */
	int getSquareValue(int row, int col);

	/**
	 * Função
	 *      popular com as peças e posições iniciais
	 * Interface implícita
	 *      boardArray
	 */
	void populate();

	/**
	* Função
	*	colocar peça Piece na posição dada por row, col
	* Assertivas de entrada
	*	0 <= row < NUM_ROwS
	*	0 <= col < NUM_COLS
	*   -KING <= piece <= KING
	*	boardArray[row][col] == 0
	* Interface implícita
	*	boardArray
	* Interface explícita
	* 	piece
	*	row
	*	col
	* Valor de retorno
	*	0 caso sucesso, ERROR caso haja erro
	*/
	int putPiece(int piece, int row, int col);
};

#endif