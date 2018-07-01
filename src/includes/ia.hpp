/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef IA
#define IA

#include "board.hpp"
#include<chrono>
#include<limits>

using namespace std;

const double MOBILITY_WEIGHT = 1.0;
const double KING_WEIGHT = 20000;
const double QUEEN_WEIGHT = 900;
const double ROOK_WEIGHT = 500;
const double KNIGHT_WEIGHT = 320;
const double BISHOP_WEIGHT = 330;
const double PAWN_WEIGHT = 100;
const int N_BEST_MOVES= 5;
const double MAX_MILLISECONDS = 10000;
const double PAWN_SCORE_ARRAY[8][8] = {0,  0,  0,  0,  0,  0,  0,  0,
								50, 50, 50, 50, 50, 50, 50, 50,
								10, 10, 20, 30, 30, 20, 10, 10,
								 5,  5, 10, 25, 25, 10,  5,  5,
								 0,  0,  0, 20, 20,  0,  0,  0,
								 5, -5,-10,  0,  0,-10, -5,  5,
								 5, 10, 10,-20,-20, 10, 10,  5,
								 0,  0,  0,  0,  0,  0,  0,  0};
const double KNIGHT_SCORE_ARRAY[8][8] = {-50,-40,-30,-30,-30,-30,-40,-50,
									-40,-20,  0,  0,  0,  0,-20,-40,
									-30,  0, 10, 15, 15, 10,  0,-30,
									-30,  5, 15, 20, 20, 15,  5,-30,
									-30,  0, 15, 20, 20, 15,  0,-30,
									-30,  5, 10, 15, 15, 10,  5,-30,
									-40,-20,  0,  5,  5,  0,-20,-40,
									-50,-40,-30,-30,-30,-30,-40,-50,};
const double BISHOP_SCORE_ARRAY[8][8] = {-20,-10,-10,-10,-10,-10,-10,-20,
									-10,  0,  0,  0,  0,  0,  0,-10,
									-10,  0,  5, 10, 10,  5,  0,-10,
									-10,  5,  5, 10, 10,  5,  5,-10,
									-10,  0, 10, 10, 10, 10,  0,-10,
									-10, 10, 10, 10, 10, 10, 10,-10,
									-10,  5,  0,  0,  0,  0,  5,-10,
									-20,-10,-10,-10,-10,-10,-10,-20,};
const double ROOK_SCORE_ARRAY[8][8] = {0,  0,  0,  0,  0,  0,  0,  0,
									  5, 10, 10, 10, 10, 10, 10,  5,
									 -5,  0,  0,  0,  0,  0,  0, -5,
									 -5,  0,  0,  0,  0,  0,  0, -5,
									 -5,  0,  0,  0,  0,  0,  0, -5,
									 -5,  0,  0,  0,  0,  0,  0, -5,
									 -5,  0,  0,  0,  0,  0,  0, -5,
									  0,  0,  0,  5,  5,  0,  0,  0};
const double QUEEN_SCORE_ARRAY[8][8] = {-20,-10,-10, -5, -5,-10,-10,-20,
									-10,  0,  0,  0,  0,  0,  0,-10,
									-10,  0,  5,  5,  5,  5,  0,-10,
									 -5,  0,  5,  5,  5,  5,  0, -5,
									  0,  0,  5,  5,  5,  5,  0, -5,
									-10,  5,  5,  5,  5,  5,  0,-10,
									-10,  0,  5,  0,  0,  0,  0,-10,
									-20,-10,-10, -5, -5,-10,-10,-20};
const double KING_SCORE_ARRAY_MID[8][8] = {-30,-40,-40,-50,-50,-40,-40,-30,
											-30,-40,-40,-50,-50,-40,-40,-30,
											-30,-40,-40,-50,-50,-40,-40,-30,
											-30,-40,-40,-50,-50,-40,-40,-30,
											-20,-30,-30,-40,-40,-30,-30,-20,
											-10,-20,-20,-20,-20,-20,-20,-10,
											 20, 20,  0,  0,  0,  0, 20, 20,
											 20, 30, 10,  0,  0, 10, 30, 20};
const double KING_SCORE_ARRAY_END[8][8] = {-50,-40,-30,-20,-20,-30,-40,-50,
											-30,-20,-10,  0,  0,-10,-20,-30,
											-30,-10, 20, 30, 30, 20,-10,-30,
											-30,-10, 30, 40, 40, 30,-10,-30,
											-30,-10, 30, 40, 40, 30,-10,-30,
											-30,-10, 20, 30, 30, 20,-10,-30,
											-30,-30,  0,  0,  0,  0,-30,-30,
											-50,-30,-30,-30,-30,-30,-30,-50};

class Ia
{
private:
	chrono::steady_clock::time_point start; // Estrutura de dado para guardar o inicio temporal de um minimax
	int depth; // Profundidade da árvore de decisão
	int depthLimit; // Proundidade máxima da iteração
public:
	/**
	 * Função
	 * 	Construtora da classe MiniMax
	 */
	Ia();


	/**
	* Função
	* 	Retorna pontuação por peças presentes no tabuleiro
	* Interface Explícita
	*	board
	* Valor retornado
	*   double correspondente a uma soma pondera das peças presentes no tabuleiro
	*/
	double getMaterialScore(Board board);


	/**
	* Função
	* 	Retorna pontuação por mobilidade no tabuleiro
	* Interface Explícita
	*	board
	* Valor retornado
	*   double correspondente ao numero de moves possíveis para branco menos número de moves possíveis para preta
	*/
	double getMobilityScore(Board board);

	/**
	* Função
	* 	Retorna pontuação por localização das peças no tabuleiro
	* Interface Explícita
	*	board
	* Valor retornado
	*   double correspondente à pontuação em questão
	*/
	double getPositionScore(Board board);

	/**
	* Função
	* 	Retorna utilidade do tabuleiro
	* Assertiva de entrada
	*	color == white or color == black
	* Interface Explícita
	*   color
	*	board
	* Valor retornado
	*   double correspondente à pontuação (utilidade) do estado do tabuleiro
	*/
	double utility(Board board, int color);

	/**
	* Função
	* 	Retorna outilidade de um tabuleiro retornado por alfabet
	* Interface Explícita
	*	board
	*	color
	* Assertiva de entrada
	*	color é white ou black
	* Valor retornado
	*   utilidade
	*/
	double alphaBetaSearch(Board board, int color, bool startClock);

	/**
	* Função
	* 	Função recursiva que retorna o maxValue de uma "folha"
	* Interface Explícita
	*	board
	*	alpha
	*	beta
	*	color
	* Assertiva de entrada
	*	color é white or black
	* Valor retornado
	*   utilidade max da folha
	*/
	double maxValue(Board board, double alpha, double beta, int color);

	/**
	* Função
	* 	Função recursiva que retorna o minValue de uma "folha"
	* Interface Explícita
	*	board
	*	alpha
	*	beta
	*	color
	* Assertiva de entrada
	*	color é white or black
	* Valor retornado
	*   utilidade min da folha
	*/
	double minValue(Board board, double alpha, double beta, int color);

	/**
	* Função
	* 	Função que retorna true se dado estado do tabuleiro é terminal ou
	*   se passou o tempo MAX_TIME
	* Interface Explícita
	*	board
	* Valor retornado
	*   true ou false
	*/
	bool terminalState(Board board);

	/**
	* Função
	* 	Retorna os n best moves obtidos por minmax
	* Interface Explícita
	*	board
	* Valor retornado
	*   vetore com coordenadas de movimentação ordenadas da melhor pra pior
	*/
	vector<pair<int, int>> bestMoves(Board board);
};

#endif