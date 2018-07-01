/**
 * @file board.hpp
 * 
 * API de interface com o usuário
 */

#ifndef IO
#define IO

#include "board.hpp"

/**
 * Função
 *      printar estado do tabuleiro 
 * Assertiva de entrada:
 *		números no tabuleiro tem valor de peça
 * Interfarce explícita
 *      board
 * Valor de Retorno
 *		0 caso sucesso ou 
 *      de erro caso algo dê errado
 */
int printBoard(Board board);


/**
 * Função
 *      pegar input do usuário até que ele seja correto e mover peça do tabuleiro
 * Assertiva de entrada:
 *		input do usuário na forma f0-d0 onde f0 é a coluna e linha de origem e d0 a coluna e linha de destino
 * Interfarce explícita
 *      board
 * Valor de Retorno
 *		board após fazer o move
 */
Board makeMove(Board board);

/**
 * Função
 *      pegar input do usuário para saber se computador vai jogar
 * Assertiva de entrada:
 *		input do usuário eh s/n para sim ou não
 * Valor de Retorno
 *		true ou false para computador jogar
 */
bool computerPlays();

/**
 * Função
 *      pegar input do usuário para saber qual cor ele vai usar
 * Assertiva de entrada:
 *		input do usuário eh p/b para preto ou branco
 * Valor de Retorno
 *		WHITE ou BLACK
 */
int getPlayerColor();

/**
 * Função
 *      fazer move do pc e printar ele para o usuário
 * Interfarce explícita
 *      board
 *		move
 * Valor de Retorno
 *		board após fazer o move
 */
Board makeComputerMove(Board board, pair<int, int> move);


/**
 * Função
 *      printar os melhores moves para o usuário
 * Interfarce explícita
 *		moves
 * Assertiva de entrada
 *		moves não vazio
 */
void showBestMoves(vector<pair<int, int>> moves);

#endif