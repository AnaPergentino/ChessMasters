/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef BOARD
#define BOARD

#include <array>
#include <vector>

using namespace std;

const int DRAW = 100;
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
	array<vector<int>, 6> whitePiecesPos; // Array de vetores com posições das peças. Por exemplo, whitePiecesPos[0] retorna um vetor com posição de peões
	array<vector<int>, 6> blackPiecesPos; // Semelhante a whitePiecePos, mas com as peças pretas
	int drawCounter; // contador de jogadas sem caputar ou movimentação de peão, empata quando chega a 100 (50 jogadas de cada jogador)
	bool whiteQueenCastle, whiteKingCastle, blackKingCastle, blackQueenCastle; // Booleano que indica se há privilegio de roque relevane
	/**
	* Função
	*	retornam lista de moves das respectivas peças
	* Interface implícita
	*	boardArray
	* Interface explícita
	*	row
	*	col
	* Valor de retorno
	*	lista de moves da peça
	*/
	vector<int> getPawnMoves(int color, int row, int col);
	vector<int> getRookMoves(int color, int row, int col);
	vector<int> getKnightMoves(int color, int row, int col);
	vector<int> getBishopMoves(int color, int row, int col);
	vector<int> getQueenMoves(int color, int row, int col);
	vector<int> getKingMoves(int color, int row, int col);

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
	 *      limpa as peças do tabuleiro
	 * Interface implícita
	 *		boardArray
	 */
	void clear();

	/**
	 * Função
	 *      retornar vetor de peça PEÇA de color BLACK ou WHITE
	 * Assertivas de entrada
	 *		-KING <= piece <= King
	 *		color == WHITE ou color == black
	 * Interface implícita
	 *		whitePiecesPos
	 *		blackPiecespos
	 * Valor de Retorno
	 *		vetor
	 */
	vector<int> getPieceVector(int piece, int color);


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

	/**
	* Função
	*	Retorna lista de possíveis movimentos da peça nas coordenadas dadas
	* Assertivas de entrada
	*	0 <= row < NUM_ROwS
	*	0 <= col < NUM_COLS
	* Interface implícita
	*	funções de conseguir moves para cada peça
	* Interface explícita
	*	row
	*	col
	* Valor de retorno
	*	lista de inteiros
	*/
	vector<int> getMovesVector(int row, int col);

	/**
	* Função
	*	Checa se dada movimentação é legal
	* Assertivas de entrada
	*	0 <= fromRow < NUM_ROwS
	*	0 <= fromCol < NUM_COLS
	*	0 <= toRow < NUM_ROwS
	*	0 <= toCol < NUM_COLS
	*	peça nas coordenadas from diferente de 0 e entre -KING e KING
	* Interface implícita
	*	funções de conseguir moves da peça
	*	boardArray
	* Interface explícita
	*	fromRrow
	*	fromCol
	* Valor de retorno
	*	true ou false
	*/
	bool isMoveLegal(int fromRow, int fromCol, int toRow, int toCol);


	/**
	* Função
	*	Retorna se um rei na posição dada por row e col estaria em cheque
	* Assertivas de entrada
	*	0 <= row < NUM_ROwS
	*	0 <= col < NUM_COLS
	*   color == WHITE or BLACK
	* Interface implícita
	*	boardArray
	* Interface explícita
	* 	color
	*	row
	*	col
	* Valor de retorno
	*	true ou false
	*/
	bool isCheck(int row, int col, int color);

	/**
	* Função
	*	Retorna true se o jogador de cor color sofreu um cheque-mate
	* Assertiva de entrada
	*	color == WHITE ou color == BLACK
	* Interface implícita
	*	boardArray
	*	Funções de movimentação de peça
	* Interface explícita
	*	color
	* Valor de retorno
	*	True ou false
	*/
	bool isCheckMate(int color);


	/**
	* Função
	*	Move peça no tabuleiro
	* Assertivas de entrada
	*	0 <= fromRow < NUM_ROwS
	*	0 <= fromCol < NUM_COLS
	*	0 <= toRow < NUM_ROwS
	*	0 <= toCol < NUM_COLS
	*	peça movida do jogador atual
	*	peça nas coordenadas from diferente de 0 e entre -KING e KING
	* Interface implícita
	*	funções de moves legais
	*	função de checagem de cheque
	*	fuñções de remoção e inserção
	*	boardArray
	* Interface explícita
	*	fromRow
	*	fromCol
	*	toRow
	*	toCol
	* Valor de retorno
	*	0 se sucesso ERROR se erro
	*/
	int movePiece(int fromRow, int fromCol, int toRow, int toCol);

	/**
	* Função
	*	Checa se peça pode ser movida considerando cheques e outras coisas
	* Assertivas de entrada
	*	0 <= fromRow < NUM_ROwS
	*	0 <= fromCol < NUM_COLS
	*	0 <= toRow < NUM_ROwS
	*	0 <= toCol < NUM_COLS
	*	peça movida do jogador atual
	*	peça nas coordenadas from diferente de 0 e entre -KING e KING
	* Interface implícita
	*	função movePiece
	*	board
	* Interface explícita
	*	fromRow
	*	fromCol
	*	toRow
	*	toCol
	* Valor de retorno
	*	true se pode false se não pode
	*/
	bool canMovePiece(int fromRow, int fromCol, int toRow, int toCol);

	
	/**
	* Função
	*	Checa se jogo terminou
	* Interface implícita
	*	funções de checagem de chequemate
	*   drawCounter
	* Valor de retorno
	*	BLACK se preto ganhou, WHITE se branco ganhou, 0 se empate, ERROR se não acabou
	*/
	int isGameEnd();

	/**
	* Função
	*	Retorna lista de possíveis movimentos dado o estado atual do tabuleiro
	* Interface explícita
	*	color
	* Assertiva de entrada
	*	color é WHITE ou BLACK
	* Interface implícita
	*	funções de movimentaão de peça
	*	boardArray
	*	pieceLists
	* Valor de retorno
	*	lista de pares de inteiro
	*/
	vector<pair<int, int>> moveList(int color);
};

#endif