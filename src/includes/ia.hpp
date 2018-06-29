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
	* Interface Explícita
	*	board
	* Valor retornado
	*   double correspondente à pontuação (utilidade) do estado do tabuleiro
	*/
	double utility(Board board);
};

#endif