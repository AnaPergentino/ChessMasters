/**
 * @file board.hpp
 * 
 * API de operações sobre representação do tabuleiro
 */

#ifndef IA
#define IA

#include "board.hpp"

using namespace std;

const double MOBILITY_WEIGHT = 0.1;
const double KING_WEIGHT = 200;
const double QUEEN_WEIGHT = 9;
const double ROOK_WEIGHT = 5;
const double KNIGHT_WEIGHT = 3;
const double BISHOP_WEIGHT = 3;
const double PAWN_WEIGHT = 1;
const int N_BEST_MOVES = 5;

class Ia
{
private:

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
	* 	Retorna os N_BEST_MOVES por meio de minimax com alphaBetaPruning do jogador color
	* Interface Explícita
	*	board
	*	color
	* Assertiva de entrada
	*	color é white ou black
	* Valor retornado
	*   vetor de pares ordenados cujo primeiro membro é a origem e o segundo membro o destino
	*/
	vector<pair<int, int>> alphaBetaSearch(Board board, int color);

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
};

#endif