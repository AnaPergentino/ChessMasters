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

const double MOBILITY_WEIGHT = 0.1;
const double KING_WEIGHT = 200;
const double QUEEN_WEIGHT = 9;
const double ROOK_WEIGHT = 5;
const double KNIGHT_WEIGHT = 3;
const double BISHOP_WEIGHT = 3;
const double PAWN_WEIGHT = 1;
const int N_BEST_MOVES = 5;
const int MAX_SECONDS = 2;

class Ia
{
private:
	chrono::steady_clock::time_point start; // Estrutura de dado para guardar o inicio temporal de um minimax
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