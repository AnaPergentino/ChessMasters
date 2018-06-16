/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef BOARD
#define BOARD

using namespace std;

const int WHITE = 1;
const int BLACK = -1;
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
const int UP = NUM_ROWS;
const int DOWN = -NUM_ROWS;
const int LEFT = -1;
const int RIGHT = 1;
const int UP_LEFT = UP + LEFT;
const int UP_RIGHT = UP + RIGHT;
const int DOWN_LEFT = DOWN + LEFT;
const int DOWN_RIGHT = DOWN + RIGHT;

class Board
{
private:
	int boardArray[NUM_ROWS][NUM_COLS]; // Array 2d com as peças do tabuleiro
	int player; // Inteiro que indica qual player tem a vez

public:
	/**
	 * Função
	 *      Construtora da classe Board
	 * Interface implícita
	 *      boardArray
	 *		player
	 */
	Board();

	/**
	 * Função
	 *      retornar valor da posição no tabuleiro
	 * Assertivas de entrada
	 *      0 <= row < NUM_ROWS
	 *		0 <= col < NUM_COLS
	 * Assertiva de saída
	 *		-KING <= Piece <= KING
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
	 *      retornar player ativo
	 * Assertiva de saída
	 *		player é WHITE ou BLACK
	 * Interface implícita
	 *		player
	 * Valor de Retorno
	 *		valor do player ativo
	 */
	int getPlayer();

	/**
	 * Função
	 *      setar player ativo
	 * Assertiva de entrada
	 *		newPlayer é WHITE ou BLACK
	 * Interface implícita
	 *		player
	 * Valor de Retorno
	 *		0 se sucesso, ERROR se erro
	 */
	int setPlayer(int newPlayer);

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
	* Assertiva de saída
	*	Retorna 0 ou ERROR
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

	/**
	* Função
	*	remove peça da posição dada por row, col
	* Assertivas de entrada
	*	0 <= row < NUM_ROwS
	*	0 <= col < NUM_COLS
	*	boardArray[row][col] != 0
	* Assertiva de saída
	*	REtorna ERROR ou valor entre -KING e KING
	* Interface implícita
	*	boardArray
	* Interface explícita
	*	row
	*	col
	* Valor de retorno
	*	valor da peça removida caso sucesso, ERROR caso haja erro
	*/
	int removePiece(int row, int col);


	/**
	* Função
	*	checa se o board é válido
	* Interface implícita
	*	boardArray
	*	player
	* Valor de retorno
	*	true se válido, false se inválido
	*/
	bool isValid();
};

#endif